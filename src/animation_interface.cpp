#include "animation_interface.h"

#include "common.h"
#include "trace.h"
#include "utility.h"

VALIDATE_SIZE(animation_interface, 0x14);

void animation_interface::_un_mash(generic_mash_header *a2, void *a3, int , generic_mash_data_ptrs *a5)
{
    TRACE("animation_interface::un_mash");

    this->field_4 = static_cast<conglomerate *>(a3);
    this->field_8 = false;
    this->field_C.custom_un_mash(a2, &this->field_C, a5, this);
}

void animation_interface_patch()
{
    {
        FUNC_ADDRESS(address, &animation_interface::_un_mash);
        set_vfunc(0x00883D00, address);
    }
}
