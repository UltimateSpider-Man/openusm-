#pragma once

#include "mash_virtual_base.h"
#include "string_hash.h"

struct mash_info_struct;

namespace ai
{
    struct param_block;
}

namespace als
{
    struct category : mash_virtual_base
    {
        string_hash field_4;
        int field_8;
        ai::param_block *field_C;

        //
        void _unmash(mash_info_struct *, void *);

        int get_mash_sizeof() const;
    };
}

extern void als_category_patch();
