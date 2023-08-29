#pragma once

#include "mvector.h"
#include "string_hash.h"

struct actor;

namespace als {

    struct als_meta_anim_base;
    struct als_nal_meta_anim;

    struct als_meta_anim_table_shared
    {
        mVector<als_meta_anim_base> field_0;
        als_nal_meta_anim *field_14;

        void unmash(mash_info_struct *a2, void *a3);

        als_nal_meta_anim *get_nal_meta_anim(
            string_hash a2,
            actor *a3) const;
    };
} // namespace als
