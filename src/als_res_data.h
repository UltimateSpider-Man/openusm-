#pragma once

#include "resource_key.h"

struct mash_info_struct;

namespace als {
struct animation_logic_system;
}

struct als_res_data {
    resource_key field_0;
    als::animation_logic_system *field_8;
    int field_C;

    als_res_data();

    void unmash(mash_info_struct *a2, void *a3);
};
