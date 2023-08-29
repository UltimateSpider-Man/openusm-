#include "als_animation_logic_system.h"

#include "actor.h"
#include "als_animation_logic_system_shared.h"
#include "als_state.h"
#include "common.h"
#include "func_wrapper.h"
#include "physical_interface.h"
#include "time_interface.h"
#include "traffic.h"
#include "utility.h"

namespace als {

VALIDATE_SIZE(animation_logic_system, 0x80u);

animation_logic_system::animation_logic_system(actor *a1) {
    THISCALL(0x004ABB80, this, a1);
}

void animation_logic_system::change_mocomp() {
    THISCALL(0x00498F30, this);
}

void animation_logic_system::enter_biped_physics() {
    if constexpr (0) {
    } else {
        THISCALL(0x00498F70, this);
    }
}

void als::animation_logic_system::exit_biped_physics() {
    auto *v2 = this->field_6C->physical_ifc();
    v2->stop_biped_physics(false);

    v2->set_allow_manage_standing(true);
}

int animation_logic_system::create_instance_data(animation_logic_system_shared *a2) {
    return THISCALL(0x004ABC60, this, a2);
}

state_machine *animation_logic_system::get_als_layer(layer_types a2) {
    return bit_cast<als::state_machine *>(THISCALL(0x004A63F0, this, a2));
}

bool animation_logic_system::frame_advance_should_do_frame_advance([[maybe_unused]] Float a2) {
    if (this->field_6C->has_time_ifc()) {
        this->field_6C->time_ifc();
    }

    if (this->the_controller == nullptr) {
        auto *v3 = this->field_6C;
        if (v3->anim_ctrl == nullptr) {
            v3->allocate_anim_controller(0, nullptr);
        }

        this->the_controller = CAST(the_controller, this->field_6C->anim_ctrl);
    }

    auto *v4 = this->field_6C;
    if ((v4->field_4 & 0x40000000) != 0 ||
        ((v4->field_8 & 0x2000) != 0 || this->field_6C->get_primary_region() == nullptr) &&
            (v4->field_4 & 8) == 0) {
        return false;
    }

    if (this->field_7C) {
        return true;
    }

    return !traffic::is_unanimated_car(this->field_6C);
}

void animation_logic_system::frame_advance_post_logic_processing([[maybe_unused]] Float a2) {
    if constexpr (0) {
        if (!this->field_7C) {
            time_interface *time_ifc = nullptr;
            if (this->field_6C->has_time_ifc()) {
                time_ifc = this->field_6C->time_ifc();
            }

            if (this->field_6C->has_physical_ifc() && this->field_18.field_14) {
                if ((this->field_6C->physical_ifc()->field_C & 0x80000) == 0 ||
                    ((time_interface *) &this->field_18)->is_combat_dilated()) {
                    auto *v3 = this->field_18.field_30;
                    if (v3 && (v3->field_C & 0x800) != 0 &&
                        (this->field_6C->physical_ifc()->field_C & 0x80000) == 0) {
                        this->enter_biped_physics();
                    }
                } else {
                    this->exit_biped_physics();
                }
            }
        }

    } else {
        THISCALL(0x0049CC90, this, a2);
    }
}

void animation_logic_system_interface::force_update(Float a2) {
#if 0
    if ( this->m_vtbl->frame_advance_should_do_frame_advance(this, a2) || a2 == EPSILON )
    {
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_main_als_advance)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_post_request_processing)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_on_layer_trans)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_post_logic_processing)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_play_new_animations)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_update_pending_params)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_change_mocomp)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_run_mocomp_pre_anim)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_controller)(
            this,
            LODWORD(a2));
        this->m_vtbl->frame_advance_post_controller(this, a2);
    }
#endif
}

} // namespace als

void animation_logic_system_patch() {
    FUNC_ADDRESS(address, &als::animation_logic_system_interface::force_update);
    //SET_JUMP(0x00492FC0, address);

    {
        FUNC_ADDRESS(address, &als::animation_logic_system::enter_biped_physics);
        REDIRECT(0x0049CD21, address);
    }
}
