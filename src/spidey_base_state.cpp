#include "spidey_base_state.h"

#include "actor.h"
#include "ai_interaction_data.h"
#include "ai_state_jump.h"
#include "ai_std_hero.h"
#include "base_ai_core.h"
#include "base_ai_state_machine.h"
#include "combat_state.h"
#include "common.h"
#include "controller_inode.h"
#include "func_wrapper.h"
#include "hit_react_state.h"
#include "interaction_inode.h"
#include "physics_inode.h"
#include "plr_loco_crawl_transition_state.h"
#include "pole_swing_inode.h"
#include "pole_swing_state.h"

#include "ai_state_run.h"
#include "ai_state_swing.h"
#include "ai_state_web_zip.h"
#include "spidey_combat_inode.h"
#include "string_hash.h"
#include "trace.h"
#include "utility.h"

namespace ai {

VALIDATE_SIZE(spidey_base_state, 0x1C);

spidey_base_state::spidey_base_state()
{
    THISCALL(0x00438E80, this);
}

string_hash spidey_base_state::get_desired_state_id(Float a3)
{
    TRACE("spidey_base_state::get_desired_state_id");

    if constexpr (0) {
        string_hash a2 = this->field_C->my_curr_state->get_name();

        auto *v4 = this->get_core();
        auto *hero_inode_ptr = (hero_inode *) v4->get_info_node(hero_inode::default_id, true);
        auto *v50 = hero_inode_ptr->field_3C;
        auto *v48 = hero_inode_ptr->field_2C;
        auto *interaction_inode_ptr = hero_inode_ptr->field_34;
        auto *v9 = hero_inode_ptr->field_48;
        auto *v49 = hero_inode_ptr->field_40;

        actor *v14;
        physics_inode *v34;
        spidey_combat_inode *v32;
        spidey_combat_inode *v13;
        web_zip_inode *v42;

        spidey_combat_inode *v43;

        swing_inode *v39;

        bool v31;
        unsigned int v18;
        actor *v19;

        if (a2 != run_state::default_id) {
            if (a2 == jump_state::default_id) {
                vhandle_type<actor> v51;
                v51.field_0 = v48->field_20;
                v19 = v51.get_volatile_ptr();
                if (v19 != nullptr) {
                    auto *v20 = this->get_core();
                    auto *v21 = (controller_inode *) v20->get_info_node(controller_inode::default_id,
                                                                        true);

                    vector3d axis = v21->get_axis(controller_inode::eControllerAxis{2});
                    auto *v22 = this->get_actor();
                    auto v53 = v19->get_abs_position() - v22->get_abs_position();
                    v53.normalize();
                    if (dot(axis, v53) != 0.0f) {
                        hero_inode_ptr->jump_can_go_to(pole_swing_state::default_id);
                    }

                    if (hero_inode_ptr->jump_can_go_to(combat_state::default_id) &&
                        v48->has_next_move()) {
                        return combat_state::default_id;
                    }
                }

                if (interaction_inode_ptr->is_eligible(a2, false)) {
                    if (string_hash v46 = interaction_inode_ptr->get_chosen_interact_state_id();
                        hero_inode_ptr->jump_can_go_to(v46)) {
                        return interaction_inode_ptr->get_chosen_interact_state_id();
                    }

                    v31 = interaction_inode_ptr->curr_status == 1;
                    interaction_inode_ptr->field_28 = 2;
                    if (v31) {
                        if (interaction_inode_ptr->target_handle.get_volatile_ptr() &&
                            interaction_inode_ptr->target_handle.get_volatile_ptr()) {
                            actor *v29 = nullptr;
                            if (interaction_inode_ptr->target_handle.get_volatile_ptr() != nullptr) {
                                auto *v29 = interaction_inode_ptr->target_handle.get_volatile_ptr();
                            }

                            v29->kill_interact_anim();
                        }

                        if (interaction_inode_ptr->curr_status != 2) {
                            auto *v30 = interaction_inode_ptr->field_2C;
                            if (v30 != nullptr) {
                                v30->unregister_interactor(
                                    {interaction_inode_ptr->field_C->my_handle.field_0});
                            }

                            interaction_inode_ptr->field_2C = nullptr;
                            interaction_inode_ptr->field_30 = nullptr;
                            interaction_inode_ptr->target_handle.field_0 = 0;
                            interaction_inode_ptr->target_interaction_type = 4;
                            interaction_inode_ptr->field_34 = nullptr;
                            interaction_inode_ptr->field_49 = 0;
                            interaction_inode_ptr->curr_status = 0;
                        }
                    }
                }

                if (hero_inode_ptr->jump_can_go_to(swing_state::default_id) &&
                    v49->is_eligible(a2, a3)) {
                    return swing_state::default_id;
                }

                hero_inode_ptr->jump_can_go_to(pole_swing_state::default_id);
                if (!hero_inode_ptr->jump_can_go_to(plr_loco_crawl_transition_state::default_id) ||
                    !hero_inode_ptr->crawl_is_eligible(a2, true)) {
                    if (!hero_inode_ptr->jump_can_go_to(run_state::default_id) ||
                        !hero_inode_ptr->run_is_eligible(a2)) {
                        if (hero_inode_ptr->jump_can_go_to(web_zip_state::default_id) &&
                            v50->is_eligible(a2)) {
                            return web_zip_state::default_id;
                        }

                        if (!hero_inode_ptr->jump_can_go_to(hit_react_state::default_id)) {
                            return hero_base_state::NO_TRANS;
                        }

                    LABEL_68:
                        v31 = !v48->needs_hit_react(a3);
                        goto LABEL_142;
                    }

                    return run_state::default_id;
                }

                return plr_loco_crawl_transition_state::default_id;
            }

            if (hero_inode::is_a_crawl_state(a2, false)) {
                v32 = v48;

                if (vhandle_type<actor>{v48->field_20}.get_volatile_ptr()) {
                    if (hero_inode_ptr->crawl_can_go_to(combat_state::default_id, a2) &&
                        v32->has_next_move()) {
                        v34 = (physics_inode *) this->get_core()
                                  ->get_info_node(physics_inode::default_id, true);
                        v34->setup_for_bounce();
                        return combat_state::default_id;
                    }
                }

                if (interaction_inode_ptr->is_eligible(a2, 0)) {
                    if (string_hash v45 = interaction_inode_ptr->get_chosen_interact_state_id();
                        hero_inode_ptr->crawl_can_go_to(v45, a2)) {
                        return interaction_inode_ptr->get_chosen_interact_state_id();
                    }

                    v31 = interaction_inode_ptr->curr_status == 1;
                    interaction_inode_ptr->field_28 = 2;
                    if (v31) {
                        if (interaction_inode_ptr->target_handle.get_volatile_ptr() &&
                            interaction_inode_ptr->target_handle.get_volatile_ptr()) {
                            actor *v36 = nullptr;
                            if (interaction_inode_ptr->target_handle.get_volatile_ptr()) {
                                v36 = interaction_inode_ptr->target_handle.get_volatile_ptr();
                            }

                            v36->kill_interact_anim();
                        }

                        if (interaction_inode_ptr->curr_status != 2) {
                            auto *v37 = interaction_inode_ptr->field_2C;
                            if (v37 != nullptr) {
                                v37->unregister_interactor(
                                    {interaction_inode_ptr->field_C->my_handle.field_0});
                            }

                            interaction_inode_ptr->field_2C = nullptr;
                            interaction_inode_ptr->field_30 = nullptr;
                            interaction_inode_ptr->target_handle.field_0 = 0;
                            interaction_inode_ptr->target_interaction_type = 4;
                            interaction_inode_ptr->field_34 = nullptr;
                            interaction_inode_ptr->field_49 = 0;
                            interaction_inode_ptr->curr_status = 0;
                        }
                    }
                }

                if (hero_inode_ptr->crawl_can_go_to(run_state::default_id, a2)) {
                    if (hero_inode_ptr->run_is_eligible(a2)) {

                        return run_state::default_id;
                    }
                }

                if (!hero_inode_ptr->crawl_can_go_to(jump_state::default_id, a2) ||
                    (!hero_inode_ptr->jump_is_eligible(a2))) {
                    if (hero_inode_ptr->crawl_can_go_to(web_zip_state::default_id, a2)) {
                        if (v50->is_eligible(a2)) {
                            return web_zip_state::default_id;
                        }
                    }

                    if (!hero_inode_ptr->crawl_can_go_to(hit_react_state::default_id, a2) ||
                        !v48->needs_hit_react(a3)) {
                        return hero_base_state::NO_TRANS;
                    }

                    hero_inode_ptr->sub_68A7F0(5, 0);

                    return jump_state::default_id;
                }

                return jump_state::default_id;
            }

            if (a2 == swing_state::default_id) {
                if (interaction_inode_ptr->is_eligible(a2, false)) {
                    v39 = v49;
                    if (string_hash v46 = interaction_inode_ptr->get_chosen_interact_state_id();
                        v49->can_go_to(v46)) {

                        return interaction_inode_ptr->get_chosen_interact_state_id();
                    }

                    v31 = interaction_inode_ptr->curr_status == 1;
                    interaction_inode_ptr->field_28 = 2;
                    if (v31) {
                        if (interaction_inode_ptr->target_handle.get_volatile_ptr() &&
                            interaction_inode_ptr->target_handle.get_volatile_ptr()) {
                            actor *v40 = nullptr;
                            if (interaction_inode_ptr->target_handle.get_volatile_ptr()) {
                                v40 = interaction_inode_ptr->target_handle.get_volatile_ptr();
                            }

                            v40->kill_interact_anim();
                        }

                        if (interaction_inode_ptr->curr_status != 2) {
                            auto *v41 = interaction_inode_ptr->field_2C;
                            if (v41 != nullptr) {
                                v41->unregister_interactor(
                                    {interaction_inode_ptr->field_C->my_handle.field_0});
                            }

                            interaction_inode_ptr->field_2C = nullptr;
                            interaction_inode_ptr->field_30 = nullptr;
                            interaction_inode_ptr->target_handle.field_0 = 0;
                            interaction_inode_ptr->target_interaction_type = 4;
                            interaction_inode_ptr->field_34 = nullptr;
                            interaction_inode_ptr->field_49 = 0;
                            interaction_inode_ptr->curr_status = 0;
                        }
                    }
                } else {
                    v39 = v49;
                }

                if (v39->can_go_to(plr_loco_crawl_transition_state::default_id)) {
                    if (hero_inode_ptr->crawl_is_eligible(a2, true)) {

                        return plr_loco_crawl_transition_state::default_id;
                    }
                }

                if (v39->can_go_to(jump_state::default_id)) {
                    if (hero_inode_ptr->jump_is_eligible(a2)) {
                        return jump_state::default_id;
                    }
                }

                if (!v39->can_go_to(run_state::default_id) || (!hero_inode_ptr->run_is_eligible(a2))) {
                    if (!v39->can_go_to(hit_react_state::default_id)) {
                        return hero_base_state::NO_TRANS;
                    }

                    goto LABEL_68;
                }

            } else {
                if (a2 != web_zip_state::default_id) {
                    if (a2 != pole_swing_state::default_id) {
                        if (a2 != combat_state::default_id) {
                            return hero_base_state::NO_TRANS;
                        }

                        v43 = v48;
                        if (!v48->needs_hit_react(a3)) {
                            return hero_base_state::NO_TRANS;
                        }

                        v31 = v43->get_cur_move()->field_80.field_4.field_8 == 16;
                    LABEL_142:
                        if (!v31) {
                            return hit_react_state::default_id;
                        }

                        return hero_base_state::NO_TRANS;
                    }

                    if (!v9->can_go_to(jump_state::default_id) ||
                        !hero_inode_ptr->jump_is_eligible(a2)) {

                        return hero_base_state::NO_TRANS;
                    }

                    return jump_state::default_id;
                }

                v42 = v50;

                if (v50->can_go_to(plr_loco_crawl_transition_state::default_id)) {
                    if (hero_inode_ptr->crawl_is_eligible(a2, 1)) {
                        return plr_loco_crawl_transition_state::default_id;
                    }
                }

                if (!v42->can_go_to(run_state::default_id) || (!hero_inode_ptr->run_is_eligible(a2))) {
                    if (!v42->can_go_to(jump_state::default_id) ||
                        (!hero_inode_ptr->jump_is_eligible(a2))) {
                        if (!v42->can_go_to(hit_react_state::default_id)) {

                            return hero_base_state::NO_TRANS;
                        }

                        goto LABEL_68;
                    }

                    return jump_state::default_id;
                }
            }

            return run_state::default_id;
        }

        if (interaction_inode_ptr->is_eligible(a2, false)) {
            if (hero_inode_ptr->run_can_go_to(interaction_inode_ptr->get_chosen_interact_state_id())) {
                return interaction_inode_ptr->get_chosen_interact_state_id();
            }

            interaction_inode_ptr->clear_interaction((interaction_result_enum)2);
        }

        v13 = v48;

        v14 = vhandle_type<actor>{v48->field_20}.get_volatile_ptr();

        this->get_core()->field_50.get_optional_pb_int(loco_allow_web_tie_id(),
                                                       v48->field_20,
                                                       nullptr);
        this->get_actor();
        if (v14 != nullptr) {
            if (v13->has_next_move()) {
                if (hero_inode_ptr->run_can_go_to(combat_state::default_id)) {
                    return combat_state::default_id;
                }
            }
        }

        if (hero_inode_ptr->run_can_go_to(swing_state::default_id) && v49->is_eligible(a2, a3)) {
            hero_inode_ptr->sub_68A7F0(9, false);
            return jump_state::default_id;
        }

        if (hero_inode_ptr->run_can_go_to(plr_loco_crawl_transition_state::default_id) &&
            hero_inode_ptr->crawl_is_eligible(a2, true)) {
            return plr_loco_crawl_transition_state::default_id;
        }

        if (hero_inode_ptr->run_can_go_to(combat_state::default_id) && v13->has_next_move()) {
            return combat_state::default_id;
        }

        if (!v13->needs_hit_react(a3) ||
            !hero_inode_ptr->run_can_go_to(hit_react_state::default_id)) {
            if (!hero_inode_ptr->run_can_go_to(jump_state::default_id) ||
                !hero_inode_ptr->jump_is_eligible(a2)) {
                if (hero_inode_ptr->run_can_go_to(web_zip_state::default_id) &&
                    v50->is_eligible(a2)) {
                    return web_zip_state::default_id;
                }

                return hero_base_state::NO_TRANS;
            }

            return jump_state::default_id;
        }

        return hit_react_state::default_id;
    } else {
        THISCALL(0x00488680, this, a3);
    }
}

} // namespace ai

void spidey_base_state_patch() {
    {
        FUNC_ADDRESS(address, &ai::spidey_base_state::get_desired_state_id);
        set_vfunc(0x0087756C, address);
    }
}
