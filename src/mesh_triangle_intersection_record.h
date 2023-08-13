#pragma once

#include "variable.h"
#include "vector3d.h"

struct fixed_pool;

struct mesh_triangle_intersection_record_t {
    vector3d field_0;
    int field_C;
    int field_10;
    mesh_triangle_intersection_record_t *field_14;

    static inline Var<fixed_pool> pool{0x00937110};
};
