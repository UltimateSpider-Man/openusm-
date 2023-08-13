#pragma once

#include "string_hash.h"

struct mash_info_struct;

namespace als
{
    struct alter_conditions
    {
        int field_0;
        int field_4;
        string_hash field_8;

        void unmash(mash_info_struct *a1, void *a3);
    };
}
