#pragma once

#include "float.hpp"

struct fx_cache {
    int field_0;
    int field_4;

    int field_8;
    char field_C;

    char field_D;

    char field_E;

    char field_F;

    fx_cache();

    //0x004D4FB0
    void frame_advance(Float a3);
};
