#pragma once

#include "us_pcuv_shader.h"

struct nglTexture;

struct PolytubeCustomMaterial : PCUV_ShaderMaterial {
    PolytubeCustomMaterial(nglTexture *a2, nglBlendModeType a3, int a4, int a5);
};
