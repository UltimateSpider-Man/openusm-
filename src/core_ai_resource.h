#pragma once

#include "mvector.h"
#include "param_block.h"

struct combo_system;
struct resource_pack_slot;
struct resource_key;
struct from_mash_in_place_constructor;
struct mash_info_struct;

namespace ai {
struct core_ai_resource {
    param_block field_0;
    int field_C;
    combo_system *field_10;
    mVector<resource_key> field_14;
    mVector<resource_key> my_locomotion_graphs;
    resource_pack_slot *field_3C;
    int field_40;
    char field_44;

    //0x006D9A10
    core_ai_resource(from_mash_in_place_constructor *a2);

    //0x006D71F0
    void unmash(mash_info_struct *info_struct, void *a3);

    //0x006D71A0
    int destruct_mashed_class();

    //0x006C4D00
    bool does_locomotion_graph_exist(resource_key the_graph);
};
} // namespace ai
