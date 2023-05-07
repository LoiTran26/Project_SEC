/*
  ******************************************************************************
  * @file		define.h                                                           *
  * @author	Luu Ngoc Anh                                                       *
  * @date		11/29/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __SEC_DEFINE_H__
#define __SEC_DEFINE_H__

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"                  // Device header

#define SET_GPIO_PORTB_1   		GPIO_Pin_12
#define SET_GPIO_PORTB_2   		GPIO_Pin_13
#define SET_GPIO_PORTB_3   		GPIO_Pin_14
#define SET_GPIO_PORTB_4   		GPIO_Pin_15
#define SET_GPIO_PORTA_5   		GPIO_Pin_11
#define SET_GPIO_PORTA_6   		GPIO_Pin_12
#define SET_GPIO_PORTAB_ALL   SET_GPIO_PORTB_1|SET_GPIO_PORTB_2|SET_GPIO_PORTB_3|SET_GPIO_PORTB_4|SET_GPIO_PORTB_5|SET_GPIO_PORTB_6

#define GET_GPIO_PORTB_1 			GPIO_Pin_5
#define GET_GPIO_PORTB_2 			GPIO_Pin_4
#define GET_GPIO_PORTB_3 			GPIO_Pin_3
#define GET_GPIO_PORTB_4 			GPIO_Pin_0
#define GET_GPIO_PORTB_5 			GPIO_Pin_1
#define GET_GPIO_PORTB_6 			GPIO_Pin_2
#define GET_GPIO_PORTB_ALL    GET_GPIO_PORTB_1|GET_GPIO_PORTB_2|GET_GPIO_PORTB_3|GET_GPIO_PORTB_4|GET_GPIO_PORTB_5|GET_GPIO_PORTB_6



#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
