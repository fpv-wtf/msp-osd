#include <stdint.h>

typedef struct packet_data_s {
    uint16_t tx_temperature;
    uint16_t version_specifier; // Used to be bitrate! Danger! 0xFFFF means V2 (no bitrate) for now.
    uint16_t tx_voltage;
    int8_t fc_vtx_channel;
    char fc_variant[4];
} __attribute__((packed)) packet_data_t;

typedef struct compressed_data_header_s {
    uint16_t version;
    uint16_t hd_options;
} __attribute__((packed)) compressed_data_header_t;