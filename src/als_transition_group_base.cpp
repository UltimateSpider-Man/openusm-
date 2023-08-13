#include "als_transition_group_base.h"

#include "trace.h"
#include "utility.h"
#include "vtbl.h"
#include "common.h"

namespace als
{
    VALIDATE_SIZE(transition_group_base, 0x4);
    VALIDATE_SIZE(scripted_trans_group, 0x40u);

    void transition_group_base::_unmash(mash_info_struct *, void *)
    {
        ;
    }

    scripted_trans_group::scripted_trans_group()
    {
        THISCALL(0x004AC950, this);
    }

    void scripted_trans_group::_unmash(mash_info_struct *a1, void *)
    {
        TRACE("scripted_trans_group::unmash");

        a1->unmash_class_in_place(this->field_4, this);

        a1->unmash_class_in_place(this->field_14, this);

        a1->unmash_class_in_place(this->field_28, this);

#ifdef TARGET_XBOX
        {
            uint8_t class_mashed = -1;
            class_mashed = *a1->read_from_buffer(mash::SHARED_BUFFER, 1, 1);
            assert(class_mashed == 0xAF || class_mashed == 0);
        }
#endif

        if ( this->field_3C != nullptr )
        {
            a1->unmash_class(this->field_3C, this
#ifdef TARGET_XBOX
                , mash::NORMAL_BUFFER
#endif
                    );
        }
    }

    int transition_group_base::get_mash_sizeof() const
    {
        auto &func = get_vfunc(m_vtbl, 0x1C);
        return func(this);
    }
}

void als_transition_group_base_patch()
{
    {
        FUNC_ADDRESS(address, &als::scripted_trans_group::_unmash);
        set_vfunc(0x0087E1BC, address);
    }
}
