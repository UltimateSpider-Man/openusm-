#pragma once

#include "ngl.h"

struct tlFixedString;

struct USExteriorMaterial : nglMaterialBase {
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    tlFixedString *field_60;
    nglTexture *field_64;
    bool field_68;
    float field_6C[3];
    int field_78;
    float field_7C;
    int field_80;
    float field_84;
};
