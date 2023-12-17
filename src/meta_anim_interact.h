#pragma once

#include "als_meta_anim_base.h"
#include "mvector.h"
#include "string_hash.h"

struct mash_info_struct;

namespace ai
{
    struct meta_anim_interact : als::als_meta_anim_base
    {
        int field_28;
        int field_2C;

        meta_anim_interact();

        void _unmash(mash_info_struct *, void *);
    };

    struct meta_anim_strength_test : als::als_meta_anim_base
    {
        int field_28;
        int field_2C;
        bool field_30;
        int field_34;

        meta_anim_strength_test();

        //virtual
        void _unmash(mash_info_struct *, void *);
    };
}

namespace als
{
    struct meta_key_anim {
        string_hash field_0;
        int field_4;
        int field_8;
        int field_C;

        void unmash(mash_info_struct *a1, void *);
    };

    struct als_meta_linear_blend : als_meta_anim_base
    {
        mVector<als::meta_key_anim> field_28;
        int field_3C;

        als_meta_linear_blend();

        //virtual
        void _unmash(mash_info_struct *, void *);
    };
}

extern void meta_anim_interact_patch();
