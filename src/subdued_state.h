#pragma once

#include "variable.h"

struct string_hash;

namespace ai {

struct subdued_state {
    subdued_state();

    static inline Var<string_hash> default_id{0x0096BFC4};
};

} // namespace ai
