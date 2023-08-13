#include "als_meta_anim_base.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "vtbl.h"
#include "utility.h"

namespace als
{
    VALIDATE_SIZE(als_meta_anim_base, 0x28);

    int als_meta_anim_base::get_mash_sizeof() const
    {
        int (__fastcall *func)(const void *) = CAST(func, get_vfunc(m_vtbl, 0x38));
        return func(this);
    }

    void als_meta_anim_base::_unmash(mash_info_struct *, void *)
    {
        TRACE("als::als_meta_anim_base::unmash");
        ;
    }
}

void als_meta_anim_base_patch()
{
    {
        FUNC_ADDRESS(address, &als::als_meta_anim_base::_unmash);
        set_vfunc(0x0087545C, address);
    }
}

