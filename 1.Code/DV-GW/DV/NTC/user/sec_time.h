/**
  ********************************************************************************
  * @file    time.h
  * @author  Luu Ngoc Anh
  * @version 
  * @date    
  * @brief   
  *******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SEC_TIME_H_
#define _SEC_TIME_H_

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "sec_uart.h"

#define TIME_OUT 100
    
void TIME4_Init(void);
uint8_t Check_time_out(void);
void TIM4_Out_set_value(int __vrTime_out_ms);

#endif /* __STM8S_UART1_H */