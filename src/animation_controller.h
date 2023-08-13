#pragma once

#include <cstdint>

struct actor;
struct nalBaseSkeleton;
struct po;

namespace als {
struct als_meta_anim_table_shared;
}

struct animation_controller {
    std::intptr_t m_vtbl;
    actor *field_4;
    nalBaseSkeleton *field_8;
    als::als_meta_anim_table_shared *field_C;

    void get_camera_root_abs_po(po &arg0);
};
