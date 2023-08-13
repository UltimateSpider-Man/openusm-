#pragma once

#include "float.hpp"

#include <vector.hpp>

#include <cstdint>

struct marky_camera;
struct motion_control_system;
struct camera;
struct controller;

struct wds_camera_manager {
    _std::vector<motion_control_system *> field_0;
    _std::vector<controller *> field_10;
    camera *field_20;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    marky_camera *field_44;
    bool field_48;

    //0x0053DB80
    wds_camera_manager();

    //0x00542630
    int add_controller(controller *a2);

    //0x005426A0
    int add_mcs(motion_control_system *a2);

    //0x00530A70
    void advance_controllers(Float a2);

    //0x0054B8A0
    void setup_cameras();

    //0x00530A30
    void frame_advance(Float a2);

    //0x0050D480
    void usercam_frame_advance(Float a2);

    //0x0051EA10
    void scene_analyzer_frame_advance(Float a2);

    //0x0050D4C0
    void enable_marky_cam(bool a2, Float a3);
};
