#pragma once

#include "string_hash.h"

struct mash_info_struct;

struct interact_sound_entry
{
    string_hash field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;

    void unmash(mash_info_struct *a1, void *);
};
