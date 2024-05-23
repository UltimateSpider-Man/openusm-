#pragma once

#include <cstdint>

#include "vector3d.h"

struct subdivision_node_large_aabb {

    char field_0[4];
    vector3d field_4;
    int field_10;
    uint16_t field_14;
    vector3d field_18;

    //0x005136F0
    bool init(uint16_t a2,
            uint32_t a3,
            const vector3d &a4,
            const vector3d &a5);

};
