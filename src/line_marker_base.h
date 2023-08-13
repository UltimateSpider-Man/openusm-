#pragma once

#include "marker.h"

struct vector3d;

struct line_marker_base : marker {
    vector3d field_68;
    vector3d field_74;
    int field_80;

    //0x0050A6E0
    line_marker_base(const string_hash &a2, uint32_t a3);

    //0x004E9020
    vector3d get_target();

    //0x004E9050
    vector3d get_origin();
};
