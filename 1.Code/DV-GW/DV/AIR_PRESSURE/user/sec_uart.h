#ifndef __SEC_UART_H__
#define __SEC_UART_H__

#include "sec_sys.h"

#define ENB_DEBUG_IRQ 1

typedef enum
{
    FSM_STATE_START_FRAME  = 0,
    FSM_STATE_TYPE_MESSAGE = 1,
    FSM_STATE_PORT_NUMBER  = 2,
    FSM_STATE_LENGHT_DATA  = 3,
    FSM_STATE_END          = 4,
} fsm_state_e;

typedef enum
{
    FSM_STATE_CHANGE_VALUE_START_FRAME  = 0,
    FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE = 2,
    FSM_STATE_CHANGE_VALUE_PORT_NUMBER  = 3,
    FSM_STATE_CHANGE_VALUE_LENGHT_DATA  = 4,
    FSM_STATE_CHANGE_VALUE_END          = 6,
} fsm_state_change_value_e;

typedef struct 
{
    uint8_t temp_data;
    uint8_t array_out[30];
    uint8_t fsm_count_array;
    uint8_t fsm_data_length;
    uint8_t Flag_Fsm;
    uint8_t Flag_fsm_True;
}Sec_ValueAll_t;
extern Sec_ValueAll_t sec_vrAll_uart_t;

extern char RRX[];
extern char RX_FLAG_END_LINE;

void UART_Rs485_Init(void);
void UART_Init(unsigned int select);
void UART_Send_Char(char _varChar);
void UART_Send_Number(int _varNumber);
void UART_Send_String(char *_varString);
void UART_Send_Number_Hex(long long _varNumber);
void UART_Send_Number_Float(float _varNumber);
void UART_Send_Byte(uint8_t *data, uint8_t sizes);

void SEC_TimeOut_Fsm(void);
void SEC_Clear_TimeOut_Fsm(void);

#endif
