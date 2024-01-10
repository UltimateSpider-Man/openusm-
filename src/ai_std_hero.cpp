#include "ai_std_hero.h"

#include "variable.h"

#include "actor.h"
#include "ai_player_controller.h"
#include "ai_state_jump.h"
#include "ai_state_swing.h"
#include "ai_state_web_zip.h"
#include "als_animation_logic_system.h"
#include "als_inode.h"
#include "base_ai_core.h"
#include "colgeom_alter_sys.h"
#include "collide.h"
#include "combat_state.h"
#include "common.h"
#include "conglom.h"
#include "custom_math.h"
#include "entity.h"
#include "entity_base_vhandle.h"
#include "from_mash_in_place_constructor.h"
#include "func_wrapper.h"
#include "glass_house_manager.h"
#include "hit_react_state.h"
#include "line_info.h"
#include "oldmath_po.h"
#include "param_list.h"
#include "physical_interface.h"
#include "physics_inode.h"
#include "pick_up_state.h"
#include "plr_loco_crawl_state.h"
#include "plr_loco_crawl_transition_state.h"
#include "put_down_state.h"
#include "throw_state.h"
#include "utility.h"
#include "vtbl.h"

#include <cmath>

namespace ai {

VALIDATE_SIZE(hero_inode::internal, 0x124);
VALIDATE_SIZE(hero_inode, 0x24C);
VALIDATE_OFFSET(hero_inode, field_70, 0x70);

hero_inode::hero_inode(from_mash_in_place_constructor *a2) {
    THISCALL(0x006A1B10, this, a2);
}

bool sub_68A0B0(int a1)
{
    bool result;
    switch ( a1 )
    {
    case 4:
    case 6:
    case 7:
    case 8:
        result = true;
        break;
    default:
        result = false;
        break;
    }

    return result;
}

bool hero_inode::jump_can_go_to(string_hash a2) {
    TRACE("ai::hero_inode::jump_can_go_to", a2.to_string());

    if constexpr (1) {
        auto *v4 = this->field_8;
        auto *info_node = bit_cast<ai::als_inode *>(v4->get_info_node(als_inode::default_id, true));
        if ( this->field_7C ) {
            return false;
        }

        if ( a2 == web_zip_state::default_id ) {
            auto v7 = this->field_50;
            if ( v7 != 13 && v7 != 12 ) {
                return true;
            }

            auto *v8 = this->field_8;
            auto *v9 = bit_cast<ai::physics_inode *>(v8->get_info_node(physics_inode::default_id, true));
            auto a3 = v9->field_1C->get_velocity();
            auto len = std::sqrt(a3[2] * a3[2] + a3[0] * a3[0]);
            return len * 0.2f < -a3[1];
        }

        if ( (a2 == plr_loco_crawl_transition_state::default_id
            || a2 == plr_loco_crawl_state::default_id)
            && sub_68A0B0(this->field_50) )
        {
            auto v2 = this->field_70;
            if ( v2 < 0.30000001f ) {
                return false;
            }
        }

        static string_hash loco_allow_aerial_hit_react_id {int(to_hash("loco_allow_aerial_hit_react"))};

        auto v19 = 0;
        auto *v11 = this->field_8;
        auto optional_pb_int = v11->field_50.get_optional_pb_int(
                  loco_allow_aerial_hit_react_id,
                  v19,
                  nullptr);

        if ( a2 == hit_react_state::default_id && !optional_pb_int ) {
            return false;
        }

        if ( a2 == put_down_state::default_id ) {
            return false;
        }

        if ( a2 == swing_state::default_id ) {
            static string_hash cat_id_jump_to_swing {int(to_hash("Jump_To_Swing"))};

            auto v15 = 0.0f;
            auto cat_id = info_node->get_category_id(static_cast<als::layer_types>(0));
            auto *v13 = bit_cast<als::state_machine *>(info_node->field_1C->get_als_layer(static_cast<als::layer_types>(0)));
            auto &anim_handle = v13->get_anim_handle();
            if ( anim_handle.get_anim_ptr() ) {
                auto &v14 = v13->get_anim_handle();
                v15 = v14.get_anim_norm_time();
            }

            return cat_id != cat_id_jump_to_swing || v15 >= 1.0f;
        } else {
            auto *v16 = info_node->field_1C->get_als_layer(static_cast<als::layer_types>(0));
            return v16->is_interruptable();
        }
    } else {
        return THISCALL(0x006A6E70, this, a2);
    }
}

void hero_inode::frame_advance(Float a2) {
    sp_log("hero_inode::frame_advance():");

    if constexpr (0) {
        auto *v3 = this->field_C->m_player_controller;

        als::param v14;
        v14.field_4 = 1;
        v14.field_0 = physics_inode::default_id.source_hash_code;
        auto *v4 = this->field_8;

        auto *v5 = (physics_inode *) v4->get_info_node(physics_inode::default_id, true);
        if (!this->field_1C) {
            setup_hero_capsule(this->field_C);
            this->field_1C = true;
        }

        auto *v6 = v5->field_C;

        auto &v7 = v6->get_abs_po().get_position();

        vector3d v18;
        v18[0] = v7[0];
        v18[1] = v7[1];
        v18[2] = v7[2];

        auto *v8 = (entity *) this->field_C;
        v8->get_primary_region();

        Var<vector3d> stru_937D94{0x00937D94};

        Var<const float> max_ground_dist_35476{0x00937F6C};

        vector3d v19 = v18 - stru_937D94() * max_ground_dist_35476();

        vector3d v20, v21;
        if (find_intersection(v18,
                              v19,
                              *local_collision::entfilter_entity_no_capsules(),
                              *local_collision::obbfilter_lineseg_test(),
                              &v20,
                              &v21,
                              nullptr,
                              nullptr,
                              nullptr,
                              false)) {
            this->field_244 = v18[1] - v20[1];
        } else {
            this->field_244 = max_ground_dist_35476();
        }

        float v17 = 0.0;
        auto *v9 = v3->get_gb_swing_raw();
        if ((v9->m_flags & 0x20) == 0) {
            if (v9->m_flags & 1) {
                float v11 = ((v9->m_flags & 0x20) != 0 ? 0.0f : v9->field_1C);

                v17 = v11 + 0.050000001f;
            }
        }

        this->field_238 += a2;

        if (v3->get_motion_force() > EPSILON) {
            this->field_238 = 0.0;
        }

        auto *v12 = (als_inode *) this->field_8->get_info_node(als_inode::default_id, true);
        als::param_list v16;

        v14.field_0 = 17;
        v14.field_4 = v17;
        v16.add_param(v14);

        v14.field_0 = 19;
        v14.field_4 = this->field_238;
        v16.add_param(v14);

        v14.field_0 = 70;
        v14.field_4 = this->field_244;
        v16.add_param(v14);

        auto *v13 = v12->field_1C->get_als_layer(static_cast<als::layer_types>(0));

        v13->set_desired_params(v16);

        if (this->field_80) {
            local_collision::destroy_primitive_list(&this->field_80);
        }

        if (this->field_84) {
            local_collision::destroy_primitive_list(&this->field_84);
        }

    } else {
        THISCALL(0x006A7950, this, a2);
    }
}

bool hero_inode::is_a_crawl_state(string_hash a1, bool a2) {
    auto result = (a1 == plr_loco_crawl_state::default_id);
    if (a2 &&
        (a1 == plr_loco_crawl_transition_state::default_id ||
         a1 == plr_loco_crawl_state::default_id)) {
        result = true;
    }

    return result;
}

bool hero_inode::ought_to_jump_off_wall(line_info &a2) {
    return (bool) THISCALL(0x006A6280, this, &a2);
}

bool hero_inode::ought_to_stick_to_wall(line_info &a2, bool a3) {
    if constexpr (0) {
        auto *v4 = this->field_C;
        entity *v20 = 0;
        subdivision_node_obb_base *v21 = 0;
        if ((v4->field_8 & 0x10000000) != 0) {
            v4->update_abs_po(true);
        }

        auto *v5 = (float *) v4->my_abs_po;

        auto *vtbl = bit_cast<thiscall_call(*)[1]>(this->field_C);
        auto func = (*vtbl)[117];

        vector3d v27;
        auto v6 = ((float *) func(this->field_C, &v27))[1] * 0.5f;

        static Var<vector3d> stru_937D94{0x00937D94};

        v27[1] = stru_937D94()[1] * v6;
        v27[2] = stru_937D94()[2] * v6;
        auto v22 = stru_937D94()[0] * v6 + v5[12];
        auto v23 = v27[1] + v5[13];
        auto v7 = v23;
        auto v8 = v27[2] + v5[14];
        a2.field_0[0] = v22;
        a2.field_0[1] = v7;
        auto v24 = v8;
        a2.field_0[2] = v24;

        vector3d a1;
        vector3d a5;
        if (!find_sphere_intersection(a2.field_0,
                                      2.0,
                                      *local_collision::entfilter_entity_no_capsules(),
                                      *local_collision::obbfilter_sphere_test(),
                                      &a1,
                                      &a5,
                                      &v20,
                                      &v21) ||
            !glass_house_manager::is_point_in_glass_house(a1) || a5[1] > 0.73242188f) {
            return false;
        }

        auto v10 = a1[1];
        auto v11 = a1[2];
        auto v12 = a1[0];
        a2.field_C[0] = a1[0];
        a2.field_C[1] = v10;
        a2.field_C[2] = v11;
        auto a2a = (v20 ? v20->get_my_handle() : 0);
        auto v13 = a5[0];
        a2.hit_entity = {a2a};
        a2.hit_norm[0] = v13;
        a2.hit_norm[1] = a5[1];
        a2.hit_norm[2] = a5[2];
        a2.hit_pos[0] = v12;
        a2.hit_pos[1] = v10;
        a2.hit_pos[2] = v11;
        auto v14 = v21;
        a2.field_4C = v14;
        a2.collision = true;

        auto get_phys_ifc = (*vtbl)[74];

        auto *v15 = (physical_interface *) get_phys_ifc(this->field_C);
        auto *v16 = v15->field_84.get_volatile_ptr();
        entity *v17 = v20;
        entity *v18 = v16;

        bool result = true;
        if (is_noncrawlable_surface(a2) || have_relative_movement(v18, v17)) {
            result = false;
        }

        return result;
    } else {
        return (bool) THISCALL(0x0069FAF0, this, &a2, a3);
    }
}

bool hero_inode::accept_crawl_spot(vector3d a1, vector3d a4) {
    return (bool) THISCALL(0x00693B00, this, a1, a4);
}

bool hero_inode::get_closest_corner(corner_info *a2, crawl_request_type a3) {
    return (bool) THISCALL(0x006A5CF0, this, a2, a3);
}

bool hero_inode::run_is_eligible(string_hash a2)
{
    TRACE("hero_inode::run_is_eligible");

    if constexpr (1) {
        auto *v3 = this->field_8;
        auto *the_phys_inode = bit_cast<physics_inode *>(v3->get_info_node(physics_inode::default_id, true));
        this->field_4C = 0;
        if ( auto *phys_ifc = the_phys_inode->field_1C;
                phys_ifc->is_effectively_standing()
                    && phys_ifc->allow_manage_standing() )
        {
            if ( a2 != jump_state::default_id ) {
                this->field_58 = the_phys_inode->get_abs_position();
            }

            return true;
        }

        return false;

    } else {
        return THISCALL(0x006A7770, this, a2);
    }
}

bool hero_inode::crawl_is_eligible(string_hash a2, bool a3) {
    return (bool) THISCALL(0x006B0EB0, this, a2, a3);
}

bool hero_inode::oldcrawl_is_eligible(string_hash a2, bool a3) {
    return (bool) THISCALL(0x006B0E60, this, a2, a3);
}

void hero_inode::set_surface_info(const line_info &a2)
{
    this->field_1B0.copy(a2);
}

void hero_inode::update_wall_run_als_params() {
    if constexpr (1) {
        auto *v2 = this->field_8;

        auto *v3 = (als_inode *) v2->get_info_node(als_inode::default_id, true);
        auto *v4 = this->field_C;
        auto *v5 = v3;
        if ((v4->field_8 & 0x10000000) != 0) {
            v4->update_abs_po(1);
        }

        auto *v6 = this->field_C;

        float v8 = -calculate_xz_angle_relative_to_local_po(*v6->my_abs_po,
                                                            YVEC,
                                                            v4->get_abs_po().m.arr[2]);

        constexpr float flt_882080 = PI / 4.0;
        constexpr float flt_8A48CC = -flt_882080;

        v8 = std::clamp(v8, flt_8A48CC, flt_882080);

        float v12 = (v8 + flt_882080) / half_PI;

        als::param_list list;
        list.add_param({18, v12});

        auto *v9 = v5->field_1C->get_als_layer(static_cast<als::layer_types>(0));
        v9->set_desired_params(list);

    } else {
        THISCALL(0x006A67E0, this);
    }
}

void hero_inode::update_crawl_als_params()
{
    TRACE("hero_inode::update_crawl_als_params");

    THISCALL(0x006A63D0, this);
}

bool hero_inode::run_can_go_to(string_hash arg0) {
    if constexpr (1) {
        auto *v3 = this->field_8;

        v3->get_info_node(physics_inode::default_id, true);

        auto *v4 = this->field_8;

        auto *v5 = (als_inode *) v4->get_info_node(als_inode::default_id, true);
        if (arg0 == hit_react_state::default_id) {
            return true;
        }

        if (arg0 == throw_state::default_id &&
            (arg0 = v5->get_category_id(static_cast<als::layer_types>(0)), arg0 != ai::cat_id_idle_walk_run())) {
            return false;
        }

        auto *v7 = v5->field_1C->get_als_layer(static_cast<als::layer_types>(0));
        return v7->is_interruptable();

    } else {
        return THISCALL(0x006A76D0, this, arg0);
    }
}

void hero_inode::engage_water_exit()
{
    TRACE("hero_inode::engage_water_exit");

    THISCALL(0x006944D0, this);
}

bool hero_inode::jump_is_eligible(string_hash a2)
{
    TRACE("hero_inode::jump_is_eligible");

    return THISCALL(0x006A7110, this, a2);
}

bool hero_inode::crawl_can_go_to(string_hash a2, string_hash a3)
{
    TRACE("hero_inode::crawl_can_go_to");

    if constexpr (1) {
        auto *v3 = this->field_8;
        auto *the_als_inode = bit_cast<als_inode *>(v3->get_info_node(als_inode::default_id, true));
        auto v5 = (a2 == jump_state::default_id
                    || a2 == combat_state::default_id
                    || a2 == web_zip_state::default_id
                    || a2 == hit_react_state::default_id
                    || a2 == pick_up_state::default_id
                    || a2 == plr_loco_crawl_state::default_id);

        bool result = false;
        if ( a3 == plr_loco_crawl_state::default_id && v5 )
        {
            result = (v5 && the_als_inode->is_layer_interruptable(static_cast<als::layer_types>(0)));
        }

        return result;
    } else {
        return THISCALL(0x006A6340, this, a2, a3);
    }
}

void hero_inode::set_jump_type(eJumpType a2, bool a3) {
    this->field_54 = static_cast<eJumpType>(a3 ? 21 : this->field_50);
    this->field_50 = a2;
}

void hero_inode::cleanup_collision_lists() {
    if (this->field_80) // ai::hero_inode::cleanup_crawl_collision_list()
    {
        local_collision::destroy_primitive_list(&this->field_80);
    }

    if (this->field_84) // ai::hero_inode::cleanup_swing_collision_list()
    {
        local_collision::destroy_primitive_list(&this->field_84);
    }
}

hero_type_enum hero_inode::get_hero_type() {
    if constexpr (0) {
        //return (hero_type_enum) get_hero_type_helper();
    } else {
        return (hero_type_enum) CDECL_CALL(0x0068A050);
    }
}

bool hero_inode::crawl_is_eligible_internals(string_hash a2, bool a3) {
    return (bool) THISCALL(0x006A6900, this, a2, a3);
}

bool hero_inode::compute_curr_ground_plane(force_recompute_enum a2, Float a3)
{
    TRACE("hero_inode::compute_curr_ground_plane");

    return (bool) THISCALL(0x00698970, this, a2, a3);
}

Var<string_hash> bip01_pelvis{0x0095AAFC};

void shrink_capsule_for_slanted_surfaces(actor *act) {
    if constexpr (1) {
        assert(act->is_a_conglomerate());

        auto *v1 = act->get_ai_core();
        v1->create_capsule_alter();
        auto *capsule_alter = act->get_ai_core()->field_70;
        assert(capsule_alter != nullptr);

        capsule_alter->set_mode((capsule_alter_sys::eAlterMode) 3);

        conglomerate *conglm_ptr = CAST(conglm_ptr, act);
        auto *v3 = conglm_ptr->get_bone(bip01_pelvis(), true);
        capsule_alter->set_base_avg_node(1, v3, 1.0);
        capsule_alter->set_base_avg_node(2, nullptr, 0.0);

        auto *ctrl = act->m_player_controller;
        assert(ctrl != nullptr);

        if (ctrl->field_420 == 2) {
            capsule_alter->set_avg_radius(0.5);
        } else {
            capsule_alter->set_avg_radius(0.30000001);
        }

    } else {
        CDECL_CALL(0x0068A5F0, act);
    }
}

void extend_capsule_for_jump(actor *act) {
    assert(act->is_a_conglomerate());

    ai_core *v1 = act->get_ai_core();
    v1->create_capsule_alter();
    auto *capsule_alter = act->get_ai_core()->field_70;
    capsule_alter->set_mode((capsule_alter_sys::eAlterMode) 3);

    Var<string_hash> bip01_l_foot{0x0095A860};
    Var<string_hash> bip01_r_foot{0x0095B970};

    conglomerate *conglom_ptr = CAST(conglom_ptr, act);
    auto *v3 = conglom_ptr->get_bone(bip01_l_foot(), true);
    capsule_alter->set_base_avg_node(0, v3, 1.75);

    auto *v4 = conglom_ptr->get_bone(bip01_r_foot(), true);
    capsule_alter->set_base_avg_node(1, v4, 1.75);

    auto *v5 = conglom_ptr->get_bone(bip01_pelvis(), true);
    capsule_alter->set_base_avg_node(2, v5, 1.0);
    capsule_alter->set_base_avg_node(3, nullptr, 0.0);
}

} // namespace ai

bool have_relative_movement(entity *a1, entity *a2) {
    return (bool) CDECL_CALL(0x0069F9A0, a1, a2);
}

void hero_inode_patch() {
    {
        FUNC_ADDRESS(address, &ai::hero_inode::frame_advance);
        //set_vfunc(0x0087DAC0, address);
    }

    {
        FUNC_ADDRESS(address, &ai::hero_inode::run_is_eligible);
        SET_JUMP(0x006A7770, address);
    }

    {
        FUNC_ADDRESS(address, &ai::hero_inode::crawl_can_go_to);
        SET_JUMP(0x006A6340, address);
    }

    {
        FUNC_ADDRESS(address, &ai::hero_inode::engage_water_exit);
        REDIRECT(0x00478EAA, address);
    }

    {
        FUNC_ADDRESS(address, &ai::hero_inode::jump_can_go_to);
        SET_JUMP(0x006A6E70, address);
    }
}
