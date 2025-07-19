#ifndef FILEOPS_H
#define FILEOPS_H

#include "structs.h"


int openFile(const char *filename);
int createHeader(struct dbheader_t **dbhdr);
int validateHeader(int fd, struct dbheader_t **dbhdr);
int readHeader(int fd, struct dbheader_t **dbhdr);
int saveHeader(int fd, struct dbheader_t *dbhdr);
int createFile(const char *filename);

#endif