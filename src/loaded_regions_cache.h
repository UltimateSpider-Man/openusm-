#pragma once

#include <cstdint>

#include "float.hpp"

struct vector3d;
struct region;

template<typename T, uint32_t>
struct fixed_vector;

struct loaded_regions_cache {
    loaded_regions_cache();

    static void get_regions_intersecting_sphere(const vector3d &a1,
                                                Float a2,
                                                fixed_vector<region *, 15> *a3);
};
