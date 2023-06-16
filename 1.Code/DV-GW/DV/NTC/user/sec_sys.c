#include "sec_sys.h"

static uint8_t flag_answer = 0;
static uint8_t count_time;

void SEC_Sys_Init(void)
{
    TIME4_Init();
    UART_Init(9600);
    UART_Rs485_Init();
}

void SEC_Sys_Run(void)
{    
    SEC_TimeOut_Fsm();
        
    if(flag_answer == 0)
    {
        if(sec_vrAll_uart_t.Flag_fsm_True == 1)
        {
            // tra loi loai Sensor
            SEC_Send_Anwser_TypeSensor();
            flag_answer = 1;
        }
    }
    else if(flag_answer == 1)
    {
        if(sec_vrAll_uart_t.Flag_fsm_True == 1)
        {
            // tra loi Data cua Sensor
            SEC_Send_Anwser_DataSensor();
        }
    }
}

void SEC_InterruptPriority(uint8_t vector, uint8_t priority)
{
    uint8_t m_reg  = ((vector & 3) << 1);
    uint8_t m_mask = ~(SEC_IP_DISABLE << m_reg);
    uint8_t m_prio = (priority << m_reg);

    switch (vector >> 2)
    {
        case 0: 
          ITC->ISPR1 &= m_mask; 
          ITC->ISPR1 |= m_prio; 
        break;
        
        case 1: 
          ITC->ISPR2 &= m_mask; 
          ITC->ISPR2 |= m_prio; 
        break;
        
        case 2: 
          ITC->ISPR3 &= m_mask; 
          ITC->ISPR3 |= m_prio; 
        break;
        
        case 3: 
          ITC->ISPR4 &= m_mask; 
          ITC->ISPR4 |= m_prio; 
        break;
        
        case 4: 
          ITC->ISPR5 &= m_mask; 
          ITC->ISPR5 |= m_prio; 
        break;
        
        case 5: 
          ITC->ISPR6 &= m_mask; 
          ITC->ISPR6 |= m_prio; 
        break;
        
        case 6: 
          ITC->ISPR7 &= m_mask; 
          ITC->ISPR7 |= m_prio; 
        break;
    }
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{
  TIM4->SR1 = 0;

  if (count_time >= 10)
  {
    adc_ain3_data = ADC_Kalman_Filter(ADC_Read(4,0), &kalman_var_ain3);
    count_time = 0;
  }
  else
  {
    count_time++;
  }
}
