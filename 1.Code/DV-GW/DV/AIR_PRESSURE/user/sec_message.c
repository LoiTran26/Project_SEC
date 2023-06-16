#include "sec_message.h"
#include "sec_convert.h"


static uint8_t flag_answer_data = 0;

/*----------------------------------------------chuyển data của struct sang data của arr-----------------------------------------*/

uint8_t SEC_Message_Create_Frame(sec_FrameMsg_t DataIn, uint8_t *DataOut)
{
    sec_FrameMsg_t *temp_datain;
    uint8_t *arr_temp;
    uint16_t count_arr = 0;

    temp_datain = &DataIn;
    /* ép kiểu temp_datain về kiểu uint8_t, mục đích để chuyển từ struct sang arr* */
    arr_temp = (uint8_t *)temp_datain;

    if(DataIn.StartFrame != START_BYTE)
    {
        return 0;
    }

    DataOut[count_arr] = (DataIn.StartFrame & 0xff);
    DataOut[count_arr + 1] = ((DataIn.StartFrame >> 8) & 0xff);
    count_arr += 2;
    DataOut[count_arr] = (DataIn.TypeMessage & 0xff);
    count_arr += 1;
    DataOut[count_arr] = (DataIn.PortNumber & 0xff);
    count_arr += 1;
    switch (DataIn.TypeMessage)
    {
        case TYPE_MESSAGE_ANSWER_TYPE:
            DataIn.LengthData = LENGTH_SENSOR_ANSWERTYPE;
        break;

        case TYPE_MESSAGE_ANSWER_DATA:
            flag_answer_data = 1;
            DataIn.LengthData = LENGTH_SENSOR_ANSWERDATA + LENGTH_SENSOR_SHT30;
        break;
    }
    
    DataOut[count_arr] = (DataIn.LengthData & 0xff);
    DataOut[count_arr + 1] = ((DataIn.LengthData >> 8) & 0xff);
    count_arr += 2;
    
    DataOut[count_arr] = (DataIn.Data[0] & 0xff); // loai sensor
    count_arr += 1;
    
    if(flag_answer_data == 1)
    {
        DataOut[count_arr] = (DataIn.Data[1] & 0xff);
        count_arr += 1;
        DataOut[count_arr] = (DataIn.Data[2] & 0xff);
        count_arr += 1;
        DataOut[count_arr] = (DataIn.Data[3] & 0xff);
        count_arr += 1;
        DataOut[count_arr] = (DataIn.Data[4] & 0xff);
        count_arr += 1;
        DataOut[count_arr] = (DataIn.Data[5] & 0xff);
        count_arr += 1;
        DataOut[count_arr] = (DataIn.Data[6] & 0xff);
        count_arr += 1;
        DataOut[count_arr] = (DataIn.Data[7] & 0xff);
        count_arr += 1;
        DataOut[count_arr] = (DataIn.Data[8] & 0xff);
        count_arr += 1;
        
        flag_answer_data = 0;
    }
    
    /*Copy từ mảng arr_temp ra mảng DataOut*/
    for (count_arr = count_arr; count_arr < (LENGTH_DEFAULT + DataIn.LengthData); count_arr++)
    {
        DataOut[count_arr] = arr_temp[count_arr];
    }
    
    /*tính toán checksum, length = LENGTH_DEFAULT(4byte) + DataIn.LengthData(tính theo bên trên)*/
    DataIn.CheckFrame = CheckSum(DataOut, (LENGTH_DEFAULT + DataIn.LengthData));
    /*Ghi giá trị checksum tính được vào cuối mảng*/
    DataOut[count_arr] = (DataIn.CheckFrame & 0xff);
    DataOut[count_arr + 1] = ((DataIn.CheckFrame >> 8) & 0xff);

    /*tăng giá trị mảng lên 2 lần vì đã thêm ở trên*/
    count_arr += 2;
    return count_arr;
}


/*----------------------------------------------chuyển data của arr sang data của struct-----------------------------------------*/

uint8_t SEC_Message_Detect_Frame(uint8_t *DataIn, sec_FrameMsg_t *DataOut)
{
    uint8_t temp = 0;

    DataOut->StartFrame  = Sec_Convert_From_Bytes_To_Uint16(DataIn[temp], DataIn[temp+1]); // truyền 2 byte
    temp += 2;
    DataOut->TypeMessage = DataIn[temp];
    temp += 1;
    DataOut->PortNumber  = DataIn[temp];
    temp += 1;
    DataOut->LengthData  = Sec_Convert_From_Bytes_To_Uint16(DataIn[temp], DataIn[temp+1]);
    temp += 2;
    DataOut->CheckFrame  = Sec_Convert_From_Bytes_To_Uint16(DataIn[temp], DataIn[temp+1]);

    return 0;
}

/*-------------------------------------------------------------------------------------------------------------------------------*/
uint16_t CheckSum(uint8_t *buf, uint8_t len)
{
    uint16_t crc = 0xFFFF, pos = 0, i = 0;
    for (pos = 0; pos < len; pos++)
    {
        crc ^= (uint16_t)buf[pos]; // XOR byte into least sig. byte of crc
        for (i = 8; i != 0; i--)   // Loop over each bit
        {
            if ((crc & 0x0001) != 0) // If the LSB is set
            {
                crc >>= 1; // Shift right and XOR 0xA001
                crc ^= 0xA001;
            }
            else // Else LSB is not set
            {
                crc >>= 1; // Just shift right
            }
        }
    }
    return crc;
}