#pragma once

#include "vector3d.h"

inline constexpr auto MIN_CAPSULE_RADIUS = 0.0099999998f;

struct capsule {
    vector3d base;
    vector3d end;
    float radius;

    capsule() = default;

    capsule(const vector3d &a2, const vector3d &a3, Float a4);
};
