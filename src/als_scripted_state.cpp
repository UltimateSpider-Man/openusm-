#include "als_scripted_state.h"

#include "func_wrapper.h"
#include "mash_info_struct.h"
#include "utility.h"
#include "trace.h"
#include "common.h"

namespace als
{
    VALIDATE_SIZE(scripted_state, 0x54u);
    VALIDATE_SIZE(base_layer_scripted_state, 0x58u);

    scripted_state::scripted_state()
    {
        THISCALL(0x004ACA80, this);
    }

    void scripted_state::_unmash(mash_info_struct *a1, void *a3)
    {
        TRACE("als::scripted_state::unmash");

        state::_unmash(a1, a3);

        a1->unmash_class_in_place(this->field_14, this);

        a1->unmash_class_in_place(this->field_18, this);
        a1->unmash_class_in_place(this->field_28, this);
        a1->unmash_class_in_place(this->field_3C, this);

#ifdef TARGET_XBOX
        {
            uint8_t class_mashed = -1;
            class_mashed = *a1->read_from_buffer(mash::SHARED_BUFFER, 1, 1);
            assert(class_mashed == 0xAF || class_mashed == 0);
        }
#endif

        if ( this->field_50 != nullptr )
        {
            a1->unmash_class(this->field_50, this
#ifdef TARGET_XBOX
                    , mash::NORMAL_BUFFER
#endif
                    );
        }
    }

    string_hash scripted_state::get_nal_anim_name() const
    {
        sp_log("0x%08X", m_vtbl);
        return this->field_14;
    }

    base_layer_scripted_state::base_layer_scripted_state()
    {
        THISCALL(0x00444000, this);
    }

    void base_layer_scripted_state::_unmash(mash_info_struct *a1, void *a3)
    {
        TRACE("base_layer_scripted_state::unmash");

        scripted_state::_unmash(a1, a3);
    }

}

string_hash * __fastcall scripted_state__get_nal_anim_name(als::scripted_state *self, void *, string_hash *a2)
{
    *a2 = self->get_nal_anim_name();
    return a2;
}

void als_scripted_state_patch()
{
    {
        FUNC_ADDRESS(address, &als::scripted_state::_unmash);
        set_vfunc(0x0087E1DC, address);
    }

    {
        auto address = &scripted_state__get_nal_anim_name;
        SET_JUMP(0x00493E90, address);
    }

    {
        FUNC_ADDRESS(address, &als::base_layer_scripted_state::_unmash);
        set_vfunc(0x0087E218, address);
    }
}
