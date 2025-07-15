#ifndef HELPER_H
#define HELPER_H

int checkFd(int fd);
int checkMalloc(void *mem_alloc, const char *context);
int checkCalloc(void *mem_alloc, const char *context);

#endif 