#pragma once

#include "mstring.h"
#include "resource_key.h"
#include "vector3d.h"

#include <vector.hpp>

struct mission_camera_marker;
struct mission_camera_transform_marker;
struct mission_marker_base;
struct mission_transform_marker;
struct po;

struct mission_manager_script_data {
    mString field_0;
    int field_10;
    _std::vector<vector3d> pos;
    _std::vector<mString> strings;
    _std::vector<float> nums;
    _std::vector<mission_marker_base *> markers;
    _std::vector<mission_camera_marker *> camera_markers;
    _std::vector<mission_transform_marker *> transform_markers;
    _std::vector<mission_camera_transform_marker *> camera_transform_markers;
    mString field_84;
    po *field_94;
    vector3d field_98;
    resource_key field_A4;
    bool uses_script_stack;
    int field_B0;
    bool field_B4;
    bool field_B5;
    mString field_B8;
    mString field_C8;
    mString field_D8;

    //0x005E9760
    mission_manager_script_data();

    ~mission_manager_script_data();

    //0x005E98A0
    void copy(const mission_manager_script_data &a2);
};
