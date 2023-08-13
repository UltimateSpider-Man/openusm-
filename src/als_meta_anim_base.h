#pragma once

#include "mash_virtual_base.h"
#include "fixedstring.h"

namespace als
{
    struct als_meta_anim_base : mash_virtual_base
    {
        int field_4;
        tlFixedString field_8;

        //virtual
        void _unmash(mash_info_struct *a1, void *a3);

        //virtual
        int get_mash_sizeof() const;
    };
}

extern void als_meta_anim_base_patch();
