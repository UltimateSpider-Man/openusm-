#pragma once

#include "nglshader.h"

#include <cstdint>

struct nglMeshSection;
struct nglMeshNode;
struct nglTexture;

struct USVariantShaderNode : nglShaderNode {
    int field_14;

    //0x0041BDA0
    USVariantShaderNode(nglMeshNode *a2, nglMeshSection *a3);

    /* virtual */ ~USVariantShaderNode() = default;

    nglTexture *sub_41BE30(nglTexture *a2);

    double sub_415D10();

    double sub_41DEA0();

    float sub_41DE40();
};

extern void USVariantShaderNode_patch();
