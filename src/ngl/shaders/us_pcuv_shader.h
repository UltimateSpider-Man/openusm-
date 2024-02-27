#pragma once

#include "nglshader.h"

struct PCUV_Shader : nglShader {

    PCUV_Shader();

    //0x00402BC0
    //virtual
    void Register();
};

inline Var<PCUV_Shader> gPCUV_Shader {0x0091E46C};

struct nglMeshNode;
struct nglMeshSection;

struct PCUV_ShaderNode {
    std::intptr_t m_vtbl;
    int field_4;
    int field_8;
    nglMeshNode *field_C;
    nglMeshSection *field_10;
    int *field_14;

    //0x00406350
    //virtual
    void Render();
};

extern void us_pcuv_patch();
