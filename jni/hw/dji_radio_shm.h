#include <stdint.h>

#define RTOS_SHM_ADDRESS 0xfffc1000
#define RTOS_SHM_SIZE 0x1000

#define RTOS_PRODUCT_OFFSET 0xc0
#define RTOS_MODEM_OFFSET 0x100

typedef struct modem_shmem_info_s {
    uint32_t frm_idx;
    uint16_t frm_isI;
    uint16_t frm_len;
    uint16_t frm_dsti;
    uint16_t frm_dstf;
    uint16_t channel_status;
    uint16_t dec_err_status;
    uint16_t cur_time;
    uint16_t delta_time;
    uint16_t dbg_msc;
    uint8_t dbg_ap_ready;
    uint8_t dbg_cp_ready;
    uint32_t local_id;
    uint8_t cp_state;
    uint8_t cp_report;
    uint8_t cp_report_seq;
    uint8_t client_type;
    uint32_t cp_boot_status0;
    uint32_t cp_boot_status1;
    uint32_t board_version;
    uint32_t board_sub_version;
    uint8_t machine_role;
    uint8_t is_reverse;
    int8_t cp_tx_power;
    uint8_t gnd_type;
    uint32_t cp_sssfn;
    uint32_t ulow_en;
    uint8_t mipi_rx_response;
    uint8_t liveview_broken_status;
    uint8_t reserved01;
    uint8_t reserved02;
    uint8_t ap_reboot_flag;
    uint8_t ap_reboot_ack_flag;
    uint8_t secure_sync_flag;
    uint8_t reserve00;
    uint8_t area_state;
    uint8_t area_substate;
    uint8_t GsCtrl;
    uint8_t GsSubState;
    uint8_t WaterLevel[4];
    uint16_t RxCntStastic[4];
    uint16_t TxCntStastic[4];
    uint8_t Reserved[8];
    uint32_t com_uart_status;
    uint32_t fcr_rx_status;
    uint32_t fcr_tx_status;
    uint32_t frm_idx_for_display;
    uint32_t frm_delay_for_display;
    uint16_t wifi_sdr_mode;
    uint16_t frm_isI_for_display;
    uint32_t country_code;
    uint16_t frm_len_for_display;
    uint16_t delta_time_for_display;
    uint8_t uint8_t_reboot_reason;
    uint8_t field_0x85;
    uint8_t field_0x86;
    uint8_t field_0x87;
    uint64_t cpa7_version;
    uint64_t dsp_version;
    uint8_t u8_dual_band_capability;
} __attribute__((packed)) modem_shmem_info_t;

typedef struct product_shm_info_s {
    uint16_t frm_width;
    uint16_t frm_height;
    uint8_t fps;
    uint8_t enc_strategy;
    uint16_t lcdc_underflow_cnt;
    uint32_t enc_sto_frm_dropped;
    uint32_t enc_lv_frm_dropped;
    uint32_t mipi_csi_frm_dropped;
    uint32_t display_frm_dropped;
    uint64_t audio_pts;
    uint32_t local_fps_num;
    uint32_t local_fps_den;
    uint16_t frame_delay_e2e;
    uint16_t cam_frame_interval;
    uint16_t outliner_frame_interval;
    uint16_t outliner_frame_interval_cnt;
    uint16_t max_frame_delay_e2e;
    uint16_t min_frame_delay_e2e;
    uint16_t avg_frame_delay_e2e;
    uint16_t if_switch;
    uint8_t if_change_pipe;
    uint8_t if_pb_pause;
    uint8_t liveview_pipeline_running;
    uint8_t avIn_pipeline_running;
    uint8_t avIn_stream_type;
    uint8_t pb_flush;
    uint8_t disp_pannel_need_reset;
    uint8_t pad;
} __attribute__((packed)) product_shm_info_t;

typedef struct dji_shm_state_s {
    void *mapped_address;
    product_shm_info_t *product_info;
    modem_shmem_info_t *modem_info;
} dji_shm_state_t;

uint16_t dji_radio_latency_ms(dji_shm_state_t *shm);
uint16_t dji_radio_mbits(dji_shm_state_t *shm);
void close_dji_radio_shm(dji_shm_state_t *shm);
void open_dji_radio_shm(dji_shm_state_t *shm);