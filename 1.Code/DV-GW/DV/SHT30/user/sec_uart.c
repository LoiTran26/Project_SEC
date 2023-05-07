#include "sec_uart.h"


sec_FrameMsg_t data_in;
Sec_ValueAll_t sec_vrAll_uart_t;
fsm_state_e fsm_state = FSM_STATE_START_FRAME;

static uint16_t TimeOut_Fsm = 0;
static uint8_t Flag_TimeOut_Fsm = 0;
static uint16_t CheckFrame_Receive;

#if (ENB_DEBUG_IRQ == 2)
    #define string_size 40
    char RX_FLAG_END_LINE = 0;
    uint8_t RXI = 0;
    char RRX[string_size];
    char temp_char;
    char Number[10];
#endif


void UART_Init(unsigned int select)
{
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  GPIOD->DDR |=  (1 << 5);
  GPIOD->DDR &= ~(1 << 6);
  // baudrate 16MHZ / 57600 = 277 = 0x115
  // baudrate 16MHZ / 9600 = 1666 = 0x682
  switch (select)
  {
    case 9600:
      UART1->BRR1 = 0x68;
      UART1->BRR2 = 0x02;
      break;
    case 57600:
      UART1->BRR1 = 0x11;
      UART1->BRR2 = 0x05;
      break;
      break;
  }
  UART1->CR1  = (0 << 5);
  UART1->CR2  = (1 << 2) | (1 << 3) | (1 << 5);
  enableInterrupts();
}
/*----------------------------------------------------------------------------*/
void UART_Send_Char(char _varChar)
{
  UART1->DR = _varChar;
  while (!(UART1->SR & (1 << 7)));
}
/*----------------------------------------------------------------------------*/
void UART_Send_String(char *_varString)
{
  GPIO_WriteHigh(GPIOD, GPIO_PIN_4);
  while (*_varString)
  {
    UART_Send_Char(*_varString);
    _varString++;
  }
  GPIO_WriteLow(GPIOD, GPIO_PIN_4);
}
/*----------------------------------------------------------------------------*/
void UART_Send_Number(int _varNumber)
{
  UART_Send_String(SEC_Conver_IntToStr(_varNumber, 1));
}

/*----------------------------------------------------------------------------*/
void UART_Send_Number_Hex(long long _varNumber)
{
  UART_Send_String(SEC_Conver_IntToHex(_varNumber));
}

void UART_Send_Number_Float(float _varNumber)
{
  UART_Send_String(SEC_Conver_FloatToStr(_varNumber, 1));
}

/*----------------------------------------------------------------------------*/
void UART_Send_Byte(uint8_t *data, uint8_t sizes)
{
  uint8_t i;
  
  GPIO_WriteHigh(GPIOD, GPIO_PIN_4);
  for (i = 0; i < sizes; i++)
  {
    UART1->DR = (data[i] & 0x00FF);
    while ((UART1->SR & 0x0080) == RESET);
  }
  SEC_Delay_Ms(1);
  GPIO_WriteLow(GPIOD, GPIO_PIN_4);
}

/*----------------------------------------------------------------------------*/
void UART_Rs485_Init(void)
{
  GPIO_DeInit(GPIOD);
  GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_WriteLow(GPIOD, GPIO_PIN_4);
}

/*----------------------------------------------------------------------------*/
void SEC_TimeOut_Fsm(void)
{
    if(Flag_TimeOut_Fsm == 1)
    {
        if(TimeOut_Fsm == 500)
        {
            //UART_Send_Number(404);
            SEC_Clear_TimeOut_Fsm();
        }
        TimeOut_Fsm++;
    }
}

void SEC_Clear_TimeOut_Fsm(void)
{
    Flag_TimeOut_Fsm = 0;
    sec_vrAll_uart_t.fsm_count_array = 0;
    fsm_state = FSM_STATE_START_FRAME;
}


INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
#if(ENB_DEBUG_IRQ == 1)

    sec_vrAll_uart_t.temp_data = UART1->DR;
    Flag_TimeOut_Fsm  = 1;
    TimeOut_Fsm = 0;
    
    switch (fsm_state)
    {
        case FSM_STATE_START_FRAME:
            sec_vrAll_uart_t.array_out[sec_vrAll_uart_t.fsm_count_array] = sec_vrAll_uart_t.temp_data;
            sec_vrAll_uart_t.fsm_count_array++;

            if (sec_vrAll_uart_t.fsm_count_array == FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE)
            {
                data_in.StartFrame = Sec_Convert_From_Bytes_To_Uint16(sec_vrAll_uart_t.array_out[0], sec_vrAll_uart_t.array_out[1]);
                if(data_in.StartFrame == START_BYTE)
                {
                    fsm_state = FSM_STATE_TYPE_MESSAGE;
                }
                else
                {
                    sec_vrAll_uart_t.fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_TYPE_MESSAGE:
            sec_vrAll_uart_t.array_out[sec_vrAll_uart_t.fsm_count_array] = sec_vrAll_uart_t.temp_data;
            sec_vrAll_uart_t.fsm_count_array++;

            if (sec_vrAll_uart_t.fsm_count_array == FSM_STATE_CHANGE_VALUE_PORT_NUMBER)
            {
                if(sec_vrAll_uart_t.array_out[2] <= 4)
                {
                    fsm_state = FSM_STATE_PORT_NUMBER;
                }
                else
                {
                    sec_vrAll_uart_t.fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_PORT_NUMBER:
            sec_vrAll_uart_t.array_out[sec_vrAll_uart_t.fsm_count_array] = sec_vrAll_uart_t.temp_data;
            sec_vrAll_uart_t.fsm_count_array++;
            if (sec_vrAll_uart_t.fsm_count_array == FSM_STATE_CHANGE_VALUE_LENGHT_DATA)
            {
                if(sec_vrAll_uart_t.array_out[3] <= 6)
                {
                    fsm_state = FSM_STATE_LENGHT_DATA;
                }
                else
                {
                    sec_vrAll_uart_t.fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_LENGHT_DATA:
            sec_vrAll_uart_t.array_out[sec_vrAll_uart_t.fsm_count_array] = sec_vrAll_uart_t.temp_data;
            sec_vrAll_uart_t.fsm_count_array++;

            if (sec_vrAll_uart_t.fsm_count_array == FSM_STATE_CHANGE_VALUE_END)
            {
                sec_vrAll_uart_t.fsm_data_length = ((sec_vrAll_uart_t.array_out[5] << 8) | sec_vrAll_uart_t.array_out[4]) + 6;

                if (sec_vrAll_uart_t.fsm_data_length < 24)
                { 
                    fsm_state = FSM_STATE_END;
                }
                else if (sec_vrAll_uart_t.fsm_data_length > 24)
                {
                    sec_vrAll_uart_t.fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_END:
            sec_vrAll_uart_t.array_out[sec_vrAll_uart_t.fsm_count_array] = sec_vrAll_uart_t.temp_data;
            sec_vrAll_uart_t.fsm_count_array++;

            if (sec_vrAll_uart_t.fsm_count_array == sec_vrAll_uart_t.fsm_data_length)
            {
                data_in.CheckFrame = CheckSum(sec_vrAll_uart_t.array_out, sec_vrAll_uart_t.fsm_data_length - 2);
                CheckFrame_Receive = Sec_Convert_From_Bytes_To_Uint16(sec_vrAll_uart_t.array_out[sec_vrAll_uart_t.fsm_count_array-2], sec_vrAll_uart_t.array_out[sec_vrAll_uart_t.fsm_count_array-1]);
                
                if(data_in.CheckFrame == CheckFrame_Receive)
                {
                    SEC_Clear_TimeOut_Fsm();
                    sec_vrAll_uart_t.Flag_fsm_True = 1;
                }
                else
                {
                    SEC_Clear_TimeOut_Fsm();
                    sec_vrAll_uart_t.Flag_fsm_True = 0;
                }
            }
        break;
    }
    sec_vrAll_uart_t.Flag_Fsm = 1;

#elif (ENB_DEBUG_IRQ == 2)

    temp_char = UART1->DR;
    if (temp_char != '!')
    {
        RRX[RXI] = temp_char;
        RXI++;
    }
    else
    {
        RRX[RXI] = 0;
        RXI = 0;
        UART_Send_String(RRX);
        RX_FLAG_END_LINE = 1;
    }
#endif
}
