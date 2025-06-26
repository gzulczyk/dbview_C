#include <stdio.h>
#include <stdlib.h>
#include "fileOps.h"


int main(int argc, char *argv[]) {
    const char *filepath = argv[1];
    const char *option = argv[2];
    struct dbheader_t *headerOut = NULL;

    int fd = openFile(filepath);
    if (fd == -1) { 
        perror("open");
        return -1;
    }

    readHeader(fd, &headerOut);
}