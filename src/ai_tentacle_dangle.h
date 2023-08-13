#pragma once

#include <cstdint>

struct ai_tentacle_info;
struct dangler;

struct ai_tentacle_dangle {
    std::intptr_t m_vtbl;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    dangler *field_1C;
    bool field_20;
    bool field_21;

    //0x00470B70
    ai_tentacle_dangle(ai_tentacle_info *a2);
};
