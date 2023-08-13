#pragma once

#include "matrix4x4.h"
#include "color32.h"

struct nglMesh;

struct PanelMeshSection {
    matrix4x4 field_0;
    nglMesh *field_40;
    float field_44;
    color32 field_48;
    bool field_4C;

    PanelMeshSection();

    //0x00607F20
    void SetMesh(nglMesh *);
};

extern void PanelMeshSection_patch();
