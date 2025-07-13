#ifndef DBUTILS_H
#define DBUTILS_H
#include "structs.h"


void load_db(const char *filepath, int *fdOut,  dbheader_t **header, employee_t **employees);
void save_db(int fd,  dbheader_t *header, employee_t *employees);
void cleanup(int fd, dbheader_t *header, employee_t *employees);


#endif