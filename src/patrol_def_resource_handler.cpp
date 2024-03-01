#include "patrol_def_resource_handler.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

VALIDATE_SIZE(patrol_def_resource_handler, 0x14);

patrol_def_resource_handler::patrol_def_resource_handler(worldly_pack_slot *a2)
{
    this->m_vtbl = 0x00888AB4;
    this->my_slot = a2;
    this->field_10 = RESOURCE_KEY_TYPE_PATROL_DEF;
}

bool patrol_def_resource_handler::_handle(worldly_resource_handler::eBehavior a2, limited_timer *a3)
{
    TRACE("patrol_def_resource_handler::handle");

    return base_engine_resource_handler::_handle(a2, a3);
}

bool patrol_def_resource_handler::_handle_resource(worldly_resource_handler::eBehavior a2,
                                                  resource_location *a3)
{
    TRACE("patrol_def_resource_handler::_handle_resource");
    return (bool) THISCALL(0x00568BD0, this, a2, a3);
}

void patrol_def_resource_handler_patch()
{
    {
        FUNC_ADDRESS(address, &patrol_def_resource_handler::_handle);
        set_vfunc(0x00888AB8, address);
    }

    {
        FUNC_ADDRESS(address, &patrol_def_resource_handler::_handle_resource);
        set_vfunc(0x00888AC0, address);
    }
}
