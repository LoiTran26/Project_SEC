#include "sec_sys.h"

//Sensor NTC
//D6-rx
//D5-tx

int main( void )
{
    SEC_Sys_Init();    
    SEC_InterruptPriority(18, 0);
    SEC_InterruptPriority(23, 1);
    
    while (1)
    {          
        SEC_Sys_Run();
    }
}
