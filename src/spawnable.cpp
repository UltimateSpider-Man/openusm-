#include "spawnable.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

VALIDATE_SIZE(spawnable, 0x8);

spawnable::spawnable(vhandle_type<entity> a2)
{
    this->m_vtbl = 0x008A59FC;
    if ( spawnable_lanes() == nullptr )
    {
        spawnable_lanes() = new _std::vector<traffic_path_graph::laneInfoStruct> {};
        spawnable_lanes()->reserve(30u);
    }

    this->field_4 = true;
    this->field_5 = true;
}

void spawnable::advance_traffic_and_peds(Float a1) {
    TRACE("spawnable::advance_traffic_and_peds");

    CDECL_CALL(0x006D8610, a1);
}

void spawnable::un_spawn()
{
    void (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x4));
    func(this);
}

actor *spawnable::get_my_actor()
{

    actor * (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0xC));
    return func(this);
}

void spawnable_patch()
{
    {
        REDIRECT(0x0055842F, spawnable::advance_traffic_and_peds);
    }
}
