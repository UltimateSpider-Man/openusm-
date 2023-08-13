#pragma once

#include "mstring.h"

struct fe_mission_text {
    int field_0[44];
    int field_B0;

    fe_mission_text();

    //0x0060D560
    void set_flavor(int a2);

    struct string {
        int field_0[2];
        char *data;
        int field_C;
    };

    //0x0060D440
    void set_text(string a2);

    //0x0061AA00
    void SetShown(bool a2);
};

extern void fe_mission_text_patch();
