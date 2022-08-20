#include <stdint.h>

typedef void (*draw_character_func)(uint32_t x, uint32_t y, uint16_t c);
typedef void (*set_options_func)(uint8_t font, uint8_t is_hd);
typedef void (*clear_screen_func)();
typedef void (*draw_complete_func)();

typedef struct displayport_vtable_s {
    draw_character_func draw_character;
    clear_screen_func clear_screen;
    draw_complete_func draw_complete;
    set_options_func set_options;
} displayport_vtable_t;

int displayport_process_message(displayport_vtable_t *display_driver, msp_msg_t *msg);