#pragma once

#include "generic_interface.h"

struct script_data_interface : generic_interface
{
    char field_0[0x88];

    void _un_mash(generic_mash_header *a2, void *a3, void *a4, generic_mash_data_ptrs *a5);
};

extern void script_data_interface_patch();
