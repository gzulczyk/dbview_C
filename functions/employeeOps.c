#include <stdio.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include "structs.h"
#include "helper.h"

int addEmployee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addString) {
    /* addString example = Grzegorz Zulczyk, Powazkowska 44c Warszawa, 268 <- thats the real value in my case xD */
    char *name = strtok(addString, ",");
    char *address = strtok(NULL, ",");
    char *hours = strtok(NULL, ",");
    printf("User ID: [%d] Name: [%s], Address: [%s], Hours: [%s]\n", dbhdr->count-1,name,address,hours);
    employees[dbhdr->count-1].userID = dbhdr->count-1;
    strncpy(employees[dbhdr->count-1].name, name, sizeof(employees[dbhdr->count-1].name));
    strncpy(employees[dbhdr->count-1].address, address, sizeof(employees[dbhdr->count-1].address));
    employees[dbhdr->count-1].hours = atoi(hours);

    return 1;
}

 int readEmployees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut) {
    if (!check_fd(fd)) {
        return -1;
    }
    lseek(fd, sizeof(struct dbheader_t), SEEK_SET);
    int count = dbhdr->count;
    if(count>0) {
    struct employee_t *employees = calloc(count, sizeof(struct employee_t));
    if (!check_calloc(employees, "Allocating memory for employees during read...")) {
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
    if (!check_fd(fd)) {
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
            printf("User ID not found!");
            return -1;
    }
    return 0;
} 

int editEmployee(int fd, struct dbheader_t *dbhdr, struct employee_t *employees, int *targetID, char *addString) {
    if (!check_fd(fd)) {
        return -1;
    }
    int userIndex = -1; 
    
    for (int i=0; i<dbhdr->count; i++) {
        if(employees[i].userID == *targetID) {
            userIndex = i;
            char *name = strtok(addString, ",");
            char *address = strtok(NULL, ",");
            char *hours = strtok(NULL, ",");
            printf("User ID: [%d] Name: [%s], Address: [%s], Hours: [%s]\n", userIndex,name,address,hours);
            employees[dbhdr->count-1].userID = userIndex;
            strncpy(employees[userIndex].name, name, sizeof(employees[userIndex].name));
            strncpy(employees[userIndex].address, address, sizeof(employees[userIndex].address));
            employees[userIndex].hours = atoi(hours);
            break;
        }
    }
    if (userIndex == -1) {
            printf("User ID not found!");
            return -1;
    }
    return 0;
}


int saveEmployee(int fd, struct dbheader_t *dbhdr, struct employee_t *employeesOut) {
    printf("[saveEmployee] count = %d\n", dbhdr->count);
    lseek(fd, sizeof(struct dbheader_t), SEEK_SET);

    for (int i = 0; i < dbhdr->count; i++) {
            printf("[saveEmployee] employee[%d].userID = %d\n", i, employeesOut[i].userID);
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
            printf("znalazlem");
            break;
        }
    }
    if (userIndex == -1) {
            printf("User not found, cannot delete the record!");
            return -1;
    }
    for (int i=userIndex; i<dbhdr->count-1; i++) {
        employees[i] = employees[i + 1];
    }
    dbhdr->count--;
    return 0;
}