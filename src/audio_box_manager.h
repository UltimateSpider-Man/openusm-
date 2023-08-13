#pragma once

#include "float.hpp"
#include "variable.h"

struct audio_box_manager {
    //0x005100E0
    static void create_inst();

    //0x00552610
    static void frame_advance(Float a1);
};

extern Var<int> s_holds;
