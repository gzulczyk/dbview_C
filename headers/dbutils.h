#ifndef DBUTILS_H
#define DBUTILS_H
#include "structs.h"


void loadDb(const char *filepath, int *fd, dbheader_t **header, employee_t **employees);
void saveDb(int fd, dbheader_t *header, employee_t *employees);
void cleanUp(int fd, dbheader_t *header, employee_t *emloyees);

#endif