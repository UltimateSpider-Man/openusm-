#pragma once

#include "variable.h"

//0x0077D060
extern void nglVif1RenderScene();

struct nglScene;

//0x0077CBB0
extern void nglVif1SetupScene(nglScene *a1);

extern Var<int> nglFrameVBlankCount;
