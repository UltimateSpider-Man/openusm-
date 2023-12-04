#pragma once

#include "fixedstring.h"
#include "nal_skeleton.h"
#include "variable.h"

struct actor;

namespace als {
struct animation_logic_system;
struct state_machine;
}

namespace als {
    struct als_meta_anim_base;

    struct als_nal_meta_anim {
        int field_0;
        int field_4;
        tlFixedString field_8;
        int field_28;
        int field_2C;
        nalBaseSkeleton *field_30;
        int field_34;
        int field_38;
        int field_3C;
        als_meta_anim_base *field_40;

        bool is_delay_create() const;

        void delay_create(actor *a2);

        //0x00493F20
        void create(als_meta_anim_base *a2);

        void *create_anim_inst(
            nalBaseSkeleton *a2,
            animation_logic_system *a3,
            state_machine *a4);

        static inline Var<int> vtbl_ptr {0x0095979C};
    };
}
