/**
  ********************************************************************************
  * @file    stm8s_uart1.h
  * @author  Nguyen Quang Bien
  * @version 
  * @date    
  * @brief   
  *******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SEC_I2C_H__
#define __SEC_I2C_H__
/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

void I2C_Init(uint32_t Speed);

void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
void I2C_Write_add(uint8_t data, uint8_t mode);
uint8_t I2C_Read_NAK(void);
uint8_t I2C_Read_ACK(void);
uint16_t I2C_Read_arr(void);

#endif /* __STM8S_UART1_H */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/