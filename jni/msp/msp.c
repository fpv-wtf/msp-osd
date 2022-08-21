#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "msp.h"

uint16_t msp_data_from_msg(uint8_t message_buffer[], msp_msg_t *msg) {
    // return size
    construct_msp_command(message_buffer, msg->cmd, msg->payload, msg->size, msg->direction);
    return msg->size + 6;
}

msp_error_e construct_msp_command(uint8_t message_buffer[], uint8_t command, uint8_t payload[], uint8_t size, msp_direction_e direction) {
    uint8_t checksum;
    message_buffer[0] = '$'; // Header
    message_buffer[1] = 'M'; // MSP V1
    if (direction == MSP_OUTBOUND) {
        message_buffer[2] = '<';
    } else {
        message_buffer[2] = '>';
    }
    message_buffer[3] = size; // Payload Size
    checksum = size;
    message_buffer[4] = command; // Command
    checksum ^= command;
    for(uint8_t i = 0; i < size; i++) {
        message_buffer[5 + i] = payload[i];
        checksum ^= message_buffer[5 + i];
    }
    message_buffer[5 + size] = checksum;
    return 0;
}

msp_error_e msp_process_data(msp_state_t *msp_state, uint8_t dat)
{
    switch (msp_state->state)
    {
        default:
        case MSP_IDLE: // look for begin
            if (dat == '$')
            {
                msp_state->state = MSP_VERSION;
            }
            else
            {
                return MSP_ERR_HDR;
            }
            break;
        case MSP_VERSION: // Look for 'M' (MSP V1, we do not support V2 at this time)
            if (dat == 'M')
            {
                msp_state->state = MSP_DIRECTION;
            }
            else
            { // Got garbage instead, try again
                msp_state->state = MSP_IDLE;
                return MSP_ERR_HDR;
            }
            break;
        case MSP_DIRECTION: // < for command, > for reply
            msp_state->state = MSP_SIZE;
            switch (dat)
            {
            case '<':
                msp_state->message.direction = MSP_OUTBOUND;
                break;
            case '>':
                msp_state->message.direction = MSP_INBOUND;
                break;
            default: // garbage, try again
                msp_state->state = MSP_IDLE;
                return MSP_ERR_HDR;
                break;
            }
            break;
        case MSP_SIZE: // next up is supposed to be size
            msp_state->message.checksum = dat;
            msp_state->message.size = dat;
            msp_state->state = MSP_CMD;
            if (msp_state->message.size > 256)
            { // bogus message, too big. this can't actually happen but good to check
                msp_state->state = MSP_IDLE;
                return MSP_ERR_LEN;
                break;
            }
            break;
        case MSP_CMD: // followed by command
            msp_state->message.cmd = dat;
            msp_state->message.checksum ^= dat;
            msp_state->buf_ptr = 0;
            if (msp_state->message.size > 0)
            {
                msp_state->state = MSP_PAYLOAD;
            }
            else
            {
                msp_state->state = MSP_CHECKSUM;
            }
            break;
        case MSP_PAYLOAD: // if we had a payload, keep going
            msp_state->message.payload[msp_state->buf_ptr] = dat;
            msp_state->message.checksum ^= dat;
            msp_state->buf_ptr++;
            if (msp_state->buf_ptr == msp_state->message.size)
            {
                msp_state->buf_ptr = 0;
                msp_state->state = MSP_CHECKSUM;
            }
            break;
        case MSP_CHECKSUM:
            if (msp_state->message.checksum == dat)
            {
                if (msp_state->cb != 0)
                {
                    msp_state->cb(&msp_state->message);
                }
                memset(&msp_state->message, 0, sizeof(msp_msg_t));
                msp_state->state = MSP_IDLE;
                break;            
            }
            else
            {
                msp_state->state = MSP_IDLE;
                return MSP_ERR_CKS;
            }
            break;
    }
    return MSP_ERR_NONE;
}