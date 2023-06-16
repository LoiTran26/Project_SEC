#include "sec_sht30.h"

void I2c_write(uint8_t addre, uint16_t command);
void I2c_Read(uint8_t addre, uint8_t *arr, uint8_t len);
uint16_t readStatus(void);
static uint8_t crc8(const uint8_t *data, int len);

void delay(int a)
{
  for (int i = 0; i < a; i++)
  for (int index = 0; index < 400; index++);
}

void SHT30_Init(void)
{
  I2C_Init(100000);
  delay(100);
  I2c_write(SHT31_DEFAULT_ADDR ,SHT31_SOFTRESET);
  delay(100);
  SHT30_SetHeater(SHT31_HEATERDIS);
  delay(100);
  readStatus();
  delay(100);
}
void SHT30_SetHeater(uint16_t heater)
{
  I2c_write(SHT31_DEFAULT_ADDR ,(uint16_t)heater);
}

uint8_t SHT30_isHeaterEnabled()
{
  uint16_t TempStatus;
  TempStatus = readStatus();
  if(TempStatus !=0)
     return ((TempStatus>>SHT31_REG_HEATER_BIT)&0x01);
  return 0;
}

uint8_t SHT30_ReadTempHum(float *temp, float *humidity)
{
  uint8_t readbuffer[6] ={0};
  uint32_t stemp, shum;
  I2c_write(SHT31_DEFAULT_ADDR, SHT31_MEAS_HIGHREP_STRETCH);
  delay(100);
  I2c_Read(SHT31_DEFAULT_ADDR, readbuffer, 6);
  if (readbuffer[2] != crc8(readbuffer, 2) || readbuffer[5] != crc8(readbuffer + 3, 2))
  {
      return 0;
  }
  stemp = (uint32_t)(((uint32_t)readbuffer[0] << 8) | readbuffer[1]);
  stemp = ((4375 * stemp) >> 14) - 4500;
  *temp = (float)stemp / 100.0f;
  
  shum = ((uint32_t)readbuffer[3] << 8) | readbuffer[4];
  shum = (625 * shum) >> 12;
  *humidity = (float)shum / 100.0f;
  return 1;
}

uint8_t AIRP_ReadPressure(float *pressure)
{
  uint8_t readbuffer[6] ={0};
  uint32_t press;
  I2c_write(SHT31_DEFAULT_ADDR, SHT31_MEAS_HIGHREP_STRETCH);
  delay(100);
  I2c_Read(SHT31_DEFAULT_ADDR, readbuffer, 6);
  
  if (readbuffer[2] != crc8(readbuffer, 2) || readbuffer[5] != crc8(readbuffer + 3, 2))
  {
      return 0;
  }
  
  press = (uint32_t)(((uint32_t)readbuffer[0] << 8) | readbuffer[1])& 0x3FFF;
  // Convert to kilopascals
  press = press*40.0/16383.0; 
  *pressure = (float)press;
  
  return 1;
}

void I2c_write(uint8_t addre, uint16_t command)
{
  uint8_t command_buffer[2] = {((command&0xff00)>>8u), (command&0xff)};
  I2C_Start();
  I2C_Write_add(addre<<1, 0);
  I2C_Write(command_buffer[0]);
  I2C_Write(command_buffer[1]);
  I2C_Stop();
}

void I2c_Read(uint8_t addre, uint8_t *arr, uint8_t len)
{
  uint8_t i;
  I2C_Start();
  I2C_Write_add(addre<<1, 1);
  for(i=0; i<len; i++)
  {
    if(i == (len-1))
    {
      arr[i] = I2C_Read_NAK();
    }
    else
    {
      arr[i] = I2C_Read_ACK();
    }
  }
}

uint16_t readStatus(void)
{
  uint8_t readbuffer[3];
  uint16_t status;
  I2c_write(SHT31_DEFAULT_ADDR, SHT31_READSTATUS);
  I2c_Read(SHT31_DEFAULT_ADDR, readbuffer, 3);
  if (readbuffer[2] != crc8(readbuffer, 2))
  {
      return 0;
  }
  status = readbuffer[0];
  status <<= 8;
  status |= readbuffer[1];
  return status;
}

static uint8_t crc8(const uint8_t *data, int len) {
  const uint8_t POLYNOMIAL = 0x31;
  uint8_t crc = 0xFF;

  for (int j = len; j; --j) {
    crc ^= *data++;

    for (int i = 8; i; --i) {
      crc = (crc & 0x80) ? (crc << 1) ^ POLYNOMIAL : (crc << 1);
    }
  }
  return crc;
}