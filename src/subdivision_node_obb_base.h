#pragma once

#include "fixed_vector.h"
#include "float.hpp"
#include "obb_closest_point_entry.h"

struct vector3d;

struct subdivision_node_obb_base {
    int field_0;
    float field_4[3];
    int field_10;
    uint16_t field_14;
    uint16_t field_16;
    vector3d field_18;
    float field_24[3];
    float field_30[3];
    vector3d field_3C;

    subdivision_node_obb_base();

    int get_type();

    bool is_obb_node();

    //0x0052C580
    void get_extents(vector3d *min_extent, vector3d *max_extent);

    //0x00513100
    void get_vertices(vector3d *out);

    float *sub_564D50(float *a2);

    float sub_52CA80();

    bool sub_564E80(vector4d &a2, vector4d &a3, vector4d &a4, vector4d &a5);

    //0x0052B880
    bool line_segment_intersection(const vector3d &arg0, const vector3d &arg4);

    //0x00538D60
    bool line_segment_intersection(
        const vector3d &a1,
        const vector3d &a2,
        vector3d *a3,
        vector3d *a4,
        float *a5,
        bool a6);

    bool sphere_intersection(
        const vector3d &arg0, Float arg4, vector3d *arg8, vector3d *argC, float *arg10);

    //0x0052C440
    bool sphere_intersection(const vector3d &center, Float radius);

    //0x0052BD30
    bool point_inside_or_on(const vector3d &a2);

    //0x005391F0
    bool find_closest_point_on_visible_faces(const vector3d &sweet_spot,
                                             const vector3d &ent_pos,
                                             fixed_vector<obb_closest_point_entry_t, 3> *results);

    static inline Var<int> visit_key{0x0095C894};
};
