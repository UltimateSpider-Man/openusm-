#pragma once

#include "string_hash.h"
#include "mvector.h"

namespace als
{
    struct alter_conditions;

    struct force_transitions
    {
        string_hash field_0;
        mVector<als::alter_conditions> field_4;

        void unmash(mash_info_struct *a1, void *);
    };
}
