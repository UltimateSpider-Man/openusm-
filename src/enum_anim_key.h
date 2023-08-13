#pragma once

#include <cstdint>

#include "mash_virtual_base.h"

struct enum_anim_key {
    struct key_enum {
        key_enum() = default;

        key_enum(int a1) : field_0(a1) {}

        int field_0;
    };

    std::intptr_t m_vtbl = 0x00873908;
    key_enum field_4;
};

#if 0
struct anim_key : enum_anim_key {
    //0x0068DE50
    static int compare(anim_key **a1, int *a2);
};
#else
struct anim_key : mash_virtual_base {

    anim_key();

    int get_mash_sizeof();
};
#endif

