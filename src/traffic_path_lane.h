#pragma once

#include <cstdint>

struct entity;
struct vector3d;
struct traffic_path_graph;
struct traffic_path_road;

struct traffic_path_lane {
    struct eLaneType {
        int field_0;
    };

    vector3d *field_0;
    traffic_path_road *my_road;
    uint16_t total_nodes;
    uint16_t flags;

    bool is_valid(traffic_path_graph *a2) const;

    int get_type() const;

    int get_num_nodes() const
    {
        return this->total_nodes;
    }

    vector3d sub_5E2040();

    vector3d sub_5E2000(int a3);

    void sub_5CCFB0(entity *ent, int a3);

    vector3d get_node_before_point(const vector3d &a3, int *a4);

    static bool lane_is_valid(const traffic_path_lane *a1);
};

extern void traffic_path_lane_patch();
