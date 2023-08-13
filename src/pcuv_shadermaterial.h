#pragma once

#include "ngl.h"

struct tlFixedString;

struct PCUV_ShaderMaterial {
    std::intptr_t m_vtbl;
    nglMeshSection *field_4;
    int field_8;
    int empty[4];
    tlFixedString *field_1C;
    nglTexture *field_20;
    nglBlendModeType field_24;
    int field_28;
    int field_2C;

    //0x00402B30
    PCUV_ShaderMaterial(nglTexture *a2, nglBlendModeType a3, int a4, int a5);
};
