#pragma once

#include "float.hpp"
#include "motion_control_system.h"

#include <cstdint>

struct camera;

struct dolly_and_strafe_mcs : motion_control_system {
    bool field_4;
    bool field_5;
    camera *field_8;
    float field_C;
    float field_10;
    float field_14;

    dolly_and_strafe_mcs();

    //0x00526940
    int do_dolly(Float a2);

    //0x00526A30
    int do_strafe(Float a2);

    //0x00526B20
    int do_lift(Float a2);

    //0x0052E6B0
    //virtual
    void frame_advance(Float a2);
};
