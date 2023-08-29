#pragma once

#include "fixedstring.h"

struct actor;

namespace als {
    struct als_meta_anim_base;

    struct als_nal_meta_anim {
        int field_0;
        int field_4;
        tlFixedString field_8;
        int field_28;
        int field_2C;
        int field_30;
        int field_34;
        int field_38;
        int field_3C;
        als_meta_anim_base *field_40;

        bool is_delay_create() const;

        void delay_create(actor *a2);

        //0x00493F20
        void create(als_meta_anim_base *a2);
    };
}
