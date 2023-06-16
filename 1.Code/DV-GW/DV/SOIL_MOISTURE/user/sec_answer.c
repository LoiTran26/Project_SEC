#include "sec_answer.h"


sec_FrameMsg_t frame_sensor_detect;
static float data_sensor;
static uint8_t Port_Number_Old = 0, Port_Number_New = 0;

/*----------------------------------------------------------------------------*/
/*-------------------- Ham gui loai SenSor len STM32 -------------------------*/
void SEC_Send_Anwser_TypeSensor(void)
{
    uint8_t arr_data_answertype[24], length_arr = 0;
    
    if(sec_vrAll_uart_t.Flag_fsm_True == 1)
    {
        /* Detect array nhan duoc tu STM32 gui xuong */
        SEC_Message_Detect_Frame(sec_vrAll_uart_t.array_out, &frame_sensor_detect);
        
        Port_Number_Old = frame_sensor_detect.PortNumber;
        
#if DEBUG_DETECT_FRAME_ASK_SENSOR
        SEC_Print_Data_Detect(frame_sensor_detect);
#endif           
        
        if(frame_sensor_detect.TypeMessage == TYPE_MESSAGE_ASK_TYPE)
        {
            frame_sensor_detect.Data[0] = SENSOR_NTC;
            frame_sensor_detect.TypeMessage = TYPE_MESSAGE_ANSWER_TYPE;
            
            /* Create struct de gui len STM32 */
            length_arr = SEC_Message_Create_Frame(frame_sensor_detect, arr_data_answertype);
            
#if DEBUG_CREATE_FRAME_ANS_SENSOR
            SEC_Print_Data_Message(arr_data_answertype, length_arr);
#endif
            
            UART_Send_Byte(arr_data_answertype, length_arr);
        }
        
        sec_vrAll_uart_t.Flag_fsm_True = 0;
    }
}

/*----------------------------------------------------------------------------*/
/*----------------- Ham gui data cua cac SenSor len STM32 --------------------*/
void SEC_Send_Anwser_DataSensor(void)
{
    uint8_t arr_data_answertype[24], length_arr = 0;

    if(sec_vrAll_uart_t.Flag_fsm_True == 1)
    {  
        /* Detect array nhan duoc tu STM32 gui xuong */
        SEC_Message_Detect_Frame(sec_vrAll_uart_t.array_out, &frame_sensor_detect);
        
        Port_Number_New = frame_sensor_detect.PortNumber;
        
#if DEBUG_DETECT_FRAME_ASK_DATA
        SEC_Print_Data_Detect(frame_sensor_detect);
#endif           
        
        if(frame_sensor_detect.TypeMessage == TYPE_MESSAGE_ASK_DATA && Port_Number_Old == Port_Number_New)
        {
            SEC_Anwser_DataSensor();
            frame_sensor_detect.TypeMessage = TYPE_MESSAGE_ANSWER_DATA;

            /* Create struct de gui len STM32 */
            length_arr = SEC_Message_Create_Frame(frame_sensor_detect, arr_data_answertype);
            
#if DEBUG_CREATE_FRAME_ANS_DATA
            SEC_Print_Data_Message(arr_data_answertype, length_arr);
#endif
            
            UART_Send_Byte(arr_data_answertype, length_arr);
        }
       
        sec_vrAll_uart_t.Flag_fsm_True = 0;
    }
}

/*----------------------------------------------------------------------------*/
void SEC_Anwser_DataSensor(void)
{
    data_sensor = SEC_Map(adc_ain3_data, 1023, 0, 0, 100);  
    
    uint8_t *data_float_to_byte = Sec_Convert_From_Float_To_Bytes(data_sensor);
    
    frame_sensor_detect.Data[0]   = SENSOR_NTC;
    
    frame_sensor_detect.Data[1]   = data_float_to_byte[0];
    frame_sensor_detect.Data[2]   = data_float_to_byte[1];
    frame_sensor_detect.Data[3]   = data_float_to_byte[2];
    frame_sensor_detect.Data[4]   = data_float_to_byte[3];
}



/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

void SEC_Print_Data_Message(uint8_t *arr, uint8_t length)
{
    UART_Send_String("- Create -\n");

    for (uint8_t i = 0; i < length; i++)
    {
        if (arr[i] <= 0x0F)
        {
            UART_Send_String("0");
            UART_Send_Number_Hex(arr[i]);
            UART_Send_String(" ");
        }
        else
        {
            UART_Send_Number_Hex(arr[i]);
            UART_Send_String(" ");
        }
    }	
    UART_Send_String("\n");
}

/*----------------------------------------------------------------------------*/

void SEC_Print_Data_Detect(sec_FrameMsg_t frame)
{
    float data_float = 0;
    
    UART_Send_String("- Detect -\n");
    UART_Send_String(" Header      : ");
    UART_Send_Number_Hex(frame.StartFrame);
    UART_Send_String("\n TypeMessage : ");
    UART_Send_Number_Hex(frame.TypeMessage);
    UART_Send_String("\n PortNumber  : ");
    UART_Send_Number_Hex(frame.PortNumber);
    UART_Send_String("\n LengthData  : ");
    UART_Send_Number(frame.LengthData);
    
    switch (frame.TypeMessage)
    {
        case TYPE_MESSAGE_ANSWER_TYPE:
            UART_Send_String("\n TypeSensor  : ");
            UART_Send_Number_Hex(frame.Data[0]);
        break;

        case TYPE_MESSAGE_ANSWER_DATA:
            UART_Send_String("\n TypeSensor  : ");
            UART_Send_Number_Hex(frame.Data[0]);

            switch (frame.Data[0])
            {
                case SENSOR_SHT30:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                break;
                
                case SENSOR_NTC:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                break;

                case SENSOR_3:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                break;

                case SENSOR_4:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                break;

                case SENSOR_5:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                break;

                case SENSOR_6:
                    data_float = Sec_Convert_From_Bytes_To_Float(frame.Data[1], frame.Data[2], frame.Data[3], frame.Data[4]);
                break;
            }
            UART_Send_String("\n DataSensor  : ");
            UART_Send_Number_Float(data_float);
        break;
    }
    
    UART_Send_String("\n CheckFrame  : ");
    UART_Send_Number_Hex(frame.CheckFrame);
    UART_Send_String("\n");
}
/*----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/      
/*----------------------------------------------------------------------------*/  