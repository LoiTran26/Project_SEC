#include "sec_sys.h"

//Sensor Soil Moisture
//D6-rx
//D5-tx

int main( void )
{
    SEC_Sys_Init();    
    SEC_InterruptPriority(18, 0);
    SEC_InterruptPriority(23, 1);
    
    while (1)
    {     
        SEC_Sys_Run();
        
    #if PRINTF_DATA_SOIL_MOISTURE
        float hum = 0;
        hum = SEC_Map(adc_ain3_data, 1023, 0, 0, 100);
        UART_Send_Number_Float(hum);
        UART_Send_String("\n\n");
        SEC_Delay_Ms(1000);
    #endif
    }
}
