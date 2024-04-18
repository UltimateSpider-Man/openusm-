#include "mouselook_controller.h"

#include "camera.h"
#include "common.h"
#include "custom_math.h"
#include "dolly_and_strafe_mcs.h"
#include "func_wrapper.h"
#include "game.h"
#include "input_mgr.h"
#include "theta_and_psi_mcs.h"
#include "trace.h"
#include "variables.h"

VALIDATE_SIZE(mouselook_controller, 0x18u);

Var<mouselook_controller *> g_mouselook_controller{0x0095C17C};

mouselook_controller::mouselook_controller(
        dolly_and_strafe_mcs *a2,
        theta_and_psi_mcs *a3,
        camera *a4)
{
    this->field_8 = a2;
    this->m_vtbl = 0x00889114;
    this->field_C = a3;
    this->field_10 = a4;
    this->field_14 = input_mgr::instance()->field_58;
}

void mouselook_controller::reset()
{
    auto *v1 = this->field_C;
    if ( v1 != nullptr ) {
        v1->reset_angles();
    }
}

static string_hash entity_id_USER_CAM {int(to_hash("USER_CAM"))};

static vector3d cur_cam_target {};

static Var<float> g_move_mult {0x00921B6C};

static Var<float> g_strafe_mult {0x00921B70};

static Var<bool> lock_target_btn_pressed {0x00960B44};

static Var<bool> byte_960B45 {0x00960B45};

static Var<bool> byte_960B46 {0x00960B46};

static Var<bool> byte_921B60 {0x00921B60};

void mouselook_controller::_frame_advance(Float a2)
{
    TRACE("mouselook_controller::frame_advance");

    auto user_camera_enabled = g_game_ptr()->is_user_camera_enabled();
    g_game_ptr()->enable_user_camera(true);

    if constexpr (0)
    {
#if 0
        if ( !g_game_ptr()->is_user_camera_enabled() ) {
            return;
        }

        auto *v41 = this->field_10;
        auto *v4 = input_mgr::instance();
        if ( v41 == nullptr ) {
            v41 = entity_handle_manager::find_entity(entity_id_USER_CAM, entity_flavor_t::CAMERA, false);
        }

        float v29 = 10.0;
        if ( 1.0f == v4->get_control_state(26, (device_id_t)-1) ) {
            v29 = 100.0;
        }

        if ( 1.0f == v4->get_control_state(27, (device_id_t)-1) ) {
            v29 *= 0.2f;
        }

        float v36 = std::clamp(v29, 5.0f, 20.0f);

        v4->get_control_state(20, (device_id_t)-1);
        v4->get_control_state(21, (device_id_t)-1);

        auto control_state = v4->get_control_state(14, (device_id_t)-1);
        auto v5 = v4->get_control_state(17, (device_id_t)-1);
        float v30 = 0.0;
        auto v39 = -(std::abs(control_state) * control_state * g_move_mult());
        auto v33 = std::abs(v5) * v5 * g_strafe_mult();
        if ( 1.0f == v4->get_control_state(18, (device_id_t)-1) ) {
            v30 = 1.0;
        }

        if ( 1.0f == v4->get_control_state(19, (device_id_t)-1) ) {
            v30 = v30 - 1.0f;
        }

        if ( cam_target_locked() )
        {
            if ( 1.0f == v4->get_control_state(22, (device_id_t)-1) ) {
                v30 = v30 - 1.0f;
            }

            if ( 1.0f == v4->get_control_state(23, (device_id_t)-1) ) {
                v30 = v30 + 1.0f;
            }
        }

        if ( 0.0f == v4->get_control_state(31, (device_id_t)-1) )
        {
            if ( byte_960B46() ) {
                byte_921B60() = !byte_921B60();
            }

            byte_960B46() = false;
        }
        else
        {
            byte_960B46() = true;
        }

        if ( 0.0f == v4->get_control_state(32, (device_id_t)-1) )
        {
            if ( byte_960B45() ) {
                byte_921B60() = !byte_921B60();
            }

            byte_960B45() = false;
        }
        else if ( byte_960B45() )
        {
            byte_960B45() = true;
        }
        else
        {
            byte_921B60() = !byte_921B60();
        }

        float v6;
        float v31;
        if ( byte_921B60() )
        {
            v31 = -v4->get_control_delta(20, (device_id_t)-1);
            if ( byte_921B60() )
            {
                v6 = -v4->get_control_delta(21, (device_id_t)-1);
                goto LABEL_39;
            }
        }
        else
        {
            v31 = 0.0;
        }

        v6 = 0.0f;

        LABEL_39:
        auto v32 = 0.5f * v31;
        auto v34 = 0.5f * v6;
        if ( 1.0f == v4->get_control_state(22, (device_id_t)-1) ) {
            v32 += 1.0f;
        }

        if ( 1.0f == v4->get_control_state(23, (device_id_t)-1) ) {
            v32 = v32 - 1.0f;
        }

        if ( 1.0f == v4->get_control_state(24, (device_id_t)-1) )
        {
            if ( cam_target_locked() ) {
                v33 = 1.0;
            }

            v34 = v34 - 1.0f;
        }

        if ( 1.0f == v4->get_control_state(25, (device_id_t)-1) )
        {
            if ( cam_target_locked() ) {
                v33 = -1.0;
            }

            v34 += 1.0f;
        }

        if ( 1.0f == v4->get_control_state(14, (device_id_t)-1) ) {
            v39 = 1.0;
        }

        if ( 1.0f == v4->get_control_state(15, (device_id_t)-1) ) {
            v39 = -1.0;
        }

        if ( 1.0f == v4->get_control_state(17, (device_id_t)-1) )
        {
            v33 = -1.0;
            if ( !cam_target_locked() ) {
                v33 = 1.0;
            }
        }

        if ( 1.0f == v4->get_control_state(16, (device_id_t)-1) )
        {
            v33 = 1.0;
            if ( !cam_target_locked() ) {
                v33 = -1.0;
            }
        }

        auto v7 = v4->get_control_state(29, (device_id_t)-1);
        auto *v8 = g_debug_cam_target_actor();
        if ( 0.0f == v7 )
        {
            if ( lock_target_btn_pressed() )
            {
                if ( !cam_target_locked() )
                {
                    if ( g_debug_cam_target_actor() != nullptr )
                    {
                        cur_cam_target = g_debug_cam_target_actor()->get_abs_position();
                    }
                    else
                    {
                        cur_cam_target = vector3d {0.0, 0.0, 0.0};
                        g_debug_cam_get_next_target() = true;
                    }
                }

                this->reset();
                cam_target_locked() = !cam_target_locked();
            }

            lock_target_btn_pressed() = false;
        }
        else
        {
            lock_target_btn_pressed() = true;
        }

        if ( cam_target_locked() && v8 != nullptr )
        {
            auto abs_pos = v8->get_abs_position();
            if ( approx_equals(cur_cam_target, ZEROVEC, 0.0099999998f) ) {
                cur_cam_target = g_debug_cam_target_actor()->get_abs_position();
            }

            v17 = v54[1].arr[0] - cur_cam_target[0];
            v54[0].arr[0] = v17;
            v18 = v54[1].arr[1] - cur_cam_target[1];
            v54[0].arr[1] = v18;
            v19 = v54[1].arr[2] - cur_cam_target[2];
            v54[0].arr[2] = v19;

            cur_cam_target = abs_pos;

            this->reset();

            v22 = v54[0].arr[0] + v41->get_abs_position();
            my_abs_po += 12;
            v54[1].arr[0] = v22;
            v54[1].arr[1] = v54[0].arr[1] + my_abs_po[1];
            v54[1].arr[2] = v54[0].arr[2] + my_abs_po[2];
            v23 = v54[1].arr[0] - cur_cam_target[0];
            v54[1].arr[0] = v23;
            v24 = v54[1].arr[1] - cur_cam_target[1];
            v25 = v54[1].arr[2] - cur_cam_target[2];
            v43 = v25;
            auto v26 = std::sqrt(v54[1].arr[0] * v54[1].arr[0] + v25 * v25 + v24 * v24);
            if ( v26 > 10.0f ) {
                v26 = 10.0f;
            }

            static float kd_24596 = v26 * 0.02f;

            v54[0].arr[1] = 0.0;
            v35 = kd_24596 * v39 * v29 * a2;
            v40 = kd_24596 * v33 * v29 * a2 * flt_87EB80;
            v56 = kd_24596 * v30 * v29 * a2;
            v50 = v23;
            v52 = v24;
            v37 = sqrt(v43 * v43 + v50 * v50 + v52 * v52);
            v54[0].arr[0] = v25;
            v54[0].arr[2] = -v50;
            vector3d::normalize(v54);
            v54[1].arr[2] = v54[0].arr[2] * v40;
            v54[0].arr[0] = v54[0].arr[0] * v40 + v50;
            v54[0].arr[1] = v54[0].arr[1] * v40 + v52;
            v54[0].arr[2] = v54[1].arr[2] + v43;
            vector3d::normalize(v54);
            v54[0].arr[2] = v54[0].arr[2] * v37;
            v54[1].arr[0] = v54[0].arr[0] * v37 + cur_cam_target[0];
            v54[1].arr[1] = v54[0].arr[1] * v37 + cur_cam_target[1];
            v54[1].arr[2] = v54[0].arr[2] + cur_cam_target[2];
            v54[0] = v54[1];
            entity_base::set_abs_position(v41, v54);
            v41->look_at(cur_cam_target);
            if ( (v41->field_8 & 0x10000000) != 0 )
                entity_base::update_abs_po(v41, 1);

            v44 = v41->my_abs_po->m.arr[3].base.arr[0];
            v46 = v41->my_abs_po->m.arr[3].base.arr[1];
            v48 = v41->my_abs_po->m.arr[3].base.arr[2];
            if ( (v41->field_8 & 0x10000000) != 0 )
                entity_base::update_abs_po(v41, 1);

            v27 = v41->my_abs_po->m.arr[1].base.arr[0];
            v28 = v41->my_abs_po->m.arr[1].base.arr[2];
            v54[1].arr[1] = v41->my_abs_po->m.arr[1].base.arr[1];
            v54[1].arr[2] = v28;
            v54[1].arr[0] = v27;
            if ( v54[1].arr[1] > 0.1f
                || v46 > cur_cam_target[1] && v56 < 0.0f 
                || v46 < cur_cam_target[1] && v56 > 0.0f )
            {
                v55 = v54[1].arr[2] * v56;
                v54[1].arr[0] = v54[1].arr[0] * v56 + v44;
                v54[1].arr[1] = v54[1].arr[1] * v56 + v46;
                v54[1].arr[2] = v55 + v48;
                v54[0] = v54[1];
                entity_base::set_abs_position(v41, v54);
            }

            if ( (v41->field_8 & 0x10000000) != 0 )
                entity_base::update_abs_po(v41, 1);

            v45 = v41->my_abs_po->m.arr[3].base.arr[0];
            v47 = v41->my_abs_po->m.arr[3].base.arr[1];
            v49 = v41->my_abs_po->m.arr[3].base.arr[2];
            if ( (v41->field_8 & 0x10000000) != 0 )
                entity_base::update_abs_po(v41, 1);

            v51 = v41->my_abs_po->m.arr[2].base.arr[0];
            v53 = v41->my_abs_po->m.arr[2].base.arr[1];
            v55 = v41->my_abs_po->m.arr[2].base.arr[2] * v35;
            v54[1].arr[0] = v51 * v35 + v45;
            v54[1].arr[1] = v53 * v35 + v47;
            v54[1].arr[2] = v55 + v49;
            v54[0] = v54[1];
            if ( (v54 - cur_cam_target).length() > 0.30000001f ) {
                v41->set_abs_position(v54);
            }
        }
        else
        {
            if ( v8 == nullptr ) {
                g_debug_cam_get_next_target() = true;
            }

            this->field_C->field_18 = v32 * v36 * 0.0033333334f;
            this->field_C->field_14 = v34 * v36 * 0.0033333334f;
            this->field_8->field_C = v39 * v29 * a2;
            this->field_8->field_14 = v30 * v29 * a2;
            this->field_8->field_10 = v33 * v29 * a2;
        }
#endif
    }
    else
    {
        THISCALL(0x00528BB0, this, a2);
    }

    g_game_ptr()->enable_user_camera(user_camera_enabled);
}

bool mouselook_controller::_is_mouselook_controller() const {
    return true;
}

void mouselook_controller_patch()
{
    {
        FUNC_ADDRESS(address, &mouselook_controller::_frame_advance);
        set_vfunc(0x00889118, address);
    }
}
