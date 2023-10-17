#pragma once

#include "fixedstring.h"
#include "mashable_vector.h"

struct generic_mash_header;
struct generic_mash_data_ptrs;
struct mString;

struct resource_pack_group {
    int field_0;
    int field_4;
    mashable_vector<fixedstring<4>> field_8;
    int *field_10;
    uint8_t *field_14;
    int field_18;
    int field_1C;

    //0x00531EA0
    int get_first_free_slot();

    //0x0054C950
    int get_pack_slot(const mString &a2);

    int get_num_free_slots() const;

    //0x0051F070
    void un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4);
};
