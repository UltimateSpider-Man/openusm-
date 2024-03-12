#pragma once

#include "mstring.h"

struct texture_to_frame_map {
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    bool field_24;
    bool from_mash;
    int total_textures;

    void un_mash(char *a2, int *a3);

    mString get_ifl_name() const;
};
