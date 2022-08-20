#include <stdint.h>

typedef struct packet_data_s {
    uint16_t tx_temperature;
    uint16_t tx_bitrate;
    uint16_t tx_voltage;
} __attribute__((packed)) packet_data_t;