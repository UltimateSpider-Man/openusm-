#pragma once

#include "hero_base_state.h"

#include "float.hpp"

struct string_hash;

namespace ai {

struct spidey_base_state : hero_base_state {
    spidey_base_state();

    //0x00488680
    /* virtual */ string_hash get_desired_state_id(Float a3) const /* override */;
};

} // namespace ai

extern void spidey_base_state_patch();
