#pragma once

struct generic_mash_header;
struct generic_mash_data_ptrs;

struct anim_info
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;

    void un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4);
};
