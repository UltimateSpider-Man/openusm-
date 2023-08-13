#pragma once

#include "animation_controller.h"

#include "als_meta_anim_table_shared.h"
#include "nal_system.h"

struct actor;

struct nal_anim_controller : animation_controller {
    struct scene_anim_client {
        //0x00492890
        //virtual
        nalAnimClass<nalAnyPose>::nalInstanceClass *CreateInstance(nalAnimClass<nalAnyPose> *a2);

        //0x0049C090
        //virtual
        int Advance(
            nalAnimClass<nalAnyPose>::nalInstanceClass *a2, float a3, float a4, float a5, float a6);
    };

    //0x0049BCF0
    nal_anim_controller(actor *a2,
                        nalBaseSkeleton *a3,
                        unsigned int a4,
                        const als::als_meta_anim_table_shared *a5);
};
