#include "sec_sys.h"

int main()
{
	SEC_Sys_Init();
	
	while(1)
	{
		SEC_Sys_Run();
	}
}
