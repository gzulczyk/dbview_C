#include <stdio.h>
#include <stdlib.h>

int check_fd(int fd, const char *context) {
	if (fd < 0) {
		printf("Invalid file descriptor: [%s] %d\n", context, fd);
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