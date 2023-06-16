#include "sec_ntc.h"
 

float SEC_GetDataSensorNTC10K(uint16_t adc_data)
{
    float temp_k = 0; 
    float temp_c = 0;
    float vout = 0;
    float rntc = 0;
    
    vout = (adc_data*3.3)/1024;
    rntc = (vout*R_10k)/(3.3 - vout);
    temp_k = (T0*B_PARAM)/(T0*log(rntc/R_10k) + B_PARAM);
    temp_c = temp_k - 273.15;
    
#if PRINTF_DATA_NTC
    UART_Send_Number_Float(adc_data);
    UART_Send_String("\n");
    UART_Send_Number_Float(temp_k);
    UART_Send_String("\n");
    UART_Send_Number_Float(temp_c);
    UART_Send_String("\n");
#endif
    
    return temp_c;
}