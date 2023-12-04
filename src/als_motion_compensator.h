#pragma once

#include "mash_virtual_base.h"
#include "float.hpp"

struct entity_base;

namespace als {

struct animation_logic_system;
struct state_machine; 

struct motion_compensator : mash_virtual_base {
    animation_logic_system *field_4;
    state_machine *field_8;
    entity_base *field_C;
    float field_10;

    void activate(animation_logic_system *a2);

    //virtual
    void post_anim_action(Float a2);

};

}
