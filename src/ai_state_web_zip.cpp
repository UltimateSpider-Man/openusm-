#include "ai_state_web_zip.h"

#include "actor.h"
#include "ai_player_controller.h"
#include "ai_state_jump.h"
#include "ai_state_run.h"
#include "ai_state_swing.h"
#include "ai_std_hero.h"
#include "als_inode.h"
#include "base_ai_core.h"
#include "base_state.h"
#include "common.h"
#include "conglom.h"
#include "controller_inode.h"
#include "event.h"
#include "from_mash_in_place_constructor.h"
#include "func_wrapper.h"
#include "glass_house_manager.h"
#include "hit_react_state.h"
#include "oldmath_po.h"
#include "physics_inode.h"
#include "polytube.h"
#include "state_machine.h"
#include "utility.h"
#include "vector2d.h"
#include "wds.h"

#include <cassert>

namespace ai {

VALIDATE_SIZE(web_zip_state, 0x40);

VALIDATE_SIZE(web_zip_inode, 0xE0);

web_zip_state::web_zip_state(from_mash_in_place_constructor *a2) {
    THISCALL(0x0044C560, this, a2);
}

state_trans_messages web_zip_state::frame_advance(Float a2)
{
    if constexpr (1) {
        auto *v2 = this->field_3C->field_3C;
        this->get_actor()->m_player_controller->set_spidey_loco_mode(static_cast<eHeroLocoMode>(9));
        v2->process_zip(a2);
        return TRANS_TOTAL_MSGS;
    } else {
        return static_cast<state_trans_messages>(THISCALL(0x0047DEF0, this, a2));
    }
}

void web_zip_state::deactivate(const mashed_state *a1) {
    THISCALL(0x0044C6E0, this, a1);
}

web_zip_inode::web_zip_inode(from_mash_in_place_constructor *a2) {
    THISCALL(0x004815D0, this, a2);
}

uint32_t web_zip_inode::get_virtual_type_enum() {
    return 326;
}

int web_zip_inode::activate(ai_core *a2) {
    sp_log("web_zip_inode::activate:");

    return THISCALL(0x00481A50, this, a2);
}

bool web_zip_inode::can_go_to(string_hash a2)
{
    TRACE("web_zip_inode::can_go_to");

    if constexpr (1) {
        if ( a2 == hit_react_state::default_id ) {
            return false;
        }

        auto *v3 = this->field_DC;
        auto *v4 = v3->field_20;
        auto zip_type = this->m_zip_type;

        switch (zip_type) {
        case 0: {
            if ( hero_inode::is_a_crawl_state(a2, true)
                    || a2 == run_state::default_id)
            {
                return false;
            }

            auto *als_layer = v4->get_als_layer(static_cast<als::layer_types>(0));
            return als_layer->get_time_to_signal(event::ANIM_ACTION) < 0.0f;
        }
        case 1: {
            auto *phys_inode_ptr = v3->field_28;
            auto floor_offset = this->field_C->get_floor_offset();
            auto v23 = floor_offset * this->field_1C.hit_norm + this->field_1C.hit_pos;

            auto v14 = phys_inode_ptr->get_abs_position() - v23;
            auto len = v14.length();
            auto v16 = this->field_1C.hit_norm.y > 0.5f;
            if ( hero_inode::is_a_crawl_state(a2, true) ) {
                return !v16 && len < 1.3f;
            } else if (a2 == ai::run_state::default_id) {
                return v16 && this->field_C->physical_ifc()->get_floor_offset() + 0.1f > len;
            } else {
                return false;
            }
            break;
        }
        case 2: {
            if (hero_inode::is_a_crawl_state(a2, true)
                && a2 == ai::run_state::default_id )
            {
                return false;
            }

            auto *v18 = v4->get_als_layer(static_cast<als::layer_types>(0));
            auto v29 = v18->get_time_to_signal(event::ANIM_ACTION);
            return !hero_inode::is_a_crawl_state(a2, true) && v29 < 0.0f;
        }
        default: {
            assert(0 && "Unknown zip type!");
        }
        }

        return false;
    } else {
        return THISCALL(0x0044C930, this, a2);
    }
}

static Var<string_hash> loco_allow_web_zip_id{0x00958E64};

bool web_zip_inode::is_eligible(string_hash a2)
{
    TRACE("web_zip_inode::is_eligible", a2.to_string());

    if constexpr (0)
    {
        auto *v3 = &this->field_8->field_50;

        if (v3->get_pb_int(loco_allow_web_zip_id()) == 0) {
            return false;
        }

        game_button v10 = this->field_DC->field_24->get_button(
            static_cast<controller_inode::eControllerButton>(13));

        bool v5 = v10.is_triggered();
        //sp_log("%d", v5);

        if (!v5) {
            return false;
        }

        bool result;

        if (a2 == run_state::default_id)
        {
            this->m_zip_type = 0;
            result = this->find_zip_anchor_and_transition_to_zip_jump({0});
        }
        else if (a2 == jump_state::default_id)
        {
            this->m_zip_type = 2;
            result = this->find_zip_anchor_and_transition_to_zip_jump({0});
        }
        else if (hero_inode::is_a_crawl_state(a2, true))
        {
            this->m_zip_type = 1;
            result = this->find_zip_anchor_from_crawl();
        }
        else
        {
            auto str = a2.to_string();
            sp_log("Trying to switch to web_zip from invalid state: %s", str);
            assert(0);

            result = true;
        }

        return result;
    }
    else
    {
        bool (__fastcall *func)(const void *, void *edx, string_hash a2) = CAST(func, 0x0046C280);
        return func(this, nullptr, a2);
    }
}

bool web_zip_inode::find_zip_anchor_from_crawl() {
    return THISCALL(0x0045D600, this);
}

bool web_zip_inode::find_zip_anchor_and_transition_to_zip_jump(web_zip_inode::eZipReattachMode a2)
{
    if constexpr (0)
    {}
    else
    {
        return THISCALL(0x0045DFD0, this, a2);
    }
}

bool web_zip_inode::correct_zip_target_pos(line_info *si)
{
    TRACE("web_zip_inode::correct_zip_target_pos");

    auto result = THISCALL(0x0044CBD0, this, si);

    if (result) {
        assert(glass_house_manager::is_point_in_glass_house(si->hit_pos));
    }

    return result;
}

int web_zip_inode::deactivate() {
    return THISCALL(0x0044C880, this);
}

void web_zip_inode::unmash(mash_info_struct *a2, void *a3) {
    THISCALL(0x00474010, this, a2, a3);
}

void web_zip_inode::process_zip(Float a2)
{
    if constexpr (1)
    {
        auto *v3 = this->field_DC->field_28;

        static Var<string_hash> has_tentacle_zip_id{0x009591A4};

        auto *v4 = &this->field_8->field_50;

        if (!v4->get_pb_int(has_tentacle_zip_id()))
        {
            if (this->field_7C == 0)
            {
                auto *v5 = this->field_C;

                if (v5->event_raised_last_frame(event::ANIM_ACTION)) {
                    auto *v6 = this->field_C;

                    entity_set_abs_po(this->field_D8, v6->get_abs_po());

                    actor *hero_ptr = bit_cast<actor *>(g_world_ptr()->get_hero_ptr(0));

                    auto v7 = hero_ptr->get_player_controller()->m_hero_type;
                    if (v7 == 1 || v7 == 3) {
                        swing_inode::do_web_splat(this->field_1C.hit_pos,
                                                  this->field_1C.hit_norm,
                                                  *local_collision::entfilter_entity_no_capsules());
                    }

                    this->field_7C = 1;
                }
            }

            if (this->field_7C == 1) {
                static Var<string_hash> bip01_r_hand{0x0095AA3C};

                auto *bone = bit_cast<conglomerate *>(this->field_C)->get_bone(bip01_r_hand(), true);

                vector3d a3 = bone->get_abs_position();

                auto *v10 = this->field_C;
                a3 = v10->get_abs_po().inverse_xform(a3);

                vector3d v13 = this->field_C->get_render_scale();
                a3[0] = a3[0] * v13.x;

                vector3d v15 = this->field_C->get_render_scale();
                a3[1] = a3[1] * v15.y;

                vector3d v17 = this->field_C->get_render_scale();
                a3[2] = a3[2] * v17.z;

                auto *v18 = this->field_C;

                a3 = v18->get_abs_po().slow_xform(a3);

                auto *v21 = this->field_D8;
                v21->set_abs_control_pt(0, a3);

                auto *v22 = this->field_D8;
                v22->set_abs_control_pt(v22->get_num_control_pts() - 1, this->field_1C.hit_pos);

                auto *v24 = this->field_D8;

                if (v24->the_spline.need_rebuild) {
                    v24->the_spline.rebuild_helper();
                }

                this->field_D8->unforce_regions();
                this->field_D8->force_regions(this->field_C);
                this->field_D8->set_visible(true, false);
            }
        }

        auto a2a = v3->get_velocity();

        vector2d tmp = {a2a.x, a2a.z};

        auto xz_velocity = tmp.length();

        static constexpr auto cap_34991 = 30.f;

        if (xz_velocity > cap_34991) {
            auto v28 = cap_34991 / xz_velocity;
            a2a[0] *= v28;
            a2a[2] *= v28;
            v3->set_velocity(a2a, false);
        }

    } else {
        THISCALL(0x00478A80, this, a2);
    }
}

void web_zip_inode::add_swingback(polytube *&a2, entity_base *a3, actor *a4)
{
    this->field_A4[this->field_D4].init(a2, a4, a3);
    ++this->field_D4;
    if ( this->field_D4 >= 3 ) {
        this->field_D4 = 0;
    }
}

} // namespace ai

void web_zip_state_patch()
{
    {
        FUNC_ADDRESS(address, &ai::web_zip_inode::is_eligible);
        REDIRECT(0x0048899E, address);
        REDIRECT(0x00488CBF, address);
        REDIRECT(0x00488F54, address);
    }

    return;
    {
        FUNC_ADDRESS(address, &ai::web_zip_state::frame_advance);
        //set_vfunc(0x008775D0, address);
    }

    {
        FUNC_ADDRESS(address, &ai::web_zip_inode::can_go_to);
        SET_JUMP(0x0044C930, address);
    }

    {
        FUNC_ADDRESS(address, &ai::web_zip_inode::process_zip);
        REDIRECT(0x0047DF1B, address);
    }

    {
        FUNC_ADDRESS(address, &ai::web_zip_inode::activate);
        //set_vfunc(0x0087DB84, address);
    }

    //process_zip
    {
        {
            FUNC_ADDRESS(address, &conglomerate::get_bone);
            REDIRECT(0x00478B80, address);
        }

        {
            FUNC_ADDRESS(address, &entity_base::event_raised_last_frame);
            REDIRECT(0x00478AD0, address);
        }
    }

}
