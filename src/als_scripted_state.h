#pragma once

#include "als_state.h"
#include "mvector.h"

struct mash_info_struct;

namespace als
{
    struct dest_weight_data
    {
        string_hash field_0;
        int field_4;
    };

    struct implicit_transition_rule;

    struct explicit_transition_rule;

    struct layer_transition_rule;

    struct scripted_state : state
    {
        string_hash field_14;
        mVectorBasic<int> field_18;
        mVector<als::implicit_transition_rule> field_28;
        mVector<als::explicit_transition_rule> field_3C;
        mVector<als::layer_transition_rule> *field_50;

        scripted_state();

        void _unmash(mash_info_struct *a1, void *a3);

        string_hash get_nal_anim_name() const;
    };

    struct base_layer_scripted_state : scripted_state
    {
        int field_54;

        base_layer_scripted_state();

        void _unmash(mash_info_struct *a1, void *a3);
    };
}

extern void als_scripted_state_patch();
