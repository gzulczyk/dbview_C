#include <stdio.h>>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "fileOps.h"
#include "structs.h"
#include "helper.c"

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
    struct dbheader_t *header = malloc(sizeof(struct dbheader_t));
    if(!check_malloc(*header, "Allocating memory for db header during header creation..."));
    {
        return -1;
    }
    header->magic = MAGIC_NUM;
    header->version = 1;
    header->filesize = sizeof(struct dbheader_t);
    header->count=0;

}

int readHeader(int fd, struct dbeader_t **headerOut) {
    if(!check_fd(fd, "FD Header")) { 
        return -1;
    }

    struct dbheader_t *header = malloc(sizeof(struct dbheader_t));
    
    if(!check_malloc(*header, "Allocating memory for db header during header read..."));
    {
        return -1;
    }

    if(read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)) {
        perror("read");
        free(header);
        return -1;
    }
}

int readFile(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut){
    if(!check_fd(fd, "FD FileOutput")) {
        return -1;
    }
}