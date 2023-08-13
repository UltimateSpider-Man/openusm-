#include "plr_loco_crawl_state.h"

#include "actor.h"
#include "ai_player_controller.h"
#include "ai_std_hero.h"
#include "als_inode.h"
#include "base_ai_core.h"
#include "common.h"
#include "oldmath_po.h"
#include "param_list.h"
#include "state_machine.h"

VALIDATE_SIZE(plr_loco_crawl_state, 0x48);

plr_loco_crawl_state::plr_loco_crawl_state() {}

void plr_loco_crawl_state::update_wallrun([[maybe_unused]] Float a2) {
    auto *v3 = this->get_core();
    auto *v4 = (ai::als_inode *) v3->get_info_node(ai::als_inode::default_id, true);
    auto v5 = this->m_wallrun_deviation;
    auto *v6 = v4;
    float v21 = 1.0;

    static constexpr auto deviance_forgiveness_timeout = 0.1f;

    if (v5 < 0.0f || this->field_1C < deviance_forgiveness_timeout) {
        auto *v9 = this->get_actor();
        if ((v9->field_8 & 0x10000000) != 0) {
            v9->update_abs_po(1);
        }

        this->field_38 = v9->my_abs_po->m[2];
        this->m_wallrun_deviation = 0.0;
    } else {
        auto *v7 = this->get_actor();
        auto *v8 = v7;
        if ((v7->field_8 & 0x10000000) != 0) {
            v7->update_abs_po(1);
        }

        this->m_wallrun_deviation = 1.0f -
            std::abs(this->field_38[2] * v8->my_abs_po->m[2][2] +
                     this->field_38[1] * v8->my_abs_po->m[2][1] +
                     this->field_38[0] * v8->my_abs_po->m[2][0]);
    }

    auto *v10 = this->get_actor();
    if ((v10->field_8 & 0x10000000) != 0) {
        v10->update_abs_po(true);
    }

    auto v11 = -YVEC[0] * v10->my_abs_po->m[2][0] +
        -YVEC[1] * v10->my_abs_po->m[2][1] +
        -YVEC[2] * v10->my_abs_po->m[2][2];
    if (v11 >= 0.0f) {
        this->m_wallrun_deviation = v11 * v11 + this->m_wallrun_deviation;
    }

    auto *v12 = this->get_actor()->m_player_controller;
    if ((v12->gb_grab.m_flags & 0x20) == 0) {
        if (v12->gb_grab.m_flags & 1) {
            if (this->field_1C > 0.12f)
                this->m_wallrun_deviation = 1.0;
        }
    }

    auto *v13 = v6->get_als_layer({0});

    string_hash tmp = v13->get_state_id();

    static Var<string_hash> wall_run_state_hash{0x009585DC};

    if (tmp == wall_run_state_hash()) {
        auto v14 = this->field_1C / 2.0f;
        if (v14 > 1.0f) {
            v14 = 1.0f;
        }

        constexpr auto flt_91F67C = 0.69999999f;

        v21 = (1.0f - flt_91F67C) * (1.0f - v14) + flt_91F67C;
    }

    als::param_list list;

    list.add_param({72, this->m_wallrun_deviation});
    list.add_param({16, v21});

    auto *v15 = v6->get_als_layer({0});
    v15->set_desired_params(list);

    auto *v16 = this->get_core();
    auto *v17 = (ai::hero_inode *) v16->get_info_node(ai::hero_inode::default_id, true);
    v17->update_wall_run_als_params();
}
