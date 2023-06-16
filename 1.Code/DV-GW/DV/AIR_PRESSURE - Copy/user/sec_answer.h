#ifndef _SEC_ANSWER_H_
#define _SEC_ANSWER_H_

#include "sec_sys.h"
#include "sec_message.h"


#define DEBUG_CREATE_FRAME_ANS_SENSOR 0
#define DEBUG_DETECT_FRAME_ASK_SENSOR 0
#define DEBUG_CREATE_FRAME_ANS_DATA 0
#define DEBUG_DETECT_FRAME_ASK_DATA 0

void SEC_Anwser_DataSensor(void);
void SEC_Send_Anwser_TypeSensor(void);
void SEC_Send_Anwser_DataSensor(void);
void SEC_Print_Data_Detect(sec_FrameMsg_t frame);
void SEC_Print_Data_Message(uint8_t *arr, uint8_t length);

#endif
