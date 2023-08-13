#pragma once

#include "variable.h"
#include "vector3d.h"

struct sampling_window {
    char field_0[0x100];
    bool field_100;
    char tmp[3];

    sampling_window();

    void push_sample(Float a2, Float a3);
};

struct direction_sampling_window
{
    sampling_window field_0[3];
    vector3d field_30C;

    //0x0048B630
    vector3d average(Float a4);
};

extern Var<direction_sampling_window> up_sampling_window;
