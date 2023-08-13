#pragma once

#include "mash.h"

struct actor;
struct combo_system_weapon;

namespace ai {

struct weapon_instance {
    int field_0;
    int field_4;

    weapon_instance();

    //0x006C8D80
    int initialize(mash::allocation_scope a2, const combo_system_weapon *a3, actor *a4);
};
} // namespace ai
