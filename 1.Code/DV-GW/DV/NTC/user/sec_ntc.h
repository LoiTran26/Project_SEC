#ifndef _SEC_NTC_H_
#define _SEC_NTC_H_

#include "sec_sys.h"

#define PRINTF_DATA_NTC 0

#define R_10k 9800
#define B_PARAM 6900
#define T0  298.15

float SEC_GetDataSensorNTC10K(uint16_t adc_data);

#endif
