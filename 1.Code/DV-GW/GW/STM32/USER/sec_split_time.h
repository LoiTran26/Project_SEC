#ifndef _SEC_SPLIT_TIME_H_
#define _SEC_SPLIT_TIME_H_

#include "sec_sys.h"

#define SENSOR_DISCONNECT 	0
#define SENSOR_JOIN 		1
#define SENSOR_CONNECT 		2

#define FRAME_SEND 1
#define FRAME_RECEIVE 1


typedef struct
{
	GPIO_TypeDef 	*GPIOx;
	uint16_t 		Port_number;	
}Array_port_t;

typedef enum
{
	START = 1,
	JOIN,
	DISCONNECT,
	DATA,
	BACK,
}sec_status_time_e;


void SEC_Split_frame_time(void);
uint8_t SEC_Join_Port(uint8_t port_number);
uint8_t SEC_Data_Port(uint8_t port_number);
void SEC_Read_status_port(uint8_t port_number);

#endif
