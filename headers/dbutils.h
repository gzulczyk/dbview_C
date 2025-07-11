#ifndef DBUTILS_H
#define DBUTILS_H

void load_db(const char *filepath, int *fdOut, struct dbheader_t **header, struct employee_t **employees);
void save_db(int fd, struct dbheader_t *header, struct employee_t *employees);
void cleanup(int fd, struct dbheader_t *header, struct employee_t *emloyees);


#endif