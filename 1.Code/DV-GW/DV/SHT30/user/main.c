#include "sec_sys.h"

//Sensor SHT30
//D6-rx
//D5-tx

int main( void )
{
    SEC_Sys_Init();    

    while (1)
    {           
        SEC_Sys_Run();
    }
}

