#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void load_db(const char *filepath, int *fd, struct dbheader_t **header, struct employee_t **employees) {
    *fd = openFile(filepath);
    check_fd(*fd);
    readHeader(*fd, *header);
    readEmployees(*fd, *header, employees);
}

void save_db(int fd, struct dbheader_t *header, struct employee_t *employees) {
    saveHeader(fd, header);
    saveEmployee(fd, header, employees);
}

void cleanup(int fd, struct dbheader_t *header, struct employee_t *emloyees) {
    if(header) free(header);
    if(emloyees) free(emloyees);
    close(fd);
}