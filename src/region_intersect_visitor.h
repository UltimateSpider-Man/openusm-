#pragma once

#include "subdivision_visitor.h"

#include "vtbl.h"

struct subdivision_node;
struct region;

struct region_intersect_visitor : subdivision_visitor {
    int field_4;
    region *field_8[15];

    region_intersect_visitor(region *r);

    int visit(subdivision_node *a1);
};
