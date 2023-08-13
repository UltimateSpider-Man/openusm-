#pragma once

#include "anchor_storage_class.h"
#include "float.hpp"
#include "game_axis.h"
#include "game_button.h"
#include "vector3d.h"

#include <cstdint>

struct actor;
struct conglomerate;

struct ai_player_controller {
    std::intptr_t m_vtbl = 0x0;

    conglomerate *field_4[2];
    int field_C;
    int field_10;
    int field_14;
    game_button gb_jump;
    game_button field_4C;
    game_button gb_attack;
    game_button gb_attack_secondary;
    game_button gb_grab;
    game_button gb_range;
    game_button field_150;
    game_button gb_camera_center;
    game_button field_1B8;
    game_button gb_swing;
    game_button field_220;
    game_button field_254;
    game_button field_288;

    game_axis field_2BC[6];
    bool field_3DC;
    bool field_3DD;
    vector3d field_3E0;
    vector3d field_3EC;
    int field_3F8[10];
    int field_420;

    //0x004728D0
    ai_player_controller(actor *a2);

    //0x00449A90
    anchor_storage_class get_poleswing_anchor() const;
    //0x00449940
    int get_spidey_loco_mode() const;

    //0x004696A0
    void set_player_num(int a2);

    //0x00468FE0
    void remap_controls();

    //0x00449AD0
    game_button *get_gb_jump();

    //0x00449B10
    game_button *get_gb_attack();

    //0x00449B20
    game_button *get_gb_attack_secondary();

    //0x00449AF0
    game_button *get_gb_grab();

    //0x00449B00
    game_button *get_gb_range();

    //0x00449B30
    game_button *get_gb_camera_center();

    //0x00449B50
    game_button *get_gb_swing_raw();

    //0x00468E80
    void frame_advance(Float a2);

    //0x004495D0
    vector3d compute_left_stick_from_camera();

    //0x00457C20
    vector3d convert_left_stick_from_camera_space_to_world_space(bool a3);

    //0x00457930
    //virtual
    void update_controls(Float a2, bool a3);

    //virtual
    float get_motion_force();
};
