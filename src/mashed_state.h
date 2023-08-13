#pragma once

#include "mash_virtual_base.h"
#include "param_block.h"

namespace ai {

struct mashed_state {
    param_block field_0;
    string_hash field_C;
    uint32_t field_10;
    mash::virtual_types_enum field_14;

    mashed_state();

    void unmash(mash_info_struct *, void *);

    string_hash get_name() const;

    bool operator>(const mashed_state &state);

    bool operator<(const mashed_state &state);

    static inline constexpr auto IS_INTERRUPT_STATE = 0;
};

} // namespace ai
