#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "structs.h"
#include "fileOps.h"
#include "employeeOps.h"
#include "helper.h"

void loadDb(const char *filepath, int *fd, dbheader_t **header, employee_t **employees) {
    *fd = openFile(filepath);
    if(!checkFd(fd)) exit(EXIT_FAILURE);
    readHeader(*fd, header);
    readEmployees(*fd, *header, employees);
}

void saveDb(int fd, dbheader_t *header, employee_t *employees) {
    saveHeader(fd, header);
    saveEmployee(fd, header, employees);
}

void cleanUp(int fd, dbheader_t *header, employee_t *emloyees) {
    if(header) free(header);
    if(emloyees) free(emloyees);
    close(fd);
}