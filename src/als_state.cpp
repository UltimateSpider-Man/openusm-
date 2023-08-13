#include "als_state.h"

#include "common.h"
#include "mash_info_struct.h"
#include "param_block.h"
#include "vtbl.h"
#include "trace.h"
#include "utility.h"

namespace als {

    VALIDATE_SIZE(state, 0x14);

    state::state()
    {

    }

    void state::_unmash(mash_info_struct *a2, void *a3)
    {
        TRACE("als::state::unmash");

        if constexpr (1)
        {
            a2->unmash_class_in_place(this->field_4, a3);
            a2->unmash_class_in_place(this->field_8, a3);

#ifdef TARGET_XBOX
            {
                uint8_t class_mashed = -1;
                class_mashed = *a2->read_from_buffer(mash::SHARED_BUFFER, 1, 1);
                assert(class_mashed == 0xAF || class_mashed == 0);
            }
#endif

            if ( this->field_10 != nullptr )
            {
                a2->unmash_class(this->field_10, a3
#ifdef TARGET_XBOX
                        , mash::NORMAL_BUFFER
#endif
                        );
            }

        }
        else
        {
            THISCALL(0x0049F050, this, a2, a3);
        }
    }

    int state::get_mash_sizeof() const
    {
        if constexpr (1)
        {
            auto &func = get_vfunc(m_vtbl, 0x38);
            return func(this);
        }

        return 0x14;
    }

} // namespace als

void als_state_patch()
{
    {
        FUNC_ADDRESS(address, &als::state::_unmash);
        //set_vfunc(0x008756CC, address);
    }

    {
        FUNC_ADDRESS(address, &als::state::get_mash_sizeof);
        //set_vfunc(0x, address);
    }
}
