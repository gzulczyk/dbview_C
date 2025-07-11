#include <stdint.h>
#ifndef STRUCTS_H
#define STRUCTS_H
#define MAGIC_NUM 0x5359505F

typedef enum {
    CMD_NONE,
    CMD_READ_HEADER,
    CMD_CREATE_HEADER,
    CMD_LIST_EMPLOYEES,
    CMD_READ_EMPLOYEE,
    CMD_ADD_EMPLOYEE,
    CMD_EDIT_EMPLOYEE,
    CMD_REMOVE_EMPLOYEE
} command_code_t;

struct command_t {
    const char *filepath;
    command_code_t type;
    int targetID;
    char *employeeDeclaration;
};

struct dbheader_t {
    unsigned int magic;
    unsigned int filesize;
    unsigned short version;
    unsigned short count;
};

struct employee_t {
    unsigned short userID;
    char name[256];
    char address[256];
    unsigned short hours;
};

#endif