#include "sec_message.h"


/*mảng này dùng để kiểm tra xem sensor chọn là loại nào*/
static sensor_list_e sensor_list_arr[SENSOR_LIST_SIZE] = {SENSOR_SHT30, SENSOR_NTC, SENSOR_3, SENSOR_4, SENSOR_5, SENSOR_6};
/*mảng này để biết data chiếm bao nhiêu byte để thực hiện cộng với length*/
static uint8_t length_sensor_arr[SENSOR_LIST_SIZE] = {4, 4, 4, 4, 4, 4};

/*-------------------------------------------------------------------------------------------------------------------------------*/
uint16_t CheckSum(uint8_t *buf, uint8_t len);


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

    switch (DataIn.TypeMessage)
    {
        case TYPE_MESSAGE_ASK_TYPE:
            DataIn.LengthData = LENGTH_SENSOR_ASKTYPE;
        break;

        case TYPE_MESSAGE_ANSWER_TYPE:
            DataIn.LengthData = LENGTH_SENSOR_ANSWERTYPE;
        break;

        case TYPE_MESSAGE_ASK_DATA:
            DataIn.LengthData = LENGTH_SENSOR_ASKDATA;
        break;

        case TYPE_MESSAGE_ANSWER_DATA:
            for (count_arr = 0; count_arr < SENSOR_LIST_SIZE; count_arr++)
            {
                if (DataIn.Data[0] == sensor_list_arr[count_arr])
                {
                    DataIn.LengthData = LENGTH_SENSOR_ANSWERDATA + length_sensor_arr[count_arr];
                }
            }
        break;
    }

    /*tính toán checksum, length = LENGTH_DEFAULT(4byte) + DataIn.LengthData(tính theo bên trên)*/
    DataIn.CheckFrame = CheckSum(arr_temp, (LENGTH_DEFAULT + DataIn.LengthData));

    /*Copy từ mảng arr_temp ra mảng DataOut*/
    for (count_arr = 0; count_arr < (LENGTH_DEFAULT + DataIn.LengthData); count_arr++)
    {
        DataOut[count_arr] = arr_temp[count_arr];
    }

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
    sec_FrameMsg_t *temp_datain;
    uint8_t temp = 0;

    /* ép kiểu uint8_t về kiểu temp_datain, mục đích để chuyển từ arr* -> struct* */
    temp_datain = (sec_FrameMsg_t *)DataIn;

    DataOut->StartFrame  = Sec_Convert_From_Bytes_To_Uint16(DataIn[temp], DataIn[temp+1]); // truyền 2 byte
    temp += 2;
    DataOut->TypeMessage = DataIn[temp];
    temp += 1;
    DataOut->PortNumber  = DataIn[temp];
    temp += 1;
    DataOut->LengthData  = Sec_Convert_From_Bytes_To_Uint16(DataIn[temp], DataIn[temp+1]);
    temp += 2;

    switch (DataOut->TypeMessage)
    {
        case TYPE_MESSAGE_ANSWER_TYPE:
            DataOut->Data[0] = DataIn[temp++]; // TypeSensor
        break;

        case TYPE_MESSAGE_ANSWER_DATA:
            DataOut->Data[0] = DataIn[temp++]; // TypeSensor

            switch (DataOut->Data[0])
            {
                case SENSOR_SHT30:
                    DataOut->Data[1] = DataIn[temp++];
					DataOut->Data[2] = DataIn[temp++];
					DataOut->Data[3] = DataIn[temp++];
					DataOut->Data[4] = DataIn[temp++];
				
					DataOut->Data[5] = DataIn[temp++];
					DataOut->Data[6] = DataIn[temp++];
					DataOut->Data[7] = DataIn[temp++];
					DataOut->Data[8] = DataIn[temp++];
                break;
            
                case SENSOR_NTC:
                    temp = SEC_Data_Sensor(DataIn, DataOut, temp);
                break;

                case SENSOR_3:
                    temp = SEC_Data_Sensor(DataIn, DataOut, temp);
                break;

                case SENSOR_4:
                    temp = SEC_Data_Sensor(DataIn, DataOut, temp);
                break;

                case SENSOR_5:
                    temp = SEC_Data_Sensor(DataIn, DataOut, temp);
                break;

                case SENSOR_6:
                    temp = SEC_Data_Sensor(DataIn, DataOut, temp);
                break;
            }

        break;
    }

    DataOut->CheckFrame  = Sec_Convert_From_Bytes_To_Uint16(DataIn[temp], DataIn[temp+1]);

    return 0;
}


/*-------------------------------------------------------------------------------------------------------------------------------*/
uint8_t SEC_Data_Sensor(uint8_t *DataIn, sec_FrameMsg_t *DataOut, uint8_t temp)
{
    DataOut->Data[1] = DataIn[temp++];
    DataOut->Data[2] = DataIn[temp++];
    DataOut->Data[3] = DataIn[temp++];
    DataOut->Data[4] = DataIn[temp++];

    return temp;
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