#include "decal_data_interface.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(decal_data_interface, 0x80);

decal_data_interface::decal_data_interface()
{

}

bool decal_data_interface::is_dynamic() const
{
    return this->field_8;
}

void decal_data_interface::frame_advance_all_decal_interfaces(Float a1) {
    CDECL_CALL(0x004D1CC0, a1);
}
