#pragma once

#include "animation_controller.h"

#include "als_meta_anim_table_shared.h"
#include "nal_system.h"
#include "usm_anim_player.h"

struct actor;
struct nalBaseSkeleton;
struct po;

namespace als {
struct als_meta_anim_table_shared;
}

struct nal_anim_controller : animation_controller {
    struct scene_anim_client {
        //0x00492890
        //virtual
        nalAnimClass<nalAnyPose>::nalInstanceClass *CreateInstance(nalAnimClass<nalAnyPose> *a2);

        //0x0049C090
        //virtual
        int Advance(
            nalAnimClass<nalAnyPose>::nalInstanceClass *a2, float a3, float a4, float a5, float a6);
    };

    struct std_play_method {
        void *CreateInstance(
            nalAnimClass<nalAnyPose> *a1,
            nalBaseSkeleton *a2,
            void *pParameter);
    };

    int field_10;
    usm_anim_player<nalAnimClass<nalAnyPose>, 3> my_player;
    nalAnyPose field_40;
    scene_anim_client *field_44;
    int field_48;
    int field_4C;
    bool field_50;

    //0x0049BCF0
    nal_anim_controller(actor *a2,
                        nalBaseSkeleton *a3,
                        unsigned int a4,
                        const als::als_meta_anim_table_shared *a5);


    //virtual
    void *get_base_layer_anim_ptr();

    void get_curr_po_offset(po &a2);

    //virtual
    bool scene_animation_playing() const;

    //virtual
    bool is_anim_active(Float a1);

    double _get_base_anim_time_in_sec() const;

    //virtual
    //0x0049BE60
    double get_anim_time_in_sec(Float a2);

    //virtual
    double get_total_base_anim_time_in_sec() const;

    //virtual
    double _get_base_anim_speed();

    //virtual
    void _set_base_anim_time_in_sec(Float a2);

    //virtual
    double _get_anim_speed(Float );

    //virtual
    void _set_base_anim_speed(Float speed);

    //virtual
    void _frame_advance(Float a2, bool a3, bool a4);

    void get_matrix_data_from_pose(nalAnyPose &arg0);
};

extern void nal_anim_controller_patch();
