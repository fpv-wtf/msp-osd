#include <stdint.h>

#define MSP_CMD_DISPLAYPORT 182

typedef enum {
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
} msp_state_machine_e;

typedef enum {
    MSP_INBOUND,
    MSP_OUTBOUND
} msp_direction_e;

typedef struct msp_msg_s {
    uint8_t checksum;
    uint8_t cmd;
    uint8_t size;
    msp_direction_e direction;
    uint8_t payload[256];
} msp_msg_t;

typedef void (*msp_msg_callback)(msp_msg_t *);

typedef struct msp_state_s {
    msp_msg_callback cb;
    msp_state_machine_e state;
    uint8_t buf_ptr;
    msp_msg_t message;
} msp_state_t;

msp_error_e msp_process_data(msp_state_t *msp_state, uint8_t dat);