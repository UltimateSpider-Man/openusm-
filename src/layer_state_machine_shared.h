#pragma once

#include "state_machine_shared.h"

namespace als
{
    struct layer_state_machine_shared : state_machine_shared
    {
        int field_40;
        int field_44;

        layer_state_machine_shared();

        //virtual
        void _unmash(mash_info_struct *a1, void *a3);

    };
}

extern void als_layer_state_machine_shared_patch();
