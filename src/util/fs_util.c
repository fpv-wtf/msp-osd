#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int32_t get_int_from_fs(char* path) {
    int32_t val;
    char read_buffer[32];
    memset(read_buffer, 0, 32);
    int fd = open(path, O_RDONLY, 0);
    if(fd < 0) {
        return -1;
    }
    int read_count = read(fd, read_buffer, 32);
    if(read_count > 0) {
        val = atoi(read_buffer);
    }
    close(fd);
    return val;
}