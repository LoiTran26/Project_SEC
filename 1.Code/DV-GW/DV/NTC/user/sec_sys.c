#include "sec_sys.h"

static uint8_t Flag_Answer = 0;

void SEC_Sys_Init(void)
{
    UART_Init(9600);
    UART_Rs485_Init();
}

void SEC_Sys_Run(void)
{    
    SEC_TimeOut_Fsm();
        
    if(Flag_Answer == 0)
    {
        if(sec_vrAll_uart_t.Flag_fsm_True == 1)
        {
            // tra loi loai Sensor
            SEC_Send_Anwser_TypeSensor();
            Flag_Answer = 1;
        }
    }
    else if(Flag_Answer == 1)
    {
        if(sec_vrAll_uart_t.Flag_fsm_True == 1)
        {
            // tra loi Data cua Sensor
            SEC_Send_Anwser_DataSensor();
        }
    }
}