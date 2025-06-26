#include <stdio.h>>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>

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

    *headerOut = header;

    return 1;
}

int readHeader(int fd, struct dbheader_t **headerOut) {
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

    if (header->magic != MAGIC_NUM) {
        printf("Invalid magic number!");
        free(header);
        return -1;
    }

    if (header->version != 1) {
        printf("Unsupported Version of dbview file");
        free(header);
        return -1;
    }

    struct stat dbstat = {0};
    fstat(fd, &dbstat);
    if (header->filesize != dbstat.st_size) {
        printf("Mismatched filesize between header declaration and the actual size!");
        free(header);
        return -1;
    }

    *headerOut = header;

}

int saveHeader(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut){
    if(!check_fd(fd, "FD FileOutput")) {
        return -1;
    }

    dbhdr->magic = htonl(dbhdr->magic);
    dbhdr->filesize = htonl(sizeof(struct dbheader_t));
    dbhdr->count = htons(dbhdr->count);
    dbhdr->version = htons(dbhdr->version);

    lseek(fd,0, SEEK_SET);
    write(fd,dbhdr, sizeof(struct dbheader_t));

    return 1;
}