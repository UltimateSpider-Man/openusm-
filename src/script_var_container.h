#pragma once

#include "chuck/vm/so_data_block.h"

struct script_library_class;
struct generic_mash_header;
struct generic_mash_data_ptrs;

struct script_var_container {
    so_data_block script_var_block;
    int (*script_var_to_addr)[2];
    int field_10;
    int *debug_info;
    int flags;

    //0x0059B9B0
    void un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *a5);

    //0x00599440
    void un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4);

    //0x005A0520
    void *get_script_var_address(const char *a2, script_library_class **a3);
};
