#pragma once

#include "variable.h"

struct fixed_pool;

struct dirty_sphere_t {
    dirty_sphere_t();

    static inline Var<fixed_pool> pool{0x0};
};
