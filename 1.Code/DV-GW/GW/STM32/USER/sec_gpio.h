#ifndef __SEC_GPIO_H__
#define __SEC_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "sec_sys.h"

typedef enum
{
	GET_GPIO_CONNECTED = 0,
	GET_GPIO_DISCONNECTED
}_status_port_plug_e;

typedef enum 
{
	GPIO_CONTROL_ENA_ALL = 0,
	GPIO_CONTROL_DIS_ALL,
} gpio_Control_en;

void SEC_GPIO_Init(void);
void SET_GPIO_PORT_Init(void);
void GET_GPIO_PORT_Init(void);
void SEC_GPIO_Set_ON(int port);
void SEC_GPIO_Set_OFF(int port);
void SEC_Test_Gpio_Control(gpio_Control_en _stt_);

#ifdef __cplusplus
}
#endif

#endif

/********************************* END OF FILE ********************************/
/******************************************************************************/
