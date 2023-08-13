#pragma once

#include "float.hpp"

#include <cstdint>

struct spawnable {
    std::intptr_t m_vtbl;
    bool field_4;
    bool field_5;

    //0x006D8610
    static void advance_traffic_and_peds(Float a1);
};
