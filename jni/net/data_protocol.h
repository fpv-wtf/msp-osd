#include <stdint.h>

typedef struct packet_data_s {
    uint16_t tx_temperature;
    uint16_t version_specifier; // Used to be bitrate! Danger! 0xFFFF means V2 (no bitrate) for now.
    uint16_t tx_voltage;
    char fc_variant[4];
} __attribute__((packed)) packet_data_t;