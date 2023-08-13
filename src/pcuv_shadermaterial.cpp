#include "pcuv_shadermaterial.h"

#include "common.h"
#include "variable.h"

VALIDATE_SIZE(PCUV_ShaderMaterial, 48u);

PCUV_ShaderMaterial::PCUV_ShaderMaterial(nglTexture *a2, nglBlendModeType a3, int a4, int a5) {
    static Var<int> gPCUV_Shader = (0x0091E46C);

    this->m_vtbl = 0x00870AD4;
    this->field_20 = a2;
    this->field_24 = a3;

    this->field_28 = a5;
    this->field_2C = a4;
    this->field_8 = (int) &gPCUV_Shader();
}
