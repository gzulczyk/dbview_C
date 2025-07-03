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
    char *addstring = NULL;
    int targetID = 0;
    bool readheader = false;
    bool createheader = false;
    bool readEmployee = false;
    bool deleteEmployees=false;
    bool addEmployees = false;
    while ((option = getopt(argc, argv, "f:r:h:a:e:d:")) != -1) {
        switch(option) {
            case 'f':
                filepath= optarg;
                break;
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
                addstring=optarg;
                addEmployees = true;
                break;
            case 'd':
                targetID=atoi(optarg);
                deleteEmployees=true;
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
        readEmployees(fd, headerOut, &employeesOut);
        headerOut->count++;
        employeesOut = realloc(employeesOut, headerOut->count*(sizeof(struct employee_t)));
        addEmployee(headerOut, employeesOut, addstring);
        saveHeader(fd, headerOut);
        saveEmployee(fd, headerOut, employeesOut);
    }
    if(deleteEmployees) {
       int fd = openFile(filepath);
       readHeader(fd, &headerOut);
       readEmployees(fd, headerOut, &employeesOut);
       deleteEmployee(headerOut,employeesOut, &targetID);
       saveHeader(fd, headerOut);
       saveEmployee(fd, headerOut, employeesOut);
       truncEmployee(fd,headerOut);

    }

    if(readEmployee) {
    int fd = openFile(filepath);
    readHeader(fd, &headerOut);
    readEmployees(fd, headerOut, &employeesOut);
    for (int i = 0; i < headerOut->count; i++) {
        printf("User ID: %d\n", employeesOut[i].userID);
        printf("Name: %s\n", employeesOut[i].name);
        printf("Address: %s\n", employeesOut[i].address);
        printf("Hours: %d\n", employeesOut[i].hours);
    } 
}

}