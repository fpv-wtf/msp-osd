#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "msp.h"

uint8_t crc8_dvb_s2(uint8_t crc, unsigned char a)
{
    crc ^= a;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0xD5;
        } else {
            crc = crc << 1;
        }
    }
    return crc;
}

uint16_t msp_data_from_msg(uint8_t message_buffer[], msp_msg_t *msg) {
    // return size
    construct_msp_command(message_buffer, msg->cmd, msg->payload, msg->size, msg->direction);
    return msg->size + 6;
}

msp_error_e construct_msp_command(uint8_t message_buffer[], uint16_t command, uint8_t payload[], uint16_t size, msp_direction_e direction) {
    if(command < 0xF && size < 0xf)
    {
        return construct_msp_command_v1(message_buffer, (uint8_t)command, payload, (uint8_t)size, direction);
    }

    return construct_msp_command_v2(message_buffer, command, payload, size, direction);
}

msp_error_e construct_msp_command_v1(uint8_t message_buffer[], uint8_t command, uint8_t payload[], uint8_t size, msp_direction_e direction) {
    uint8_t checksum;
    message_buffer[0] = '$'; // Header
    message_buffer[1] = MSP_V1; // MSP V1
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

msp_error_e construct_msp_command_v2(uint8_t message_buffer[], uint16_t command, uint8_t payload[], uint16_t size, msp_direction_e direction) {
    uint8_t checksum;
    int off = 0;
    message_buffer[off++] = '$'; // 0: Header0
    message_buffer[off++] = MSP_V2; // 1: MSP V2
    if (direction == MSP_OUTBOUND) {
        message_buffer[off++] = '<'; // 2: direction
    } else {
        message_buffer[off++] = '>'; // 2: direction
    }
    message_buffer[off++] = 0; // 3: flag
    checksum = crc8_dvb_s2(0, message_buffer[off]);

    message_buffer[off++] = (0xf & command); // 4: cmd low
    checksum = crc8_dvb_s2(0, message_buffer[off]);
    message_buffer[off++] = (0xf & (command>>8)); // 5: cmd high
    checksum = crc8_dvb_s2(0, message_buffer[off]);

    message_buffer[off++] = (0xf & size); // 6: size low
    checksum = crc8_dvb_s2(0, message_buffer[off]);
    message_buffer[off++] = (0xf & (size>>8)); // 7: size high
    checksum = crc8_dvb_s2(0, message_buffer[off]);

    for(uint16_t i = 0; i < size; i++) {
        message_buffer[off+ i] = payload[i];
        checksum = crc8_dvb_s2(0, message_buffer[off + i]);
    }
    message_buffer[off + size] = checksum;
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
            switch(dat)
            {
            case MSP_V1:
                msp_state->state = MSP_DIRECTION;
                msp_state->version = dat;
                break;
            case MSP_V2:
                msp_state->state = MSP_DIRECTION;
                msp_state->version = dat;
                break;
            default:
                // Got garbage instead, try again
                msp_state->state = MSP_IDLE;
                return MSP_ERR_HDR;
            }
            break;
        case MSP_DIRECTION: // < for command, > for reply
            msp_state->state = msp_state->version == MSP_V1 ? MSP_SIZE : MSP_FLAG_V2; // this is where v1 diverts from v2
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

            // MSP_V2
            case MSP_FLAG_V2: // CRC
                if(dat != 0) {
                    msp_state->state = MSP_IDLE;
                    return MSP_ERR_HDR;
                }
                msp_state->message.checksum = crc8_dvb_s2(0, dat);
                msp_state->state = MSP_CMD_L_V2;
                break;
            case MSP_CMD_L_V2: // CRC
                msp_state->message.cmd = dat;
                msp_state->message.checksum = crc8_dvb_s2(msp_state->message.checksum, dat);
                msp_state->state = MSP_CMD_H_V2;
                break;
            case MSP_CMD_H_V2: // CRC
                msp_state->message.cmd |= (dat << 8);
                msp_state->message.checksum = crc8_dvb_s2(msp_state->message.checksum, dat);
                msp_state->state = MSP_SIZE_L_V2;
                break;
            case MSP_SIZE_L_V2: // CRC
                msp_state->message.size = dat;
                msp_state->message.checksum = crc8_dvb_s2(msp_state->message.checksum, dat);
                msp_state->state = MSP_SIZE_H_V2;
                break;
            case MSP_SIZE_H_V2: // CRC
                msp_state->message.size |= (dat << 8);
                if(msp_state->message.size > MSP_V2_MAX_PAYLOAD) {
                    msp_state->state = MSP_IDLE;
                    return MSP_ERR_HDR;
                }
                msp_state->message.checksum = crc8_dvb_s2(msp_state->message.checksum, dat);
                msp_state->state = msp_state->message.size > 0 ? MSP_PAYLOAD_V2 : MSP_CHECKSUM;
                break;
         case MSP_PAYLOAD_V2: // if we had a payload, keep going
            msp_state->message.payload[msp_state->buf_ptr] = dat;
            msp_state->message.checksum = crc8_dvb_s2(msp_state->message.checksum, dat);
            msp_state->buf_ptr++;
            if (msp_state->buf_ptr == msp_state->message.size)
            {
                msp_state->buf_ptr = 0;
                msp_state->state = MSP_CHECKSUM;
            }
            break;
    }
    return MSP_ERR_NONE;
}