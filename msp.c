#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "msp.h"

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
                msp_msg_t *msg_copy = malloc(sizeof(msp_msg_t));
                memcpy(msg_copy, &msp_state->message, sizeof(msp_msg_t));
                if (msp_state->cb != 0)
                {
                    msp_state->cb(msg_copy);
                }
                free(msg_copy);
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
    return 0;
}