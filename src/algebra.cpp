#include "algebra.h"

#include "vector3d.h"

#include <cassert>

vector3d sub_87D3A0(const vector3d &a1, const vector3d &normal)
{
    assert(normal.is_normal());

    auto a3 = dot(a1, normal);
    auto v3 = normal * a3;
    return (a1 - v3);
}
