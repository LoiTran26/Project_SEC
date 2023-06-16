#ifndef     _SEC_DELAY_H_
#define     _SEC_DELAY_H_


#define   FRIQUENCY	16000000
#define   CYCLES_PER_US ((FRIQUENCY + 500000)/1000000)

void SEC_Delay_Us(unsigned int _vrui_Delay);
void SEC_Delay_Ms(unsigned int _vrui_Delay);

#endif

