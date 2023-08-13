#pragma once

#include "mashable_vector.h"
#include "mstring.h"

struct sin_strip_container;

struct sin_container {
    char *master_script_name;
    char *field_4;
    int field_8;
    int field_C[6];

    mashable_vector<sin_strip_container> field_24;
    int field_2C;

    //0x0055BB00
    void setup_world();

    //0x0055F530
    mString *get_master_script_name(mString *out);

    //0x0052AF50
    void un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *);

    //0x00520B00
    void un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4);

    [[nodiscard]] mString sub_55F530();
};

extern void sin_container_patch();
