#ifndef __SEC_SYS_H__
#define __SEC_SYS_H__


#include "math.h"
#include "stm8s.h"
#include "stdio.h"
#include "string.h"

#include "sec_adc.h"
#include "sec_time.h"
#include "sec_uart.h"
#include "sec_gpio.h"
#include "sec_delay.h"
#include "sec_answer.h"
#include "sec_convert.h"
#include "sec_message.h"
#include "sec_soil_moisture.h"

#define PRINTF_DATA_SOIL_MOISTURE 0

typedef enum
{
    SEC_IP_DISABLE = 3, /*!< as main */
    SEC_IP_LOW2    = 0, /*!< low     */
    SEC_IP_LOWER1  = 1, /*!< lower   */
    SEC_IP_LOWEST0 = 2  /*!< lowest  */
}sec_InterruptPriority;


void SEC_Sys_Init(void);
void SEC_Sys_Run(void);
void SEC_InterruptPriority(uint8_t vector, uint8_t priority);

#endif 
