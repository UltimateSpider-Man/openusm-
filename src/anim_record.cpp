#include "anim_record.h"

#include "enum_anim_key.h"
#include "mash_info_struct.h"
#include "func_wrapper.h"
#include "utility.h"
#include "vtbl.h"

anim_record::anim_record()
{
    THISCALL(0x00695CE0, this);
}

void anim_record::_unmash(mash_info_struct *a2, void *a3)
{
    a2->unmash_class_in_place(this->field_8, this);
    if ( this->field_4 != nullptr )
    {
        a2->unmash_class(this->field_4, this
#ifdef TARGET_XBOX
            , mash::NORMAL_BUFFER
#endif
                );
    }
}

int anim_record::get_mash_sizeof()
{
    auto &func = get_vfunc(m_vtbl, 0x1C);
    return func(this);
}


void anim_record_patch()
{
    {
        FUNC_ADDRESS(address, &anim_record::_unmash);
        set_vfunc(0x0087392C, address);
    }
}
