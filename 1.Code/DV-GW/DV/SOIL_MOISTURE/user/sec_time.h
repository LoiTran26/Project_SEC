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
    
typedef enum
{
  TIM4_PRESCALER_1  = ((uint8_t)0x00),
  TIM4_PRESCALER_2    = ((uint8_t)0x01),
  TIM4_PRESCALER_4    = ((uint8_t)0x02),
  TIM4_PRESCALER_8     = ((uint8_t)0x03),
  TIM4_PRESCALER_16   = ((uint8_t)0x04),
  TIM4_PRESCALER_32     = ((uint8_t)0x05),
  TIM4_PRESCALER_64    = ((uint8_t)0x06),
  TIM4_PRESCALER_128   = ((uint8_t)0x07)
} TIM4_Prescaler_TypeDef;

    
void TIME4_Init(void);
uint8_t Check_time_out(void);
void TIM4_Out_set_value(int __vrTime_out_ms);

#endif /* __STM8S_UART1_H */