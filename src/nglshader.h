#pragma once

#include "nglrendernode.h"

#include <variable.h>

#include <cstdint>

struct nglMeshNode;
struct nglMeshSection;
struct nglMaterialBase;
struct tlFixedString;

struct nglShader {
    std::intptr_t m_vtbl;
    nglShader *field_4;
    int field_8;

    nglShader();

    void Register();

    /* virtual */ tlFixedString GetName();

    /* virtual */ void BindMaterial(nglMaterialBase *mat);

    /* virtual */ void ReleaseMaterial(nglMaterialBase *mat);

    /* virtual */ void RebaseMaterial(nglMaterialBase *mat, unsigned int a2);

    /* virtual */ bool CheckMaterialVersion(nglMaterialBase *mat);

    /* virtual */ bool CheckVertexDefVersion(nglMeshSection *Section);

    /* virtual */ void BindSection(nglMeshSection *Section);

    /* virtual */ bool IsSwitchable();

    static Var<int> NextID;
};

struct nglShaderNode : nglRenderNode {
    nglMeshNode *field_C;
    nglMeshSection *field_10;

    void sub_413AF0();

    void Render();
};

extern float *sub_413F80(float *a1, int a2, uint32_t *a3, uint32_t a4);
