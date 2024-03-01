#include "glass_house_resource_handler.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

VALIDATE_SIZE(glass_house_resource_handler, 0x14);

glass_house_resource_handler::glass_house_resource_handler(worldly_pack_slot *a2)
{
    this->m_vtbl = 0x00888B04;
    this->my_slot = a2;
    this->field_10 = static_cast<resource_key_type>(39);
}

bool glass_house_resource_handler::_handle(worldly_resource_handler::eBehavior a2, limited_timer *a3)
{
    TRACE("glass_house_resource_handler::handle");

    return base_engine_resource_handler::_handle(a2, a3);
}

bool glass_house_resource_handler::_handle_resource(worldly_resource_handler::eBehavior a2,
                                                   resource_location *a3)
{
    TRACE("glass_house_resource_handler::handle_resource");

    return (bool) THISCALL(0x005730A0, this, a2, a3);
}

void glass_house_resource_handler_patch()
{
    {
        FUNC_ADDRESS(address, &glass_house_resource_handler::_handle);
        set_vfunc(0x00888B08, address);
    }

    {
        FUNC_ADDRESS(address, &glass_house_resource_handler::_handle_resource);
        set_vfunc(0x00888B10, address);
    }
}
