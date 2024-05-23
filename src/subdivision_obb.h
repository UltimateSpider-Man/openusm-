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

struct subdivision_node_large_obb {
    char field_0[4];
    vector3d field_4;
    int field_10;
    uint16_t field_14;
    vector3d field_18;
    vector3d field_24;
    vector3d field_30;
    float x_length;
    float y_length;
    float z_length;

    //0x00513770
    bool init(
        uint16_t a2,
        uint32_t a3,
        const vector3d &a4,
        const vector3d &a5,
        const vector3d &a6,
        const vector3d &a7);
};
