#pragma once

#include "float.hpp"

#include <cstdint>

struct force_generator {
    std::intptr_t m_vtbl;

    force_generator();

    //virtual
    bool is_active();

    //virtual
    void frame_advance(Float a4);
};
