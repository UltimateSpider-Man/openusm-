#pragma once

#include "string_hash.h"
#include "als_basic_rule_data.h"

struct mash_info_struct;

namespace als
{
    namespace basic_rule_data
    {
        struct rule_action;
        struct post_action_rule_set;
    }

    struct filter_data;

    struct base_transition_rule
    {
        mVector<als::filter_data> field_0;
        als::basic_rule_data::rule_action field_14;
        als::basic_rule_data::post_action_rule_set *field_20;

        void unmash(mash_info_struct *, void *);
    };

    struct implicit_transition_rule : base_transition_rule
    {
        void unmash(mash_info_struct *a1, void *a3);
    };

    struct explicit_transition_rule : base_transition_rule {

        string_hash field_24;

        void unmash(mash_info_struct *a1, void *a3);
    };

    struct layer_transition_rule {
        int field_0;
        int field_4;
        basic_rule_data::rule_action field_8;
        int field_14;

        void unmash(mash_info_struct *, void *);
    };

    struct incoming_transition_rule : base_transition_rule {
        int field_24;
        int field_28;

        void unmash(mash_info_struct *a1, void *a3);
    };
}
