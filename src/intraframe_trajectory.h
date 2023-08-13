#pragma once

#include "capsule.h"
#include "oldmath_po.h"

struct sphere;
struct actor;
struct dynamic_conglomerate_clone;
struct fixed_pool;
struct collision_capsule;
struct collision_geometry;

struct intraframe_trajectory_t {
    po world_po0;
    po world_po1;
    po final_po;
    capsule my_abs_cap0;
    capsule my_abs_cap1;
    capsule relcap0;
    capsule relcap1;
    capsule *final_relcap;
    bool is_capsule;
    actor *ent;
    dynamic_conglomerate_clone *field_13C;
    vector3d field_140;
    float field_14C;
    float field_150;
    float field_154;
    float field_158;
    intraframe_trajectory_t *field_15C;
    int field_160;
    bool field_164;
    bool field_165;

    struct iterator {
        intraframe_trajectory_t *trj;
        iterator *field_4;
    };

    iterator *field_168;

    intraframe_trajectory_t();

    //0x0051BFF0
    [[nodiscard]] capsule get_abs_cap0();

    //0x0051C010
    [[nodiscard]] capsule get_abs_cap1();

    //0x005282A0
    [[nodiscard]] sphere get_bounding_sphere();

    collision_capsule &get_capsule();

    collision_geometry *get_colgeom();

    static inline Var<fixed_pool> pool{0x0092244C};
};
