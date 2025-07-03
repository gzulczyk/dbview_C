#include <stdio.h>
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
    if (!check_fd(fd, "Validating the fd during read employees...")) {
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
/*
int listEmployees() {
    printf("");
    return -1;
} */

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
    printf("[truncEmployee] przycinam do %u bajtów\n", dbhdr->filesize);

    ftruncate(fd, dbhdr->filesize);
    return 0;
}

int deleteEmployee(struct dbheader_t *dbhdr, struct employee_t *employees, int *targetID)
{

    int userIndex = -1; 
    printf("moj count to: [%d]", dbhdr->count);
    
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
    printf("jestem tu");
    for (int i=userIndex; i<dbhdr->count-1; i++) {
        employees[i] = employees[i + 1];
        printf("%d staje sie %d", employees[i].userID, employees[i+1].userID);
    }
    dbhdr->count--;
    return 0;
}