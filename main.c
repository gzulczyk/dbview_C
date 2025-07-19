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
#include "infos.h"


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
        fprintf(stderr, "Lost? Use --help to figure out what this thing actually does!\n");
        exit(EXIT_FAILURE);
    }
    return cmd; 
    conflict:
        fprintf(stderr, "You can only do one opearation during runtime!\n");
        exit(EXIT_FAILURE);
}


int main(int argc, char *argv[])  {
    printLogo();
    if (printWhatYouExactlyWant(argc, argv)) {
        return 0;
    }
    struct command_t cmd = parseArgs(argc, argv);
    struct dbheader_t *header = NULL;
    struct employee_t *employees = NULL;
    int fd;
    
  

    switch (cmd.type) {
        case CMD_CREATE_HEADER:
            fd = createFile(cmd.filepath);
            if (fd != -1) {
                createHeader(fd, &header);
                saveHeader(fd, header);
                printf("DB file created sucessfully!\n");
            }
            free(header);
            close(fd);
            break;
            

        case CMD_READ_HEADER:
            fd = openFile(cmd.filepath);
            if (fd != -1) {
            int resultHeader = readHeader(fd, &header);
            if (resultHeader != -1) {
            printf("Header Info:\n");
            printf("Magic number: 0x%X\n", header->magic);
            printf("Version %u\n", header->version);
            printf("Filesize: %u bytes\n", header->filesize);
            printf("Record count: %u\n", header->count);
            } else {
                printf("Cannot find any header info from declared file!\n");
            } 
            }
            free(header);
            close(fd);
            break;

        case CMD_READ_EMPLOYEE:
            loadDb(cmd.filepath, &fd, &header, &employees);
            readOneEmployee(fd, header, employees, &cmd.targetID);
            cleanUp(fd, header, employees);
            break;        
        
        case CMD_LIST_EMPLOYEES:
            loadDb(cmd.filepath, &fd, &header, &employees);
            printf("List of employees:\n");
            for (int i = 0; i < header->count; i++) {
            printf("[User ID: %d] ", employees[i].userID);
            printf("[Name: %s] ", employees[i].name);
            printf("[Address: %s] ", employees[i].address);
            printf("[Hours: %d] \n", employees[i].hours);
            } 
            cleanUp(fd, header, employees);
            break;

        case CMD_ADD_EMPLOYEE:
            loadDb(cmd.filepath, &fd, &header, &employees);
            header->count++;
            employees = realloc(employees, header->count*(sizeof(struct employee_t)));
            int employeeStatus = addEmployee(header, employees, cmd.employeeDeclaration);
            if (employeeStatus != -1) {
            saveDb(fd, header, employees);
            printf("Employee was added sucessfully!\n");
            }
            cleanUp(fd, header, employees);
            break;

        case CMD_EDIT_EMPLOYEE:
            loadDb(cmd.filepath, &fd, &header, &employees);
            int employeeEditStatus = editEmployee(fd, header, employees, &cmd.targetID, cmd.employeeDeclaration);
            if (employeeEditStatus != -1) {
            saveDb(fd, header, employees);
            printf("Employee was edited sucessfully!\n");
            }
            cleanUp(fd, header, employees);
            break;
        
        case CMD_REMOVE_EMPLOYEE:
            loadDb(cmd.filepath, &fd, &header, &employees);
            int employeeDeleteStatus = deleteEmployee(header, employees, &cmd.targetID);
            if (employeeDeleteStatus != -1) {
            employees = realloc(employees, header->count * sizeof(struct employee_t));
            saveDb(fd, header, employees);
            truncEmployee(fd, header);
            printf("Employee was deleted sucessfully!\n");
            }
            cleanUp(fd, header, employees);
            break;
        
        default:
            fprintf(stderr, "Option was not declared\n");
            return -1;
    }
    return 0;
}