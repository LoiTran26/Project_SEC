#include "sec_log.h"


void Sec_Log_Error(char *Log, uint8_t port_number)
{
	printf("\n!(ERROR: %s%d)!\n", Log, port_number);
}

void Sec_Log_Done(char *Log, uint8_t port_number)
{
	printf("\n!(DONE: %s%d)!\n", Log, port_number);
}

void Sec_Clear_Frame_Message(sec_FrameMsg_t *Frame)
{
	uint8_t i;
	Frame->StartFrame = 0;
	Frame->TypeMessage = 0;
	Frame->PortNumber = 0;
	Frame->LengthData = 0;
	for(i = 0; i< 24; i++)
	{
		Frame->Data[i] = 0;
	}
	Frame->CheckFrame = 0;
}

void Sec_Printf_Arr_Receive(uint8_t *arr, uint8_t len)
{
	uint8_t i;
	for(i = 0; i < len; i++)
	{
		printf("%x ",arr[i]);
	}
	printf("\n");
}
