#include "sampling_window.h"

#include "common.h"
#include "func_wrapper.h"

Var<direction_sampling_window> up_sampling_window{0x009588A8};

VALIDATE_SIZE(sampling_window, 0x104);

sampling_window::sampling_window() {}

void sampling_window::push_sample(Float a2, Float a3) {
    THISCALL(0x00527040, this, a2, a3);
}

vector3d direction_sampling_window::average(Float a4) {
    vector3d result;
    THISCALL(0x0048B630, this, &result, a4);

    return result;
}
