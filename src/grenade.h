#pragma once

#include "actor.h"

#include "float.hpp"

struct grenade : actor {
    //0x00536580
    grenade(const string_hash &a2, unsigned int a3);

    void sub_4D6B10(int a2);

    //0x0051E070
    static void frame_advance_all_grenades(Float a3);
};
