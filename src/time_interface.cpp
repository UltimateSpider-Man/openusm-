#include "time_interface.h"

#include "variables.h"
#include "common.h"
#include "entity.h"
#include "func_wrapper.h"

VALIDATE_SIZE(time_interface, 0x34);

time_interface::time_interface(entity *a2) {
    this->m_vtbl = 0x00883850;
    this->field_8 = 0;
    this->field_4 = a2;
    this->field_8 = 1;
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    if (!g_generating_vtables()) {
        this->field_C = 1.0;
        this->field_10 = 1.0;
        this->field_14 = 1.0;
        this->field_2C = 2;
        this->field_18 = 0;
        this->field_1C = 0;
        this->field_20 = 0;
        this->field_24 = 0;
        this->field_28 = 0;
        this->field_30 = 0;
        this->add_to_time_ifc_list();
    }
}

void time_interface::frame_advance_all_time_interfaces(Float a1) {
    CDECL_CALL(0x004D18D0, a1);
}

void time_interface::add_to_time_ifc_list() {
    THISCALL(0x004D9870, this);
}

bool time_interface::is_combat_dilated() {
    auto *v1 = (int16_t *) this->field_30;
    return v1 && (v1[6] & 0x800) != 0;
}
