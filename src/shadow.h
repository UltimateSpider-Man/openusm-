#pragma once

#include "float.hpp"

//0x0059B220
extern void send_shadow_projectors();

struct conglomerate;
struct vector3d;

//0x0059B090
extern bool render_projected_shadow(
    conglomerate &a1, Float a2, const vector3d &a3, const vector3d &a4, Float radius, Float fade);
