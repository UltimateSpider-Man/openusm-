#include "als_animation_logic_system.h"

#include "actor.h"
#include "als_animation_logic_system_shared.h"
#include "als_state.h"
#include "common.h"
#include "func_wrapper.h"
#include "layer_state_machine_shared.h"
#include "physical_interface.h"
#include "resource_manager.h"
#include "time_interface.h"
#include "trace.h"
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
    TRACE("animation_logic_system::frame_advance_should_do_frame_advance");

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

float animation_logic_system::convert_layer_id_to_priority(layer_types a2) {
    float (__fastcall *func)(void *, void *, als::layer_types) = CAST(func, 0x0049F360);
    return func(this, nullptr, a2);
}

void animation_logic_system::frame_advance_play_new_animations(Float a2)
{
    TRACE("animation_logic_system::frame_advance_play_new_animations");

    if constexpr (0) {
        if ( !this->field_7C ) {
            if ( this->field_6C->has_time_ifc() ) {
                this->field_6C->time_ifc();
            }

            auto *old_context = resource_manager::push_resource_context(this->field_6C->field_BC);
            auto v5 = this->field_8.size();
            for ( auto i = -1; i < v5; ++i ) {
                state_machine *the_state_machine = (i == -1 ? &this->field_18 : this->field_8[i]);

                if ( the_state_machine->is_active() ) {
                    bool v19 = true;
                    if (!the_state_machine->did_do_transition()) {
                        if (i != -1
                            || the_state_machine->field_48.is_anim_active()) {
                            v19 = false;
                        }
                    }

                    if (v19 || this->field_7D) {
                        auto *curr_state = the_state_machine->get_curr_state();
                        assert(curr_state != nullptr);

                        auto v20 = curr_state->get_nal_anim_name();
                        animation_controller::anim_ctrl_handle v9{};
                        if ( i == -1 )
                        {
                            float a4 = this->field_18.get_optional_pb_int(
                                                anim_start_frame_hash,
                                                0,
                                                nullptr) / 30.0;
                            auto v18 = curr_state->field_C;
                            v9 = this->the_controller->play_base_layer_anim(
                                v20,
                                a4,
                                v18,
                                true);
                        }
                        else
                        {
                            auto v10 = this->field_8[i]->field_4->field_40;
                            auto v11 = curr_state->field_C;
                            auto v19 = the_state_machine->get_layer_id();
                            auto v12 = the_state_machine->get_layer_id();
                            auto a5 = this->convert_layer_id_to_priority(v12);
                            v9 = this->the_controller->play_layer_anim(v20, v11, a5, v10, true, v19);
                        }

                        the_state_machine->field_48 = v9;
                        this->field_7D = false;
                    }

                }
            }

            resource_manager::pop_resource_context();
            assert(resource_manager::get_resource_context() == old_context);
        }
    } else {
        THISCALL(0x004A6400, this, a2);
    }
}

void animation_logic_system::frame_advance_post_request_processing(Float a2)
{
    TRACE("animation_logic_system::frame_advance_post_request_processing");

    THISCALL(0x0049F1A0, this, a2);
}

void animation_logic_system::frame_advance_main_als_advance(Float a2)
{
    TRACE("animation_logic_system::frame_advance_main_als_advance");

    THISCALL(0x004A90B0, this, a2);
}

void animation_logic_system::frame_advance_on_layer_trans(Float a2)
{
    TRACE("animation_logic_system::frame_advance_on_layer_trans");

    THISCALL(0x0049F220, this, a2);
}


} // namespace als

void animation_logic_system_patch() {

    {
        FUNC_ADDRESS(address, &als::animation_logic_system::frame_advance_should_do_frame_advance);
        set_vfunc(0x00881478, address);
    }

    {
        FUNC_ADDRESS(address, &als::animation_logic_system::frame_advance_on_layer_trans);
        set_vfunc(0x00881484, address);
    }

    {
        FUNC_ADDRESS(address, &als::animation_logic_system::frame_advance_post_request_processing);
        set_vfunc(0x00881480, address);
    }

    {
        FUNC_ADDRESS(address, &als::animation_logic_system::frame_advance_main_als_advance);
        set_vfunc(0x0088147C, address);
    }

    {
        FUNC_ADDRESS(address, &als::animation_logic_system::frame_advance_play_new_animations);
        set_vfunc(0x0088148C, address);
    }
    return;


    {
        FUNC_ADDRESS(address, &als::animation_logic_system::enter_biped_physics);
        REDIRECT(0x0049CD21, address);
    }
}
