#pragma once

#include <cstdint>

struct region;
struct hull;
struct vector3d;

struct lego_render_visitor {
    std::intptr_t m_vtbl;

    //0x0052DEC0
    lego_render_visitor(region *a2, const hull *a3, const vector3d &a4, float a5);
};
