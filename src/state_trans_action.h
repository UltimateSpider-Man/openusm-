#pragma once

#include "string_hash.h"

namespace ai {
struct param_block;

inline constexpr auto MACHINE_EXIT = 2;

struct state_trans_action {
    int the_action;
    string_hash field_4;
    int the_message;
    param_block *field_C;

    state_trans_action() = default;

    state_trans_action(int a1, string_hash a2, int a3, param_block *a4);

    //0x00401980
    state_trans_action(const state_trans_action &a2);

    state_trans_action &operator=(const state_trans_action &a2) = default;
};

} // namespace ai
