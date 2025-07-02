#ifndef STRUCTS_H
#define STRUCTS_H
#define MAGIC_NUM 0x18CE962


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