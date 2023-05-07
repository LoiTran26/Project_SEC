#ifndef SEC_CONVERT_H
#define SEC_CONVERT_H

#ifdef __cplusplus
    extern "C" {
#endif

#include<stdio.h>
#include<stdint.h>
#include "math.h"
#include "sec_define.h"            
#include "stm32f10x_gpio.h"

typedef union 
{
	float data_float;
	uint8_t bytes[4];	
} data_format_float_bytes;

typedef union 
{
    uint32_t data_int;
    uint8_t bytes[4];
} data_format_int_bytes;

typedef union 
{
    uint16_t data_uint16;
    uint8_t bytes[2];
} data_format_uint8_16_t;

/******************************************************************************/
char* SEC_Conver_IntToStr(const int32_t _data_, uint8_t d);
char* SEC_Conver_FloatToStr(const float _data_, uint8_t afterpoint);

int32_t SEC_Conver_StrToInt(const char *_data_);
float 	SEC_Conver_StrToFloat(const char *_data_);
/******************************************************************************/

uint8_t* Sec_Convert_From_Float_To_Bytes(float data);

float Sec_Convert_From_Bytes_To_Float(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);

uint8_t* Sec_Convert_From_Int_To_Bytes(int data);

uint32_t Sec_Convert_From_Bytes_To_Int(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);

uint8_t* Sec_Convert_From_Uint16_To_Bytes(int data);

uint16_t Sec_Convert_From_Bytes_To_Uint16(uint8_t data1, uint8_t data2);

uint8_t Sec_Convert_From_Bytes_To_Uint8(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif // SEC_CONVERT_H
