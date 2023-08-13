#include "interaction_inode.h"

#include "ai_interaction_data.h"
#include "attach_state.h"
#include "common.h"
#include "func_wrapper.h"
#include "generic_interaction.h"
#include "interaction_state.h"
#include "pick_up_state.h"
#include "put_down_state.h"
#include "throw_state.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

namespace ai {

VALIDATE_SIZE(interaction_inode, 0x4C);

interaction_inode::interaction_inode(from_mash_in_place_constructor *a2) : info_node(a2) {
    this->field_1C.field_0 = 0; // ai::interaction_inode::initialize()
    this->field_40 = 0;
    this->field_2C = nullptr;
    this->field_30 = nullptr;
    this->field_28 = 2;
    this->field_1C.field_0 = 0;
    this->field_34 = nullptr;
    this->target_interaction_type = 4;
    this->field_49 = 0;
    this->field_24 = 0;
}

interaction_inode::interaction_inode() : info_node() {
    this->field_1C = {0};
    this->field_48 = 0;
    this->field_49 = 0;
    this->field_40 = 0;
    this->field_2C = nullptr;
    this->field_30 = nullptr;
    this->field_28 = 2;
    this->field_1C = {0};
    this->field_34 = nullptr;
    this->target_interaction_type = 4;
    this->field_49 = 0;
    this->field_24 = 0;
}

bool interaction_inode::is_eligible(string_hash a2, bool a3) {
    return THISCALL(0x00479850, this, a2, a3);
}

void interaction_inode::set_curr_anim(enum_anim_key::key_enum a2)
{
    TRACE("interaction_inode::set_curr_anim:");

#if 0
    if constexpr (0) {
        auto *v3 = (anim_key *) this->field_2C->does_anim_exist(a2, false);
        if (v3 != nullptr) {
            this->field_34 = CAST(field_34, v3->field_4);
        } else {
            this->field_34 = nullptr;
        }
    } else {
        THISCALL(0x00451340, this, a2);
    }
#else
    assert(0);
#endif
}

bool interaction_inode::is_in_master_mode() {
    return this->field_24 == 2;
}

string_hash interaction_inode::get_chosen_interact_state_id() {
    static constexpr auto NUM_INTERACT_TYPES = 4;

    assert(target_interaction_type != NUM_INTERACT_TYPES);

    string_hash result;

    switch (this->target_interaction_type) {
    case 0:
        result = interaction_state::default_id;
        break;
    case 1:

        if (this->is_in_master_mode()) {
            result = put_down_state::default_id;
        } else {
            result = pick_up_state::default_id;
        }

        break;
    case 2:
        result = ai::attach_state::default_id;
        break;
    case 3:
        result = throw_state::default_id;
        break;
    default:
        assert(0 && "Unhandled interaction type.");

        result = string_hash{};

        break;
    }

    return result;
}

actor *interaction_inode::get_target() {
    actor *target = nullptr;

    if (this->field_1C.get_volatile_ptr()) {
        target = this->field_1C.get_volatile_ptr();
    }

    return target;
}

void interaction_inode::set_flag_from_param(const string_hash &a2, interaction_type_enum a3) {
    THISCALL(0x00463980, this, &a2, a3);
}

void interaction_inode::set_scripted_start(actor *a2, generic_interaction *a3) {
    if constexpr (1) {
        this->field_48 = true;
        auto v4 = a3->field_28;

        auto &func = get_vfunc(a3->m_vtbl, 0x20);

        auto *v5 = (ai_interaction_data *) func(a3);
        if (this->field_24 != 2) {
            this->field_24 = 1;
        }

        this->field_1C = {a2->my_handle};
        this->field_2C = v5;
        if (v5 != nullptr) {
            v5->register_interactor(this->field_1C);
        }

        this->field_30 = a3;
        this->target_interaction_type = v4;
        this->field_28 = 2;
    } else {
        THISCALL(0x0046E380, this, a2, a3);
    }
}

} // namespace ai

void interaction_inode_patch() {
    FUNC_ADDRESS(address, &ai::interaction_inode::set_curr_anim);
    REDIRECT(0x00463C59, address);
}
