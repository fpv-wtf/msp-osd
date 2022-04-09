#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#ifdef __APPLE__
#include <util.h>
#endif
#include "serial.h"

int open_serial_port(const char *device, speed_t baudrate)
{
    struct termios tio;
    int tty_fd;

    memset(&tio, 0, sizeof(tio));
    tio.c_iflag = 0;
    tio.c_oflag = 0;
    tio.c_cflag = CS8 | CREAD | CLOCAL;
    tio.c_lflag = 0;
    tio.c_cc[VMIN] = 1;
    tio.c_cc[VTIME] = 0;

    tty_fd = open(device, O_RDWR | O_NONBLOCK);
    cfsetospeed(&tio, baudrate);
    cfsetispeed(&tio, baudrate);
    tcsetattr(tty_fd, TCSANOW, &tio);
    return tty_fd;
}

int open_pty(const char **pty_name)
{
    int app_pty;
    int virtual_serial_pty;

    // openpty makes a connection between the first argument, a parent FD which acts as the "receiving" end of the virtual PTY
    // and the second argument, a child FD which represents a "virtual serial port."
    // using ttyname on the second argument will return a /dev which can be opened as a serial port
    pid_t pid = openpty(&app_pty, &virtual_serial_pty, NULL, NULL, NULL);

    if (pid != 0)
    {
        printf("Could not get PTY!");
        exit(1);
        return pid;
    }

    (*pty_name) = ttyname(virtual_serial_pty);
    struct termios orig_termios;
    if (tcgetattr(app_pty, &orig_termios) < 0)
    {
        printf("Could not get termio for current FD");
        return -1;
    }

    orig_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    orig_termios.c_oflag &= ~(OPOST);
    orig_termios.c_cflag |= (CS8);
    orig_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    orig_termios.c_cc[VMIN] = 0;
    orig_termios.c_cc[VTIME] = 1;

    if (tcsetattr(app_pty, TCSANOW, &orig_termios) < 0)
    {
        perror("Could not set termio for current FD");
        return -1;
    }    

    if (tcgetattr(virtual_serial_pty, &orig_termios) < 0)
    {
        printf("Could not get termio for current FD");
        return -1;
    }

    orig_termios.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    orig_termios.c_oflag &= ~(OPOST);
    orig_termios.c_cflag |= (CS8);
    orig_termios.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    orig_termios.c_cc[VMIN] = 0;
    orig_termios.c_cc[VTIME] = 1;

    if (tcsetattr(virtual_serial_pty, TCSANOW, &orig_termios) < 0)
    {
        perror("Could not set termio for current FD");
        return -1;
    }    
    fcntl(app_pty, F_SETFL, O_NONBLOCK);
    return app_pty; // Return the file descriptor
}

#ifdef DEBUG_TRACE
void _trace(const char* format, ...);
#endif

#ifdef DEBUG_TRACE
#define TRACE(X) _trace X;
#else /*DEBUG_TRACE*/
#define TRACE(X)
#endif /*DEBUG_TRACE*/
#ifdef __ANDROID__
int
openpty (int *amaster, int *aslave, char *name, struct termios *termp,
         struct winsize *winp)
{
  int master, slave;
  char *name_slave;

  master = open("/dev/ptmx", O_RDWR | O_NONBLOCK);
  if (master == -1) {
    TRACE(("Fail to open master"))
    return -1;
  }

  if (grantpt(master))
    goto fail;

  if (unlockpt(master))
    goto fail;

  name_slave = ptsname(master);
  TRACE(("openpty: slave name %s", name_slave))
  slave = open(name_slave, O_RDWR | O_NOCTTY);
  if (slave == -1)
    {
      goto fail;
    }

  if(termp)
    tcsetattr(slave, TCSAFLUSH, termp);
  if (winp)
    ioctl (slave, TIOCSWINSZ, winp);

  *amaster = master;
  *aslave = slave;
  if (name != NULL)
    strcpy(name, name_slave);

  return 0;

 fail:
  close (master);
  return -1;
}
#endif