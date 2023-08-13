#pragma once

#include "info_node.h"

#include "variable.h"

namespace ai {

struct std_default_trans_inode : info_node {
    int field_1C;
    int field_20;
    bool field_24;
    bool field_25;
    bool field_26;

    std_default_trans_inode();

    static const inline string_hash default_id{
        static_cast<int>(to_hash("std_default_trans_inode"))};
};

} // namespace ai
