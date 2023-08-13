#pragma once

#include "variable.h"

struct fixed_pool;

struct intersected_trajectory_t {
    intersected_trajectory_t();

    static inline Var<fixed_pool> pool{0x00937580};
};
