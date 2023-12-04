#include "als_motion_compensator.h"

#include "actor.h"
#include "als_animation_logic_system.h"
#include "common.h"
#include "vtbl.h"

namespace als {

VALIDATE_SIZE(motion_compensator, 0x14);

void motion_compensator::activate(animation_logic_system *a2)
{
    this->field_4 = a2;
    this->field_8 = (als::state_machine *)this->field_4->get_als_layer_internal(static_cast<als::layer_types>(0));
    this->field_C = this->field_4->field_6C;
    this->field_10 = 10.0;
}

void motion_compensator::post_anim_action(Float a2)
{
    void (__fastcall *func)(void *, void *, Float) = CAST(func, get_vfunc(m_vtbl, 0x24));
    func(this, nullptr, a2);
}

}
