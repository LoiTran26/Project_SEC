#ifndef __SEC_SYS__H__
#define __SEC_SYS__H__


#ifdef __cplusplus
 extern "C" {
#endif

#include "stdio.h"
#include "string.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#include "sec_ask.h"
#include "sec_fsm.h"
#include "sec_log.h"
#include "sec_uart.h"
#include "sec_gpio.h"
#include "sec_delay.h"
#include "sec_define.h" 
#include "sec_convert.h"
#include "sec_message.h"
#include "sec_split_time.h"


void SEC_Sys_Init(void);
void SEC_Sys_Run(void);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
