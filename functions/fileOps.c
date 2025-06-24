#include <stdio.h>>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "fileOps.h"
#include "structs.h"

int openFile(char *filename)
{
    int fd = open(filename, O_RDWR,0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    return fd;
}

int createHeader(int fd, struct dbheader_t **headerOut) {
    struct dbheader_t *header = calloc(1, sizeof(struct dbheader_t));
    if (header == NULL) {
        print("Program was unable to allocate memory for the header buffer!");
        return -1;
    }
    header->magic = MAGIC_NUM;

}

int readFile(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut){
    if (fd<0) {
        printf("Broken file decryptor! Exiting...");
        return -1;
    }
}