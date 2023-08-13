#pragma once

#include "resource_key.h"

struct mash_info_struct;

struct combo_system_weapon {
    resource_key field_0;
    resource_key field_8;
    resource_key field_10;
    string_hash field_18;
    string_hash field_1C;
    int field_20;

    combo_system_weapon();

    void unmash(mash_info_struct *a1, void *a3);
};
