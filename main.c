#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <getopt.h>

#include "fileOps.h"
#include "employeeOps.h"
#include "structs.h"
#include "helper.h"
#include "dbutils.h"

void print_help(char *argv[]) {
    printf("Usage %s -f <db file> <arg> \n", argv[0]);
}


struct command_t parseArgs(int argc, char *argv[]) {
    struct command_t cmd = {0};
    cmd.type = CMD_NONE;
    int option; 

    while ((option = getopt(argc, argv, "f:rhae:d:o:m:i:")) != -1 ) {
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
                cmd.type = CMD_CREATE_HEADER;
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
    if (cmd.filepath == NULL && cmd.type != CMD_CREATE_HEADER) {
        fprintf(stderr, "You have to provide a db file via -f tag\n");
        exit(EXIT_FAILURE);
    }
    return cmd; 
    conflict:
        fprintf(stderr, "You can only do one opearation during runtime!");
        exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])  {
    struct command_t cmd = parseArgs(argc, argv);
    struct dbheader_t *header = NULL;
    struct employee_t *employees = NULL;
    int fd;
 
    switch (cmd.type) {
        case CMD_CREATE_HEADER:
            fd = createFile(cmd.filepath);
            check_fd(fd);
            createHeader(fd, &header);
            saveHeader(fd, header);
            free(header);
            close(fd);
            break;
            

        case CMD_READ_HEADER:
            fd = openFile(cmd.filepath);
            check_fd(fd);
            int resultHeader = readHeader(fd, &header);
            if (resultHeader != -1) {
            printf("Header Info:\n");
            printf("Magic number: 0x%X\n", header->magic);
            printf("Version %u\n", header->version);
            printf("Filesize: %u bytes\n", header->filesize);
            printf("Record count: %u\n", header->count);
            }
            free(header);
            close(fd);
            break;

        case CMD_READ_EMPLOYEE:
            load_db(cmd.filepath, &fd, &header, &employees);
            readOneEmployee(fd, header, employees, &cmd.targetID);
            cleanup(fd, header, employees);
            break;        
        
        case CMD_LIST_EMPLOYEES:
            load_db(cmd.filepath, &fd, &header, &employees);
            for (int i = 0; i < header->count; i++) {
            printf("[User ID: %d] ", employees[i].userID);
            printf("[Name: %s] ", employees[i].name);
            printf("[Address: %s] ", employees[i].address);
            printf("[Hours: %d] \n", employees[i].hours);
            } 
            cleanup(fd, header, employees);
            break;

        case CMD_ADD_EMPLOYEE:
            load_db(cmd.filepath, &fd, &header, &employees);
            header->count++;
            employees = realloc(employees, header->count*(sizeof(struct employee_t)));
            addEmployee(header, employees, cmd.employeeDeclaration);
            save_db(fd, header, employees);
            break;

        case CMD_EDIT_EMPLOYEE:
            load_db(cmd.filepath, &fd, &header, &employees);
            editEmployee(fd, header, employees, &cmd.targetID, cmd.employeeDeclaration);
            save_db(fd, header, employees);
            cleanup(fd, header, employees);
            break;
        
        case CMD_REMOVE_EMPLOYEE:
            load_db(cmd.filepath, &fd, &header, &employees);
            deleteEmployee(header, employees, &cmd.targetID);
            employees = realloc(employees, header->count * sizeof(struct employee_t));
            save_db(fd, header, employees);
            truncEmployee(fd, header);
            cleanup(fd, header, employees);
            break;
        
        default:
            fprintf(stderr, "Option was not declared\n");
            return -1;
    }
    return 0;
}