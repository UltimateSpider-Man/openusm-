#include "vehicle.h"

#include "common.h"
#include "func_wrapper.h"
#include "wds.h"
#include "wds_entity_manager.h"

VALIDATE_SIZE(vehicle, 0x130);

VALIDATE_OFFSET(vehicle_model, refcount, 0x14);

vehicle::vehicle()
{

}

bool vehicle::terminate_vehicles()
{
    return (bool) CDECL_CALL(0x006C12B0);
}

void vehicle_model::sub_6B9F30(vhandle_type<entity> a2)
{
    --this->refcount;
    auto *e = a2.get_volatile_ptr();
    g_world_ptr()->ent_mgr.release_entity(e);
}

