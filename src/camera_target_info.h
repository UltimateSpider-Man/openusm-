#pragma once

#include "float.hpp"
#include "vector3d.h"

struct entity;
struct actor;

struct camera_target_info {
    vector3d pos;
    vector3d field_C;
    float radius;
    float min_look_dist;
    float field_20;
    vector3d field_24;
    vector3d up;
    vector3d facing;
    vector3d field_48;
    actor *field_54;
    int field_58;

    //0x004B3DC0
    camera_target_info(entity *target, Float a3, const vector3d &a4, const vector3d &a5);

    //0x004B28A0
    int get_loco_mode() const;
};

extern void camera_target_info_patch();
