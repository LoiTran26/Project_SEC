#include "sec_adc.h"


volatile uint16_t adc_ain3_data;
adc_kalman_filter_t kalman_var_ain3;
static uint16_t analogRead(const uint8_t channel);

static uint16_t analogRead(const uint8_t channel)
{
  uint16_t val = 0;
  ADC1->CSR = ((0x0F)&channel);
  ADC1->CR2 = (1 << 3);
  ADC1->CR1 = (1 << 0);
  ADC1->CR1 = (1 << 0);
  while (((ADC1->CSR) & (1 << 7)) == 0);
  val |= (unsigned int)ADC1->DRL;
  val |= (unsigned int)ADC1->DRH << 8;
  ADC1->CR1 &= ~(1 << 0);
  val &= 0x03ff;
  return (val);
}

uint16_t ADC_Read(const uint8_t channel, uint8_t number_read)
{
  long Sum = 0, i, n = 100;

  for (i = 0; i < n; i++)
  {
    Sum += analogRead(channel);
  }
  return Sum / n;
}

uint16_t ADC_Kalman_Filter(unsigned long ADC_Value, adc_kalman_filter_t *adc_kalman)
{
  float x_k1_k1, x_k_k1;
  uint16_t kalman_adc;
  float Z_k;
  if (adc_kalman->init_data == 0)
  {
    adc_kalman->ADC_OLD_Value = 0.0;
    adc_kalman->P_k1_k1 = 0.0;
    adc_kalman->kalman_adc_old = 0;
    adc_kalman->Q = 0.00001;
    adc_kalman->R = 0.005;
    adc_kalman->Kg = 0;
    adc_kalman->P_k_k1 = 1;
    adc_kalman->init_data = 1;
  }

  Z_k = ADC_Value;
  x_k1_k1 = adc_kalman->kalman_adc_old;

  x_k_k1 = x_k1_k1;
  adc_kalman->P_k_k1 = adc_kalman->P_k1_k1 + adc_kalman->Q;

  adc_kalman->Kg = adc_kalman->P_k_k1 / (adc_kalman->P_k_k1 + adc_kalman->R);

  kalman_adc = (uint16_t)(x_k_k1 + adc_kalman->Kg * (Z_k - adc_kalman->kalman_adc_old));
  adc_kalman->P_k1_k1 = (1 - adc_kalman->Kg) * adc_kalman->P_k_k1;
  adc_kalman->P_k_k1 = adc_kalman->P_k1_k1;

  adc_kalman->ADC_OLD_Value = ADC_Value;
  adc_kalman->kalman_adc_old = kalman_adc;
  return kalman_adc;
}

