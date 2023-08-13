#pragma once

#include "float.hpp"

struct game_axis {
    int field_0;
    int field_4;
    float field_8;
    float field_C;
    float field_10;
    int field_empty[7];

    game_axis();

    //0x0051D900
    void update(Float a2);
};
