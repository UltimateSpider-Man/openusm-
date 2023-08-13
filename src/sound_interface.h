#pragma once

#include <cstdint>

#include "float.hpp"
#include "vector3d.h"
#include "generic_interface.h"

struct shared_sound_interface_info;

struct sound_emitter_id
{
    int field_0;
};

struct sound_interface : generic_interface {
    int field_4;
    bool field_8;
    sound_emitter_id field_C;
    shared_sound_interface_info *field_10;
    vector3d field_14;
    float field_20;
    float field_24;

    sound_interface();

    //0x004D1910
    static void frame_advance_all_sound_ifc(Float a3);
};
