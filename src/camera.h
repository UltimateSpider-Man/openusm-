#pragma once

#include "actor.h"

struct vector3d;
struct string_hash;
struct entity;
struct mic;

struct camera : actor {
    mic *field_C0;
    float field_C4;
    float field_C8;

    //0x00577970
    camera(entity *a2, const string_hash &a3);

    float compute_xz_projected_fov();

    bool is_externally_controlled();

    //0x00577BE0
    void get_look_and_up(vector3d *a2, vector3d *a3);

    //0x0057EFD0
    //virtual
    void sync(camera &a2);

    /* virtual */ float get_fov();

    /* virtual */ float get_far_plane_factor();

    //0x00577AF0
    /* virtual */ void adjust_geometry_pipe(bool a2);
};

extern void camera_patch();
