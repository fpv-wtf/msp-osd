#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "dji_radio_shm.h"

void open_dji_radio_shm(dji_shm_state_t *shm) {
    int fd = open("/dev/mem", O_RDWR);
    assert(fd > 0);
    shm->mapped_address = mmap64(NULL, RTOS_SHM_SIZE, PROT_READ, MAP_SHARED, fd, RTOS_SHM_ADDRESS);
    assert(shm->mapped_address != MAP_FAILED);
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

uint16_t dji_radio_mbits(dji_shm_state_t *shm) {
    return shm->modem_info->channel_status;
}

uint32_t frm_idx(dji_shm_state_t *shm) {
    return shm->modem_info->frm_idx;
}
uint16_t frm_isI(dji_shm_state_t *shm) {
    return shm->modem_info->frm_isI;
}
uint16_t frm_len(dji_shm_state_t *shm) {
    return shm->modem_info->frm_len;
}
uint16_t frm_dsti(dji_shm_state_t *shm) {
    return shm->modem_info->frm_dsti;
}
uint16_t frm_dstf(dji_shm_state_t *shm) {
    return shm->modem_info->frm_dstf;
}
uint16_t channel_status(dji_shm_state_t *shm) {
    return shm->modem_info->channel_status;
}
uint16_t dec_err_status(dji_shm_state_t *shm) {
    return shm->modem_info->dec_err_status;
}
uint16_t cur_time(dji_shm_state_t *shm) {
    return shm->modem_info->cur_time;
}
uint16_t delta_time(dji_shm_state_t *shm) {
    return shm->modem_info->delta_time;
}
uint16_t dbg_msc(dji_shm_state_t *shm) {
    return shm->modem_info->dbg_msc;
}
uint8_t dbg_ap_ready(dji_shm_state_t *shm) {
    return shm->modem_info->dbg_ap_ready;
}
uint8_t dbg_cp_ready(dji_shm_state_t *shm) {
    return shm->modem_info->dbg_cp_ready;
}
uint32_t local_id(dji_shm_state_t *shm) {
    return shm->modem_info->local_id;
}
uint8_t cp_state(dji_shm_state_t *shm) {
    return shm->modem_info->cp_state;
}
uint8_t cp_report(dji_shm_state_t *shm) {
    return shm->modem_info->cp_report;
}
uint8_t cp_report_seq(dji_shm_state_t *shm) {
    return shm->modem_info->cp_report_seq;
}
uint8_t client_type(dji_shm_state_t *shm) {
    return shm->modem_info->cp_report_seq;
}
uint32_t cp_boot_status0(dji_shm_state_t *shm) {
    return shm->modem_info->cp_boot_status0;
}
uint32_t cp_boot_status1(dji_shm_state_t *shm) {
    return shm->modem_info->cp_boot_status1;
}
uint32_t board_version(dji_shm_state_t *shm) {
    return shm->modem_info->board_version;
}
uint32_t board_sub_version(dji_shm_state_t *shm) {
    return shm->modem_info->board_sub_version;
}
uint8_t machine_role(dji_shm_state_t *shm) {
    return shm->modem_info->machine_role;
}
uint8_t is_reverse(dji_shm_state_t *shm) {
    return shm->modem_info->is_reverse;
}
uint8_t cp_tx_power(dji_shm_state_t *shm) {
    return shm->modem_info->cp_tx_power;
}
uint8_t gnd_type(dji_shm_state_t *shm) {
    return shm->modem_info->gnd_type;
}
uint32_t cp_sssfn(dji_shm_state_t *shm) {
    return shm->modem_info->cp_sssfn;
}
uint32_t ulow_en(dji_shm_state_t *shm) {
    return shm->modem_info->ulow_en;
}
uint8_t mipi_rx_response(dji_shm_state_t *shm) {
    return shm->modem_info->mipi_rx_response;
}
uint8_t liveview_broken_status(dji_shm_state_t *shm) {
    return shm->modem_info->liveview_broken_status;
}
uint8_t reserved01(dji_shm_state_t *shm) {
    return shm->modem_info->reserved01;
}
uint8_t reserved02(dji_shm_state_t *shm) {
    return shm->modem_info->reserved02;
}
uint8_t ap_reboot_flag(dji_shm_state_t *shm) {
    return shm->modem_info->ap_reboot_flag;
}
uint8_t ap_reboot_ack_flag(dji_shm_state_t *shm) {
    return shm->modem_info->ap_reboot_ack_flag;
}
uint8_t secure_sync_flag(dji_shm_state_t *shm) {
    return shm->modem_info->secure_sync_flag;
}
uint8_t reserve00(dji_shm_state_t *shm) {
    return shm->modem_info->reserve00;
}
uint8_t area_state(dji_shm_state_t *shm) {
    return shm->modem_info->area_state;
}
uint8_t area_substate(dji_shm_state_t *shm) {
    return shm->modem_info->area_substate;
}
uint8_t GsCtrl(dji_shm_state_t *shm) {
    return shm->modem_info->GsCtrl;
}
uint8_t GsSubState(dji_shm_state_t *shm) {
    return shm->modem_info->GsSubState;
}
uint32_t com_uart_status(dji_shm_state_t *shm) {
    return shm->modem_info->com_uart_status;
}
uint32_t fcr_rx_status(dji_shm_state_t *shm) {
    return shm->modem_info->fcr_rx_status;
}
uint32_t fcr_tx_status(dji_shm_state_t *shm) {
    return shm->modem_info->fcr_tx_status;
}
uint32_t frm_idx_for_display(dji_shm_state_t *shm) {
    return shm->modem_info->frm_idx_for_display;
}
uint32_t frm_delay_for_display(dji_shm_state_t *shm) {
    return shm->modem_info->frm_delay_for_display;
}
uint16_t wifi_sdr_mode(dji_shm_state_t *shm) {
    return shm->modem_info->wifi_sdr_mode;
}
uint16_t frm_isI_for_display(dji_shm_state_t *shm) {
    return shm->modem_info->frm_isI_for_display;
}
uint32_t country_code(dji_shm_state_t *shm) {
    return shm->modem_info->country_code;
}
uint16_t frm_len_for_display(dji_shm_state_t *shm) {
    return shm->modem_info->frm_len_for_display;
}
uint16_t delta_time_for_display(dji_shm_state_t *shm) {
    return shm->modem_info->delta_time_for_display;
}
uint8_t uint8_t_reboot_reason(dji_shm_state_t *shm) {
    return shm->modem_info->uint8_t_reboot_reason;
}
uint8_t field_0x85(dji_shm_state_t *shm) {
    return shm->modem_info->field_0x85;
}
uint8_t field_0x86(dji_shm_state_t *shm) {
    return shm->modem_info->field_0x86;
}
uint8_t field_0x87(dji_shm_state_t *shm) {
    return shm->modem_info->field_0x87;
}
uint64_t cpa7_version(dji_shm_state_t *shm) {
    return shm->modem_info->cpa7_version;
}
uint64_t dsp_version(dji_shm_state_t *shm) {
    return shm->modem_info->dsp_version;
}
uint8_t u8_dual_band_capability(dji_shm_state_t *shm) {
    return shm->modem_info->u8_dual_band_capability;
}

uint16_t frm_width(dji_shm_state_t *shm) {
    return shm->product_info->frm_width;
}
uint16_t frm_height(dji_shm_state_t *shm) {
    return shm->product_info->frm_height;
}
uint8_t fps(dji_shm_state_t *shm) {
    return shm->product_info->fps;
}
uint8_t enc_strategy(dji_shm_state_t *shm) {
    return shm->product_info->enc_strategy;
}
uint16_t lcdc_underflow_cnt(dji_shm_state_t *shm) {
    return shm->product_info->lcdc_underflow_cnt;
}
uint32_t enc_sto_frm_dropped(dji_shm_state_t *shm) {
    return shm->product_info->enc_sto_frm_dropped;
}
uint32_t enc_lv_frm_dropped(dji_shm_state_t *shm) {
    return shm->product_info->enc_lv_frm_dropped;
}
uint32_t mipi_csi_frm_dropped(dji_shm_state_t *shm) {
    return shm->product_info->mipi_csi_frm_dropped;
}
uint32_t display_frm_dropped(dji_shm_state_t *shm) {
    return shm->product_info->display_frm_dropped;
}
uint64_t audio_pts(dji_shm_state_t *shm) {
    return shm->product_info->audio_pts;
}
uint32_t local_fps_num(dji_shm_state_t *shm) {
    return shm->product_info->local_fps_num;
}
uint32_t local_fps_den(dji_shm_state_t *shm) {
    return shm->product_info->local_fps_den;
}
uint16_t frame_delay_e2e(dji_shm_state_t *shm) {
    return shm->product_info->frame_delay_e2e;
}
uint16_t cam_frame_interval(dji_shm_state_t *shm) {
    return shm->product_info->cam_frame_interval;
}
uint16_t outliner_frame_interval(dji_shm_state_t *shm) {
    return shm->product_info->outliner_frame_interval;
}
uint16_t outliner_frame_interval_cnt(dji_shm_state_t *shm) {
    return shm->product_info->outliner_frame_interval_cnt;
}
uint16_t max_frame_delay_e2e(dji_shm_state_t *shm) {
    return shm->product_info->max_frame_delay_e2e;
}
uint16_t min_frame_delay_e2e(dji_shm_state_t *shm) {
    return shm->product_info->min_frame_delay_e2e;
}
uint16_t avg_frame_delay_e2e(dji_shm_state_t *shm) {
    return shm->product_info->avg_frame_delay_e2e;
}
uint16_t if_switch(dji_shm_state_t *shm) {
    return shm->product_info->if_switch;
}
uint8_t if_change_pipe(dji_shm_state_t *shm) {
    return shm->product_info->if_change_pipe;
}
uint8_t if_pb_pause(dji_shm_state_t *shm) {
    return shm->product_info->if_pb_pause;
}
uint8_t liveview_pipeline_running(dji_shm_state_t *shm) {
    return shm->product_info->liveview_pipeline_running;
}
uint8_t avIn_pipeline_running(dji_shm_state_t *shm) {
    return shm->product_info->avIn_pipeline_running;
}
uint8_t avIn_stream_type(dji_shm_state_t *shm) {
    return shm->product_info->avIn_stream_type;
}
uint8_t pb_flush(dji_shm_state_t *shm) {
    return shm->product_info->pb_flush;
}
uint8_t disp_pannel_need_reset(dji_shm_state_t *shm) {
    return shm->product_info->disp_pannel_need_reset;
}
uint8_t pad(dji_shm_state_t *shm) {
    return shm->product_info->pad;
}