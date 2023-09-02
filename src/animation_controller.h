#pragma once

#include "als_layer_types.h"
#include "float.hpp"

#include <cstdint>

struct actor;
struct nalBaseSkeleton;
struct po;
struct string_hash;

namespace als {
struct als_meta_anim_table_shared;
}

struct animation_controller {

    struct anim_ctrl_handle {
        bool field_0;
        float field_4;
        animation_controller *field_8;

        void set_anim_speed(Float a2);

        bool is_anim_active();
    };

    std::intptr_t m_vtbl;
    actor *field_4;
    nalBaseSkeleton *field_8;
    als::als_meta_anim_table_shared *field_C;

    void get_camera_root_abs_po(po &arg0);

    anim_ctrl_handle play_layer_anim(
            const string_hash &a3,
            unsigned int a4,
            Float a5,
            unsigned int a6,
            bool a7,
            als::layer_types);

    anim_ctrl_handle play_base_layer_anim(
        const string_hash &a3,
        Float a4,
        uint32_t a5,
        bool a6);

    //virtual
    bool is_anim_active(float a1);
};

//0x0049B910
extern void *get_anim_by_hash(
        const string_hash &a1,
        const als::als_meta_anim_table_shared *a2,
        actor *a3);

extern void animation_controller_patch();
