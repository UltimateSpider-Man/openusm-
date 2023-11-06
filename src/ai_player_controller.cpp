#include "ai_player_controller.h"

#include "actor.h"
#include "base_ai_core.h"
#include "camera.h"
#include "common.h"
#include "conglom.h"
#include "func_wrapper.h"
#include "game.h"
#include "pole_swing_inode.h"

#include <vtbl.h>

VALIDATE_SIZE(ai_player_controller, 0x424u);

ai_player_controller::ai_player_controller(actor *a2) {
    THISCALL(0x004728D0, this, a2);
}

anchor_storage_class ai_player_controller::get_poleswing_anchor() const
{
    auto *v2 = this->field_4[1]->get_ai_core();
    auto *v3 = (ai::pole_swing_inode *) v2->get_info_node(ai::pole_swing_inode::default_id(), true);

    auto a2 = v3->field_1C;
    return a2;
}

int ai_player_controller::get_spidey_loco_mode() const
{
    return this->field_C;
}

void ai_player_controller::set_player_num(int a2) {
    this->field_14 = a2;
    this->remap_controls();
}

void ai_player_controller::remap_controls() {
    THISCALL(0x00468FE0, this);
}

game_button *ai_player_controller::get_gb_jump() {
    return &this->gb_jump;
}

game_button *ai_player_controller::get_gb_attack() {
    return &this->gb_attack;
}

game_button *ai_player_controller::get_gb_attack_secondary() {
    return &this->gb_attack_secondary;
}

game_button *ai_player_controller::get_gb_grab() {
    return &this->gb_grab;
}

game_button *ai_player_controller::get_gb_range() {
    return &this->gb_range;
}

game_button *ai_player_controller::get_gb_camera_center() {
    return &this->gb_camera_center;
}

game_button *ai_player_controller::get_gb_swing_raw() {
    return &this->gb_swing;
}

vector3d ai_player_controller::convert_left_stick_from_camera_space_to_world_space(bool a3) {
    vector3d result;
    THISCALL(0x00457C20, this, &result, a3);

    return result;
}

vector3d ai_player_controller::compute_left_stick_from_camera() {
    vector3d result;

    if constexpr (1) {
        auto *cam = g_game_ptr()->get_current_view_camera(0);
        if (cam != nullptr) {
            auto v8 = this->field_2BC[1].field_10;
            auto v7 = this->field_2BC[0].field_10;

            vector3d look, up;
            cam->get_look_and_up(&look, &up);

            vector3d v11 = vector3d::cross(up, look);

            look[1] = 0.0;
            look.normalize();

            v11[1] = 0.0;
            v11.normalize();
            if (std::abs(v8) < 0.1f) {
                v8 = 0.0;
            }

            if (std::abs(v7) < 0.1f) {
                v7 = 0.0;
            }

            v11 = v11 * v8 - look * v7;
            v11.normalize();

            result = v11;
        } else {
            result = ZEROVEC;
        }

        return result;

    } else {
        THISCALL(0x004495D0, this, &result);

        return result;
    }
}

void ai_player_controller::update_controls(Float a2, bool a3) {
    if (a3 || (this->field_3DC && this->field_C != 14)) {
        this->gb_jump.update(a2);
        this->field_4C.update(a2);
        this->gb_attack.update(a2);
        this->gb_attack_secondary.update(a2);
        this->gb_grab.update(a2);
        this->gb_range.update(a2);
        this->field_150.update(a2);
        this->field_254.update(a2);
        this->field_288.update(a2);
        this->gb_camera_center.update(a2);
        this->field_1B8.update(a2);
        this->gb_swing.update(a2);

        this->field_2BC[0].update(a2);
        this->field_2BC[1].update(a2);
        this->field_2BC[2].update(a2);
        this->field_2BC[3].update(a2);
        this->field_2BC[4].update(a2);
        this->field_2BC[5].update(a2);
    }

    this->field_220.update(a2);
}

void ai_player_controller::frame_advance(Float a2) {
    if (this->field_4[0] == nullptr) {
        this->field_4[0] = CAST(this->field_4[0], g_game_ptr()->current_game_camera);
    }

    this->update_controls(a2, false);

    this->field_3E0 = this->convert_left_stick_from_camera_space_to_world_space(false);

    this->field_3EC = this->compute_left_stick_from_camera();
}

float ai_player_controller::get_motion_force() {
    float __fastcall (*func)(void *self) = CAST(func, 0x00449880);

    return func(this);
}

void ai_player_controller_patch()
{
    {
        FUNC_ADDRESS(address, &ai_player_controller::frame_advance);
        SET_JUMP(0x00468E80, address);
    }
}
