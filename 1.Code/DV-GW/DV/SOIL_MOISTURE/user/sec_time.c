#include "sec_time.h"


volatile uint16_t Time_out = 1;

void TIME4_Init(void)
{
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  TIM4->PSCR =  TIM4_PRESCALER_128;
  TIM4->ARR = 125;
  TIM4->IER =0x01;
  TIM4->CR1 = 0x01;
  enableInterrupts();  
}



void TIM4_Out_set_value(int __vrTime_out_ms)
{
  Time_out = __vrTime_out_ms;
}

uint8_t Check_time_out(void)
{
  if(Time_out <= 1)
    return 1;
  else
    return 0;
}