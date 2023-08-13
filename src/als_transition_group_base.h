#pragma once

#include "mvector.h"
#include "mash_virtual_base.h"

namespace als
{
    struct transition_group_base : mash_virtual_base
    {
        //virtual
        void _unmash(mash_info_struct *, void *);

        int get_mash_sizeof() const;
    };

    struct implicit_transition_rule;
    struct explicit_transition_rule;
    struct layer_transition_rule;

    struct scripted_trans_group : transition_group_base
    {
        mVectorBasic<int> field_4;
        mVector<als::implicit_transition_rule> field_14;
        mVector<als::explicit_transition_rule> field_28;
        mVector<als::layer_transition_rule> *field_3C;

        scripted_trans_group();

        //virtual
        void _unmash(mash_info_struct *a1, void *);
    };
}

extern void als_transition_group_base_patch();
