#pragma once

#include "float.hpp"
#include "color32.h"

struct vector3d;
struct entity;

struct beam {
    beam();

    //0x005406D0
    void _render(Float a1);

    //0x0051CED0
    static void frame_advance_all_beams(Float a3);
};

extern void beam_patch();
