#pragma once

#include "variable.h"

struct fixed_pool;

struct trajectory_cluster_t {
    trajectory_cluster_t();

    static inline Var<fixed_pool> pool{0x0};
};
