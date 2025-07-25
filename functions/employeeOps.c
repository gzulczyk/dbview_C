#include <stdio.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include "structs.h"
#include "helper.h"

int addEmployee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addString) {
    char *name = strtok(addString, ",");
    char *address = strtok(NULL, ",");
    char *hours = strtok(NULL, ",");

    if (!name || !address || !hours || strlen(name) == 0 || strlen(address) == 0 || strlen(hours) == 0) {
        fprintf(stderr, "The syntax of your declaration is broken! Expected format: Grzegorz Zulczyk, ul. Sezamkowa 12A, 120\n");
        return -1;
    }

    printf("User ID: [%d ] Name: [%s ], Address: [%s ], Hours: [%s ]\n", dbhdr->count-1,name,address,hours);
    employees[dbhdr->count-1].userID = dbhdr->count-1;
    strncpy(employees[dbhdr->count-1].name, name, sizeof(employees[dbhdr->count-1].name));
    strncpy(employees[dbhdr->count-1].address, address, sizeof(employees[dbhdr->count-1].address));
    employees[dbhdr->count-1].hours = atoi(hours);

    return 1;
}

 int readEmployees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut) {
    if (!checkFd(fd)) {
        return -1;
    }
    lseek(fd, sizeof(struct dbheader_t), SEEK_SET);
    int count = dbhdr->count;
    if(count>0) {
    struct employee_t *employees = calloc(count, sizeof(struct employee_t));
    if (!checkCalloc(employees, "Allocating memory for employees during read...")) {
        return -1;
    } 
    read(fd, employees, count*sizeof(struct employee_t));
    for (int i =0; i<count; i++) {
        employees[i].hours = ntohs(employees[i].hours);
    }
    *employeesOut = employees;}
    return 1;

} 

int readOneEmployee(int fd, struct dbheader_t *dbhdr, struct employee_t *employees, int *targetID) {
    if (!checkFd(fd)) {
        return -1;
    }
    int userIndex = -1; 

    for (int i=0; i<dbhdr->count; i++) {
        if(employees[i].userID == *targetID) {
            userIndex = i;
            printf("Declared ID: %d\n", employees[i].userID);
            printf("Name: %s\n", employees[i].name);
            printf("Address: %s\n", employees[i].address);
            printf("Hours: %d\n", employees[i].hours);
            break;
        }
    }
    if (userIndex == -1) {
            printf("User ID not found!\n");
            return -1;
    }
    return 0;
} 

int editEmployee(int fd, struct dbheader_t *dbhdr, struct employee_t *employees, int *targetID, char *addString) {
    if (!checkFd(fd)) {
        return -1;
    }
    int userIndex = -1; 
    
    for (int i=0; i<dbhdr->count; i++) {
        if(employees[i].userID == *targetID) {
            userIndex = i;
            char *name = strtok(addString, ",");
            char *address = strtok(NULL, ",");
            char *hours = strtok(NULL, ",");
            if (!name || !address || !hours || strlen(name) == 0 || strlen(address) == 0 || strlen(hours) == 0) {
                fprintf(stderr, "The syntax of your declaration is broken! Expected format: Grzegorz Zulczyk, ul. Sezamkowa 12A, 120\n");
                return -1;
            }       
            printf("User ID: [%d] Name: [%s], Address: [%s], Hours: [%s]\n", userIndex,name,address,hours);
            employees[userIndex].userID = userIndex;
            strncpy(employees[userIndex].name, name, sizeof(employees[userIndex].name));
            strncpy(employees[userIndex].address, address, sizeof(employees[userIndex].address));
            employees[userIndex].hours = atoi(hours);
            break;
        }
    }
    if (userIndex == -1) {
            printf("User ID not found!\n");
            return -1;
    }
    return 0;
}


int saveEmployee(int fd, struct dbheader_t *dbhdr, struct employee_t *employeesOut) {
    lseek(fd, sizeof(struct dbheader_t), SEEK_SET);

    for (int i = 0; i < dbhdr->count; i++) {
        struct employee_t temp = employeesOut[i]; 
        temp.hours = htons(temp.hours);            
        write(fd, &temp, sizeof(struct employee_t)); 
    }

    return 0;
}

int truncEmployee(int fd, struct dbheader_t *dbhdr) {
    ftruncate(fd, dbhdr->filesize);
    return 0;
}

int deleteEmployee(struct dbheader_t *dbhdr, struct employee_t *employees, int *targetID)
{

    int userIndex = -1; 
    
    for (int i=0; i<dbhdr->count; i++) {
        if(employees[i].userID == *targetID) {
            userIndex = i;
            break;
        }
    }
    if (userIndex == -1) {
            printf("User not found, cannot delete the record!\n");
            return -1;
    }
    for (int i=userIndex; i<dbhdr->count-1; i++) {
        employees[i] = employees[i + 1];
    }
    
    dbhdr->count--;
    
    for (int i=0; i<dbhdr->count; i++) {
        employees[i].userID = i;
    }

    return 0;
}