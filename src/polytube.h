#pragma once

#include "entity.h"

#include "spline.h"

#include <cstdint>

struct string_hash;
struct PCUV_ShaderMaterial;

struct polytube_pt_anim {
    float field_0[11];
};

struct polytube : entity {
    polytube *field_68;
    polytube *field_6C;
    void **field_70;
    void **field_74;

    char field_78;
    char field_79;
    char field_7A;
    char field_7B;
    int field_7C;
    spline the_spline;
    PCUV_ShaderMaterial *field_D0;
    PCUV_ShaderMaterial *field_D4;
    PCUV_ShaderMaterial *field_D8;
    int field_DC;
    int field_E0;
    int field_E4;
    int field_E8;
    int field_EC;
    float tube_radius;
    int num_sides;
    float tiles_per_meter;
    float max_length;
    float field_100;
    float field_104;
    int field_108;
    _std::vector<polytube_pt_anim> pt_anims;
    int field_11C;
    int field_120;
    float field_124;
    int field_128;
    int field_12C;
    int field_130;
    int empty[3];
    int16_t field_140;
    char field_142;
    char field_143;
    int field_144;
    int field_148;
    int field_14C;
    int field_150;
    int field_154;
    int field_158;
    int field_15C[7];

    //0x005A57A0
    polytube(const string_hash &a2, uint32_t a3);

    void rebuild_helper();

    //0x0048F090
    void set_abs_control_pt(int index, const vector3d &a3);

    void set_max_length(Float a2);

    void set_control_pt(int index, const vector3d &a2);

    vector3d get_control_pt(int a3);

    int get_num_control_pts();

    void build(int a1, spline::eSplineType a2);

    //0x005A3960
    void init();

    //0x00B96220
    void init_offsets();

    //0x005A2390
    void set_material(string_hash a2);

    //0x005A5B10
    //virtual
    void _render(Float a2);

    //0x0059B490
    static void frame_advance_all_polytubes(Float a1);
};

extern void polytube_patch();
