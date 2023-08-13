#pragma once

#include "info_node.h"

struct from_mash_in_place_constructor;

struct venom_inode : ai::info_node {
    int field_1C[40];

    //0x0072F650
    venom_inode(from_mash_in_place_constructor *a2);
};
