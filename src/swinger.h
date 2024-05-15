#pragma once

#include "pendulum.h"
#include "vector3d.h"

struct entity;
struct polytube;
struct ai_tentacle_web_curly;

struct swinger_t {
    pendulum field_0;

    float field_38;
    entity *field_3C;
    vector3d field_40;
    float field_4C;
    float field_50;
    vector3d m_visual_point;
    vector3d field_60;

    int field_6C[8];

    int field_8C;
    polytube *field_90;
    polytube *field_94;
    ai_tentacle_web_curly *field_98;
};
