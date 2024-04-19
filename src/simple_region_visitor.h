#pragma once

#include "subdivision_visitor.h"

#include "vector3d.h"

#include <cstdint>

struct region;
struct subdivision_node;

inline constexpr auto MAX_REGIONS_TO_FIND_FROM_POINT = 4;

struct simple_region_visitor : subdivision_visitor {
    vector3d field_4;
    int region_count;
    void *field_14[MAX_REGIONS_TO_FIND_FROM_POINT];

    bool field_24;

    simple_region_visitor(const vector3d &a2, bool a3);

    //0x00560210
    //virtual
    int visit(subdivision_node *a2);
};
