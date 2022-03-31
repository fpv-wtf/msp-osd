int open_serial_port(const char *device);
int open_pty(const char **pty_name);
#ifdef __ANDROID__
int
openpty (int *amaster, int *aslave, char *name, struct termios *termp,
         struct winsize *winp);
#endif