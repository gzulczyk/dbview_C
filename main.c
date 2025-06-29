#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


#include "fileOps.h"


int main(int argc, char *argv[]) {
    const char *filepath = NULL;
    struct dbheader_t *headerOut = NULL;
    int option;

    while ((option = getopt(argc, argv, "r:")) != -1) {
        switch(option) {
            case 'r':
                filepath = optarg;
                break;
            case '?':
                printf("Unknown operation [%c]", option);
                return -1;
            default:
                return -1;
        }

    }

    int fd = openFile(filepath);
    if (fd == -1) { 
        perror("open");
        return -1;
    }

    if (readHeader(fd, &headerOut) == 1 && headerOut) {
        printf("Header Info:\n");
        printf("Magic number: 0x%X\n", headerOut->magic);
        printf("Version %u\n", headerOut->version);
        printf("Filesize: %u bytes\n", headerOut->filesize);
        printf("Record count: %u\n", headerOut->count);
        free(headerOut);
    }
}