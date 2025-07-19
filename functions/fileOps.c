
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#include "fileOps.h"
#include "structs.h"
#include "helper.h"

int openFile(const char *filename)
{
    int fd = open(filename, O_RDWR,0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    return fd;
}

int createFile(const char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd != -1) {
        close(fd);
        printf("File already exists!\n");
        return -1;
    }
    fd = open(filename, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    return fd;
}

int createHeader(struct dbheader_t **dbhdr) {
    struct dbheader_t *header = malloc(sizeof(struct dbheader_t));
    if(!checkMalloc(header, "Allocating memory for db header during header creation..."))
    {
        return -1;
    }
    header->magic = MAGIC_NUM;
    header->version = 1;
    header->count=0;

    *dbhdr = header;

    return 1;
}

int readHeader(int fd, struct dbheader_t **dbhdr) {
    if(!checkFd(fd)) { 
        return -1;
    }

    struct dbheader_t *header = malloc(sizeof(struct dbheader_t));
    
    if(!checkMalloc(header, "Allocating memory for db header during header read..."))
    {
        return -1;
    }

    if(read(fd, header, sizeof(struct dbheader_t)) != sizeof(struct dbheader_t)) {
        perror("read");
        free(header);
        return -1;
    }
        header->magic    = ntohl(header->magic);
        header->filesize = ntohl(header->filesize);
        header->count    = ntohs(header->count);
        header->version  = ntohs(header->version);
   
        if (header->magic != MAGIC_NUM) {
        printf("Invalid magic number! Gerrara here hackier!\n");
        free(header);
        return -1;
    }

    if (header->version != 1) {
        printf("Unsupported Version of dbview file\n");
        free(header);
        return -1;
    }

    struct stat dbstat = {0};
    fstat(fd, &dbstat);
    if (header->filesize != dbstat.st_size) {
        printf("Mismatched filesize between header declaration and the actual size!\n");
        free(header);
        return -1;
    }

    *dbhdr = header;
    return 1;

}

int saveHeader(int fd, struct dbheader_t *dbhdr){
    if(!checkFd(fd)) {
        return -1;
    }

    struct dbheader_t tempDbhdr = *dbhdr;
    tempDbhdr.magic = htonl(tempDbhdr.magic);
    tempDbhdr.filesize = sizeof(struct dbheader_t) + tempDbhdr.count * sizeof(struct employee_t);
    tempDbhdr.filesize = htonl(tempDbhdr.filesize);
    tempDbhdr.count = htons(tempDbhdr.count);
    tempDbhdr.version = htons(tempDbhdr.version);

    lseek(fd,0, SEEK_SET);
    write(fd,&tempDbhdr, sizeof(struct dbheader_t));
    dbhdr->filesize = sizeof(struct dbheader_t) + dbhdr->count * sizeof(struct employee_t);

    return 1;
}

