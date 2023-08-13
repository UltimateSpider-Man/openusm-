#include "damage_interface.h"

#include "common.h"
#include "func_wrapper.h"
#include "resource_key.h"

VALIDATE_SIZE(damage_interface, 0x23Cu);

damage_interface::damage_interface()
{

}

damage_interface::damage_interface(actor *a2) {
    THISCALL(0x004DE8A0, this, a2);
}

bool damage_interface::get_ifc_num(const resource_key &att, float *a3, bool is_log) {
    assert(att.get_type() == RESOURCE_KEY_TYPE_IFC_ATTRIBUTE);

    return (bool) THISCALL(0x004C8C60, this, &att, a3, is_log);
}

bool damage_interface::set_ifc_num(const resource_key &att, Float a3, bool is_log) {
    assert(att.get_type() == RESOURCE_KEY_TYPE_IFC_ATTRIBUTE);

    return (bool) THISCALL(0x004CE940, this, &att, a3, is_log);
}

void damage_interface::frame_advance_all_damage_ifc(Float a1) {
    CDECL_CALL(0x004D1990, a1);
}
