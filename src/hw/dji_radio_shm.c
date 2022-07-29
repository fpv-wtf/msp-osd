#include "dji_radio_shm.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

void open_dji_radio_shm(dji_shm_state_t *shm) {
    int fd = open("/dev/mem", O_RDONLY);
    shm->mapped_address = mmap(NULL, RTOS_SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, RTOS_SHM_ADDRESS);
    close(fd);
    shm->modem_info = (modem_shmem_info_t *)((uint8_t *)shm->mapped_address + 0x100);
    shm->product_info = (product_shm_info_t *)((uint8_t *)shm->mapped_address + 0xC0);
}

void close_dji_radio_shm(dji_shm_state_t *shm) {
    munmap(shm->mapped_address, RTOS_SHM_SIZE);
    shm->mapped_address = NULL;
    shm->modem_info = NULL;
    shm->product_info = NULL;
}

uint16_t dji_radio_latency_ms(dji_shm_state_t *shm) {
    return shm->product_info->frame_delay_e2e;
}

float dji_radio_mbits(dji_shm_state_t *shm) {
    return (float)((double)(uint16_t)shm->modem_info->channel_status + 50.0f);
}