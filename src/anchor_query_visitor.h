#pragma once

#include "fixed_vector.h"
#include "quick_anchor_info.h"
#include "subdivision_visitor.h"
#include "vector3d.h"

struct subdivision_node;
struct conglomerate;
struct conglomerate_clone;

struct Grid;

struct anchor_query_visitor : subdivision_visitor {
    fixed_vector<quick_anchor_info, 100> *field_4;
    vector3d field_8;
    vector3d field_14;
    bool field_20;
    Grid *field_24;

    anchor_query_visitor() = default;

    anchor_query_visitor(fixed_vector<quick_anchor_info, 100> *a2,
                         const vector3d &a1,
                         const vector3d &a4,
                         bool a5,
                         Grid *a6);

    //0x004901E0
    void add_quick_anchor(conglomerate *anchor, conglomerate_clone *clone_ptr);

    //0x004860D0
    /* virtual */ int visit(subdivision_node *a2);
};

extern void anchor_query_visitor_patch();
