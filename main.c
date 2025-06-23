#include <stdio.h>
#include <stdlib.h>
#include "fileOps.h"

int main(int argc, char *argv[]) {
    const char *filepath = argv[1];
    const char *option = argv[2];
    
    openFile = openFile(filepath)
    if (openFile == -1) {
        perror("open");
        return -1;
    }
}