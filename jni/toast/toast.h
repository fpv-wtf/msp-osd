int toast(char*, ...);
void toast_load_config();
void do_toast(void (*display_print_string)(uint8_t init_x, uint8_t y, const char *string, uint8_t len));