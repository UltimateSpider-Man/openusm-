#include "als_nal_meta_anim.h"

#include "als_meta_anim_base.h"
#include "common.h"
#include "trace.h"
#include "vtbl.h"

namespace als {

VALIDATE_SIZE(als_nal_meta_anim, 0x44);

bool als_nal_meta_anim::is_delay_create() const {
    TRACE("als_nal_meta_anim::is_delay_create");

    sp_log("0x%08X", this->field_40->m_vtbl);
    auto &func = get_vfunc(this->field_40->m_vtbl, 0x30);
    return (bool) func(this->field_40);
}

void als_nal_meta_anim::delay_create(actor *a2) {
    TRACE("als_nal_meta_anim::delay_create");

    auto &func = get_vfunc(this->field_40->m_vtbl, 0x34);
    func(this->field_40, a2);
    this->create(this->field_40);
}

void als_nal_meta_anim::create(als_meta_anim_base *a2) {
    TRACE("als_nal_meta_anim::create");

    THISCALL(0x00493F20, this, a2);
}

void *als_nal_meta_anim::create_anim_inst(
        nalBaseSkeleton *a2,
        animation_logic_system *a3,
        state_machine *a4)
{
    TRACE("als_nal_meta_anim::create_anim_inst");

    sp_log("0x%08X", this->field_40->m_vtbl);

    struct {
        char field_0[0x2C];
        void * (__fastcall *func)(void *, void *,
                nalBaseSkeleton *,
                als_nal_meta_anim *,
                animation_logic_system *,
                state_machine *);
    } *vtbl = CAST(vtbl, this->field_40->m_vtbl);
    return vtbl->func(this->field_40, nullptr,
           a2,
           this,
           a3,
           a4);
}


}
