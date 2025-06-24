#ifndef STRUCTS.H
#define STRUCTS.H
#define MAGIC_NUM = 0x18CE962


struct dbheader_t {
    unsigned int magic_numer;
    unsigned int filesize;
    unsigned short version;
    unsigned short count;
};

struct employee_t {
    char buff[256];
    char address[256];
    unsigned short hours;
};

#endif