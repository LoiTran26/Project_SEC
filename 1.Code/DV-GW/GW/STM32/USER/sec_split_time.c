#include "sec_split_time.h"


sec_FrameMsg_t frame_detect;
sec_status_time_e status_time = START;

Array_port_t arr_port[] =
{
  {GPIOB, GET_GPIO_PORTB_1},
  {GPIOB, GET_GPIO_PORTB_2},
  {GPIOB, GET_GPIO_PORTB_3},
  {GPIOB, GET_GPIO_PORTB_4},
  {GPIOB, GET_GPIO_PORTB_5},
  {GPIOB, GET_GPIO_PORTB_6}
};

static uint8_t count_port = 1;
static uint8_t count_timeout = 0;

static uint8_t arr_status_new[10]      = {0};
static uint8_t arr_status_old[10]      = {0};
static uint8_t arr_status_standard[10] = {0};
static uint8_t flag_change_status[10]  = {0};


void SEC_Split_frame_time(void)
{
  switch (status_time)
  {
    case START:
      SEC_Read_status_port(count_port);
      status_time = JOIN;
	break;

    case JOIN:
      if(flag_change_status[count_port] == 1)
      {
        printf("count: %d, new: %d, old: %d, sta: %d\n", count_port, arr_status_new[count_port], arr_status_old[count_port], arr_status_standard[count_port]);
        if (arr_status_standard[count_port] == SENSOR_JOIN)
        {
          if (SEC_Join_Port(count_port) == 1)
          {
            arr_status_standard[count_port] = SENSOR_CONNECT;
            flag_change_status[count_port] = 0;
            status_time = DISCONNECT;
          }
          else
          {
            count_timeout++;
            if (count_timeout >= 5)
            {
              count_timeout = 0;
              status_time = DISCONNECT;
            }
          }
        }
        else if (arr_status_standard[count_port] == SENSOR_DISCONNECT)
        {
		  SEC_GPIO_Set_OFF(count_port);
          flag_change_status[count_port] = 0;
          status_time = DISCONNECT;
        }
      }
      else
      {
        status_time = DISCONNECT;
      }
	break;

    case DISCONNECT:
      status_time = DATA;
	break;

    case DATA:
      if (arr_status_standard[count_port] == SENSOR_CONNECT)
      {
        if (SEC_Data_Port(count_port) == 1)
        {
          status_time = BACK;
        }
        else
        {
          count_timeout++;
          if (count_timeout >= 5)
          {
            count_timeout = 0;
            status_time = BACK;
          }
        }
      }
      else
      {
        status_time = BACK;
      }
	break;

    case BACK:
      count_port++;
      if (count_port >= 7)
      {
        count_port = 1;
      }

      status_time = START;
	break;
  }
}

uint8_t SEC_Join_Port(uint8_t port_number)
{
  // Bat nguon port
  SEC_GPIO_Set_ON(port_number);
  // Gui ban tin hoi type sensor
  SEC_create_frame_asksensor(port_number);
  // Cho 3ms doi phan hoi ve
  SEC_DELAY_ms(3);
	
  #if FRAME_SEND
  printf("Send type_%d\n", port_number);
  #endif
	
  if (sec_vrAll_fsm_t.Flag_fsm_True == 1)
  {
	#if FRAME_RECEIVE
    printf("Ask_%d\n", port_number);
	#endif
    // Giai ma ban tin nhan duoc
    SEC_Message_Detect_Frame(sec_vrAll_fsm_t.array_out, &frame_detect);
    // Hien thi ban tin nhan duoc
    Print_Data_Detect(frame_detect);
    // Reset cac gia tri trong Struct
    Sec_Clear_Frame_Message(&frame_detect);
    sec_vrAll_fsm_t.Flag_fsm_True = 0;
    return 1;
  }
  return 0;
}

uint8_t SEC_Data_Port(uint8_t port_number)
{
  // Gui ban tin hoi data sensor
  SEC_create_frame_askdata(port_number);
  // Cho 3ms doi phan hoi ve
  SEC_DELAY_ms(3);
	
  #if FRAME_SEND
  printf("Send data_%d\n", port_number);
  #endif
	
  if (sec_vrAll_fsm_t.Flag_fsm_True == 1)
  {
	#if FRAME_RECEIVE
    printf("Data_%d\n", port_number);
	#endif
    // Giai ma ban tin nhan duoc
    SEC_Message_Detect_Frame(sec_vrAll_fsm_t.array_out, &frame_detect);
    // Hien thi ban tin nhan duoc
    Print_Data_Detect(frame_detect);
    // Reset cac gia tri trong Struct
    Sec_Clear_Frame_Message(&frame_detect);
    sec_vrAll_fsm_t.Flag_fsm_True = 0;
    return 1;
  }
  return 0;
}

void SEC_Read_status_port(uint8_t port_number)
{
  if (GPIO_ReadInputDataBit(arr_port[port_number - 1].GPIOx, arr_port[port_number - 1].Port_number) == 0)
  {
    arr_status_new[port_number] = 1;
  }
  else
  {
    arr_status_new[port_number] = 0;
  }

  if (arr_status_new[port_number] != arr_status_old[port_number])
  {
    // Bat co thay doi trang thai
    flag_change_status[port_number] = 1;

    if ((arr_status_old[port_number] == 0) && (arr_status_new[port_number] == 1))
    {
      arr_status_standard[port_number] = SENSOR_JOIN;
    }
    else if ((arr_status_old[port_number] == 1) && (arr_status_new[port_number] == 0))
    {
      arr_status_standard[port_number] = SENSOR_DISCONNECT;
    }
    // Cap nhat lai trang thai
    arr_status_old[port_number] = arr_status_new[port_number];
  }
}

