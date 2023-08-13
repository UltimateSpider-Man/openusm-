#pragma once

#include "float.hpp"
#include "local_collision.h"

struct vector3d;

struct swing_anchor_obbfilter_t : local_collision::obbfilter_base {
    vector3d field_4;
    float field_10;

    swing_anchor_obbfilter_t(const vector3d &a1, Float a3);

    bool accept(subdivision_node_obb_base *a2, const local_collision::query_args_t &a3);
};

extern void swing_anchor_obbfilter_patch();
