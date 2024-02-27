#pragma once

#include "ngl.h"

struct tlFixedString;
struct PCUV_Shader; 

struct PCUV_ShaderMaterial {
    std::intptr_t m_vtbl {0x00870AD4};
    nglMeshSection *field_4;
    PCUV_Shader *field_8;
    int empty[4];
    tlFixedString *field_1C;
    nglTexture *field_20;
    nglBlendModeType field_24;
    int field_28;
    int field_2C;

    //0x00402B00
    PCUV_ShaderMaterial();

    //0x00402B30
    PCUV_ShaderMaterial(nglTexture *a2, nglBlendModeType a3, int a4, int a5);
};
