#ifndef __SEC_UART_H__
#define __SEC_UART_H__


#ifdef __cplusplus
 extern "C" {
#endif

#include "stdio.h"
#include "string.h"
#include "sec_delay.h"
#include "stm32f10x.h"    
#include "sec_fsm.h"


#define  UART1_BAUDRATE (9600)
#define  UART2_BAUDRATE (9600)
#define  UART3_BAUDRATE (9600)
	 
#define string_size 50
#define GPIO_CONTROL_RS485 GPIO_Pin_4
#define PORT_CONTROL_RS485 GPIOA


extern char Flag1_Receive;
extern char Array1_Receive[];
extern char Count1_Data;

extern char Flag2_Receive;
extern char Array2_Receive[];
extern char Count2_Data;

extern char Flag3_Receive;
extern char Array3_Receive[];
extern char Count3_Data;
	
	 
void SEC_Uart_Init(void);
void SET_GPIO_PORT_RS485_Init(void);

void SEC_Uart_Init1(unsigned int BaudRates);
void SEC_Uart1_SendChar(char data);
void SEC_Uart1_SendString(char *data);
void SEC_Uart1_SendByte(uint8_t *data, uint8_t sizes); 

void SEC_Uart_Init2(unsigned int BaudRates);
void SEC_Uart2_SendChar(char data);
void SEC_Uart2_SendString(char *data);
void SEC_Uart2_SendByte(uint8_t *data, uint8_t sizes); 
uint8_t UART2_Compare(char *string);

void SEC_Uart_Init3(unsigned int BaudRates);
void Gw_Uart2_SendChar(char data);		 
void Gw_Uart2_SendString(char *data);

#ifdef __cplusplus
}
#endif

#endif

