#include "ai_state_swing.h"

#include "actor.h"
#include "ai_find_best_swing_anchor.h"
#include "ai_player_controller.h"
#include "ai_state_jump.h"
#include "ai_state_run.h"
#include "ai_state_swing.h"
#include "ai_std_hero.h"
#include "ai_tentacle_web_curly.h"
#include "als_inode.h"
#include "base_ai_core.h"
#include "base_state.h"
#include "color32.h"
#include "common.h"
#include "conglom.h"
#include "controller_inode.h"
#include "custom_math.h"
#include "debug_render.h"
#include "debug_user_render.h"
#include "entity.h"
#include "entity_base_vhandle.h"
#include "event.h"
#include "event_manager.h"
#include "from_mash_in_place_constructor.h"
#include "func_wrapper.h"
#include "game_button.h"
#include "hit_react_state.h"
#include "info_node_desc_list.h"
#include "info_node_descriptor.h"
#include "layer_state_machine.h"
#include "marker.h"
#include "oldmath_po.h"
#include "oldmath_usefulmath.h"
#include "os_developer_options.h"
#include "physical_interface.h"
#include "physics_inode.h"
#include "pick_up_state.h"
#include "polytube.h"
#include "region.h"
#include "sampling_window.h"
#include "spiderman_camera.h"
#include "spidey_combat_inode.h"
#include "state_machine.h"
#include "sweet_cone.h"
#include "utility.h"
#include "vtbl.h"
#include "wds.h"
#include "web_polytube.h"

#include <cassert>
#include <cmath>

static Var<int> swinger_lr_swing_accel{0x0095804C};
static Var<int> swinger_ud_swing_accel{0x00958048};

static Var<float> flt_9581D8 = (0x009581D8);

static Var<bool> fast_swing = (0x0095833C);

static constexpr auto start_speed = 0.5f;

static constexpr auto minimum_web_length = 5.0f;

static Var<const float> magic_velocity_cancelling_angle_in_degrees{0x0091F764};

static Var<float> min_swing_web_length_squared = (0x0091F420);
static Var<float> max_swing_web_length_squared = (0x0091F424);
static Var<float> sweet_cone_angle_cos = (0x00958108);

static Var<float> swing_collision_break_length{0x009585BC};
static Var<float> swing_collision_stick_length{0x0091F468};

Var<swinger_t[2]> swingers = (0x00958188);

static Var<float> no_swing_timer{0x00958034};
static Var<float> no_swing_lockout_time{0x0091F43C};

Var<something_to_swing_to_data_t> something_to_swing_to_data = {0x00958098};

static const string_hash loco_allow_swing_id{static_cast<int>(to_hash("loco_allow_swing"))};

find_best_anchor_result_t::find_best_anchor_result_t() {
    this->m_visual_point = ZEROVEC;
    this->m_normal = ZEROVEC;
    this->m_point = this->m_normal;
    this->m_entity = nullptr;
    this->m_best_distance_squared = -1.0;
    this->m_target_length = -1.0;
    this->valid_flags = 0;
}

float find_best_anchor_result_t::get_target_length() {
    assert(valid_flags & TARGET_LENGTH_IS_VALID);

    return this->m_target_length;
}

void find_best_anchor_result_t::set_target_length(Float target_length) {
    this->m_target_length = target_length;
    this->valid_flags |= TARGET_LENGTH_IS_VALID;
}

float find_best_anchor_result_t::get_best_distance_squared() {
    assert(valid_flags & BEST_DISTANCE_SQUARED_IS_VALID);

    return this->m_best_distance_squared;
}

void find_best_anchor_result_t::set_best_distance_squared(Float best_distance_squared) {
    this->m_best_distance_squared = best_distance_squared;
    this->valid_flags |= BEST_DISTANCE_SQUARED_IS_VALID;
}

vector3d *find_best_anchor_result_t::get_point() {
    assert(valid_flags & POINT_IS_VALID);
    return &this->m_point;
}

void find_best_anchor_result_t::set_point(const vector3d &point) {
    this->m_point = point;
    this->valid_flags |= POINT_IS_VALID;
}

vector3d &find_best_anchor_result_t::get_normal() {
    assert(valid_flags & NORMAL_IS_VALID);
    return this->m_normal;
}

void find_best_anchor_result_t::set_normal(const vector3d &normal) {
    this->m_normal = normal;
    this->valid_flags |= NORMAL_IS_VALID;
}

vector3d &find_best_anchor_result_t::get_visual_point() {
    assert(valid_flags & VISUAL_POINT_IS_VALID);

    return this->m_visual_point;
}

void find_best_anchor_result_t::set_visual_point(const vector3d &a1) {
    this->m_visual_point = a1;
    this->valid_flags |= VISUAL_POINT_IS_VALID;
}

entity_base *find_best_anchor_result_t::get_entity() {
    assert(valid_flags & ENT_IS_VALID);

    return this->m_entity;
}

void find_best_anchor_result_t::set_entity(entity_base *a2) {
    this->m_entity = a2;
    this->valid_flags |= ENT_IS_VALID;
}

namespace ai {

VALIDATE_SIZE(swing_state, 0x40);

swing_state::swing_state() : enhanced_state() {
    
}

swing_state::swing_state(from_mash_in_place_constructor *a2) {
    THISCALL(0x0045AC60, this, a2);
}

uint32_t swing_state::get_virtual_type_enum() {
    return 319;
}

void swing_state::activate(ai_state_machine *a2,
                           const mashed_state *arg4,
                           const mashed_state *a4,
                           const param_block *a5,
                           base_state::activate_flag_e a6) {
    //sp_log("swing_state::activate:");

    if constexpr (1) {
        enhanced_state::activate(a2, arg4, a4, a5, a6);

        auto *v7 = this->get_core();
        this->field_3C = (hero_inode *) v7->get_info_node(hero_inode::default_id, true);
        auto *v8 = this->get_actor()->m_player_controller;
        auto v9 = v8->field_C;
        if (v9 != 3) {
            v8->field_10 = v9;
        }

        v8->field_C = 3;

        auto *v10 = &g_world_ptr()->field_1B0;
        if (!v10->field_8.is_set()) {
            g_world_ptr()->activate_web_splats();
        }

        auto *v11 = &g_world_ptr()->field_1F0;
        if (!v11->field_8.is_set()) {
            g_world_ptr()->activate_corner_web_splats();
        }

        this->field_3C->field_2C->left_air();

        auto *v12 = this->field_3C;
        auto *v13 = v12->field_20;
        auto *v14 = v12->field_28;
        auto *v15 = v12->field_40;

        v15->field_24 = true;
        v15->field_54 = false;

        v15->m_swing_time = 0.0;
        auto *v35 = v14;
        auto *v32 = v13;

        static const string_hash Swing_Launch{to_hash("Swing_Launch")};

        v13->request_category_transition(Swing_Launch, static_cast<als::layer_types>(0), true, false, false);
        auto *v16 = this->get_actor();

        po &abs_po = v16->get_abs_po();

        static constexpr auto swing_up = 0.2f;
        static constexpr auto swing_front = 0.0f;

        static Var<vector3d> stru_958154{0x00958154};
        stru_958154() = abs_po.m.arr[2];

        vector3d v33;
        v33[0] = abs_po.m.arr[3][0] + abs_po.m.arr[2][0] * swing_front +
            abs_po.m.arr[1][0] * swing_up;
        v33[1] = abs_po.m.arr[3][1] + abs_po.m.arr[2][1] * swing_front +
            abs_po.m.arr[1][1] * swing_up;
        v33[2] = abs_po.m.arr[1][2] * swing_up +
            (abs_po.m.arr[3][2] + abs_po.m.arr[2][2] * swing_front);

        auto *v17 = this->get_actor();
        entity_set_abs_position(v17, v33);

        vector3d v30 = something_to_swing_to_data().field_C - abs_po.get_position();
        v30[1] = LARGE_EPSILON;
        v30.normalize();

        auto *v21 = v35;
        auto v22 = v35->get_velocity();

        v15->field_80 = RAD_TO_DEG(calculate_xz_angle_relative_to_local_po(abs_po, v30, v22));

        als::param_list v29{};

        v29.add_param({13, v15->field_80});

        auto *v23 = v32->get_als_layer(static_cast<als::layer_types>(0));
        v23->set_desired_params(v29);

        if constexpr (1)
        //( SHOW_LOCOMOTION_INFO )
        {
            line_info v56;

            auto abs_pos = abs_po.get_position();
            v56.field_0 = abs_pos;
            v56.field_C = something_to_swing_to_data().field_C;
            v56.field_C.y = abs_pos.y;
            v56.render(20, false);

            v56.field_0 = abs_po.get_position();

            float v67 = 3.0;
            auto v52 = v35->get_velocity() * v67;
            auto v32 = abs_po.get_position();
            v56.field_C = v32 + v52;
            v56.render(21, false);
            auto v40 = mString{0, "anchor ang %.2f", v15->field_80};

            auto v34 = color32{255, 255, 255, 255};
            insertDebugString(2, v40, v34);
        }

        v21->setup_for_swing();
        v15->setup_new_web();

    } else {
        THISCALL(0x0047DA60, this, a2, arg4, a4, a5, a6);
    }
}

void swing_state::deactivate(const ai::mashed_state *a1) {
    base_state::deactivate(a1);
    if (this->get_actor() != nullptr) {
        auto *v3 = this->get_actor();
        if (v3->has_physical_ifc())
            this->field_3C->field_28->cleanup_from_swing();
    }
}

int swing_state::frame_advance(Float a2) {
    //sp_log("swing_state::frame_advance():");
    if constexpr (1) {
        auto *v3 = this->get_actor()->m_player_controller;
        auto v4 = v3->field_C;
        if (v4 != 3) {
            v3->field_10 = v4;
        }

        v3->field_C = 3;

        auto *hero_ptr = this->field_3C;
        auto *swing_inode_ptr = hero_ptr->field_40;
        auto *als_inode_ptr = hero_ptr->field_20;
        {
            auto &self = swingers()[0].field_94;
            self->set_visible(swingers()[0].field_90->is_visible(), false);

            self = swingers()[1].field_94;
            self->set_visible(swingers()[1].field_90->is_visible(), false);
        }

        if (swing_inode_ptr->field_24)
        {
            if (os_developer_options::instance()->get_int_from_name(mString{"SWING_DEBUG_TRAILS"}) >
                0) {
                auto v15 = color32{0x80, 0xFF, 0xFF, 0x40};
                float v14 = bit_cast<float>(0x3E4CCCCD);
                auto *v9 = this->get_actor();
                auto v13 = v9->get_abs_position();

                add_debug_sphere(v13, v14, v15);
            }

            swing_inode_ptr->field_24 = false;

        } else {
            if (!swing_inode_ptr->field_54 &&
                als_inode_ptr->get_eta_of_combat_signal(static_cast<als::layer_types>(0)) <= 0.0f) {
                swing_inode_ptr->fire_new_web(true);
            }

            swing_inode_ptr->update_mode_swinging(a2);
            if (swing_inode_ptr->m_constraint <= minimum_web_length) {
                if (this->field_3C->crawl_is_eligible(auto_crawl_attach_id, false)) {
                    return 73;
                }

                if (this->field_3C->oldcrawl_is_eligible(auto_crawl_attach_id, false)) {
                    return 1;
                }
            }
        }

        return 75;

    } else {
        return THISCALL(0x0047DDD0, this, a2);
    }
}

void swing_state::get_info_node_list(info_node_desc_list &a1) {
    return a1.add_entry(info_node_descriptor{swing_inode::default_id, 0});
}

int swing_state::get_mash_sizeof() {
    return 64;
}

static const string_hash cat_id_swing{"Swing"};

VALIDATE_OFFSET(swing_inode, field_1C, 0x1C);
VALIDATE_OFFSET(swing_inode, field_54, 0x54);
VALIDATE_OFFSET(swing_inode, field_7C, 0x7C);
VALIDATE_SIZE(swing_inode, 0x94);

swing_inode::swing_inode() {
    this->field_1C = false;
    this->field_24 = false;
    this->field_44 = false;
    this->field_54 = false;
}

vector3d sub_444A60(const vector3d &a2, const vector3d &a3);

Var<string_hash> state_id_sticky_hang_left{0x00958798};
Var<string_hash> state_id_sticky_hang_right{0x00958374};

Var<string_hash> cat_id_sticky_hang_right_push_off{0x00958580};
Var<string_hash> cat_id_sticky_hang_left_push_off{0x00958378};

void swing_inode::update_mode_swinging(Float a2)
{
    TRACE("swing_inode::update_mode_swinging");

    if constexpr (1)
    {
        auto *v174 = this->field_20->field_24;
        auto *v173 = this->field_20->field_20;
        auto *v172 = this->field_20->field_28;
        this->field_74 += a2;
        if (this->field_38 == 1) {
            constexpr auto sticky_exit_threshhold = 0.0099999998f;

            vector3d v171 = v174->get_axis(controller_inode::eControllerAxis{0});
            if (v171.length2() <= sticky_exit_threshhold) {
                v172->set_velocity(ZEROVEC, false);

                auto v76 = sub_444A60(YVEC, this->field_64);
                auto v15 = -this->field_64;

                po v170;
                v170.set_po(v15, v76, this->field_58);
                auto *v17 = this->get_actor();

                v17->set_abs_po(v170);
                return;
            }

            auto v83 = v173->get_state_id(static_cast<als::layer_types>(0));

            string_hash v81;

            auto v84 = v83 == state_id_sticky_hang_left() ||
                (v81 = v173->get_state_id(static_cast<als::layer_types>(0)), v81 == state_id_sticky_hang_right());

            if (v84) {
                string_hash hash_id = (this->field_7C < 0.0
                                        ? cat_id_sticky_hang_right_push_off()
                                        : cat_id_sticky_hang_left_push_off()
                                        );

                v173->request_category_transition(hash_id, static_cast<als::layer_types>(0), true, false, false);

                auto *v83 = this->get_actor();

                auto v76 = 5.0f;
                auto *v6 = this->get_actor();
                auto &v7 = v6->get_abs_po();
                auto v8 = v7.get_z_facing();

                auto *v9 = v83->physical_ifc();
                v9->set_velocity(v8 * v76, false);
            } else {
                v173->request_category_transition(cat_id_swing, static_cast<als::layer_types>(0), true, false, false);

                auto *v83 = this->get_actor();

                auto &v13 = v83->get_abs_po();
                auto v76 = v13.get_z_facing();
                auto *v14 = v83->physical_ifc();
                v14->set_velocity(v76, false);
            }

            this->field_40 = 0;
        }

        this->check_for_collision();
        vector3d norm_move_dir;
        vector3d up;

        this->compute_forward_and_up_directions(norm_move_dir, up);
        als::param_list v167{};

        assert(!vector3d::is_colinear(norm_move_dir, up));

        v167.add_param(27, norm_move_dir);
        v167.add_param(24, up);

        assert(std::abs(dot(norm_move_dir, up)) < LARGE_EPSILON);

        auto vel = v172->get_velocity();
        auto speed = vel.length();

        vel[1] = 0.0;
        auto lateral = vel.length();
        if constexpr (0) { //SHOW_LOCOMOTION_INFO

            insertDebugString(7, mString{0, "speed   %.2f", speed}, color32{255, 255, 255, 255});

            insertDebugString(8, mString{0, "lateral %.2f", lateral}, color32{255, 255, 255, 255});
        }

        this->clip_web(a2);
        this->update_pendulums(a2);

        {
            auto *v19 = v173->get_als_layer(static_cast<als::layer_types>(0));
            v19->set_desired_params(v167);
        }

        for (int i = 0; i < 2; ++i)
        {
            if (swingers()[i].field_0.field_34) {
                auto *v28 = this->get_actor();

                auto *v29 = swingers()[i].field_90;
                v29->set_abs_po(v28->get_abs_po());

                auto &v77 = swingers()[i].field_40;
                auto abs_pos = swingers()[i].field_3C->get_abs_position();
                auto tmp = abs_pos + v77;
                v77 = tmp;

                auto *v32 = this->get_actor();
                auto &v33 = v32->get_abs_po();
                tmp = v33.slow_xform(v77);

                auto *v83 = this->get_actor();
                vector3d v36 = v83->get_render_scale();
                tmp[0] *= v36[0];

                vector3d v38 = v83->get_render_scale();
                tmp[1] *= v38[1];

                vector3d v40 = v83->get_render_scale();
                tmp[2] *= v40[2];
                auto &a1 = tmp;

                auto *v42 = this->get_actor();
                auto &v43 = v42->get_abs_po();
                tmp = v43.slow_xform(a1);

                a1 = tmp;

                auto pivot_abs_pos_0 = swingers()[i].field_0.get_pivot_abs_pos();
                auto v160 = pivot_abs_pos_0 - a1;
                auto v159 = -v160;
                v159.normalize();
                float v158 = swingers()[i].field_4C * 4.0;
                if (v158 > 0.0) {
                    v158 = 0.0;
                }

                a1 = tmp;

                auto *v46 = swingers()[i].field_90;
                v46->set_abs_control_pt(0, a1);
                if (swingers()[i].field_4C >= 1.0) {
                    vector3d v155;
                    auto v53 = v159 * 0.0;
                    v155 = tmp + v53;

                    auto *v55 = swingers()[i].field_90;
                    v55->max_length = -1.0f;
                } else {
                    vector3d v157{};
                    vector3d v156{};

                    float v83 = (fast_swing() ? 6.f : 1.5f);

                    swingers()[i].field_4C += (a2 * v83);
                    auto v47 = v159 * v158;
                    v157 = tmp + v47;

                    auto v49 = v160 * swingers()[i].field_4C;
                    v156 = tmp + v49;

                    float v78 = v160.length() * swingers()[i].field_4C;
                    auto *v52 = swingers()[i].field_90;
                    v52->max_length = v78;
                }

                auto v154 = swingers()[i].field_0.get_pivot_abs_pos();
                auto v153 = tmp - v154;
                auto v152 = v153[1];

                auto v56 = YVEC * v152;
                auto v57 = v56 * 0.75f;
                v154 += v57;

                auto *v58 = swingers()[i].field_90;
                auto idx = v58->get_num_control_pts() - 1;

                auto *v59 = swingers()[i].field_90;
                v59->set_abs_control_pt(idx, swingers()[i].m_visual_point);
                auto v151 = tmp;
                auto v150 = swingers()[i].m_visual_point;

                auto v61 = v151 * 3.0f + v150 * 2.0f;
                auto v149 = v61 / 5.0f;

                auto v62 = swingers()[i].field_0.get_pivot_abs_pos();
                auto v63 = v151 - v62;
                auto v64 = v63.length();
                auto v82 = (swingers()[i].field_0.get_constraint() - v64 - 0.5f) / 2.0f;

                auto len = swingers()[i].field_0.get_constraint();
                auto v148 = (len - 9.0) / 9.0 + v82;
                if (v148 < LARGE_EPSILON) {
                    v148 = 0.0;
                }

                auto v78 = YVEC * v148;

                auto v66 = v151 + v149;
                auto v67 = v66 / 2.f;
                v78 = v67 - v78;

                auto *v68 = swingers()[i].field_90;
                v68->set_abs_control_pt(1, v78);
                v78 = YVEC * v148;

                auto v69 = v150 + v149;
                auto v70 = v69 / 2.0f;
                v78 = v70 - v78;

                auto *v71 = swingers()[i].field_90;
                v71->set_abs_control_pt(2, v78);

                {
                    auto *v72 = swingers()[i].field_90;

                    if (v72->the_spline.need_rebuild) {
                        v72->the_spline.rebuild_helper();
                    }
                }

                auto *pltb = swingers()[i].field_90;
                pltb->unforce_regions();

                auto *v74 = this->get_actor();
                auto *v144 = (entity *) v74->get_my_vhandle().get_volatile_ptr();

                pltb = swingers()[i].field_90;
                pltb->force_regions(v144);
            }
        }

        this->field_88 = this->field_8C;

    } else {
        THISCALL(0x004779B0, this, a2);
    }
}

double generic_compute_swing_angle(const vector3d &forward,
                                   const vector3d &up,
                                   const vector3d &basis) {
    assert(forward.is_normal());
    assert(up.is_normal());
    assert(basis.is_normal());

    auto v8 = dot(forward, basis);

    auto ang = bounded_acos(v8);

    if (dot(up, basis) >= 0.0) {
        ang = -ang;
    }

    return wrap_angle(ang);
}

void sub_44BCD0(entity_base *a1) {
    vector3d v3 = -YVEC;

    auto &v2 = a1->get_abs_po();

    generic_compute_swing_angle(v2.m[2], v2.m[1], v3);
}

vector3d swing_inode::get_desired_up_facing() {
    vector3d v8 = swingers()[0].m_visual_point - this->field_20->field_28->get_abs_position();

    if (v8.length2() >= LARGE_EPSILON) {
        v8.normalize();
        return v8;
    }

    return YVEC;
}

vector3d sub_444A60(const vector3d &a2, const vector3d &a3) {
    auto v1 = vector3d::cross(a2, a3);

    vector3d result = vector3d::cross(a2, v1);

    return result;
}

bool swing_inode::is_eligible(string_hash a2, Float a3) {
    if constexpr (1) {
        auto *v4 = &this->field_8->field_50;

        if (v4->get_pb_int(loco_allow_swing_id) == 0) {
            return false;
        }

        game_button v30;

        vector3d a3a;

        po v28;

        vector3d a4;
        vector3d v29;

        auto func = [](const game_button &self) -> bool {
            if ((32 & self.m_flags) == 0) {
                return (self.m_flags & 1);
            }

            return false;
        };

        bool cond;

        uint32_t local_flag = 0;

        if (!hero_inode::is_a_crawl_state(a2, true)) {
            auto *hero_inode_ptr = this->field_20;
            auto *physics_inode_ptr = hero_inode_ptr->field_28;
            auto *cntrl_inode_ptr = hero_inode_ptr->field_24;
            no_swing_timer() += a3;

            v29 = physics_inode_ptr->get_abs_position();
            a4 = physics_inode_ptr->get_abs_po().m[2];

            v28.m[0][0] = 1.0;
            v28.m[0][1] = 0.0;
            v28.m[0][2] = 0.0;
            v28.m[0][3] = 0.0;
            v28.m[1][0] = 0.0;
            v28.m[1][1] = 1.0;
            v28.m[1][2] = 0.0;
            v28.m[1][3] = 0.0;
            v28.m[2][0] = 0.0;
            v28.m[2][1] = 0.0;
            v28.m[2][2] = 1.0;
            v28.m[2][3] = 0.0;
            v28.m[3][0] = 0.0;
            v28.m[3][1] = 0.0;
            v28.m[3][2] = 0.0;
            v28.m[3][3] = 1.0;
            v28.set_rotate_y(0.0);

            constexpr float swing_length_mod = 1.0f;
            auto v24 = this->get_swing_cur_max_anchor_dist() * swing_length_mod * 0.5f;
            a4 *= v24;

            a3a = a4;
            a3a = v28.slow_xform(a3a);
            this->field_3C = 1;

            const float a6 = (a2 == run_state::default_id ? 15.f : 10.f);

            game_button v31 = cntrl_inode_ptr->get_button(controller_inode::eControllerButton{11});

            local_flag |= 4;

            game_button v30;
            cond = func(v31) &&
                (v30 = cntrl_inode_ptr->get_button(controller_inode::eControllerButton{4}),
                 local_flag = 12,
                 !func(v30));

            if ((local_flag & 8) != 0) {
                local_flag &= 0xFFFFFFF7;

                v30.~game_button();
            }

            if ((local_flag & 4) != 0) {
                local_flag &= 0xFFFFFFFB;
                v31.~game_button();
            }

            if (cond) {
                float sweet_spot_ground_level;

                this->find_best_anchor_point(v29, v29, a4, nullptr, a6, &sweet_spot_ground_level);
                assert(sweet_spot_ground_level != -1e10f);

                if (something_to_swing_to_data().field_64) {
                    this->update_something_to_swing_to(a3);

                    return true;
                }
            }

            if (a2 == jump_state::default_id && this->field_20->field_50 == 9) {
                return true;
            }

            return false;
        }

        auto *v6 = this->field_20->field_24;

        game_button v32 = v6->get_button(controller_inode::eControllerButton{11});

        local_flag |= 1u;

        game_button v33;

        cond = func(v32) &&
            (v33 = v6->get_button(controller_inode::eControllerButton{4}),
             local_flag = 3,
             !func(v33));

        if ((local_flag & 2) != 0) {
            local_flag &= 0xFFFFFFFD;

            v33.~game_button();
        }

        if ((local_flag & 1) != 0) {
            local_flag &= 0xFFFFFFFE;
            v32.~game_button();
        }

        return cond;
    } else {
        return THISCALL(0x004882C0, this, a2, a3);
    }
}

void swing_inode::play_fire_web_sound() {
    THISCALL(0x0045C7B0, this);
}

void swing_inode::frame_advance(Float a2) {
    auto v2 = this->field_1C;
    this->m_swing_time += a2;
    if (!v2) {
        this->field_1C = true;
        this->init_swingers();
    }
}

float swing_inode::get_swing_cur_max_anchor_dist() {
    static constexpr float swing_sweet_upper = 25.f;
    static Var<const float> swing_sweet_lower{0x009591C0};
    static constexpr float swing_sweet_min_dist = 30.f;
    static constexpr float swing_max_anchor_dist = 72.f;

    auto v3 = this->field_C->get_abs_position()[1];
    if (v3 >= swing_sweet_upper) {
        return swing_max_anchor_dist;
    }

    if (v3 >= swing_sweet_lower()) {
        return (v3 - swing_sweet_lower()) / (swing_sweet_upper - swing_sweet_lower()) *
            (swing_max_anchor_dist - swing_sweet_min_dist) +
            swing_sweet_min_dist;
    }

    return swing_sweet_min_dist;
}

void swing_inode::init_swingers() {
    THISCALL(0x004875F0, this);
}

void swing_inode::cleanup_swingers() {
    if constexpr (0) {
        if (this->field_1C) {
            for (auto i = 0u; i < 2; ++i) {
                if (swingers()[i].field_94 != nullptr) {
                    g_world_ptr()->ent_mgr.destroy_entity(swingers()[i].field_94);
                }

                if (swingers()[i].field_90 != nullptr) {
                    g_world_ptr()->ent_mgr.destroy_entity(swingers()[i].field_90);
                }

                auto *v3 = (entity *) swingers()[i].field_0.get_volatile_ptr();
                if (v3 != nullptr) {
                    g_world_ptr()->ent_mgr.destroy_entity(v3);
                }
            }
            this->field_1C = 0;
        }
    } else {
        THISCALL(0x0044C320, this);
    }
}

void swing_inode::clip_web(Float a2) {
    if constexpr (0) {
        auto *v3 = this->field_20->field_28;

        for (swinger_t &v4 : swingers()) {
            if (v4.field_0.field_34) {
                line_info v19{};

                v19.field_0 = v3->get_abs_position();
                auto v5 = v4.field_0.get_pivot_abs_pos();
                v19.field_C = v5;

                v19.check_collision(*local_collision::entfilter_entity_no_capsules(),
                                    *local_collision::obbfilter_lineseg_test(),
                                    nullptr);
                if ( v19.collision ) {
                    if (v19.hit_entity.get_volatile_ptr() != nullptr) {
                        event_manager::raise_event(event::COLLIDED_WITH_SWING_WEB,
                                                   v19.hit_entity.field_0);
                    }

                    auto v7 = v3->get_abs_position();

                    auto v18 = v7 - v19.hit_pos;
                    auto v12 = v18.length2();
                    if (v12 >= swing_collision_break_length() * swing_collision_break_length()) {
                        if (v12 < swing_collision_stick_length() * swing_collision_stick_length()) {
                            auto *v13 = v4.field_0.get_volatile_ptr();
                            v13->clear_parent(true);

                            auto *v14 = static_cast<entity_base *>(v4.field_0.get_volatile_ptr());
                            v14->set_abs_position(v19.hit_pos);

                            v4.field_0.set_constraint(v18.length());
                            v4.m_visual_point = v4.field_0.get_pivot_abs_pos();
                        }
                    } else {
                        this->field_44 = true;
                    }
                }
            }
        }

    } else {
        THISCALL(0x0045AF30, this, a2);
    }
}

void swing_inode::fire_new_web(bool is_play_fire_web_sound) {
    //sp_log("fire_new_web:");

    if constexpr (1) {
        this->field_54 = true;

        vector3d new_velocity = swingers()[0].field_40 + swingers()[0].field_3C->get_abs_position();

        auto *v12 = swingers()[0].field_90;

        v12->set_abs_control_pt(0, new_velocity);

        auto &pivot_abs_pos = swingers()[0].field_0.get_pivot_abs_pos();

        auto idx = v12->get_num_control_pts() - 1;

        v12->set_abs_control_pt(idx, pivot_abs_pos);

        v12->max_length = 0.0;

        v12->build(10, spline::eSplineType{3});

        v12->set_visible(true, false);

        swingers()[0].field_98->reset_curl();
        if (is_play_fire_web_sound) {
            this->play_fire_web_sound();
        }

        swingers()[0].field_50 = -1.0;
        if (std::abs(this->field_80) > magic_velocity_cancelling_angle_in_degrees()) {
            auto *act = this->get_actor();

            auto *v15 = act->physical_ifc();
            v15->cancel_all_velocity();

            new_velocity = -YVEC;
            auto *v18 = act->physical_ifc();
            v18->set_velocity(new_velocity, false);
        }

        do_web_splat(something_to_swing_to_data().m_visual_point,
                     something_to_swing_to_data().field_18,
                     *local_collision::entfilter_reject_all());

    } else {
        THISCALL(0x00478820, this, is_play_fire_web_sound);
    }
}

[[nodiscard]] vector3d average_direction(
    Float a2, const vector3d &a3, const vector3d &a4, Float a5, direction_sampling_window &a7)
{
    vector3d a3a = a7.average(a5);
    a3a.normalize();

    static const float flt_9591B8 = std::cos(DEG_TO_RAD(60.0)) * (-1.f);

    auto v17 = a3;
    auto v15 = dot(v17, a3a);
    if ( flt_9591B8 > v15 )
    {
        auto v10 = dot(a3a, YVEC);
        if ( std::abs(v10) <= 0.99000001 )
        {
            v17 = vector3d::cross(YVEC, a3a);
        }
        else
        {
            v17 = vector3d::cross(ZVEC, a3a);
        }
    }

    auto v14 = dot(v17, a4);
    if ( v14 < -0.30000001 )
    {
        v17 = a4;
    }

    a7.field_0[0].push_sample(a2, a3.x);
    a7.field_0[1].push_sample(a2, a3.y);
    a7.field_0[2].push_sample(a2, a3.z);

    v17 = a7.average(a5);
    v17.normalize();

    return v17;
}

static constexpr float triggered_reel_in_factor = 11.0f;

static constexpr float reel_in_factor = 10.f;

void swing_inode::update_pendulums(Float a2)
{
    TRACE("swing_inode::update_pendulums");

    if constexpr (0) {
#if 0
        auto *v3 = this->field_20;
        auto *controller_ptr = v3->field_24;
        auto *v5 = v3->field_28;
        auto *als_inode_ptr = v3->field_20;
        auto v118 = 0u;
        auto *v124 = v5;
        auto v6 = *v5->get_abs_po()->get_z_facing();

        vector3d v121;
        v121.arr[0] = v6[0];
        v121.arr[1] = v6[1];
        v121.arr[2] = v6[2];

        vector3d v117;
        controller_ptr->get_axis(&v117, controller_inode::eControllerAxis{2});

        auto v113 = this->get_desired_up_facing();
        v113.normalize();

        auto v10 = *v5->get_y_facing();

        vector3d v127 = average_direction(a2, &v113, &v10, 0.30000001, &up_sampling_window());

        float tmp;

        float v9;

        int i = 0;
        do {
            if (i == 0) {
                auto *v11 = v124;
                auto v12 = v124->get_abs_position();
                auto v13 = swingers()[0].field_0.get_pivot_abs_pos();

                auto v14 = v13[2] - v12[2];
                auto v15 = v13[1] - v12[1];
                auto v16 = v13[0] - v12[0];

                auto v109 = sqrt(v16 * v16 + v15 * v15 + v14 * v14);
                auto v17 = 1.f / v109;
                this->_constraint = v109;

                auto v119 = v17 * v14;
                float v116 = v17 * v15;
                auto v129 = v17 * v16;

                tmp = std::abs(v119 * YVEC().arr[2] + v116 * YVEC().arr[1] + v129 * YVEC().arr[0]);

                vector3d v131;
                v131[0] = -v129;
                v131[1] = -v116;
                v131[2] = -v119;

                auto v18 = v11->get_velocity();
                auto v113 = sub_444A60(v18.arr, v131.arr);
                v113.normalize();

                if (swingers()[0].field_50 < 0.f) {
                    swingers()[0].field_50 = this->_constraint;
                }

                float v31;

                if (this->field_3C == 1) {
                    if (this->field_2C + LARGE_EPSILON > swingers()[0].field_50) {
                        this->field_3C = 2;
                    }

                    Var<string_hash> swing_ground_avoidance_height_multiplier_id{0x009585F0};

                    if (this->field_3C == 1 &&
                        this->field_2C + LARGE_EPSILON < swingers()[0].field_50) {
                        auto *v21 = &this->field_8->field_50;

                        auto v22 = v21->get_pb_float(swing_ground_avoidance_height_multiplier_id());
                        auto *v23 = this->field_C;

                        auto v114 = v22 * this->field_2C;
                        auto v125 = 0.0;

                        vector3d v128 = YVEC() * 15.0f;

                        auto v25 = *v23->get_abs_position();

                        vector3d a2a = v25 - v128;

                        auto *v26 = this->field_C;

                        float v30;

                        vector3d a5;
                        vector3d a6;
                        if (find_intersection(*v26->get_abs_position(),
                                              a2a,
                                              *local_collision::entfilter_entity_no_capsules(),
                                              *local_collision::obbfilter_lineseg_test(),
                                              &a5,
                                              &a6,
                                              nullptr,
                                              nullptr,
                                              nullptr,
                                              false)) {
                            auto *v29 = this->field_C;

                            auto abs_pos = *v29->get_abs_position();

                            v30 = abs_pos[1] - a5[1];
                            if (v30 <= 0.0f) {
                                goto LABEL_22;
                            }

                        } else {
                            v30 = v114 + EPSILON;
                        }

                        if (v30 > 0.0f && v30 < v114) {
                            v31 = 1.0f - v30 / v114;
                            goto LABEL_29;
                        }

                        if (v30 > 0.0f) {
                            v31 = v125;
                            goto LABEL_29;
                        }
                    LABEL_22:
                        v31 = 1.0f;
                    LABEL_29:
                        v116 = swingers()[0].field_50 - this->field_2C;
                        const auto *v32 = &v116;

                        const auto flt_91F710 = 0.1f;

                        if (flt_91F710 >= (double) v116) {
                            v32 = &flt_91F710;
                        }

                        auto v123 = *v32;

                        const float flt_91F70C = 20.0f;
                        auto *v33 = &flt_91F70C;
                        if (flt_91F70C >= (double) v123) {
                            v33 = &v123;
                        }

                        auto v34 = v31 * *v33 * 4.5 * a2;
                        swingers()[0].field_0.field_1C = swingers()[0].field_0.field_1C - v34;
                        this->_constraint = this->_constraint - v34;
                        if (swingers()[0].field_50 > v34)
                            swingers()[0].field_50 = swingers()[0].field_50 - v34;
                        goto LABEL_35;
                    }
                }

                if (swingers()[0].field_50 <= 0.0f) {
                    auto v40 = a2 * 0.80000001;

                    auto v119 = swingers()[0].m_visual_point.arr[2] * v40;
                    auto v111 = swingers()[0].m_visual_point.arr[1] * v40;
                    auto tmp = swingers()[0].m_visual_point.arr[0] * v40;
                    auto *v41 = static_cast<entity_base *>(swingers()[0].field_0.get_volatile_ptr());

                    auto v43 = 1.f - v40;
                    auto v44 = *v41->get_abs_position();

                    vector3d v136;
                    v136[0] = v43 * v44[0] + tmp;
                    v136[1] = v43 * v44[1] + v111;
                    v136[2] = v43 * v44[2] + v119;
                    auto *v45 = static_cast<entity_base *>(swingers()[0].field_0.get_volatile_ptr());
                    entity_set_abs_position(v45, v136);
                } else if (a3.arr[2] > 0.85000002f &&
                           swingers()[0].field_50 * 1.2f > this->_constraint) {
                    swingers()[0].field_50 = 0.0;
                }

            LABEL_35:
                if (v109 + 0.1f < swingers()[0].field_50) {
                    swingers()[0].field_50 = (swingers()[0].field_50 + v109) * 0.5f;
                    swingers()[0].field_0.field_1C = swingers()[0].field_50;
                }

                Var<string_hash> swing_entry_smoothing_id{0x0095813C};

                auto *v35 = &this->field_8->field_50;
                auto v36 = v35->get_pb_float(swing_entry_smoothing_id());
                auto v111 = (1.0f - v117) * v36 * 50.0f;
                swingers()[0].field_0.set_constraint_lenience(v111);

                auto v110 = 0.0f;

                auto *v37 = &this->field_8->field_50;

                Var<string_hash> reel_buttons_delay_id{0x00958E60};
                a3.arr[2] = v37->get_optional_pb_float(reel_buttons_delay_id(), v110, nullptr);

                game_button v38;
                controller_ptr->get_button(&v38, controller_inode::eControllerButton{14});

                uint32_t v39 = ((v38.m_flags & 0x20) != 0 ? 0 : v38.m_flags & 1);

                if (v39) {
                    game_button v46;
                    controller_ptr->get_button(&v46, controller_inode::eControllerButton{14});
                    auto v47 = (v46.m_flags & 0x20) != 0 ? 0.0f : v46.field_1C;
                    auto v48 = v47 < v117;

                    auto v49 = v48 ? triggered_reel_in_factor : reel_in_factor;
                    auto v50 = v49 * a2 * 1.1f;
                    swingers()[0].field_0.field_1C = swingers()[0].field_0.field_1C + v50;
                    if (swingers()[0].field_50 > (double) 0.0f)
                        swingers()[0].field_50 = swingers()[0].field_50 + v50;
                }

                game_button v51;
                controller_ptr->get_button(&v51, controller_inode::eControllerButton{10});

                v118 |= 1u;
                bool v53 = false;
                if ((v51.m_flags & 0x20) == 0) {
                    auto v112 = v51.m_flags & 1;
                    if (v112) {
                        if (swingers()[0].field_0.field_1C > minimum_web_length) {
                            v53 = true;
                        }
                    }
                }

                if ((v118 & 1) != 0) {
                    v118 &= 0xFFFFFFFE;
                }

                if (!v53) {
                    if (this->field_40 == 3) {
                        v111 = COERCE_FLOAT(v106);
                        als_inode_ptr->request_category_transition(cat_id_swing,
                                                                   als::layer_types{0},
                                                                   true,
                                                                   false,
                                                                   false);
                    }
                    goto LABEL_78;
                }

                auto v54 = this->field_20->field_34->field_24 == 2;

                game_button v55;
                controller_ptr->get_button(&v55, controller_inode::eControllerButton{10});

                float v56 = ((v55.m_flags & 0x20) != 0 ? 0.0f : v55.field_1C);

                auto v112 = v56 < v117;
                if (v112) {
                    auto v57 = triggered_reel_in_factor * a2;
                    swingers()[0].field_0.field_1C = swingers()[0].field_0.field_1C - v57;
                    if (swingers()[0].field_50 > 0.0f) {
                        swingers()[0].field_50 = swingers()[0].field_50 - v57;
                    }

                    if (v54) {
                        goto LABEL_78;
                    }

                } else {
                    auto v58 = 10.0f * a2;
                    swingers()[0].field_0.field_1C = swingers()[0].field_0.field_1C - v58;
                    if (swingers()[0].field_50 > 0.0f) {
                        swingers()[0].field_50 = swingers()[0].field_50 - v58;
                    }
                    if (v54) {
                        goto LABEL_78;
                    }
                }

                v111 = COERCE_FLOAT(v106);

                Var<string_hash> cat_id_swing_reel_up{0x00958BD4};
                als_inode_ptr->request_category_transition(cat_id_swing_reel_up(),
                                                           als::layer_types{0},
                                                           true,
                                                           false,
                                                           false);
                this->field_40 = 3;
            LABEL_78:
                v9 = this->_constraint;
                if (v9 < minimum_web_length) {
                    v59 = minimum_web_length;
                    this->_constraint = minimum_web_length;
                    swingers()[0].field_0.field_1C = v59;
                }

                ++i;
            }
        } while (i < 2);

        auto *v60 = v124;
        auto v110 = 1.0f;
        auto v126 = v124->get_velocity();
        sub_44BCD0(this->field_C);
        this->field_8C = v9;
        if (this->field_88 < 0.0f) {
            this->field_88 = v9;
        }

        auto v61 = std::sqrt(v126.arr[2] * v126.arr[2] + v126.arr[1] * v126.arr[1] +
                             v126.arr[0] * v126.arr[0]);
        auto v123 = v61;

        float v62;
        if (v61 >= 15.0) {
            v62 = v110;
        } else {
            v62 = v60->get_abs_po()->field_0.arr[1].arr[1];
            if (v62 < EPSILON) {
                v62 = 0.0f;
            }
        }

        v114 = v62 * 20.0f;
        auto v63 = v117.arr[2] * v117.arr[2];
        auto v64 = v117.arr[0] * v117.arr[0];
        if (v117.arr[1] * v117.arr[1] + v64 + v63 <= LARGE_EPSILON) {
            if (this->field_3C != 1) {
                float v110 = 0.0;
                float v111 = 0.0;

                constexpr auto initial_boost_time = 0.2f;
                constexpr auto initial_boost_factor = 0.60000002f;
                v117 = v121 *
                    sub_48C0C0(this->m_swing_time,
                               v111,
                               initial_boost_time,
                               initial_boost_factor,
                               v110);
            }
        } else {
            v65 = v63 + v64;
            v117.arr[1] = 0.0;
            if (v65 > flt_86F854) {
                v66 = float_ONE / sqrt(v65);
                v117.arr[0] = v117.arr[0] * v66;
                v117.arr[1] = 0.0f * v66;
                v117.arr[2] = v117.arr[2] * v66;
            }
        }
        if (v117.arr[1] * v117.arr[1] + v117.arr[2] * v117.arr[2] + v117.arr[0] * v117.arr[0] >
            LARGE_EPSILON) {
            v67 = &v60->get_abs_po()->field_0.arr[1];
            v113.arr[0] = v67->base.arr[0];
            v113.arr[2] = v67->base.arr[2];
            v113.arr[1] = 0.0;
            v109 = v113.arr[2] * swingers()[0].field_0.field_1C;
            v68 = v113.arr[0] * swingers()[0].field_0.field_1C;
            v69 = v109;
            v70 = v68 * v68 + v109 * v109;
            if (v70 >= EPSILON) {
                v110 = v70;
                if (v70 > flt_86F854) {
                    v74 = float_ONE / sqrt(v110);
                    v68 = v68 * v74;
                    v113.arr[1] = 0.0f * v74;
                    v69 = v74 * v109;
                }
            } else {
                v71 = v67->base.arr[0];
                v72 = v67->base.arr[1];
                v73 = v67->base.arr[2];
                v113.arr[0] = v71;
                v68 = v71;
                v113.arr[2] = v73;
                v69 = v73;
                v113.arr[1] = v72;
            }
            v111 = 0.0;
            v75 = v113.arr[1] * v117.arr[1] + v69 * v117.arr[2] + v68 * v117.arr[0];
            a3.arr[2] = v75;
            if (v75 <= 0.0f) {
                v110 = -1.0;
                LODWORD(v108.field_4) = &stru_91F494;
            } else {
                v110 = 1.0;
                LODWORD(v108.field_4) = &stru_91F490;
            }
            v109 = sub_48C0C0(&a3.arr[2], &v111, &v110, &flt_91F498, (float *) LODWORD(v108.field_4));
            v111 = 1.0;
            v110 = 3.5;
            v125 = 60.0;
            a3.arr[2] = 15.0;
            v76 = sub_48C0C0(&this->field_2C, &a3.arr[2], &v125, &v111, &v110);
            v109 = v76 * v109;
            v127.arr[0] = v117.arr[0] * a2;
            v110 = v117.arr[2] * a2 * v114;
            v111 = v117.arr[1] * a2 * v114;
            out.arr[0] = out.arr[0] * v114;
            v113.arr[0] = out.arr[0] * v109;
            v113.arr[1] = v111 * v109;
            v113.arr[2] = v110 * v109;
            v121 = v113;
            v77 = v60->get_abs_po();
            v78 = sub_444A60((vector3d *) &a6.arr[2], v121.arr, v77->field_0.arr[1].base.arr);
            v79 = v78->arr[0];
            v108.field_4 = 0.0;
            v121.arr[0] = v79;
            v80 = v78->arr[1];
            v108.field_0 = (int) &IGNORE_LOC_13;
            v107 = 1;
            v121.arr[1] = v80;
            v121.arr[2] = v78->arr[2];
            v60->apply_force_increment(&v121, (physical_interface::force_type) 1, &IGNORE_LOC_13, 0);
        }
        actor::get_velocity(this->field_C, &v122);
        v81 = ai::physics_inode::get_abs_po(v60);
        v82 = average_direction((vector3d *) &a6.arr[2],
                                a2,
                                &v122,
                                &v81->field_0.arr[2].base,
                                0.30000001,
                                &heading_sampling_window);
        v83 = this->m_swing_time;
        v122 = *v82;
        v84 = v82->arr[0];
        v130 = v82->arr[1];
        v85 = v82->arr[2];
        v130 = 0.0;
        if (v83 <= flt_91F6FC) {
            stru_958154.arr[0] = v84;
            stru_958154.arr[1] = v130;
            stru_958154.arr[2] = v85;
        }
        v110 = v122.arr[2] * stru_958154.arr[2] + v122.arr[1] * stru_958154.arr[1] +
            v122.arr[0] * stru_958154.arr[0];
        sampling_window::push_sample(&stru_958610, a2, v110);
        als::param_list::param_list(&v120);
        v108.field_4 = this->m_swing_time;
        v143 = 0.0;
        v108.field_0 = 17;
        als::param_list::add_param_0(&v120, v108);
        v108.field_4 = this->field_8C * flt_87E734;
        v108.field_0 = 10;
        als::param_list::add_param_0(&v120, v108);
        v108.field_4 = sampling_window::average(&stru_958610, dword_91F6F8);
        v108.field_0 = 12;
        als::param_list::add_param_0(&v120, v108);
        v108.field_4 = v123;
        v108.field_0 = 0;
        als::param_list::add_param_0(&v120, v108);
        v86 = ai::als_inode::get_als_layer_0((ai::als_inode *) LODWORD(a3.arr[1]), 0);
        v86->base.m_vtbl->set_desired_params(v86, &v120);
        if (v122.arr[2] * v122.arr[2] + v122.arr[1] * v122.arr[1] + v122.arr[0] * v122.arr[0] <
            EPSILON)
            v122 = ai::physics_inode::get_abs_po(v60)->field_0.arr[2].base;
        v87 = pendulum::get_pivot_abs_pos((pendulum *) swingers, (vector3d *) &a6.arr[2]);
        v88 = ai::physics_inode::get_abs_position(v124, (vector3d *) &v137.field_14);
        v89 = v88->arr[2] - v87->arr[2];
        a3.arr[1] = v88->arr[1] - v87->arr[1];
        v90 = v88->arr[0] - v87->arr[0];
        v113.arr[1] = a3.arr[1];
        v113.arr[0] = v90;
        v113.arr[2] = v89;
        v91 = v113.arr[0] * v113.arr[0] + a3.arr[1] * a3.arr[1] + v89 * v89;
        if (v91 > flt_86F854) {
            v92 = float_ONE / sqrt(v91);
            v113.arr[0] = v113.arr[0] * v92;
            v113.arr[1] = a3.arr[1] * v92;
            v113.arr[2] = v92 * v89;
        }
        LODWORD(v108.field_4) = (string_hash) stru_958174.source_hash_code;

        auto *v93 = &this->field_8->field_50;
        v110 = COERCE_FLOAT((als::param *) &v108.field_4);

        Var<string_hash> boost_force_id{0x00958174};
        a3.arr[2] = v93->get_pb_float(boost_force_id());
        LODWORD(v108.field_4) = (string_hash) stru_958884.source_hash_code;

        v110 = COERCE_FLOAT((als::param *) &v108.field_4);

        Var<string_hash> boost_cooldown_id{0x00958884};
        v110 = v93->get_pb_float(boost_cooldown_id());

        LODWORD(v108.field_4) = (string_hash) stru_958140.source_hash_code;

        v111 = COERCE_FLOAT((als::param *) &v108.field_4);

        Var<string_hash> boost_min_angle_id{0x00958140};
        auto boost_min_angle = v93->get_pb_float(boost_min_angle_id());

        v111 = COERCE_FLOAT((als::param *) &v108.field_4);

        Var<string_hash> boost_max_angle_id{0x009587D0};
        auto boost_max_angle = v93->get_pb_float(boost_max_angle_id());
        v109 = boost_min_angle * 0.017453292f;
        v114 = boost_max_angle * 0.017453292f;
        auto v98 = -YVEC().arr[2] * v113.arr[2] + v113.arr[1] * (-YVEC().arr[1]) +
            (-YVEC().arr[0]) * v113.arr[0];
        if (v98 <= 1.f) {
            if (v98 < -1.f) {
                v98 = -1.f;
            }

        } else {
            v98 = 1.0f;
        }

        auto a3 = v98;
        if (v100 | v101) {
            a3 = -1.0;
        } else if (v98 > 1.0f) {
            a3 = 1.0;
        }

        a3 = std::acos(a3);

        Var<float> boost_cooldown_timer{0x00958100};
        v102 = boost_cooldown_timer - a2;
        boost_cooldown_timer = v102;
        if (v102 < 0.0f)
            boost_cooldown_timer = 0.0;
        if (a3.arr[0] > (double) v114) {
            boost_cooldown_timer = 0.0;
        } else {
            v103 = v4->base.m_vtbl
                       ->get_button(v4, &v139, (ai::controller_inode::eControllerButton) 9)
                       ->m_flags;
            v118 |= 2u;
            v104 = 0;
            if ((v103 & 0x20) == 0) {
                v112 = (v103 & 2) != 0;
                if ((v103 & 2) != 0 && boost_cooldown_timer <= (double) 0.0f)
                    v104 = 1;
            }
            if ((v118 & 2) != 0)
                game_button::~game_button(&v139);
            if (v104) {
                this->field_C->base.base.base.m_vtbl->has_sound_and_pfx_ifc(this->field_C);
                a3.arr[1] = a3.arr[2];
                if (a3.arr[0] > (double) v109 && v114 > (double) v109) {
                    v105 = (a3.arr[0] - v109) / (v114 - v109);
                    a3.arr[1] = (float_ONE - v105 * v105) * a3.arr[2];
                }
                v128.arr[0] = v122.arr[0] * a3.arr[1];
                v128.arr[1] = v122.arr[1] * a3.arr[1];
                v128.arr[2] = v122.arr[2] * a3.arr[1];
                ai::physics_inode::apply_force_increment(v124,
                                                         &v128,
                                                         (physical_interface::force_type) 1,
                                                         &IGNORE_LOC_13,
                                                         0);
                boost_cooldown_timer = v110;
            }
        }
        v143 = NAN;
        als::param_list::~param_list(&v120);
#endif

    } else {
        THISCALL(0x0045B110, this, a2);
    }
}

void swing_inode::check_for_collision() {
    THISCALL(0x0045C3C0, this);
}

void sub_44C3B0(line_info *a1) {
    if constexpr (1) {
        auto v1 = a1->hit_norm * 0.1f;

        auto &v3 = g_world_ptr()->field_1B0;

        vector3d arg4 = v1 + a1->hit_pos;

        auto *v4 = a1->hit_entity.get_volatile_ptr();
        v3.spawn(false, arg4, a1->hit_norm, nullptr, nullptr, v4, ZEROVEC, false, true);

    } else {
        CDECL_CALL(0x0044C3B0, a1);
    }
}

void sub_44C430(line_info *a1) {
    if constexpr (1) {
        auto v1 = a1->hit_norm[0] * 0.1f;
        auto v2 = a1->hit_norm[1] * 0.1f;
        auto v6 = a1->hit_norm[2] * 0.1f;
        auto *v3 = &g_world_ptr()->field_1F0;

        vector3d arg4;
        arg4[0] = v1 + a1->hit_pos[0];
        arg4[1] = v2 + a1->hit_pos[1];
        arg4[2] = v6 + a1->hit_pos[2];
        auto *v4 = a1->hit_entity.get_volatile_ptr();
        v3->spawn(false, arg4, a1->hit_norm, nullptr, nullptr, v4, ZEROVEC, false, true);

    } else {
        CDECL_CALL(0x0044C430, a1);
    }
}

void swing_inode::do_web_splat(vector3d target_point,
                               vector3d target_normal,
                               const local_collision::entfilter_base &entfilter_arg) {
    //sp_log("do_web_splat: %s, %s", target.to_string(), a4.to_string());

    if constexpr (1) {
        vector3d array_vectors[6];

        array_vectors[0] = target_point + target_normal;
        array_vectors[1] = target_point - target_normal;

        static constexpr auto halfUp = vector3d{0.0, 0.5, 0.0};

        array_vectors[2] = array_vectors[0] + halfUp;
        array_vectors[3] = array_vectors[1] - halfUp;
        array_vectors[4] = array_vectors[0] - halfUp;
        array_vectors[5] = array_vectors[1] + halfUp;

        line_info line{};

        static Var<bool> byte_958044{0x00958044};

        //byte_958044() = true;

        for (int i = 0; i < 6; i += 2) {
            line.clear();
            line.field_0 = array_vectors[i];
            line.field_C = array_vectors[i + 1];

            if (byte_958044()) {
                line.render(i / 2, false);
            }

            if (line.check_collision(entfilter_arg,
                                     *local_collision::obbfilter_lineseg_test(),
                                     nullptr)) {
                vector3d axis;

                if (line.hit_norm == YVEC) {
                    axis = XVEC;
                } else {
                    axis = YVEC;
                }

                vector3d local_vec3 = vector3d::sub_401870(line.hit_norm, YVEC);

                auto float_from_world = g_world_ptr()->field_1B0.field_2C * 0.5f;

                auto hit_pos = line.hit_pos;

                auto local_vec3_1 = local_vec3 * float_from_world;
                const auto axis1 = axis * float_from_world;

                auto local_vec3_4 = (hit_pos + axis1) - local_vec3_1;

                auto a2 = (hit_pos - axis1) - local_vec3_1;

                auto v87 = (hit_pos + axis1) + local_vec3_1;

                auto v86 = (hit_pos - axis1) + local_vec3_1;

                const auto local_normal = target_normal * 0.2;

                line_info array_lines[4];
                array_lines[3] = line_info{local_vec3_4 + local_normal, local_vec3_4 - local_normal};
                array_lines[2] = line_info{a2 + local_normal, a2 - local_normal};
                array_lines[1] = line_info{v87 + local_normal, v87 - local_normal};
                array_lines[0] = line_info{v86 + local_normal, v86 - local_normal};

                if (byte_958044()) {
                    array_lines[3].render(3, false);
                    array_lines[2].render(4, false);
                    array_lines[1].render(5, false);
                    array_lines[0].render(6, false);
                }

                bool cond[4]{};

                cond[3] = array_lines[3].check_collision(entfilter_arg,
                                                         *local_collision::obbfilter_lineseg_test(),
                                                         nullptr);
                cond[2] = array_lines[2].check_collision(entfilter_arg,
                                                         *local_collision::obbfilter_lineseg_test(),
                                                         nullptr);
                cond[1] = array_lines[1].check_collision(entfilter_arg,
                                                         *local_collision::obbfilter_lineseg_test(),
                                                         nullptr);
                cond[0] = array_lines[0].check_collision(entfilter_arg,
                                                         *local_collision::obbfilter_lineseg_test(),
                                                         nullptr);

                static constexpr auto flt_87EEE4 = 0.050000001f;

                if (!cond[1] || !cond[0] || cond[3] || cond[2]) {
                    if (cond[1] || cond[0] || !cond[3] || !cond[2]) {
                        if (cond[1] && cond[0] && cond[3] && cond[2]) {
                            sub_44C3B0(&line);
                        }
                    } else {
                        auto tmp = local_vec3 * flt_87EEE4;
                        line.hit_pos = line.hit_pos - tmp;

                        tmp = line.hit_norm * flt_87EEE4;
                        line.hit_pos = line.hit_pos + tmp;

                        if (line.hit_norm != YVEC) {
                            line.hit_norm = vector3d::sub_401870(line.hit_norm, YVEC);
                            sub_44C430(&line);
                        }
                    }

                } else {
                    auto tmp = local_vec3 * flt_87EEE4;
                    line.hit_pos = line.hit_pos - tmp;

                    tmp = line.hit_norm * flt_87EEE4;
                    line.hit_pos = line.hit_pos - tmp;

                    sub_44C430(&line);
                }

                break;
            }
        }

    } else {
        CDECL_CALL(0x0046B180, target_point, target_normal, &entfilter_arg);
    }
}

void swing_inode::compute_forward_and_up_directions(vector3d &forward, vector3d &up)
{
    physical_interface *v4 = this->field_C->physical_ifc();

    forward = v4->get_velocity();

    vector3d v26;
    up = this->get_desired_up_facing();

    this->field_48 = up;

    forward = sub_444A60(forward, up);

    if (forward.length2() < EPSILON) {
        auto *v13 = this->field_C;

        forward = v13->get_abs_po().get_z_facing();

        forward = sub_444A60(forward, up);
    }

    forward.normalize();

    assert(up.is_normal());
    assert(forward.is_normal());

    //assert(std::abs(dot(forward, up)) < LARGE_EPSILON);

    float slerp;
    if (this->m_swing_time >= 1.0f) {
        slerp = 0.5f;
    } else {
        float v16 = this->m_swing_time / 1.0f;
        slerp = v16 * v16;
    }

    po &v19 = this->field_C->get_abs_po();

    vector3d v23 = v19.get_y_facing();
    vector3d v24 = v19.get_z_facing();

    vector3d a14;
    reorient_vectors(v24, v23, forward, up, forward, a14, slerp);

    forward = sub_444A60(forward, up);
    forward.normalize();

    if constexpr (1) {
        mString v47 = {0, "slerp %.2f", slerp};

        auto v40 = color32{255, 255, 255, 255};
        insertDebugString(9, v47, v40);
    }
}

float swing_inode::compute_ground_level_at_sweet_spot_position(const vector3d &a1,
                                                               Float a2,
                                                               const region *reg) {
    assert(reg != nullptr);

    if constexpr (1) {
        vector3d v1 = a1 - YVEC * a2;

        vector3d a5;
        vector3d a6;

        float result;
        if (find_intersection(a1,
                              v1,
                              *local_collision::entfilter_entity_no_capsules(),
                              *local_collision::obbfilter_lineseg_test(),
                              &a5,
                              &a6,
                              nullptr,
                              nullptr,
                              nullptr,
                              false)) {
            result = a5[1];
        } else {
            result = reg->get_ground_level();
        }
        return result;

    } else {
        return (double) THISCALL(0x0044C280, this, &a1, a2, reg);
    }
}

void swing_inode::compute_dynamic_sweet_spot_params(float *result_angle,
                                                    float *result_length,
                                                    float *result_ground_level,
                                                    vector3d *result_direction) {
    if constexpr (1) {
        auto *cntrl_inode_ptr = this->field_20->field_24;
        auto *cam_ptr = g_world_ptr()->get_chase_cam_ptr(0);

        vector3d a2;
        vector3d a3;
        cam_ptr->get_look_and_up(&a2, &a3);

        a2.normalize();

        vector3d v60 = cntrl_inode_ptr->get_axis(controller_inode::eControllerAxis{0});
        if (v60.length() < EPSILON) {
            v60 = this->get_actor()->get_abs_po().get_z_facing();

        } else {
            v60 = cntrl_inode_ptr->get_axis(controller_inode::eControllerAxis{0});
        }

        auto a1 = v60;
        bool v19 = false;
        auto v20 = v60.length();
        if (v20 <= LARGE_EPSILON) {
            v19 = true;
        } else {
            a1 = a1 / v20;
        }

        auto *v22 = this->get_actor()->physical_ifc();
        auto vel = v22->get_velocity();
        assert(vel.is_valid());

        auto xz_velocity = sqrt(vel[0] * vel[0] + vel[2] * vel[2]);
        assert(vector3d(0.0f, 0.0f, xz_velocity).is_valid());

        float cos_alpha = dot(a1, a2);
        assert(std::abs(cos_alpha) < 1.0f + EPSILON);

        if (cos_alpha >= -1.f) {
            if (cos_alpha > 1.f)
                cos_alpha = 1.f;
        } else {
            cos_alpha = -1.f;
        }

        auto v55 = cos_alpha;
        if (cos_alpha < -1.f) {
            v55 = -1.0;
        } else if (cos_alpha > 1.f) {
            v55 = 1.0;
        }

        float alpha = std::acos(v55);
        if (alpha > half_PI) {
            alpha = PI - alpha;
        }

        alpha = alpha / half_PI;

        assert(alpha > -EPSILON && alpha < 1.0f + EPSILON);

        if (alpha >= 0.0f) {
            if (alpha > 1.f) {
                alpha = 1.f;
            }
        } else {
            alpha = 0.0f;
        }

        auto v30 = 1.f - (1.f - alpha) * (1.f - alpha);

        static constexpr auto sweet_spot_overdrive_velocity = 20.01f;
        assert(sweet_spot_overdrive_velocity > LARGE_EPSILON);

        auto v31 = xz_velocity / sweet_spot_overdrive_velocity;
        if (v31 > 1.f) {
            v31 = 1.f;
        }

        auto v52 = 1.f - v30;
        auto current_length = ((1.f - v31) * 55.f + 55.f * v31) * v52 + 35.f * v30;
        auto v58 = v52 * 0.6983062f + 0.87283915f * v30;

        assert(vector3d(0.0f, 0.0f, current_length).is_valid());

        double angle;
        double v42;

        auto clamp_and_asin = [](float a1) -> float {
            if (a1 < -1.f) {
                a1 = -1.f;
            } else if (a1 > 1.f) {
                a1 = 1.f;
            }

            return asin(a1);
        };

        if (v19) {
            constexpr float sweet_spot_distance = 30.01f;

            current_length = sweet_spot_distance;

            assert(vector3d(0.0f, 0.0f, current_length).is_valid());

            auto clamp_and_asin = [](float a1) -> double {
                if (a1 < -1.f) {
                    a1 = -1.f;
                }

                if (a1 > 1.f) {
                    a1 = 1.f;
                }

                return asin(a1);
            };

            static const float sweet_spot_incline_angle_sin = std::sin(0.6983062238602997f);

            assert(sweet_spot_incline_angle_sin >= 0.0f && sweet_spot_incline_angle_sin <= 1.0f);

            v58 = clamp_and_asin(sweet_spot_incline_angle_sin);
            if (v58 < 0.f) {
                v58 = 0.0;
            }
        }

        auto *v33 = this->field_C;

        int i = 0;
        auto v56 = v33->get_abs_position().y + 2.f;

        swing_anchor_finder anchor_finder{};
        anchor_finder.field_0 = std::cos(v58);
        auto v53 = std::sin(v58);
        while (1) {
            anchor_finder.field_4 = v53;
            anchor_finder.sweet_spot_distance = current_length;
            anchor_finder.field_C = min_swing_web_length_squared();
            anchor_finder.field_10 = max_swing_web_length_squared();
            anchor_finder.web_min_length = sqrt(min_swing_web_length_squared());
            anchor_finder.web_max_length = sqrt(max_swing_web_length_squared());
            anchor_finder.field_1C = sweet_cone_angle_cos();
            anchor_finder.field_20 = anchor_finder.web_max_length;
            auto v61 = v53 * current_length + v56 - current_length;

            auto *v35 = this->field_C;

            if ((v35->field_8 & 0x10000000) != 0) {
                v35->update_abs_po(1);
            }

            auto *v37 = v35->my_abs_po;
            if ((v35->field_8 & 0x10000000) != 0) {
                v35->update_abs_po(1);
            }

            sweet_cone_t sweet_cone{anchor_finder,
                                    v35->my_abs_po->get_position(),
                                    v37->get_z_facing(),
                                    v60,
                                    vector3d{0}};

            a1[0] = sweet_cone.sweet_spot[0];
            a1[1] = sweet_cone.sweet_spot[1];
            a1[2] = sweet_cone.sweet_spot[2];
            a1[1] = v56;

            auto *v38 = this->field_C;
            if (v38->get_primary_region() != nullptr) {
                auto *reg = v38->get_primary_region();
                this->compute_ground_level_at_sweet_spot_position(a1, current_length, reg);
            }

            auto v40 = v61 < 1.5f;
            *result_ground_level = 0.0;
            if (!v40) {
                angle = v58;

                *result_angle = angle;
                *result_length = current_length;
                *result_direction = v60;

                return;
            }

            if (i) {
                assert(i == 1);

                assert(current_length > LARGE_EPSILON);

                break;
            }

            auto v41 = (1.5f - v56) / (v53 - 1.f) * 0.69999999f;
            current_length = v41;
            if (v41 >= 35.f) {
                if (current_length > 55.f) {
                    current_length = 55.f;
                }

                i = 1;
            } else {
                current_length = 35.f;
                i = 1;
            }
        }

        v42 = (current_length + 1.5f - v56) / current_length;
        if (v42 >= -1.f) {
            if (v42 > 1.f) {
                v42 = 1.f;
            }

        } else {
            v42 = -1.f;
        }

        angle = clamp_and_asin(v42);

        if (angle <= 0.87283915f) {
            if (angle < 0.6983062f) {
                angle = 0.6983062f;
            }
        } else {
            angle = 0.87283915f;
        }

        *result_angle = angle;
        *result_length = current_length;
        *result_direction = v60;

    } else {
        THISCALL(0x0046AB90,
                 this,
                 result_angle,
                 result_length,
                 result_ground_level,
                 result_direction);
    }
}

void swing_inode::setup_new_web() {
    if constexpr (1) {
        constexpr float max_swing_length_mod = 3.0;

        this->field_54 = false;
        this->field_44 = false;
        this->field_84 = 100.0;
        constexpr float swing_length_mod = 1.0;
        swinger_lr_swing_accel() = 0;
        swinger_ud_swing_accel() = 0;
        this->field_8C = -1.0;
        this->field_88 = -1.0;
        fast_swing() = false;
        this->field_40 = 0;
        constexpr bool v6 = (max_swing_length_mod * 0.5 + 0.5 <= swing_length_mod);

        this->field_2C = something_to_swing_to_data().m_target_length;
        physical_interface *v8 = this->field_C->physical_ifc();
        v8->set_gravity(true);

        auto *ent = swingers()[0].field_0.get_volatile_ptr();
        ent->clear_parent(true);

        if (ent->is_rel_po_dirty()) {
            ent->compute_rel_po_from_model();
        }

        ent->my_rel_po->set_position(something_to_swing_to_data().field_C);

        ent->dirty_family(false);

        if (ent->is_conglom_member() || ent->is_a_conglomerate()) {
            ent->dirty_model_po_family();
        }

        ent->po_changed();

        swingers()[0].m_visual_point = something_to_swing_to_data().m_visual_point;
        swingers()[0].field_60 = something_to_swing_to_data().field_C;

        if (something_to_swing_to_data().field_8.get_volatile_ptr() &&
            something_to_swing_to_data().field_8.get_volatile_ptr()) {
            entity_base *v12 = something_to_swing_to_data().field_8.get_volatile_ptr();
            entity_base *v10 = swingers()[0].field_0.get_volatile_ptr();
            entity_set_abs_parent(v10, v12);
        }

        vector3d pivot_abs_pos = swingers()[0].field_0.get_pivot_abs_pos();

        const float distance = (something_to_swing_to_data().field_28 - pivot_abs_pos).length();

        this->m_constraint = distance;

        if (this->m_constraint > this->field_2C) {
            float v45 = 0.75 * this->m_constraint + this->field_2C * 0.25;
            float v22 = this->m_constraint - start_speed;

            this->m_constraint = std::max(v22, v45);
        }

        swingers()[0].field_0.m_constraint = this->m_constraint;
        if (swingers()[0].field_0.m_constraint >= 3.0) {
            swingers()[0].field_0.field_34 = true;
            something_to_swing_to_data().goal_constraint = swingers()[0].field_0.get_constraint();
            swingers()[0].field_38 = swingers()[0].field_0.get_constraint();
        }

        fast_swing() = v6;

        swingers()[0].field_4C = 0;
        entity_base *v25 = this->field_C;
        if ((v25->field_8 >> 28) & 1) {
            v25->update_abs_po(true);
        }

        auto *_polytube = swingers()[0].field_90;

        //sp_log("Address of vtbl = 0x%08X", get_vtbl(_polytube));

        entity_set_abs_po(_polytube, *v25->my_abs_po);
        entity_base *v26 = swingers()[0].field_3C;

        vector3d a2a = swingers()[0].field_40 + v26->get_abs_position();

        auto *v30 = swingers()[0].field_90;

        v30->set_abs_control_pt(0, a2a);

        vector3d v48 = swingers()[0].field_0.get_pivot_abs_pos();

        auto v36 = v30->get_num_control_pts() - 1;

        v30->set_abs_control_pt(v36, v48);

        v30->set_max_length(0.0f);
        flt_9581D8() = -1.0;
        this->field_C->physical_ifc()->m_gravity_multiplier = 5.0f;

        vector3d norm_move_dir;
        vector3d up;
        this->compute_forward_and_up_directions(norm_move_dir, up);
        ai::als_inode *v40 = this->field_20->field_20;

        assert(norm_move_dir.is_normal());
        assert(norm_move_dir.is_valid());
        assert(up.is_normal());
        assert(up.is_valid());
        assert(!vector3d::is_colinear(norm_move_dir, up));

        als::param_list v44;
        v44.add_param(27u, norm_move_dir);
        v44.add_param(24u, up);

        //assert(std::abs(dot(norm_move_dir, up)) < LARGE_EPSILON);

        auto *v41 = v40->get_als_layer(static_cast<als::layer_types>(0));

        //als::param_list v43;
        v41->set_desired_params(v44);
        v44.clear();
    } else {
        THISCALL(0x004783B0, this);
    }
}

void swing_inode::propose_something_to_swing_to(vector3d a1,
                                                entity_base *a4,
                                                vector3d a5,
                                                vector3d normal,
                                                Float a11,
                                                Float a12,
                                                vector3d visual_point) {
    if constexpr (1) {
        if (something_to_swing_to_data().field_0 <= 0.0f) {
            something_to_swing_to_data().field_28 = a1;

            uint32_t a4a;
            if (a4) {
                a4a = a4->get_my_handle().field_0;
            } else {
                a4a = 0;
            }

            something_to_swing_to_data().field_38 = a5;
            something_to_swing_to_data().field_34 = a4a;
            something_to_swing_to_data().field_44 = normal;
            something_to_swing_to_data().m_visual_point = visual_point;
            something_to_swing_to_data().m_target_length = a12;
            something_to_swing_to_data().field_5C = a11;
            something_to_swing_to_data().field_64 = (no_swing_timer() > no_swing_lockout_time());
        }

    } else {
        THISCALL(0x0044C100, this, a1, a4, a5, normal, a11, a12, visual_point);
    }
}

static string_hash web_swing_timer_id{static_cast<int>(to_hash("web_swing_timer"))};

bool swing_inode::can_go_to(string_hash a2) {
    if constexpr (0) {
        auto v2 = a2.source_hash_code;
        auto *v4 = this->field_20;
        auto *v5 = v4->field_20;
        auto *v6 = v4->field_24;

        if (hero_inode::is_a_crawl_state(a2, 1)) {
            return this->field_84 < 0.2f;
        }

        if (v2 != run_state::default_id.source_hash_code &&
            v2 != pick_up_state::default_id.source_hash_code) {
            static string_hash loco_allow_aerial_hit_react_id{
                to_hash("loco_allow_aerial_hit_react")};

            auto &v8 = this->field_8->field_50;

            auto v9 = v8.get_optional_pb_int(loco_allow_aerial_hit_react_id, 0, 0);
            if (v2 == ai::hit_react_state::default_id.source_hash_code && !v9) {
                return false;
            }

            auto &v10 = this->field_8->field_50;

            if (v10.get_pb_float(web_swing_timer_id) > this->m_swing_time) {
                return false;
            }

            auto &v11 = this->field_8->field_50;

            auto v12 = v11.get_pb_int(loco_allow_swing_id);
            if (!this->field_44) {
                if (v12 != 0) {
                    auto v13 = v6->get_button(controller_inode::eControllerButton{11});
                    auto v14 = v13.sub_48B270();
                    v13.~game_button();
                    if (v14) {
                        return false;
                    }

                    auto *v15 = v5->get_als_layer(static_cast<als::layer_types>(0));
                    return v15->is_interruptable();
                }
            }
        }

        auto *v16 = v5->get_als_layer(static_cast<als::layer_types>(0));
        return v16->is_interruptable();

    } else {
        return (bool) THISCALL(0x0045C850, this, a2);
    }
}

void swing_inode::update_something_to_swing_to(Float a2) {
    if constexpr (0) {
    } else {
        THISCALL(0x0045AD80, this, a2);
    }
}

void swing_inode::find_best_anchor_point(const vector3d &a1,
                                         [[maybe_unused]] const vector3d &a2,
                                         [[maybe_unused]] const vector3d &a3,
                                         [[maybe_unused]] const entity_base *a4,
                                         Float length,
                                         float *sweet_spot_ground_level) {
    if constexpr (1) {
        //sp_log("find_best_anchor_point:");

        static constexpr float safety_34730 = 3.0;

        entity *v8 = this->field_C;

        if (v8->get_primary_region()) {
            region *v9 = v8->get_primary_region();
            v9->get_ground_level();
        }

        vector3d direction;
        float ground_level = 0.0;
        float angle = 0.0;
        float sweet_spot_length = 0.0;
        this->compute_dynamic_sweet_spot_params(&angle,
                                                &sweet_spot_length,
                                                &ground_level,
                                                &direction);

        float s, c;
        fast_sin_cos_approx(angle, &s, &c);

        swing_anchor_finder finder{c,
                                   s,
                                   sweet_spot_length,
                                   min_swing_web_length_squared(),
                                   max_swing_web_length_squared(),
                                   sweet_cone_angle_cos()};

        finder.set_max_pull_length(length);

        find_best_anchor_result_t anchor_result;
        if (finder.find_best_anchor(this->field_C, direction, &anchor_result)) {
            auto v10 = anchor_result.m_point - a1;

            auto target_length = anchor_result.get_target_length();

            float v13 = v10.length();
            sweet_spot_length = target_length - safety_34730;

            target_length = std::min(sweet_spot_length, v13, std::less_equal<float>{});

            auto best_distance = sqrt(anchor_result.m_best_distance_squared);

            this->propose_something_to_swing_to(a1,
                                                anchor_result.m_entity,
                                                anchor_result.m_point,
                                                anchor_result.m_normal,
                                                best_distance,
                                                target_length,
                                                anchor_result.m_visual_point);
            //*(float *) v33 = v19;
        } else {
            if (something_to_swing_to_data().field_0 <= 0.0) {
                something_to_swing_to_data().field_34 = 0;
                something_to_swing_to_data().field_8.field_0 = 0;
                something_to_swing_to_data().field_64 = false;
            }
        }

        *sweet_spot_ground_level = ground_level;
    } else {
        THISCALL(0x00488060, this, &a1, &a2, &a3, a4, length, sweet_spot_ground_level);
    }
}

} // namespace ai

void swing_state_patch() {

    return;
    {
        FUNC_ADDRESS(address, &ai::swing_state::activate);
        SET_JUMP(0x0047DA60, address);
    }

    if constexpr (0) {
        {
            FUNC_ADDRESS(address, &ai::swing_state::frame_advance);
            set_vfunc(0x008774D8, address);
        }

        {
            {
                FUNC_ADDRESS(address, &ai::enhanced_state::activate);
                REDIRECT(0x0047DAAB, address);
            }

            {
                FUNC_ADDRESS(address, &world_dynamics_system::activate_web_splats);
                REDIRECT(0x0047DB2B, address);
            }

            {
                FUNC_ADDRESS(address, &ai::als_inode::request_category_transition);
                REDIRECT(0x0047DBAC, address);
            }

            REDIRECT(0x0047DC97, entity_set_abs_position);

            {
                void (als::param_list::*func)(als::param a2) = &als::param_list::add_param;

                FUNC_ADDRESS(address, func);
                REDIRECT(0x0047DD6F, address);
            }

            {
                FUNC_ADDRESS(address, &ai::physics_inode::setup_for_swing);
                REDIRECT(0x0047DD8D, address);
            }

            {
                double (*func)(const po &,
                               const vector3d &,
                               const vector3d &) = calculate_xz_angle_relative_to_local_po;
                REDIRECT(0x0047DD2F, func);
            }
        }
    }
}

void swing_inode_patch() {

    {
        FUNC_ADDRESS(address, &ai::swing_inode::update_pendulums);
        REDIRECT(0x00477BCB, address);
    }

    {
        FUNC_ADDRESS(address, &ai::swing_inode::compute_forward_and_up_directions);
        REDIRECT(0x00477B64, address);
        REDIRECT(0x004787A6, address);
    }

    return;

    {
        FUNC_ADDRESS(address, &ai::swing_inode::clip_web);
        REDIRECT(0x00477BC3, address);
    }
    
    {
        FUNC_ADDRESS(address, &ai::swing_inode::update_mode_swinging);
        REDIRECT(0x0047DE7E, address);
    }

    {
        FUNC_ADDRESS(address, &ai::swing_inode::setup_new_web);
        REDIRECT(0x0047DD94, address);
    }

#if 0
    {
        FUNC_ADDRESS(address, &ai::swing_inode::frame_advance);
        set_vfunc(0x0087DB50, address);
    }

    

    {
        FUNC_ADDRESS(address, &ai::swing_inode::is_eligible);
        REDIRECT(0x00488BE6, address);
    }

    {
        FUNC_ADDRESS(address, &ai::swing_inode::find_best_anchor_point);
        REDIRECT(0x00488627, address);
    }

    {
        FUNC_ADDRESS(address, &ai::swing_inode::fire_new_web);
        REDIRECT(0x0047DE72, address);
    }

    {
        FUNC_ADDRESS(address, &ai::swing_inode::check_for_collision);
        REDIRECT(0x00477B4D, address);
    }

    {
        FUNC_ADDRESS(address, &conglomerate::get_bone);
        REDIRECT(0x004878E5, address);
    }

    {
        FUNC_ADDRESS(address, &swing_anchor_finder::find_best_offset_anchor);
        REDIRECT(0x00488148, address);
    }

    {
        FUNC_ADDRESS(address, &ai::swing_inode::propose_something_to_swing_to);
        //REDIRECT(0x0048824A, address);
    }
#endif
}
