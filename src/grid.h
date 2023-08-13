#pragma once

#include "vector4d.h"

inline constexpr auto MAX_3DGRID_BITS = 32;

struct Grid {
    vector4d field_0;
    vector4d field_10;
    vector4d field_20;
    vector4d field_30;
    vector4d field_40;
    vector4d field_50;
    uint32_t field_60[MAX_3DGRID_BITS * MAX_3DGRID_BITS];

    Grid();

    bool sub_48CEB0(const vector4d &a2);

    void sub_48CD70(
        const vector4d &a2, int &minx, int &miny, int &minz, int &maxx, int &maxy, int &maxz);
};
