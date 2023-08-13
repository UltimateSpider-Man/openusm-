#pragma once

#include "mvector.h"

namespace als {

    struct als_meta_anim_base;

    struct als_meta_anim_table_shared
    {
        mVector<als_meta_anim_base> field_0;
        void *field_14;

        void unmash(mash_info_struct *a2, void *a3);
    };
} // namespace als
