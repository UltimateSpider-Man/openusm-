#pragma once

#include "game_camera.h"

#include "game_button.h"

struct camera_mode;

struct spiderman_camera : game_camera {

    camera_mode *field_1A0;
    vector3d field_1A4;
    vector3d field_1B0;
    bool field_1BC;
    int field_1C0;
    int field_1C4;
    int field_1C8;
    bool field_1CC;
    game_button field_1D0;

    //0x004B78E0
    spiderman_camera(const string_hash &a2, entity *a3);

    void * operator new(size_t size);

    void operator delete(void *ptr);

    //0x004B6480
    /* virtual */ void adjust_geometry_pipe(bool a1);

    void autocorrect(Float a2);

    /* virtual */ void _autocorrect(Float a2);

    /* virtual */ void set_target_entity(entity *a1);
};

extern Var<spiderman_camera *> g_spiderman_camera_ptr;

extern void spiderman_camera_patch();
