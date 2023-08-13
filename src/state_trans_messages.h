#pragma once

namespace ai {

inline constexpr auto TRANS_TOTAL_MSGS = 75;

inline constexpr auto TRANS_MACHINE_EXIT_REQUEST_MSG = 0;

struct state_trans_messages {
    int field_0;

    state_trans_messages();

    state_trans_messages(int a1) : field_0(a1) {}

    operator int() {
        return field_0;
    }
};
} // namespace ai
