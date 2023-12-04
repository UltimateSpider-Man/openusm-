#pragma once

#include "nal_anim_controller.h"

struct character_anim_controller : nal_anim_controller {
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;

    void play_base_layer_anim(
        nalAnimClass<nalAnyPose> *a2,
        Float a3,
        Float a4,
        bool a5,
        bool a6,
        void *a7);
};

extern void character_anim_controller_patch();
