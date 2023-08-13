#pragma once

#include "physical_interface.h"
#include "rb_ragdoll_model.h"

struct conglomerate;

struct biped_system {
    rb_ragdoll_model field_0;
    int field_1564[755];
    int field_2130;
    float field_2134;
    float field_2138;

    biped_system();

    //0x005A2260
    void create_bps(conglomerate *a2, int a3, physical_interface::biped_physics_body_types arg4a);

    //0x005A0CB0
    void setup_physics(conglomerate *a2, physical_interface::biped_physics_body_types arg4);

    void prolog_frame_advance(Float a2);
};
