#include "sec_fsm.h"
#include "sec_sys.h"


sec_FrameMsg_t data_in;
Sec_ValueAll_t sec_vrAll_fsm_t;
fsm_state_e fsm_state = FSM_STATE_START_FRAME;

static uint16_t TimeOut_Fsm = 0;
static uint8_t Flag_TimeOut_Fsm = 0;
static uint16_t CheckFrame_Receive;


void SEC_TimeOut_Fsm(void)
{
    if(Flag_TimeOut_Fsm == 1)
    {
        if(TimeOut_Fsm == FSM_TIMEOUT)
        {
			printf("101\n");
            SEC_Clear_TimeOut_Fsm();
        }
        TimeOut_Fsm++;
    }
}

void SEC_Clear_TimeOut_Fsm(void)
{
    Flag_TimeOut_Fsm = 0;
    sec_vrAll_fsm_t.fsm_count_array = 0;
    fsm_state = FSM_STATE_START_FRAME;
}

void Fsm_Receive_Message(uint8_t temp_data)
{
	Flag_TimeOut_Fsm  = 1;
    TimeOut_Fsm = 0;
	
	switch (fsm_state)
    {
        case FSM_STATE_START_FRAME:
            sec_vrAll_fsm_t.array_out[sec_vrAll_fsm_t.fsm_count_array] = temp_data;
            sec_vrAll_fsm_t.fsm_count_array++;

            if (sec_vrAll_fsm_t.fsm_count_array == FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE)
            {
                data_in.StartFrame = Sec_Convert_From_Bytes_To_Uint16(sec_vrAll_fsm_t.array_out[0], sec_vrAll_fsm_t.array_out[1]);
                if(data_in.StartFrame == START_BYTE)
                {
                    fsm_state = FSM_STATE_TYPE_MESSAGE;
                }
                else
                {
                    sec_vrAll_fsm_t.fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_TYPE_MESSAGE:
            sec_vrAll_fsm_t.array_out[sec_vrAll_fsm_t.fsm_count_array] = temp_data;
            sec_vrAll_fsm_t.fsm_count_array++;

            if (sec_vrAll_fsm_t.fsm_count_array == FSM_STATE_CHANGE_VALUE_PORT_NUMBER)
            {
                if(sec_vrAll_fsm_t.array_out[2] <= 4)
                {
                    fsm_state = FSM_STATE_PORT_NUMBER;
                }
                else
                {
                    sec_vrAll_fsm_t.fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_PORT_NUMBER:
            sec_vrAll_fsm_t.array_out[sec_vrAll_fsm_t.fsm_count_array] = temp_data;
            sec_vrAll_fsm_t.fsm_count_array++;
            if (sec_vrAll_fsm_t.fsm_count_array == FSM_STATE_CHANGE_VALUE_LENGHT_DATA)
            {
                if(sec_vrAll_fsm_t.array_out[3] <= 6)
                {
                    fsm_state = FSM_STATE_LENGHT_DATA;
                }
                else
                {
                    sec_vrAll_fsm_t.fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_LENGHT_DATA:
            sec_vrAll_fsm_t.array_out[sec_vrAll_fsm_t.fsm_count_array] = temp_data;
            sec_vrAll_fsm_t.fsm_count_array++;

            if (sec_vrAll_fsm_t.fsm_count_array == FSM_STATE_CHANGE_VALUE_END)
            {
                sec_vrAll_fsm_t.fsm_data_length = ((sec_vrAll_fsm_t.array_out[5] << 8) | sec_vrAll_fsm_t.array_out[4]) + 6;

                if (sec_vrAll_fsm_t.fsm_data_length < 24)
                { 
                    fsm_state = FSM_STATE_END;
                }
                else if (sec_vrAll_fsm_t.fsm_data_length > 24)
                {
                    sec_vrAll_fsm_t.fsm_count_array = 0;
                    fsm_state = FSM_STATE_START_FRAME;
                }
            }
        break;

        case FSM_STATE_END:
            sec_vrAll_fsm_t.array_out[sec_vrAll_fsm_t.fsm_count_array] = temp_data;
            sec_vrAll_fsm_t.fsm_count_array++;

            if (sec_vrAll_fsm_t.fsm_count_array == sec_vrAll_fsm_t.fsm_data_length)
            {
				data_in.CheckFrame = CheckSum(sec_vrAll_fsm_t.array_out, sec_vrAll_fsm_t.fsm_data_length - 2);
                CheckFrame_Receive = Sec_Convert_From_Bytes_To_Uint16(sec_vrAll_fsm_t.array_out[sec_vrAll_fsm_t.fsm_count_array-2], sec_vrAll_fsm_t.array_out[sec_vrAll_fsm_t.fsm_count_array-1]);
				
                if(data_in.CheckFrame == CheckFrame_Receive)
                {
                    SEC_Clear_TimeOut_Fsm();
                    sec_vrAll_fsm_t.Flag_fsm_True = 1;
                }
                else
                {
                    SEC_Clear_TimeOut_Fsm();
                    sec_vrAll_fsm_t.Flag_fsm_True = 0;
                }
            }
        break;
    }
	
	sec_vrAll_fsm_t.Flag_Fsm = 1;
}