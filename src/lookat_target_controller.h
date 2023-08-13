#pragma once

#include "controller.h"
#include "euler_direction.h"
#include "float.hpp"
#include "vector3d.h"

struct entity_base;

struct lookat_target_controller : controller {
    entity_base *field_8;
    vector3d field_C;
    float field_18;
    euler_direction field_1C;

    //0x00529630
    lookat_target_controller(entity_base *a2);

    //0x0051D0F0
    //virtual
    void frame_advance(Float);
};
