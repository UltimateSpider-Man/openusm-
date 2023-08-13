#pragma once

struct generic_mash_header;
struct generic_mash_data_ptrs;

struct city_gradients {
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;

    //0x00527690 
    void un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *a5);

    //0x0051ACD0
    void un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *a4);
};
