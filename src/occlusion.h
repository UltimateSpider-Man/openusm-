#pragma once

#include "plane.h"
#include "variable.h"
#include "vector3d.h"

struct occlusion {
    struct quad {
        int field_0[12];
    };

    struct quad_shadow_volume
    {
        vector3d field_0[4];
        plane field_30[5];
        int field_80;
        vector3d field_84;
    };

    occlusion();

    //0x00510800
    static void add_quad_to_database(const occlusion::quad &a1);

    static void debug_render_occluders();

    //0x00510840
    static void empty_quad_database();

    //0x0095C880
    static Var<occlusion::quad *> quad_database;

    //0x0095C884
    static Var<int> quad_database_count;

    //0x0095C87C
    static Var<bool> initialized;

    //0x0095C88C
    static Var<int> num_active_shadow_volumes;

    static inline Var<quad_shadow_volume [14]> active_shadow_volumes {0x0095CC08};
};
