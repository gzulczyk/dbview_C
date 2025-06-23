#include <stdio.h>>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int openFile(char *filename)
{
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    }
}
