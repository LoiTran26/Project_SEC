#ifndef SEC_MESSAGE_H
#define SEC_MESSAGE_H


#include "stdint.h"


#define START_BYTE 0xAA55
#define LENGTH_DEFAULT 4 /*StartFrame 2 + TypeMessage 1 + PortNumber 1*/
#define LENGTH_SENSOR_ANSWERTYPE 3 /*Data[0] = TypeSensor 1 + CheckFame 2*/
#define LENGTH_SENSOR_ANSWERDATA 3 /*Data[0] = TypeSensor 1 + CheckFame 2*/

#define LENGTH_SENSOR_NTC 4


typedef enum
{
    TYPE_MESSAGE_ASK_TYPE         = 1,
    TYPE_MESSAGE_ANSWER_TYPE      = 2,
    TYPE_MESSAGE_ASK_DATA         = 3,
    TYPE_MESSAGE_ANSWER_DATA      = 4,
}type_message_e;

typedef enum
{
    PORT_NUMBER_1 = 1,
    PORT_NUMBER_2,
    PORT_NUMBER_3,
    PORT_NUMBER_4,
    PORT_NUMBER_5,
    PORT_NUMBER_6,
}port_number_list_e;

#define SENSOR_LIST_SIZE 6 /*độ dài phần tử có trong sensor_list_e */
typedef enum
{
    SENSOR_SHT30 = 1,
    SENSOR_NTC,
    SENSOR_3,
    SENSOR_4,
    SENSOR_5,
    SENSOR_6,
}sensor_list_e;

/* Bản tin cập nhật cảm biến */
typedef struct
{
    uint16_t StartFrame;
    uint8_t  TypeMessage;
    uint8_t  PortNumber;
    uint16_t LengthData; 
    uint8_t  Data[16];
    uint16_t CheckFrame;
}sec_FrameMsg_t;


/*
    @brief: Hàm tạo Frame data chuẩn.
    @node: Chức năng chính của hàm để tạo các bản tin AskType, AswerType, AskData, AnswerData
    @param datain: Là một struct chưa các thông tin được người dùng chỉ định để tạo bản tin.
    @param dataout: Là con trỏ dùng để lấy mảng sao khi tạo thành công.
    @retval: Trả về 0 là lỗi, Lớn hơn 0 là thành công.
*/
uint8_t SEC_Message_Create_Frame(sec_FrameMsg_t DataIn, uint8_t *DataOut);

/*
    @brief: Hàm tách Frame data.
    @node: Chức năng của hàm là chuyển data từ dạng arr về dạng struct.
    @param datain: Là một mảng chứa data.
    @param dataout: Là một struct chứa data đầu ra.
    @retval: trả về 1 thành công, trả về 0 là lỗi.
*/
uint8_t SEC_Message_Detect_Frame(uint8_t *DataIn, sec_FrameMsg_t *DataOut);

/* ham tinh checksum */
uint16_t CheckSum(uint8_t *buf, uint8_t len);

#endif // SEC_MESSAGE_H
