/* Print FFMPEG version information */
#include <libavcodec/avcodec.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned ver = avcodec_version();

    printf("ver: %d.%d.%d", ver >> 16, (ver >> 8) & 0xff, ver & 0xff);
    printf("config: %s\n", avcodec_configuration());

    return 0;
}
