#include "layer_state_machine_shared.h"

#include "common.h"
#include "func_wrapper.h"
#include "utility.h"
#include "trace.h"

namespace als {

    VALIDATE_SIZE(layer_state_machine_shared, 0x48);

    layer_state_machine_shared::layer_state_machine_shared()
    {
        THISCALL(0x00444850, this);
    }

    void layer_state_machine_shared::_unmash(mash_info_struct *a1, void *a3)
    {
        TRACE("layer_state_machine_shared::unmash");

        if constexpr (1)
        {
            state_machine_shared::_unmash(a1, a3);
        }
        else
        {
            THISCALL(0x004AB690, this, a1, a3);
        }
    }
}

void als_layer_state_machine_shared_patch()
{
    {
        FUNC_ADDRESS(address, als::layer_state_machine_shared::_unmash);
        set_vfunc(0x0087E3A8, address);
    }
}
