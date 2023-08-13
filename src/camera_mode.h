#pragma once

#include "float.hpp"

#include <cstdint>

struct camera_target_info;
struct spiderman_camera;

struct camera_mode {
    std::intptr_t m_vtbl;
    spiderman_camera *field_4;
    camera_mode *field_8;

    camera_mode();

    /* virtual */ void request_recenter(Float a2, const camera_target_info &a3);
};
