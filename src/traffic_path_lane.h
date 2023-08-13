#pragma once

#include <cstdint>

struct vector3d;
struct traffic_path_road;

struct traffic_path_lane {
    struct eLaneType {
        int field_0;
    };

    vector3d *field_0;
    traffic_path_road *field_4;
    uint16_t field_C;

    vector3d sub_5E2040();

    vector3d sub_5E2000(int a3);

    vector3d get_node_before_point(const vector3d &a3, int *a4);
};
