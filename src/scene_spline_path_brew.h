#pragma once

#include "progress.h"
#include "traffic_path_brew.h"

#include <cstdint>

struct worldly_pack_slot;

struct scene_spline_path_brew {
    progress field_0;
    int field_4;
    worldly_pack_slot *field_8;
    int field_C;
    uint8_t *field_10;
    int field_14;
    int parse_code;
    traffic_path_brew field_1C;

    scene_spline_path_brew();
};
