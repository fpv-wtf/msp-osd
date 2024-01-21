#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "msp.h"

static uint8_t message_buffer[256];

uint8_t total_bands = 1;
uint8_t total_channels = 8;
uint8_t total_powers = 6;

uint8_t * resetVTXTableMessage() {
  uint8_t payload_size = 15;
  uint8_t default_table[15] = {
    0, // idx LSB
    0, // idx MSB
    0, // 25mW Power idx
    0, // pitmode
    0, // lowPowerDisarm
    0, // pitModeFreq LSB
    0, // pitModeFreq MSB
    0, // band
    0, // channel
    0, // newFreq  LSB
    0, // newFreq  MSB
    total_bands, // bandCount,
    total_channels, // channelCount
    total_powers, // powerCount
    1  // vtxtable should be cleared
  };

  construct_msp_command(message_buffer, MSP_CMD_SET_VTX_CONFIG, default_table, payload_size, MSP_OUTBOUND);

  return message_buffer;
}

uint8_t * setupVTXPowerMessage(int index, int value, char name[]) {
  uint8_t name_size = strlen(name);
  uint8_t payload_size = 4 + name_size;
  uint8_t vtx_power[4 + 3] = {
    index, // idx
    value & 0xFF, // powerValue LSB
    (value >> 8) & 0xFF, // powerValue MSB
    strlen(name), // label lenght
  };

  for(int i = 0; i < strlen(name); i++) {
    vtx_power[i] = name[i];
  }
  /*txPacket[8] = idx;
    txPacket[9] = saPowerLevelsLut[idx - 1] & 0xFF;         // powerValue LSB
    txPacket[10] = (saPowerLevelsLut[idx - 1] >> 8) & 0xFF; // powerValue MSB
    txPacket[11] = POWER_LEVEL_LABEL_LENGTH;
    txPacket[12] = saPowerLevelsLabel[((idx - 1) * POWER_LEVEL_LABEL_LENGTH) + 0];
    txPacket[13] = saPowerLevelsLabel[((idx - 1) * POWER_LEVEL_LABEL_LENGTH) + 1];
    txPacket[14] = saPowerLevelsLabel[((idx - 1) * POWER_LEVEL_LABEL_LENGTH) + 2];*/

  construct_msp_command(message_buffer, MSP_CMD_SET_VTXTABLE_POWERLEVEL, vtx_power, payload_size, MSP_OUTBOUND);

  return message_buffer;
}

uint8_t * setupVTXBandMessage() {
  uint8_t payload_size = 8 + total_channels;
  uint8_t vtx_band[8 + 8] = {
    0, // band
    3, // label lenght
    'D',
    'J',
    'I',
    'D', // band letter
    0, // is factory band
    total_channels, // total channel
  };

  for(int i = 8; i < total_channels; i++) {
    vtx_band[i] = i & 0xFF;
    i++;
    vtx_band[i] = (i >> 8) & 0xFF;
  }

  construct_msp_command(message_buffer, MSP_CMD_SET_VTXTABLE_POWERLEVEL, vtx_band, payload_size, MSP_OUTBOUND);

  return message_buffer;
}
