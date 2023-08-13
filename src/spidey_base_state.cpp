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
#include "utility.h"

namespace ai {

VALIDATE_SIZE(spidey_base_state, 0x1C);

spidey_base_state::spidey_base_state()
{
    THISCALL(0x00438E80, this);
}

string_hash spidey_base_state::get_desired_state_id(Float a3) {
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

    if (a2.source_hash_code != run_state::default_id.source_hash_code) {
        if (a2.source_hash_code == jump_state::default_id.source_hash_code) {
            vhandle_type<actor> v51;
            v51.field_0 = v48->field_20;
            v19 = v51.get_volatile_ptr();
            if (v19 != nullptr) {
                auto *v20 = this->get_core();
                auto *v21 = (controller_inode *) v20->get_info_node(controller_inode::default_id,
                                                                    true);

                vector3d v54 = v21->get_axis(controller_inode::eControllerAxis{2});
                auto *v22 = this->get_actor();
                auto *v23 = v22;
                if ((v22->field_8 & 0x10000000) != 0) {
                    v22->update_abs_po(1);
                }

                if ((v19->field_8 & 0x10000000) != 0) {
                    v19->update_abs_po(1);
                }

                auto *v24 = (float *) v19->my_abs_po;
                auto *v25 = (float *) v23->my_abs_po;
                auto v26 = v24[14] - v25[14];
                v24 += 12;
                v25 += 12;
                auto v27 = v24[1] - v25[1];

                vector3d v53;
                v53[0] = *v24 - *v25;
                v53[1] = v27;
                v53[2] = v26;
                v53.normalize();
                if (v54[2] * v53[2] + v54[1] * v53[1] + v54[0] * v53[0] !=
                    0.0f) {
                    hero_inode_ptr->jump_can_go_to(pole_swing_state::default_id);
                }

                if (hero_inode_ptr->jump_can_go_to(combat_state::default_id) &&
                    v48->has_next_move()) {
                    goto LABEL_43;
                }
            }

            if (interaction_inode_ptr->is_eligible(a2, false)) {
                if (string_hash v46 = interaction_inode_ptr->get_chosen_interact_state_id();
                    hero_inode_ptr->jump_can_go_to(v46)) {
                    goto LABEL_102;
                }

                v31 = interaction_inode_ptr->field_24 == 1;
                interaction_inode_ptr->field_28 = 2;
                if (v31) {
                    if (interaction_inode_ptr->field_1C.get_volatile_ptr() &&
                        interaction_inode_ptr->field_1C.get_volatile_ptr()) {
                        actor *v29 = nullptr;
                        if (interaction_inode_ptr->field_1C.get_volatile_ptr()) {
                            auto *v29 = interaction_inode_ptr->field_1C.get_volatile_ptr();
                        }

                        v29->kill_interact_anim();
                    }

                    if (interaction_inode_ptr->field_24 != 2) {
                        auto *v30 = interaction_inode_ptr->field_2C;
                        if (v30 != nullptr) {
                            v30->unregister_interactor(
                                {interaction_inode_ptr->field_C->my_handle.field_0});
                        }

                        interaction_inode_ptr->field_2C = nullptr;
                        interaction_inode_ptr->field_30 = nullptr;
                        interaction_inode_ptr->field_1C.field_0 = 0;
                        interaction_inode_ptr->target_interaction_type = 4;
                        interaction_inode_ptr->field_34 = nullptr;
                        interaction_inode_ptr->field_49 = 0;
                        interaction_inode_ptr->field_24 = 0;
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
                        goto LABEL_144;
                    }

                LABEL_68:
                    v31 = !v48->needs_hit_react(a3);
                    goto LABEL_142;
                }

            LABEL_90:
                v18 = run_state::default_id.source_hash_code;
                goto LABEL_145;
            }

        LABEL_117:

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
                LABEL_74:
                    v18 = combat_state::default_id.source_hash_code;
                    goto LABEL_145;
                }
            }

            if (interaction_inode_ptr->is_eligible(a2, 0)) {
                if (string_hash v45 = interaction_inode_ptr->get_chosen_interact_state_id();
                    hero_inode_ptr->crawl_can_go_to(v45, a2)) {
                    goto LABEL_102;
                }

                v31 = interaction_inode_ptr->field_24 == 1;
                interaction_inode_ptr->field_28 = 2;
                if (v31) {
                    if (interaction_inode_ptr->field_1C.get_volatile_ptr() &&
                        interaction_inode_ptr->field_1C.get_volatile_ptr()) {
                        actor *v36 = nullptr;
                        if (interaction_inode_ptr->field_1C.get_volatile_ptr()) {
                            v36 = interaction_inode_ptr->field_1C.get_volatile_ptr();
                        }

                        v36->kill_interact_anim();
                    }

                    if (interaction_inode_ptr->field_24 != 2) {
                        auto *v37 = interaction_inode_ptr->field_2C;
                        if (v37 != nullptr) {
                            v37->unregister_interactor(
                                {interaction_inode_ptr->field_C->my_handle.field_0});
                        }

                        interaction_inode_ptr->field_2C = nullptr;
                        interaction_inode_ptr->field_30 = nullptr;
                        interaction_inode_ptr->field_1C.field_0 = 0;
                        interaction_inode_ptr->target_interaction_type = 4;
                        interaction_inode_ptr->field_34 = nullptr;
                        interaction_inode_ptr->field_49 = 0;
                        interaction_inode_ptr->field_24 = 0;
                    }
                }
            }

            if (hero_inode_ptr->crawl_can_go_to(run_state::default_id, a2)) {
                if (hero_inode_ptr->run_is_eligible(a2)) {
                    goto LABEL_90;
                }
            }

            if (!hero_inode_ptr->crawl_can_go_to(jump_state::default_id, a2) ||
                (!hero_inode_ptr->jump_is_eligible(a2))) {
                if (hero_inode_ptr->crawl_can_go_to(web_zip_state::default_id, a2)) {
                    if (v50->is_eligible(a2)) {
                        goto LABEL_32;
                    }
                }

                if (!hero_inode_ptr->crawl_can_go_to(hit_react_state::default_id, a2) ||
                    !v48->needs_hit_react(a3)) {
                LABEL_144:
                    v18 = hero_base_state::NO_TRANS().source_hash_code;
                    goto LABEL_145;
                }

                hero_inode_ptr->sub_68A7F0(5, 0);
            LABEL_98:

                return jump_state::default_id;
            }

            goto LABEL_138;
        }

        if (a2 == swing_state::default_id) {
            if (interaction_inode_ptr->is_eligible(a2, false)) {
                v39 = v49;
                if (string_hash v46 = interaction_inode_ptr->get_chosen_interact_state_id();
                    v49->can_go_to(v46)) {
                    goto LABEL_102;
                }

                v31 = interaction_inode_ptr->field_24 == 1;
                interaction_inode_ptr->field_28 = 2;
                if (v31) {
                    if (interaction_inode_ptr->field_1C.get_volatile_ptr() &&
                        interaction_inode_ptr->field_1C.get_volatile_ptr()) {
                        actor *v40 = nullptr;
                        if (interaction_inode_ptr->field_1C.get_volatile_ptr()) {
                            v40 = interaction_inode_ptr->field_1C.get_volatile_ptr();
                        }

                        v40->kill_interact_anim();
                    }

                    if (interaction_inode_ptr->field_24 != 2) {
                        auto *v41 = interaction_inode_ptr->field_2C;
                        if (v41 != nullptr) {
                            v41->unregister_interactor(
                                {interaction_inode_ptr->field_C->my_handle.field_0});
                        }

                        interaction_inode_ptr->field_2C = nullptr;
                        interaction_inode_ptr->field_30 = nullptr;
                        interaction_inode_ptr->field_1C.field_0 = 0;
                        interaction_inode_ptr->target_interaction_type = 4;
                        interaction_inode_ptr->field_34 = nullptr;
                        interaction_inode_ptr->field_49 = 0;
                        interaction_inode_ptr->field_24 = 0;
                    }
                }
            } else {
                v39 = v49;
            }

            if (v39->can_go_to(plr_loco_crawl_transition_state::default_id)) {
                if (hero_inode_ptr->crawl_is_eligible(a2, true)) {
                    goto LABEL_117;
                }
            }

            if (v39->can_go_to(jump_state::default_id)) {
                if (hero_inode_ptr->jump_is_eligible(a2)) {
                LABEL_138:
                    v18 = jump_state::default_id.source_hash_code;
                    goto LABEL_145;
                }
            }

            if (!v39->can_go_to(run_state::default_id) || (!hero_inode_ptr->run_is_eligible(a2))) {
                if (!v39->can_go_to(hit_react_state::default_id)) {
                    goto LABEL_144;
                }

                goto LABEL_68;
            }

        } else {
            if (a2 != web_zip_state::default_id) {
                if (a2 != pole_swing_state::default_id) {
                    if (a2 != combat_state::default_id) {
                        goto LABEL_144;
                    }

                    v43 = v48;
                    if (!v48->needs_hit_react(a3)) {
                        goto LABEL_144;
                    }

                    v31 = v43->get_cur_move()->field_80.field_4.field_8 == 16;
                LABEL_142:
                    if (!v31) {
                        return hit_react_state::default_id;
                    }

                    goto LABEL_144;
                }

                if (!v9->can_go_to(jump_state::default_id) ||
                    !hero_inode_ptr->jump_is_eligible(a2)) {
                    goto LABEL_144;
                }

                goto LABEL_138;
            }

            v42 = v50;

            if (v50->can_go_to(plr_loco_crawl_transition_state::default_id)) {
                if (hero_inode_ptr->crawl_is_eligible(a2, 1)) {
                LABEL_127:
                    v18 = plr_loco_crawl_transition_state::default_id;
                    goto LABEL_145;
                }
            }

            if (!v42->can_go_to(run_state::default_id) || (!hero_inode_ptr->run_is_eligible(a2))) {
                if (!v42->can_go_to(jump_state::default_id) ||
                    (!hero_inode_ptr->jump_is_eligible(a2))) {
                    if (!v42->can_go_to(hit_react_state::default_id)) {
                        goto LABEL_144;
                    }

                    goto LABEL_68;
                }

                goto LABEL_138;
            }
        }

        return run_state::default_id;
    }

    if (!interaction_inode_ptr->is_eligible(a2, false)) {
        goto LABEL_15;
    }

    if (hero_inode_ptr->run_can_go_to(interaction_inode_ptr->get_chosen_interact_state_id())) {
    LABEL_102:

        string_hash out = interaction_inode_ptr->get_chosen_interact_state_id();
        return out;
    }

    v31 = interaction_inode_ptr->field_24 == 1;
    interaction_inode_ptr->field_28 = 2;
    if (v31) {
        if (interaction_inode_ptr->field_1C.get_volatile_ptr() &&
            interaction_inode_ptr->field_1C.get_volatile_ptr()) {
            actor *v11 = nullptr;
            if (interaction_inode_ptr->field_1C.get_volatile_ptr()) {
                v11 = interaction_inode_ptr->field_1C.get_volatile_ptr();
            }

            v11->kill_interact_anim();
        }

        if (interaction_inode_ptr->field_24 != 2) {
            auto *v12 = interaction_inode_ptr->field_2C;
            if (v12 != nullptr) {
                v12->unregister_interactor({interaction_inode_ptr->field_C->my_handle.field_0});
            }

            interaction_inode_ptr->field_2C = nullptr;
            interaction_inode_ptr->field_30 = nullptr;
            interaction_inode_ptr->field_1C.field_0 = 0;
            interaction_inode_ptr->target_interaction_type = 4;
            interaction_inode_ptr->field_34 = nullptr;
            interaction_inode_ptr->field_49 = 0;
            interaction_inode_ptr->field_24 = 0;
        }
    }
    LABEL_15:
        v13 = v48;

        v14 = vhandle_type<actor>{v48->field_20}.get_volatile_ptr();

        this->get_core()->field_50.get_optional_pb_int(loco_allow_web_tie_id(),
                                                       v48->field_20,
                                                       nullptr);
        this->get_actor();
        if (v14 != nullptr) {
            if (v13->has_next_move()) {
                if (hero_inode_ptr->run_can_go_to(combat_state::default_id)) {
                    goto LABEL_74;
                }
            }
        }

        if (hero_inode_ptr->run_can_go_to(swing_state::default_id) && v49->is_eligible(a2, a3)) {
            hero_inode_ptr->sub_68A7F0(9, false);
            return jump_state::default_id;
        }

        if (hero_inode_ptr->run_can_go_to(plr_loco_crawl_transition_state::default_id) &&
            hero_inode_ptr->crawl_is_eligible(a2, true)) {
            goto LABEL_127;
        }

        if (hero_inode_ptr->run_can_go_to(combat_state::default_id) && v13->has_next_move()) {
        LABEL_43:
            return combat_state::default_id;
        }

        if (!v13->needs_hit_react(a3) ||
            !hero_inode_ptr->run_can_go_to(hit_react_state::default_id)) {
            if (!hero_inode_ptr->run_can_go_to(jump_state::default_id) ||
                !hero_inode_ptr->jump_is_eligible(a2)) {
                if (hero_inode_ptr->run_can_go_to(web_zip_state::default_id) &&
                    v50->is_eligible(a2)) {
                LABEL_32:
                    v18 = web_zip_state::default_id.source_hash_code;
                    goto LABEL_145;
                }
                goto LABEL_144;
            }
            goto LABEL_98;
        }

        v18 = hit_react_state::default_id.source_hash_code;
    LABEL_145:
        return string_hash{static_cast<int>(v18)};
}

} // namespace ai

void spidey_base_state_patch() {
    {
        FUNC_ADDRESS(address, &ai::spidey_base_state::get_desired_state_id);
        set_vfunc(0x0087756C, address);
    }
}
