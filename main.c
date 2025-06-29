#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include "fileOps.h"

void print_help(char *argv[]) {
    printf("Usage %s -r <db file>\n", argv[0]);
}

int main(int argc, char *argv[]) {
    const char *filepath = NULL;
    struct dbheader_t *headerOut = NULL;
    int option;
    bool readheader = false;
    bool createheader = false;

    while ((option = getopt(argc, argv, "r:h:")) != -1) {
        switch(option) {
            case 'r':
                readheader = true;
                filepath = optarg;
                break;
            case 'h':
                filepath=optarg;
                createheader = true;
                break;
            case '?':
                printf("Unknown operation [%c]", option);
                return -1;
            default:
                return -1;
        }

    }
    if (filepath == NULL) {
        print_help(argv);
        return 0;
    }

    if (readheader) {
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
    }}

    if (createheader) {
        int fd1 = createFile(filepath);
        if (fd1 != -1) {
        createHeader(fd1, &headerOut);
        saveHeader(fd1, headerOut);
        free(headerOut);
    }
        close(fd1);
    }

}