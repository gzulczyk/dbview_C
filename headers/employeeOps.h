#ifndef EMPLOYEEOPS_H
#define EMPLOYEEOPS_H
int addEmployee(struct dbheader_t *dbhdr, struct employee_t *employees, char *addString);
int readEmployees(int fd, struct dbheader_t *dbhdr, struct employee_t **employeesOut);
int saveEmployee(int fd, struct dbheader_t *dbhdr, struct employee_t *employeesOut);
int deleteEmployee(struct dbheader_t *dbhdr, struct employee_t *employees, int *targetID);
int truncEmployee(int fd, struct dbheader_t *dbhdr);
#endif