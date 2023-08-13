#pragma once

#include "variable.h"
#include "subdivision_node.h"
#include "float.hpp"
#include "vector3d.h"

struct fixed_pool;
struct subdivision_visitor;
struct sector2d;
struct dynamic_proximity_map_stack;

struct proximity_map {

    enum proximity_map_type_t
    {
        DYNAMIC = 1
    };

    unsigned short field_0;
    proximity_map_type_t map_type;
    unsigned short field_8;
    vector3d field_C;
    vector3d field_18;
    vector3d field_24;
    vector3d field_30;
    vector3d field_3C;
    vector3d field_48;
    int number_of_cells;
    int log_number_of_cells;
    bool initialized;

    //0x005115E0
    int traverse_point(const vector3d &a2, subdivision_visitor &a3);

    //0x00522680
    void traverse_sector_raster(const sector2d &sec,
                                Float sector_radius,
                                subdivision_visitor &visitor);

    bool is_initialized();
};

struct dynamic_proximity_map : proximity_map
{

    //0x00522500
    void init(dynamic_proximity_map_stack *alloc, fixed_pool *a3, int number_of_cells_arg, const vector3d &a5, const vector3d &a6, subdivision_node::type_t a7);
};
