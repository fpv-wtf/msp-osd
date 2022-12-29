#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "dji_media.h"
#include "duss_media.h"

int main(int argc, char *argv[])
{
    int mcc = dji_open_media_control_channel();
    if (mcc == -1) {
        printf("mcc = %d, errno = %d: %s\n", mcc, errno, strerror(errno));
        return 1;
    }

    int mpc = dji_open_media_playback_channel();
    if (mpc == -1) {
        printf("mpc = %d, errno = %d: %s\n", mpc, errno, strerror(errno));
        return 1;
    }

    dji_send_media_command(mcc, DUSS_MEDIA_CMD_PB_START, 1280 | 720 << 10);

    while (1) {
        int r = 0;
        int iores = 0;

        iores = ioctl(mpc, 0x800c4205, &r);
        if (iores == -1) {
            printf("ioctl = %d, errno = %d: %s\n", iores, errno, strerror(errno));
            return 1;
        }

        printf("5r = %x\n", r);

        iores = ioctl(mpc, 0x400c4206, &r);
        if (iores == -1) {
            printf("ioctl = %d, errno = %d: %s\n", iores, errno, strerror(errno));
            return 1;
        }

        printf("6r = %x\n", r);

        sleep(1);
    }

    return 0;
}
