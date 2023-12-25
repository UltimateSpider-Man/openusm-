#pragma once

#include "als_meta_anim_base.h"

struct nalAnyPose;

template<typename T>
struct nalAnimClass;

namespace als {

    struct meta_aimed_shot_vert : als_meta_anim_base {
        nalAnimClass<nalAnyPose> *field_28;
        void *field_2C;

        float get_anim_duration() const;
    };
}

extern void als_meta_aimed_shot_vert_patch();
