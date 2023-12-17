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

    layer_types layer_state_machine_shared::_get_layer_id() const
    {
        TRACE("als::layer_state_machine_shared::get_layer_id");

        return this->field_44;
    }

    void layer_state_machine_shared::set_layer_id(layer_types a2)
    {
        TRACE("als::layer_state_machine_shared::set_layer_id");
        
        this->field_44 = a2;
    }
}

void als_layer_state_machine_shared_patch()
{
    {
        FUNC_ADDRESS(address, als::layer_state_machine_shared::_unmash);
        set_vfunc(0x0087E3A8, address);
    }

    {
        FUNC_ADDRESS(address, als::layer_state_machine_shared::set_layer_id);
        set_vfunc(0x0087E3C4, address);
    }
}
