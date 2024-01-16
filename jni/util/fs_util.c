#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "fs_util.h"

#define DICTIONARY_PATH "/opt/mspdictionaries"

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

void *open_dict(int dict_version, int *size) {
    char file_path[255];
    snprintf(file_path, 255, "%s/dictionary_%d.bin", DICTIONARY_PATH, dict_version);
    struct stat st;
    memset(&st, 0, sizeof(st));
    stat(file_path, &st);
    size_t filesize = st.st_size;
    int fd = open(file_path, O_RDONLY, 0);
    if (!fd) {
        return NULL;
    }
    void* dict = malloc(filesize);
    void* mmappedData = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    *size = filesize;
    memcpy(dict, mmappedData, filesize);
    close(fd);
    munmap(mmappedData, filesize);
    return dict;
}
