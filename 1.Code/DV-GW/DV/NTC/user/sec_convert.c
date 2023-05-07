#include "sec_convert.h"
#include "stdio.h"

#define MAX_HEX_LEN 10

static void SEC_Conver_reverse(char* str, int len);
static uint8_t SEC_Conver_intToStr(int32_t x, char str[], uint8_t d, uint8_t negative);

static void SEC_Conver_reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) 
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

static uint8_t SEC_Conver_intToStr(int32_t x, char str[], uint8_t d, uint8_t negative)
{
    uint8_t i = 0, vrui_negative = 0;
    if (x < 0)
    {
        vrui_negative = 1;
        x *= -1;
    }

    while (x) 
    {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    while (i < d)
    {
        str[i++] = '0';
    }

    if ((vrui_negative == 1) || (negative == 1))
    {
        str[i++] = '-';
    }

    SEC_Conver_reverse(str, i);
    str[i] = '\0';
    return i;
}

char* SEC_Conver_IntToStr(const int32_t _data_, uint8_t d)
{
    uint8_t i = 0, negative = 0;
    int32_t vrui_tempdata = _data_;

    static char str[10];
    
    if (_data_ < 0)
    {
        negative = 1;
        vrui_tempdata *= -1;
    }

    while (vrui_tempdata) 
    {
        str[i++] = (vrui_tempdata % 10) + '0';
        vrui_tempdata = vrui_tempdata / 10;
    }

    while (i < d)
    {
        str[i++] = '0';
    }

    if (negative == 1)
    {
        str[i++] = '-';
    }
    
    SEC_Conver_reverse(str, i);
    str[i] = '\0';
    return str;
}

float SEC_Conver_StrToFloat(const char *_data_)
{
    float val = 0;
    int afterdot = 0;
    float scale = 1;
    int neg = 0;

    if (*_data_ == '-') 
    {
        _data_++;
        neg = 1;
    }
    
    while (*_data_) 
    {
        if (afterdot) 
        {
            scale = scale / 10;
            val = val + (*_data_ - '0') * scale;
        } 
        else 
        {
            if (*_data_ == '.')
            {
                afterdot++;
            }
            else
            {
                val = val * 10.0 + (*_data_ - '0');
            }
        }
        _data_++;
    }
    
    if(neg)
    {
        return -val;
    }
    else
    {
        return  val;
    }
}


int32_t SEC_Conver_StrToInt(const char *_data_)
{
    int32_t result = 0;
    int32_t puiss = 1;

    puiss = 1;
    
    while (('-' == (*_data_)) || ((*_data_) == '+'))
    {
        if (*_data_ == '-')
        {
            puiss = puiss * -1;
        }
        _data_++;
    }
    
    while ((*_data_ >= '0') && (*_data_ <= '9'))
    {
        result = (result * 10) + ((*_data_) - '0');
        _data_++;
    }
    return (result * puiss);
}

char* SEC_Conver_FloatToStr(const float _data_, uint8_t afterpoint)
{
    uint8_t i = 0, vrui_negative = 0;
    static char str[20];
    int ipart = (int)_data_;
    float fpart = _data_ - (float)ipart;
    
    if (_data_ < 0)
    {
        vrui_negative = 1;
    }
    
    if (fpart < 0)
    {
        fpart *= -1.0;
    }
    
    i = SEC_Conver_intToStr(ipart, str, 1, vrui_negative);
    
    if (afterpoint != 0)
    {
        str[i] = '.';
        fpart = fpart * pow(10, afterpoint);
        SEC_Conver_intToStr((int)fpart, str + i + 1, afterpoint, 0);
    }
    return str;
}

char* SEC_Conver_IntToHex(long long number) 
{
    int i = 0;
    static char str[10];
    
    if(number == 0)
    {
        str[i] = 48;
        i++;
    }
    
    while (number != 0) 
    {
        long temp = 0;
        temp = number % 16;
        if (temp < 10) 
        {
            str[i] = temp + 48;
            i++;
        }
        else 
        {
            str[i] = temp + 55;
            i++;
        }
 
        number = number / 16;
    }
    
    SEC_Conver_reverse(str,i);
    str[i] = 0x00;
    
    return str;
}

/*
    @brief: Chuyển biến kiểu float sang dạng mảng byte
    @node: Chức năng hàm được sử dụng để Chuyển biến kiểu float sang dạng mảng byte 4 phần tử
    @param data: Là một biến kiểu float cần được chuyển sang mảng byte.
    @retval: Mảng bytes.
*/
uint8_t *Sec_Convert_From_Float_To_Bytes(float data)
{
    static data_format_float_bytes input_convert;
    input_convert.data_float = data;
    return input_convert.bytes;
}

/*
    @brief: Chuyển mảng các biến kiểu bytes sang biến kiểu float
    @node: Chức năng hàm được sử dụng để Chuyển mảng các biến kiểu bytes sang biến kiểu float
    @param data0: Biến đầu tiên của mảng .
    @param data1: Biến thứ hai của mảng .
    @param data2: Biến thứ ba của mảng .
    @param data3: Biến thứ tư của mảng .
    @retval: Biến int.
*/
float Sec_Convert_From_Bytes_To_Float(uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3)
{
    data_format_float_bytes input_convert;
    input_convert.bytes[3] = data3;
    input_convert.bytes[2] = data2;
    input_convert.bytes[1] = data1;
    input_convert.bytes[0] = data0;
    return input_convert.data_float;
}

/*
    @brief: Chuyển biến kiểu int sang dạng mảng byte
    @node: Chức năng hàm được sử dụng để Chuyển biến kiểu int sang dạng mảng byte 4 phần tử
    @param data: Là một biến kiểu int cần được chuyển sang mảng byte.
    @retval: Mảng bytes.

uint8_t *Sec_Convert_From_Int_To_Bytes(int data)
{
    static data_format_int_bytes input_convert;
    input_convert.data_int = data;
    return input_convert.bytes;
}
*/
/*
    @brief: Chuyển mảng các biến kiểu bytes sang biến kiểu int
    @node: Chức năng hàm được sử dụng để Chuyển mảng các biến kiểu bytes sang biến kiểu int
    @param data0: Biến đầu tiên của mảng .
    @param data1: Biến thứ hai của mảng .
    @param data2: Biến thứ ba của mảng .
    @param data3: Biến thứ tư của mảng .
    @retval: Biến int.

uint32_t Sec_Convert_From_Bytes_To_Int(uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4)
{
    data_format_int_bytes input_convert;
    input_convert.bytes[0] = data1;
    input_convert.bytes[1] = data2;
    input_convert.bytes[2] = data3;
    input_convert.bytes[3] = data4;

  return input_convert.data_int;
}
*/
/*
    @brief: Chuyển biến kiểu uint16_t sang dạng mảng byte
    @node: Chức năng hàm được sử dụng để Chuyển biến kiểu uint16_t sang dạng mảng byte 4 phần tử
    @param data: Là một biến kiểu uint16_t cần được chuyển sang mảng byte.
    @retval: Mảng bytes.

uint8_t *Sec_Convert_From_Uint16_To_Bytes(int data)
{
    static data_format_uint8_16_t input_convert;
    input_convert.data_uint16 = data;
    return input_convert.bytes;
}
*/
/*
    @brief: Chuyển mảng các biến kiểu bytes sang biến kiểu uint16_t
    @node: Chức năng hàm được sử dụng để Chuyển mảng các biến kiểu bytes sang biến kiểu uint16_t
    @param data0: Biến đầu tiên của mảng .
    @param data1: Biến thứ hai của mảng .
    @retval: Biến Uint16_t.
*/
uint16_t Sec_Convert_From_Bytes_To_Uint16(uint8_t data1, uint8_t data2) ////////////////////////////////////////////
{
    data_format_uint8_16_t input_convert;
    input_convert.bytes[1] = data1;
    input_convert.bytes[0] = data2;

    return input_convert.data_uint16;
}

/*
    Hàm chuyển đổi Big endian sang Little endian

uint16_t Convert_Big_Endian_To_Little_Endian(uint16_t num)
{
    return ((num & 0xff00) >> 8) | ((num & 0x00ff) << 8);
}
*/

