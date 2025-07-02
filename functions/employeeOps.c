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
    printf("Name: [%s], Address: [%s], Hours: [%s]\n", name,address,hours);
    strncpy(employees[dbhdr->count-1].name, name, sizeof(employees[dbhdr->count-1].name));
    strncpy(employees[dbhdr->count-1].address, address, sizeof(employees[dbhdr->count-1].address));
    employees[dbhdr->count-1].hours = atoi(hours);

    return 1;
}

 int readEmployees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut) {
    if (!check_fd(fd, "Validating the fd during read employees...")) {
        return -1;
    }
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
    printf("tbd");
    return -1;
} */

int saveEmployee(int fd, struct dbheader_t *dbhdr, struct employee_t *employeesOut) {
    lseek(fd, sizeof(struct dbheader_t), SEEK_SET);

    for (int i = 0; i < dbhdr->count; i++) {
        struct employee_t temp = employeesOut[i]; 
        temp.hours = htons(temp.hours);            
        write(fd, &temp, sizeof(struct employee_t)); 
    }

    return 0;
}



int removeEmployee(int fd, struct employee_t *employeesOut)
{
    printf("tbd");
    return 0;
}