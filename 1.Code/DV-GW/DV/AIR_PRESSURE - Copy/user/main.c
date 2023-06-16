#include "sec_sys.h"

//Sensor SHT30
//D6-rx
//D5-tx

int main( void )
{
    SEC_Sys_Init();    
    
    while (1)
    {           
        //SEC_Sys_Run();
        float a = 0, b = 0;
        SHT30_ReadTempHum(&a, &b);
        UART_Send_Number_Float(a);
        UART_Send_String("\n");
        UART_Send_Number_Float(b);
        UART_Send_String("\n");
        SEC_Delay_Ms(1000);
    }
}

