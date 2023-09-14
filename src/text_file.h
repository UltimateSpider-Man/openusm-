#pragma once

#include "os_file.h"

struct text_file : os_file {
    mString field_34;
    void *field_44;
    int field_48;
    int field_4C;
    char field_50;
    int field_54;

    //0x005BC240
    text_file();

    //0x005BC4B0
    bool is_open();

    //0x005D2DD0
    void read(char *a2, int a3);

    //0x005D26C0
    void read(int *a2);
};
