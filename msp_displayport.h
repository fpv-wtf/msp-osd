#include <stdint.h>

#define FONT_WIDTH 36
#define FONT_HEIGHT 54

typedef void (*draw_character_func)(uint32_t x, uint32_t y, uint8_t c);
typedef void (*clear_screen_func)();
typedef void (*draw_complete_func)();

typedef struct displayport_vtable_s {
    draw_character_func draw_character;
    clear_screen_func clear_screen;
    draw_complete_func draw_complete;
} displayport_vtable_t;

void set_display_driver(displayport_vtable_t *driver);
int displayport_process_message(msp_msg_t *msg);