#include <stdio.h>
#include <stdlib.h>

int checkFd(int fd) {
	if (fd < 0) {
		printf("Invalid file descriptor: [%d]\n", fd);
		return -1;
	}
    return 1;
}

int checkMalloc(void *mem_alloc, const char *context) {
    if (mem_alloc == NULL) {
        printf("Memory allocation failed: [%s]", context);
        return 0;
    }
    return 1;
}

int checkCalloc(void *mem_alloc, const char *context) {
    if (mem_alloc == NULL) {
        printf("Memory allocation failed: [%s]", context);
        return 0;
    }
    return 1;
}