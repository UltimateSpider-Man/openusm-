#include "loaded_regions_cache.h"

#include "fixed_vector.h"
#include "vector3d.h"
#include "vector4d.h"

loaded_regions_cache::loaded_regions_cache() {}

void loaded_regions_cache::get_regions_intersecting_sphere(const vector3d &a1,
                                                           Float a2,
                                                           fixed_vector<region *, 15> *a3) {
    vector4d v5;
    v5[0] = a1[0];
    v5[1] = a1[1];
    v5[2] = a1[2];
    v5[3] = a2;
    sub_565BF0(v5, a3);
}
