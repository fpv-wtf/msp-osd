#include <termios.h>

int open_serial_port(const char *device, speed_t baudrate);
int open_pty(const char **pty_name);
#ifdef __ANDROID__
int
openpty (int *amaster, int *aslave, char *name, struct termios *termp,
         struct winsize *winp);
#endif