#pragma once

#include "mvector.h"
#include "string_hash.h"

struct mash_info_struct;

namespace als
{
    struct dest_weight_data;
    struct post_kill_rule;
    struct post_layer_alter;

    namespace basic_rule_data {
        struct rule_action {
            int field_0;
            mVector<als::dest_weight_data> *field_4;
            string_hash field_8;

            void unmash(mash_info_struct *, void *);
        };

        struct post_action_rule_set
        {
            mVector<als::post_kill_rule> field_0;
            mVector<als::post_layer_alter> field_14;

            void unmash(mash_info_struct *, void *);
        };
    }
}

