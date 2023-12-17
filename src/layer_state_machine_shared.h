#pragma once

#include "state_machine_shared.h"

#include "als_layer_types.h"

namespace als
{
    struct layer_state_machine_shared : state_machine_shared
    {
        int field_40;
        layer_types field_44;

        layer_state_machine_shared();

        //virtual
        void _unmash(mash_info_struct *a1, void *a3);

        //virtual
        layer_types _get_layer_id() const;

        //virtual
        void set_layer_id(layer_types a2);
    };
}

extern void als_layer_state_machine_shared_patch();
