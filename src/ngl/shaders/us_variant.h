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

    nglTexture *ResolveIFL(nglTexture *a2);

    double sub_415D10();

    double sub_41DEA0() const;

    float GetDistanceScale() const;
};

extern void USVariantShaderNode_patch();
