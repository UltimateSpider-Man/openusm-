#pragma once

#include "generic_interface.h"
#include "mashable_vector.h"

struct conglomerate;
struct anim_map_ptr_entry;

struct animation_interface : generic_interface
{
    conglomerate *field_4;
    bool field_8;
    mashable_vector<anim_map_ptr_entry> field_C;

    void _un_mash(generic_mash_header *a2, void *a3, int a4, generic_mash_data_ptrs *a5);
};

extern void animation_interface_patch();
