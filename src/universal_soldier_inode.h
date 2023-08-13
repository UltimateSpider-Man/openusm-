#pragma once

#include "info_node.h"

struct from_mash_in_place_constructor;

namespace ai {

struct universal_soldier_inode : info_node {
    string_hash field_1C;
    int field_20[22];

    //0x006B58F0
    universal_soldier_inode(from_mash_in_place_constructor *a2);
};
} // namespace ai
