#pragma once

#include <cstdint>

struct region;
struct ai_quad_path_cell;

struct ai_quad_path {
    int field_0[6];

    region *field_18;
    uint16_t field_1C;
    uint16_t field_1E;
    int field_20;
    ai_quad_path_cell *field_24;
    uint16_t field_28;
    uint16_t field_2A;
    int field_2C;
    int field_30;

    ai_quad_path();

    //0x00464FA0
    void un_mash(void *buffer_ptr, region *reg, int a4, int a5, int a6);
};
