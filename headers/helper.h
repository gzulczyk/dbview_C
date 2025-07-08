#ifndef HELPER_H
#define HELPER_H

int check_fd(int fd, const char *context);
int check_malloc(void *mem_alloc, const char *context);
int check_calloc(void *mem_alloc, const char *context);

#endif 