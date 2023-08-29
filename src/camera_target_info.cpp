#include "camera_target_info.h"

#include "actor.h"
#include "ai_player_controller.h"
#include "ai_std_combat_target.h"
#include "ai_team.h"
#include "base_ai_core.h"
#include "collide.h"
#include "common.h"
#include "entity.h"
#include "func_wrapper.h"
#include "generic_anim_controller.h"
#include "oldmath_po.h"
#include "trace.h"
#include "utility.h"

VALIDATE_SIZE(camera_target_info, 0x5C);

static const float flt_881AC0 = 0.5;
static const float flt_882098 = 2.5;
static const float flt_87EA34 = 0.75;
static const float flt_8820A0 = 0.66000003;
static const float flt_881AB4 = 2.25;
static const float flt_87EEDC = 0.69999999;

static Var<float> flt_881ABC {0x00881ABC};

vector3d sub_48C000(vector3d a2, vector3d a5, float t)
{
    assert(t >= 0.0f && t <= 1.0f);

    vector3d result = a2 + (a5 - a2) * t;
    return result;
}

camera_target_info::camera_target_info(entity *target,
                                       Float a3,
                                       const vector3d &a4,
                                       const vector3d &a5)
{
    TRACE("camera_target_info::camera_target_info");

    assert(target != nullptr);
    assert(target->is_a_conglomerate());

    if constexpr (1)
    {
        this->field_54 = (actor *)target;
        auto v69 = this->field_54->get_abs_po();
        this->field_C = this->field_54->get_visual_center();
        auto *v8 = this->field_54->anim_ctrl;
        if ( v8 != nullptr )
        {
            this->field_C = v69.inverse_xform(this->field_C);

            v8->get_camera_root_abs_po(v69);
            this->field_C = v69.slow_xform(this->field_C);
        }

        this->pos = v69.get_position();

        this->facing = v69.get_z_facing();

        this->up = v69.get_y_facing();

        assert(facing.is_normal());

        assert(up.is_normal());

        auto v19 = this->field_54;
        auto *v20 = v19->m_player_controller;
        int v21 = 0;
        if ( v20 != nullptr )
        {
            v21 = v20->field_420;
        }

        switch (v21)
        {
            case 1:
                this->radius = 0.75;
                break;
            case 2:
                this->radius = 1.15;
                break;
            case 3:
                this->radius = 0.75;
                break;
            default: {
                auto v24 = v19->get_visual_radius() * flt_881AC0;
                if ( v24 >= flt_87EA34 )
                {
                    if ( v24 > flt_882098 )
                    {
                        v24 = flt_882098;
                    }

                    this->radius = v24;
                }
                else
                {
                    this->radius = flt_87EA34;
                }
            }
        }

        this->min_look_dist = (this->radius * flt_8820A0 + flt_881AC0) * flt_881AB4;
        auto v63 = this->min_look_dist * 2;
        this->field_20 = std::min(v63, flt_881ABC());

        auto v66 = this->pos;

        if ( this->get_loco_mode() == 8 )
        {
            this->up = YVEC;
            auto *v33 = this->field_54;
            if ( v33->m_player_controller != nullptr )
            {
                auto v64 = v33->m_player_controller->get_poleswing_anchor();
                if ( v64.is_valid() )
                {
                    auto v61 = v64.get_origin();
                    auto v34 = v64.get_target();
                    closest_point_segment(this->pos, v34, v61, this->pos);
                }
            }
        }
        else
        {
            auto v35 = this->radius * 0.69999999;
            this->pos += this->up * v35;
        }

        static Var<float> pronto_mix {0x00959E40};

        this->field_C += this->pos - v66;
        this->field_24 = ZEROVEC;
        if ( (8.0 * 8.0) > (this->pos - a4).length2() )
        {
            this->pos = sub_48C000(this->pos, a4, pronto_mix());
            if ( dot(this->up, a5) > -0.99000001 )
            {
                static Var<float> slow_mix {0x00959E4C};

                auto v51 = sub_48C000(
                  this->up,
                  a5,
                  slow_mix());
                this->up = v51.normalized();
            }

            if ( a3 != 0.0f )
            {
                auto v63 = 1.f / a3;
                this->field_24 = (this->pos - a4) * v63;
            }
        }

        if ( this->field_54->get_ai_core() != nullptr )
        {
            auto v62 = ai::combat_target_inode::team_hash();
            auto *v56 = this->field_54;
            auto *v58 = v56->get_ai_core();
            auto v59 = v58->field_50.get_pb_hash(v62);
            this->field_58 = ai::team::manager::get_team_enum_by_hash(v59);
        }
        else
        {
            this->field_58 = 0;
        }
    }
    else
    {
        THISCALL(0x004B3DC0, this, target, a3, &a4, &a5);
    }
}

void * __fastcall camera_target_info_constructor(void *self, int,
                                       entity *target,
                                       Float a3,
                                       const vector3d &a4,
                                       const vector3d &a5)
{
    return new (self) camera_target_info {target, a3, a4, a5};
}

int camera_target_info::get_loco_mode() const
{
    TRACE("camera_target_info::get_loco_mode");

    auto *v1 = this->field_54->m_player_controller;
    if (v1 != nullptr)
    {
        return 1;
    }

    if ( auto result = v1->get_spidey_loco_mode(); result >= 0)
    {
        return result;
    }

    return 1;
}

void camera_target_info_patch()
{
    REDIRECT(0x004B6415, &camera_target_info_constructor);
}
