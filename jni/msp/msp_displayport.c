#include "msp.h"
#include "msp_displayport.h"

static void process_draw_string(displayport_vtable_t *display_driver, uint8_t *payload) {
    if(!display_driver || !display_driver->draw_character) return;
    uint8_t row = payload[0];
    uint8_t col = payload[1];
    uint8_t attrs = payload[2]; // INAV and Betaflight use this to specify a higher page number. 
    uint8_t str_len;
    for(str_len = 1; str_len < 255; str_len++) {
        if(payload[2 + str_len] == '\0') {
            break;
        }
    }
    for(uint8_t idx = 0; idx < (str_len - 1); idx++) {
        uint16_t character = payload[3 + idx];
        if(attrs & 0x3) {
            // shift over by the page number if they were specified
            character |= ((attrs & 0x3) * 0x100);
        }
        display_driver->draw_character(col, row, character);
        col++;
    }
}

static void process_clear_screen(displayport_vtable_t *display_driver) {
    if(!display_driver || !display_driver->clear_screen) return;
    display_driver->clear_screen();
}

static void process_draw_complete(displayport_vtable_t *display_driver) {
    if(!display_driver || !display_driver->draw_complete) return;
    display_driver->draw_complete();
}

static void process_set_options(displayport_vtable_t *display_driver, uint8_t *payload) {
    if(!display_driver || !display_driver->set_options) return;
    uint8_t font = payload[0];
    msp_hd_options_e is_hd = payload[1];
    display_driver->set_options(font, is_hd);
}

static void process_open(displayport_vtable_t *display_driver) {

}

static void process_close(displayport_vtable_t *display_driver) {
    process_clear_screen(display_driver);
}

int displayport_process_message(displayport_vtable_t *display_driver, msp_msg_t *msg) {
    if (msg->direction != MSP_INBOUND) {
        return 1;
    }
    if (msg->cmd != MSP_CMD_DISPLAYPORT) {
        return 1;
    }
    uint8_t sub_cmd = msg->payload[0];
    switch(sub_cmd) {
        case 0: // 0 -> Open/Keep-Alive DisplayPort
            process_open(display_driver);
            break;
        case 1: // 1 -> Close DisplayPort
            process_close(display_driver);
            break;
        case 2: // 2 -> Clear Screen
            process_clear_screen(display_driver);
            break;
        case 3: // 3 -> Draw String
            process_draw_string(display_driver, &msg->payload[1]);
            break;
        case 4: // 4 -> Draw Screen
            process_draw_complete(display_driver);
            break;
        case 5: // 5 -> Set Options (HDZero/iNav)
            process_set_options(display_driver, &msg->payload[1]);
            break;
        default:
            break;
    }
    return 0;
}

