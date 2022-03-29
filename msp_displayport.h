#include <stdint.h>

typedef void (*draw_character_func)(uint32_t x, uint32_t y, uint8_t c);
typedef void (*clear_screen_func)();
typedef void (*draw_complete_func)();

typedef struct displayport_vtable_s {
    draw_character_func draw_character;
    clear_screen_func clear_screen;
    draw_complete_func draw_complete;
} displayport_vtable_t;

int displayport_process_message(displayport_vtable_t *display_driver, msp_msg_t *msg);