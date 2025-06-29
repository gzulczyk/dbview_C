#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "structs.h"

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

/* int readEmployees() {
    printf("tbd");
    return -1;
} 

int listEmployees() {
    printf("tbd");
    return -1;
} */