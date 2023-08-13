#pragma once

#include <cstdint>

struct generic_mash_header;
struct generic_mash_data_ptrs;

struct resource_allocation_pool {
    int field_0;
    uint16_t count;
    int field_8;

    //0x0050E340
    void un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *);
};
