#include "msp.h"
#include "msp_displayport.h"

#define MSP_COLS 30

displayport_vtable_t *display_driver;

static void process_draw_string(uint8_t *payload) {
    if(!display_driver || !display_driver->draw_character) return;
    uint8_t row = payload[0];
    uint8_t col = payload[1];
    uint8_t attrs = payload[2]; // todo implement blink
    uint8_t str_len;
    for(str_len = 1; str_len < 255; str_len++) {
        if(payload[2 + str_len] == '\0') {
            break;
        }
    }
    for(uint8_t idx = 0; idx < str_len; idx++) {
        display_driver->draw_character(col, row, payload[3+idx]);
        col++;
        if(col > MSP_COLS) {
            col = 0;
            row++;
        }
    }
}

static void process_clear_screen() {
    if(!display_driver || !display_driver->clear_screen) return;
    display_driver->clear_screen();
}

static void process_draw_complete() {
    if(!display_driver || !display_driver->draw_complete) return;
    display_driver->draw_complete();
}

static void process_open() {

}

static void process_close() {
    process_clear_screen();
}

void set_display_driver(displayport_vtable_t *driver) {
    display_driver = driver;
}

int displayport_process_message(msp_msg_t *msg) {
    if (msg->direction != MSP_INBOUND) {
        return 1;
    }
    if (msg->cmd != MSP_CMD_DISPLAYPORT) {
        return 1;
    }
    uint8_t sub_cmd = msg->payload[0];
    switch(sub_cmd) {
        case 0: // 0 -> Open/Keep-Alive DisplayPort
            process_open();
            break;
        case 1: // 1 -> Close DisplayPort
            process_close();
            break;
        case 2: // 2 -> Clear Screen
            process_clear_screen();
            break;
        case 3: // 3 -> Draw String
            process_draw_string(&msg->payload[1]);
            break;
        case 4: // 4 -> Draw Screen
            process_draw_complete();
            break;
        default:
            return 1;
            break;
    }
    return 0;
}

