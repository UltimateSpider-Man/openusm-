#pragma once

#include "nglshader.h"

#include "variable.h"

#include <cstdint>

struct nglEmptyShader : nglShader {
    nglEmptyShader();
};

extern Var<nglEmptyShader> gEmptyShader;
