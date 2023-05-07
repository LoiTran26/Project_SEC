/*
  ******************************************************************************
  * @file		delay.h                                                            *
  * @author	Luu Ngoc Anh                                                       *
  * @date		18/07/2022                                                         *
  ******************************************************************************
*/
	
#ifndef __SEC_DELAY__H__
#define __SEC_DELAY__H__

#ifdef __cplusplus
 extern "C" {
#endif

void SEC_DELAY_Init (unsigned char _CLK);
void SEC_DELAY_us (unsigned long _vrui_Time);
void SEC_DELAY_ms (unsigned int _vrui_Time);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
