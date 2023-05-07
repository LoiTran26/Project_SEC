#include "sec_time.h"


volatile uint16_t Time_out = 1;

void TIME4_Init(void)
{
  CLK->CKDIVR = 0;
  CLK->PCKENR1 = 0xff;
  CLK->PCKENR2 = 0xff;
  TIM4->PSCR =  0x07;
  TIM4->ARR = 125;
  TIM4->IER =0x01;
  TIM4->CR1 = 0x01;
  enableInterrupts();  
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{
/*
    if(UART_Flag())
    {
    Time_out = TIME_OUT;
    }
    Time_out--;
    if(Time_out <= 0)
    {
    Time_out = 1;
    }
    TIM4->SR1 = 0;
*/
    /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
    */
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