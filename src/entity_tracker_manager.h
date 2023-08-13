#pragma once

#include "slot_pool.h"

#include <cstdint>

struct entity_tracker;
struct vector3d;

struct entity_tracker_manager {
    int field_0[3];
    slot_pool<entity_tracker *, unsigned int> field_C;

    //0x00629E30
    entity_tracker *id_to_ptr(uint32_t a2);

    //0x0062EE10
    bool get_the_arrow_target_pos(vector3d *);
};
