#pragma once

#include "param_block.h"
#include "resource_key.h"

namespace ai {
struct ai_core;
}

struct base_ai_data {
    resource_key field_0;
    ai::param_block field_8;
    ai::ai_core *field_14;

    //0x006BDB00
    void post_entity_mash();

    //0x006D7310
    void destruct_mashed_class();
};
