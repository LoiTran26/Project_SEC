#ifndef _SEC_LOG_H_
#define _SEC_LOG_H_

#include "sec_sys.h"
#include "sec_message.h"

#define LOG_CREATE_FRAME 0

void Sec_Log_Error(char *Log, uint8_t port_number);
void Sec_Log_Done(char *Log, uint8_t port_number);
void Sec_Clear_Frame_Message(sec_FrameMsg_t *Frame);
void Sec_Printf_Arr_Receive(uint8_t *arr, uint8_t len);

#endif