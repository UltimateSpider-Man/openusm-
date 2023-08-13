#pragma once

#include "float.hpp"

struct wds_time_manager {
    float field_0;
    float field_4;
    float field_8;
    int field_C;
    float field_10;
    float field_14;
    float field_18;
    bool field_1C;

    wds_time_manager();

    //0x0051E7D0
    void frame_advance(Float a2);

    //0x0050D350
    float get_level_time();
};
