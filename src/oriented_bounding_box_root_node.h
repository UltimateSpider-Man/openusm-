#pragma once

#include "subdivision_node_obb_base.h"
#include "color32.h"
#include "float.hpp"

struct vector3d;
struct subdivision_visitor;
struct proximity_map;

struct oriented_bounding_box_root_node {
    char field_0[0x5C];
    proximity_map *field_5C;

    oriented_bounding_box_root_node();

    void set_color(color32 a2);

    //0x00522E50
    void traverse_sphere(const vector3d &a2, Float a3, subdivision_visitor *a4);
};
