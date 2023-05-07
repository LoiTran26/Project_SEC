#ifndef _SEC_ASK_H_
#define _SEC_ASK_H_

#include "sec_sys.h"
#include "sec_convert.h"
#include "sec_message.h"

typedef enum
{
	ASK_PORT_1 = 1,
	ASK_PORT_2,
	ASK_PORT_3,
	ASK_PORT_4,
	ASK_PORT_5,
	ASK_PORT_6,
}ask_port_e;

uint8_t SEC_create_frame_asksensor(uint8_t port_number);
uint8_t SEC_create_frame_askdata(uint8_t port_number);

void Print_Data_Message(uint8_t *arr, uint8_t length);
void Print_Data_Detect(sec_FrameMsg_t frame);

#endif
