#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include "fileOps.h"
#include "employeeOps.h"

void print_help(char *argv[]) {
    printf("Usage %s -r <db file>\n", argv[0]);
}

int main(int argc, char *argv[]) {
    const char *filepath = NULL;
    struct dbheader_t *headerOut = NULL;
    struct employee_t *employeesOut = NULL;
    int option;
    bool readheader = false;
    bool createheader = false;
    bool readEmployee = false;
    bool addEmployees = false;
    while ((option = getopt(argc, argv, "r:h:a:e:")) != -1) {
        switch(option) {
            case 'r':
                readheader = true;
                filepath = optarg;
                break;
            case 'h':
                filepath=optarg;
                createheader = true;
                break;
            case 'a':
                filepath=optarg;
                readEmployee = true;
                break;
            case 'e':
                filepath=optarg;
                addEmployees = true;
                break;
            case '?':
                printf("Unknown operation [%c]", option);
                return -1;
            default:
                return -1;
        }

    }
    if (filepath == NULL) {
        print_help(argv);
        return 0;
    }

    if (readheader) {
    int fd = openFile(filepath);
    if (fd == -1) { 
        perror("open");
        return -1;
    }
    if (readHeader(fd, &headerOut) == 1 && headerOut) {
        printf("Header Info:\n");
        printf("Magic number: 0x%X\n", headerOut->magic);
        printf("Version %u\n", headerOut->version);
        printf("Filesize: %u bytes\n", headerOut->filesize);
        printf("Record count: %u\n", headerOut->count);
        free(headerOut);
    }}

    if (createheader) {
        int fd = createFile(filepath);
        if (fd != -1) {
        createHeader(fd, &headerOut);
        saveHeader(fd, headerOut);
        free(headerOut);
    }
        close(fd);
    }

    if(addEmployees) {
        int fd = openFile(filepath);
        readHeader(fd, &headerOut);
        addEmployee(headerOut, employeesOut, "Grzegorz Zulczyk, Powazkowska 44c Warszawa, 268");
        printf("finished!");
        //tired af, tommorow gonna fix this
    }

    if(readEmployee) {
    int fd = openFile(filepath);
    readHeader(fd, &headerOut);
    readEmployees(fd, headerOut, &employeesOut);
    for (int i = 0; i < headerOut->count; i++) {
        printf("Name: %s\n", employeesOut[i].name);
        printf("Address: %s\n", employeesOut[i].address);
        printf("Hours: %d\n", employeesOut[i].hours);
    } 
}

}