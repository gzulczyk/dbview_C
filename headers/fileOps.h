#ifndef FILEOPS_H
#define FILEOPS_H
#include <structs.h>


int openFile(char *filename);
int createHeader(int fd, struct dbheader_t **headerOut);
int validateHeader(int fd, struct dbheader_t **headerOut);

int readFile(int fd, struct dbheader_t *dbhdr, struct employee_t *employees);

#endif