#pragma once
#include <stdint.h>

#define MSP_CMD_API_VERSION 1
#define MSP_CMD_FC_VARIANT 2
#define MSP_CMD_FC_VERSION 3
#define MSP_CMD_NAME 10
#define MSP_CMD_FILTER_CONFIG 92
#define MSP_CMD_PID_ADVANCED 94
#define MSP_CMD_STATUS 101
#define MSP_CMD_RC 105
#define MSP_CMD_ATTITUDE 108
#define MSP_CMD_ANALOG 110
#define MSP_CMD_RC_TUNING 111
#define MSP_CMD_PID 112
#define MSP_CMD_BATTERY_STATE 130
#define MSP_CMD_STATUS_EX 150
#define MSP_CMD_DISPLAYPORT 182
#define MSP_CMD_SET_OSD_CANVAS 188

//#define MSP_V2_MAX_PAYLOAD  65535
#define MSP_V2_MAX_PAYLOAD  8192

typedef enum {
    MSP_ERR_NONE,
    MSP_ERR_HDR,
    MSP_ERR_LEN,
    MSP_ERR_CKS
} msp_error_e;

typedef enum {
    MSP_IDLE,
    MSP_VERSION,
    MSP_DIRECTION,
    MSP_SIZE,
    MSP_CMD,
    MSP_PAYLOAD,
    MSP_CHECKSUM,
    MSP_FLAG_V2,
    MSP_CMD_L_V2,
    MSP_CMD_H_V2,
    MSP_SIZE_L_V2,
    MSP_SIZE_H_V2,
    MSP_PAYLOAD_V2,
} msp_state_machine_e;

typedef enum {
    MSP_INBOUND,
    MSP_OUTBOUND
} msp_direction_e;

typedef enum {
    MSP_V1 = 'M',
    MSP_V2 = 'X'
} msp_version_e;

typedef struct msp_msg_s {
    uint8_t checksum;
    uint16_t cmd;
    uint16_t size;
    msp_direction_e direction;
    uint8_t payload[MSP_V2_MAX_PAYLOAD];
} msp_msg_t;

typedef void (*msp_msg_callback)(msp_msg_t *);

typedef struct msp_state_s {
    msp_msg_callback cb;
    msp_state_machine_e state;
    uint16_t buf_ptr;
    msp_msg_t message;
    msp_version_e version;
} msp_state_t;

uint16_t msp_data_from_msg(uint8_t message_buffer[], msp_msg_t *msg);
msp_error_e construct_msp_command(uint8_t message_buffer[], uint16_t command, uint8_t payload[], uint16_t size, msp_direction_e direction);
msp_error_e construct_msp_command_v1(uint8_t message_buffer[], uint8_t command, uint8_t payload[], uint8_t size, msp_direction_e direction);
msp_error_e construct_msp_command_v2(uint8_t message_buffer[], uint16_t command, uint8_t payload[], uint16_t size, msp_direction_e direction);
msp_error_e msp_process_data(msp_state_t *msp_state, uint8_t dat);