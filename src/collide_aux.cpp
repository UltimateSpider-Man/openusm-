#include "collide_aux.h"

#include "capsule.h"
#include "log.h"
#include "sphere.h"
#include "utility.h"

#include <cassert>
#include <cmath>

void compute_bounding_sphere_for_two_capsules(const capsule &cap0, const capsule &cap1, sphere *a3) {
    //sp_log("compute_bounding_sphere_for_two_capsules:");

    auto tmp = (cap0.base + cap0.end + cap1.base + cap1.end) * 0.25;

    float array_dist2[4];
    array_dist2[0] = (tmp - cap0.base).length2();
    array_dist2[1] = (tmp - cap0.end).length2();
    array_dist2[2] = (tmp - cap1.base).length2();
    array_dist2[3] = (tmp - cap1.end).length2();

    auto max_dist2 = *std::max_element(std::begin(array_dist2), std::end(array_dist2));

    a3->center = tmp;

    assert(max_dist2 >= 0.0f);

    float v20 = (cap0.radius >= cap1.radius ? cap0.radius : cap1.radius);

    a3->radius = std::sqrt(max_dist2) + v20;
}

void sub_5628F0(
    const vector3d &a1, Float a2, const vector3d &a3, Float a4, vector3d &center, float &radius) {
    center = (a1 + a3) * 0.5f;

    auto v8 = a1 - center;
    auto v19 = v8.length();

    auto v9 = a3 - center;
    auto v10 = v9.length();
    auto v11 = v10 - v19;

    auto delta = std::abs(v11);
    assert(delta < LARGE_EPSILON);

    auto v16 = v19 + a4;
    auto v17 = v19 + a2;
    radius = std::max(v17, v16) + EPSILON;
}

void collide_aux_patch() {
    SET_JUMP(0x005C3900, compute_bounding_sphere_for_two_capsules);
}
