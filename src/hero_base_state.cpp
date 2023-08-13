#include "hero_base_state.h"

#include "actor.h"
#include "ai_state_jump.h"
#include "ai_state_web_zip.h"
#include "ai_std_hero.h"
#include "als_inode.h"
#include "base_ai_core.h"
#include "base_ai_state_machine.h"
#include "common.h"
#include "damage_interface.h"
#include "func_wrapper.h"
#include "glass_house_inode.h"
#include "plr_loco_crawl_transition_state.h"
#include "state_machine.h"
#include "state_trans_action.h"
#include "std_default_trans_inode.h"
#include "subdued_state.h"
#include "utility.h"
#include "vtbl.h"

namespace ai {

VALIDATE_SIZE(hero_base_state, 0x1C);

hero_base_state::hero_base_state()
{

}

hero_base_state::hero_base_state(int a2) : base_state(a2) {
    
}

void hero_base_state::combat_inode_transition_notification(Float a2, string_hash a3) {
    THISCALL(0x00474040, this, a2, a3);
}

string_hash hero_base_state::get_desired_state_id(Float) {
    return hero_base_state::NO_TRANS();
}

state_trans_action *hero_base_state::check_transition(state_trans_action *out, Float a3) {
#if 0
    if constexpr (0) {
        ai::state_trans_action *result;

        auto *v4 = this->get_core();
        auto *hero_inode_ptr = (hero_inode *) v4->get_info_node(hero_inode::default_id, true);

        string_hash v21 = this->field_C->my_curr_state->get_name();

        unsigned int v11;

        actor *v9;
        actor *v8;

        auto *v6 = this->get_core();
        auto *v7 = (std_default_trans_inode *)
                       v6->get_info_node(std_default_trans_inode::default_id(), true);
        if (v21.source_hash_code != subdued_state::default_id().source_hash_code) {
            if (v7->field_26) {
                v8 = this->get_actor();
                if (v8->damage_ifc()) {
                    v9 = this->get_actor();
                    if (v9->damage_ifc()->field_1FC <= 0.0f) {
                        result = out;
                        v11 = subdued_state::default_id().source_hash_code;
                        out->the_action = 0;
                    LABEL_19:
                        result->field_4.source_hash_code = v11;
                        goto LABEL_20;
                    }
                }
            }
        }

        auto *glass_house_inode_ptr = hero_inode_ptr->field_44;
        if (glass_house_inode_ptr->field_20 &&
            (v21.source_hash_code != ai::jump_state::default_id().source_hash_code ||
             hero_inode_ptr->field_50 != 14)) {
            hero_inode_ptr->sub_68A7F0(14, false);
            glass_house_inode_ptr->show_glass_house_message();
            result = out;
            glass_house_inode_ptr->field_20 = 0;
            v11 = ai::jump_state::default_id().source_hash_code;
            out->the_action = 0;
            goto LABEL_19;
        }

        if (hero_inode_ptr->field_23C.get_volatile_ptr() != nullptr) {
            hero_inode_ptr->engage_water_exit();
            result = out;
            v11 = plr_loco_crawl_transition_state::default_id().source_hash_code;
            out->the_action = 0;
            goto LABEL_19;
        }

        string_hash hash_id;
        string_hash v20;

        ai_core *v13 = this->get_core();
        auto *v14 = (ai::als_inode *) v13->get_info_node(als_inode::default_id(), true);
        auto *v15 = v14->get_als_layer({0});
        if (!v15->is_interruptable() &&
            v21.source_hash_code != web_zip_state::default_id().source_hash_code) {
            hash_id.initialize(0, nullptr, 0);
            v11 = hash_id.source_hash_code;
        LABEL_18:
            result = out;
            out->the_action = 3;
            goto LABEL_19;
        }

        v20 = this->get_desired_state_id(a3);
        if (v20.source_hash_code == NO_TRANS().source_hash_code) {
            string_hash v22;
            v22.initialize(0, 0, 0);
            v11 = v22.source_hash_code;
            goto LABEL_18;
        }

        hash_id = this->field_C->my_curr_state->get_name();

        this->combat_inode_transition_notification(a3, v20);
        //string_hash::to_string(&v20);
        //string_hash::to_string(&a3);
        result = out;
        out->the_action = 0;
        out->field_4.source_hash_code = v20.source_hash_code;
    LABEL_20:
        result->field_C = 0;
        result->the_message = 75;
        return result;
    }

#else
    return (ai::state_trans_action *) THISCALL(0x00478D80, this, out, a3);
#endif
}

} // namespace ai
