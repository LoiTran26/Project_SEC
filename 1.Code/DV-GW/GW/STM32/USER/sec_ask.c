#include "sec_ask.h"



/*---------------------------------------------- (- Type Sensor -) ----------------------------------------------*/
uint8_t SEC_create_frame_asksensor(uint8_t port_number)
{
	sec_FrameMsg_t frame_sensor_asktype;
	uint8_t arr_data_answertype[24], length_arr = 0;
	
	frame_sensor_asktype.StartFrame  = START_BYTE;
	frame_sensor_asktype.TypeMessage = TYPE_MESSAGE_ASK_TYPE;
	
	switch (port_number)
	{
		case ASK_PORT_1:
			frame_sensor_asktype.PortNumber  = PORT_NUMBER_1;
		break;
		
		case ASK_PORT_2:
			frame_sensor_asktype.PortNumber  = PORT_NUMBER_2;
		break;
		
		case ASK_PORT_3:
			frame_sensor_asktype.PortNumber  = PORT_NUMBER_3;
		break;
		
		case ASK_PORT_4:
			frame_sensor_asktype.PortNumber  = PORT_NUMBER_4;
		break;
		
		case ASK_PORT_5:
			frame_sensor_asktype.PortNumber  = PORT_NUMBER_5;
		break;
		
		case ASK_PORT_6:
			frame_sensor_asktype.PortNumber  = PORT_NUMBER_6;
		break;
	}
	// Tao ban tin
	length_arr = SEC_Message_Create_Frame(frame_sensor_asktype, arr_data_answertype);
	
	#if LOG_CREATE_FRAME
	Print_Data_Message(arr_data_answertype, length_arr);
	#endif
	if(length_arr < 0)
	{
		Sec_Log_Error("Create_Frame_AskSensor_Port_", port_number);
		return 0;
	}
	
	// Gui ban tin hoi type sensor 
	SEC_Uart2_SendByte(arr_data_answertype, length_arr);
			
	#if LOG_CREATE_FRAME
		Sec_Log_Done("Create_Frame_AskSensor_Port_", port_number);
	#endif
	
	return 1;
}

/*---------------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------- (- Data Sensor -) ----------------------------------------------*/

uint8_t SEC_create_frame_askdata(uint8_t port_number)
{
	sec_FrameMsg_t frame_sensor_askdata;
	uint8_t arr_data_answerdata[24], length_arr = 0;
	
	frame_sensor_askdata.StartFrame  = START_BYTE;
	frame_sensor_askdata.TypeMessage = TYPE_MESSAGE_ASK_DATA;
	
	switch (port_number)
	{
		case ASK_PORT_1:
			frame_sensor_askdata.PortNumber  = PORT_NUMBER_1;
		break;
		
		case ASK_PORT_2:
			frame_sensor_askdata.PortNumber  = PORT_NUMBER_2;
		break;
		
		case ASK_PORT_3:
			frame_sensor_askdata.PortNumber  = PORT_NUMBER_3;
		break;
		
		case ASK_PORT_4:
			frame_sensor_askdata.PortNumber  = PORT_NUMBER_4;
		break;
		
		case ASK_PORT_5:
			frame_sensor_askdata.PortNumber  = PORT_NUMBER_5;
		break;
		
		case ASK_PORT_6:
			frame_sensor_askdata.PortNumber  = PORT_NUMBER_6;
		break;
	}
	// Tao ban tin
	length_arr = SEC_Message_Create_Frame(frame_sensor_askdata, arr_data_answerdata);
	
	#if LOG_CREATE_FRAME
	Print_Data_Message(arr_data_answerdata, length_arr);
	#endif
	if(length_arr < 0)
	{
		Sec_Log_Error("Create_Frame_AskData_Port_", port_number);
		return 0;
	}
	
	// Gui ban tin hoi data sensor 
	SEC_Uart2_SendByte(arr_data_answerdata, length_arr);
			
	#if LOG_CREATE_FRAME
		Sec_Log_Done("Create_Frame_AskData_Port_", port_number);
	#endif
	
	return 1;
}


/*------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------*/

void Print_Data_Message(uint8_t *arr, uint8_t length)
{
    printf("- Create -\n");

    for (uint8_t i = 0; i < length; i++)
    {
        if (arr[i] <= 0x0F)
        {
            printf("0%x ", arr[i]);
        }
        else
        {
            printf("%x ", arr[i]);
        }
    }
	
	printf("\n");
}

/*------------------------------------------------------------------------------------------------------------*/

void Print_Data_Detect(sec_FrameMsg_t frame)
{
	float data_float = 0;
	float temperature = 0, humidity = 0;
	
    printf("------------- Detect -------------");
//    printf("\n Header       : %x ", frame.StartFrame);
//    printf("\n TypeMessage  : %x ", frame.TypeMessage);
    printf("\n PortNumber   : %x ", frame.PortNumber);
//    printf("\n LengthData   : %d ", frame.LengthData);
    
    switch (frame.TypeMessage)
    {
        case TYPE_MESSAGE_ANSWER_TYPE:
//            printf("\n TypeSensor   : %x ", frame.Data[0]);
        break;

        case TYPE_MESSAGE_ANSWER_DATA:
//            printf("\n TypeSensor   : %x ", frame.Data[0]);

            switch (frame.Data[0])
            {
                case SENSOR_SHT30:
					// nhiet do
                    temperature = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                    printf("\n Temperature  : %0.2f ", temperature);
					// do am
					humidity = Sec_Convert_From_Bytes_To_Float(frame.Data[5], frame.Data[6], frame.Data[7], frame.Data[8]);
                    printf("\n Humidity     : %0.2f ", humidity);
                break;
				
				case SENSOR_NTC:
                    temperature = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                    printf("\n Temperature  : %0.2f ", temperature);
                break;

                case SENSOR_3:
                    humidity = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                    printf("\n humidity    : %0.2f ", humidity);
                break;

                case SENSOR_4:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                    printf("\n DataSensor   : %0.2f ", data_float);
                break;

                case SENSOR_5:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                    printf("\n DataSensor   : %0.2f ", data_float);
                break;

                case SENSOR_6:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                    printf("\n DataSensor   : %0.2f ", data_float);
                break;
            }
        break;
    }

//    printf("\n CheckFrame   : %x\n", frame.CheckFrame);
	printf("\n");
}

/*------------------------------------------------------------------------------------------------------------*/
