#pragma once

#include "float.hpp"
#include "vector3d.h"

struct actor;
struct resource_key;

struct damage_interface {
    char field_0[0x1FC];

    vector3d field_1FC;
    float field_208;

    int field_20C[12];

    damage_interface();

    //0x004DE8A0
    damage_interface(actor *a2);

    /* virtual */ bool get_ifc_num(const resource_key &att, float *a3, bool is_log);

    /* virtual */ bool set_ifc_num(const resource_key &att, Float a3, bool is_log);

    //0x004D1990
    static void frame_advance_all_damage_ifc(Float a1);
};
