#ifndef __SEC_SYS_H__
#define __SEC_SYS_H__


#include "math.h"
#include "stm8s.h"
#include "stdio.h"
#include "string.h"

#include "sec_i2c.h"
#include "sec_time.h"
#include "sec_uart.h"
#include "sec_gpio.h"
#include "sec_delay.h"
#include "sec_sht30.h"
#include "sec_answer.h"
#include "sec_convert.h"
#include "sec_message.h"


void SEC_Sys_Init(void);
void SEC_Sys_Run(void);

#endif 
