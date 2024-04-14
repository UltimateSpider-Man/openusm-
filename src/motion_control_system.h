#pragma once

#include <cstdint>

struct motion_control_system {
    std::intptr_t m_vtbl;

    motion_control_system();

    void * operator new(size_t size);
};
