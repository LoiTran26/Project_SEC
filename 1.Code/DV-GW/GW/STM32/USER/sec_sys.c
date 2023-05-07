#include "sec_sys.h"

uint16_t count_time = 0;

void SEC_Sys_Init(void)
{	
	SEC_GPIO_Init();
	SEC_DELAY_Init(72);
	SEC_Uart_Init1(9600);
	SEC_Uart_Init2(9600);
}


void SEC_Sys_Run(void)
{
	SEC_TimeOut_Fsm();
	count_time++;
	if(count_time == 20)
	{
		SEC_Split_frame_time();
		count_time = 0;
	}
	SEC_DELAY_ms(1);
}
