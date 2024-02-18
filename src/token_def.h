#pragma once

#include "vector3d.h"

struct region;

struct token_def {
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    vector3d field_10;
    int field_1C;
    int field_20;
    int field_24;
    region *field_28;
    int field_2C;

    token_def();

    void show_dot(bool a2);
};
