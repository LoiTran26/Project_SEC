#ifndef _SEC_ADC_H_
#define _SEC_ADC_H_

#include "sec_sys.h"

typedef struct
{
    float ADC_OLD_Value;
    float P_k1_k1;

    float Q;
    float R; 
    float Kg;
    float P_k_k1;
    float kalman_adc_old;

    uint8_t init_data;
}adc_kalman_filter_t;
extern adc_kalman_filter_t kalman_var_ain3;

extern volatile uint16_t adc_ain3_data;

uint16_t ADC_Read(const uint8_t channel, uint8_t number_read);
uint16_t ADC_Kalman_Filter(unsigned long ADC_Value, adc_kalman_filter_t *adc_kalman);

#endif
