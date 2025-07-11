#include <stdio.h>
#include <stdlib.h>

int check_fd(int fd) {
	if (fd < 0) {
		printf("Invalid file descriptor: [%d]\n", fd);
		return 0;
	}
    return 1;
}

int check_malloc(void *mem_alloc, const char *context) {
    if (mem_alloc == NULL) {
        printf("Memory allocation failed: [%s]", context);
        return 0;
    }
    return 1;
}

int check_calloc(void *mem_alloc, const char *context) {
    if (mem_alloc == NULL) {
        printf("Memory allocation failed: [%s]", context);
        return 0;
    }
    return 1;
}