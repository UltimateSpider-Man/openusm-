#pragma once

#include "color32.h"
#include "entity_base_vhandle.h"
#include "vector2d.h"
#include "vector3d.h"

struct mString;

struct motion_effect_struct {
    int field_0[11];
    char field_2C;

    //0x004DC560
    motion_effect_struct(entity_base_vhandle a2, const mString &a3);

    ~motion_effect_struct();

    //0x004DC820
    void render_trail(vector3d a1,
                      vector3d a4,
                      vector3d a7,
                      vector2d a10,
                      vector2d a12,
                      vector2d a14,
                      color32 a16,
                      color32 a17,
                      color32 a18,
                      bool a19,
                      vector3d a20,
                      vector3d a23);

    //0x004EFA50
    static void record_all_motion_fx(Float a1);
};
