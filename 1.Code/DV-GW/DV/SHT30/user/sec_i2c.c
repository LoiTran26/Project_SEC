#include "sec_i2c.h"

void I2C_Init(uint32_t Speed)
{
  I2C->CR1 = 0;
  I2C->FREQR = 16;
  I2C->CCRL = (16 * 1000000) / (Speed << 1);
  I2C->CCRH &= 0x00;
  I2C->OARH = 0x40;
  I2C->TRISER = 17;
  I2C->CR1 = I2C_CR1_PE;
}

void I2C_Start(void)
{
  I2C->CR2 |= I2C_CR2_START | I2C_CR2_ACK;
  while (!(I2C->SR1 & I2C_SR1_SB));
}

void I2C_Stop(void)
{
  I2C->CR2 |= I2C_CR2_STOP;
}

void I2C_Write(uint8_t data)
{
  volatile int reg;
  reg = I2C->SR1;
  reg = I2C->SR3;
  I2C->DR = data;
  while (!(I2C->SR1 & I2C_SR1_TXE));
}

void I2C_Write_add(uint8_t add, uint8_t mode)
{
  volatile int reg;
  reg = I2C->SR1;
  I2C->DR = (add) | mode;
  if (mode == 1) {
    I2C->OARL = 0; 
    I2C->OARH = 0;
  }
  while (!(I2C->SR1 & I2C_SR1_ADDR));
  I2C->SR1 &= ~I2C_SR1_ADDR;
}

uint8_t I2C_Read_NAK(void)
{
  volatile uint8_t reg;
  reg = I2C->SR1;
  reg = I2C->SR3;
  I2C->CR2 &= ~I2C_CR2_ACK;
  I2C_Stop();
  while (!(I2C->SR1 & (I2C_SR1_RXNE)));
  return I2C->DR;

}

uint8_t I2C_Read_ACK(void)
{
  volatile uint8_t reg;
  reg = I2C->SR1;
  reg = I2C->SR3;
  I2C->CR2 |= I2C_CR2_ACK;
  while (!(I2C->SR1 & I2C_SR1_RXNE));
  return I2C->DR;
}