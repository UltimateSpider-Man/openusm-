#pragma once

#include "mvector.h"
#include "resource_key.h"

struct mash_info_struct;
struct from_mash_in_place_constructor;
struct path_graph_node;
struct path_graph_edge;

struct path_graph {
    resource_key field_0;
    mVector<path_graph_node> field_8;
    mVector<path_graph_edge> field_1C;
    int field_30;

    //0x005DE080
    path_graph(from_mash_in_place_constructor *a2);

    //0x005DC3A0
    int destruct_mashed_class();

    //0x005DC3E0
    int unmash(mash_info_struct *a1, void *a3);
};
