#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>
#include "fileOps.h"
#include "employeeOps.h"
#include "structs.h"

void print_help(char *argv[]) {
    printf("Usage %s -f <db file> <arg> \n", argv[0]);
}

command_t parseArgs(int argc, char *argv[]) {
    command_t cmd = {0};
    cmd.type = CMD_NONE;
    int option; 

    while ((option = getopt(argc, argv, "f:r:h:a:e:d:o:m:i:")) != -1 ) {
        switch(option) {
            case 'f':
                cmd.filepath = optarg;
                break;
            
            case 'r':
                if(cmd.type != CMD_NONE) goto conflict;
                cmd.type = CMD_READ_HEADER;
                break;
            
                case 'h':
                if (cmd.type != CMD_NONE) goto conflict;
                cmd.type = CMD_READ_HEADER;
                break;
            
                case 'a':
                if (cmd.type != CMD_NONE) goto conflict;
                cmd.type = CMD_LIST_EMPLOYEES;
                break;
            
                case 'e':
                if (cmd.type != CMD_NONE) goto conflict;
                cmd.type = CMD_ADD_EMPLOYEE;
                cmd.employeeDeclaration = optarg;
                break;

                case 'd':
                    if (cmd.type != CMD_NONE) goto conflict;
                    cmd.type = CMD_REMOVE_EMPLOYEE;
                    cmd.targetID = atoi(optarg);
                    break;
                
                case 'o':
                    if (cmd.type != CMD_NONE) goto conflict;
                    cmd.type = CMD_READ_EMPLOYEE;
                    cmd.targetID = atoi(optarg);
                    break;

                case 'm':
                    if (cmd.type != CMD_NONE) goto conflict;
                    cmd.type = CMD_EDIT_EMPLOYEE;
                    cmd.employeeDeclaration = optarg;
                    break;
                
                case 'i':
                    cmd.targetID = atoi(optarg);
                    break;
                
                default:
                    fprintf(stderr, "Unknown operation -%c\n", option);
                    exit(EXIT_FAILURE);                
        }
    }
}


int main(int argc, char *argv[]) {
    const char *filepath = NULL;
    struct dbheader_t *headerOut = NULL;
    struct employee_t *employeesOut = NULL;
    int option;
    char *addstring = NULL;
    int targetID = 0;
    

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
        printf("[User ID: %d] ", employeesOut[i].userID);
        printf("[Name: %s] ", employeesOut[i].name);
        printf("[Address: %s] ", employeesOut[i].address);
        printf("[Hours: %d] \n", employeesOut[i].hours);
    } 
}

    if(readOneEmployeeS) {
    int fd = openFile(filepath);
    readHeader(fd, &headerOut);
    readEmployees(fd, headerOut, &employeesOut);
    readOneEmployee(fd, headerOut, employeesOut, &targetID);
}

    if(editEmployeeFlag) {
        int fd = openFile(filepath);
        readHeader(fd, &headerOut);
        readEmployees(fd, headerOut, &employeesOut);
        editEmployee(fd, headerOut,employeesOut, &targetID, addstring);
        saveHeader(fd, headerOut);
        saveEmployee(fd, headerOut, employeesOut);
    }

}