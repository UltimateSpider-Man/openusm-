#include "pcuv_shadermaterial.h"

#include "common.h"
#include "us_pcuv_shader.h"
#include "variable.h"

VALIDATE_SIZE(PCUV_ShaderMaterial, 0x30u);

PCUV_ShaderMaterial::PCUV_ShaderMaterial()
{
    this->field_1C = nullptr;
    this->field_20 = nullptr;
    this->field_24 = static_cast<nglBlendModeType>(0);
    this->field_28 = 2;
    this->field_2C = 0;
    this->field_8 = &gPCUV_Shader();
}

PCUV_ShaderMaterial::PCUV_ShaderMaterial(nglTexture *a2, nglBlendModeType a3, int a4, int a5)
{
    this->field_20 = a2;
    this->field_24 = a3;

    this->field_28 = a5;
    this->field_2C = a4;
    this->field_8 = &gPCUV_Shader();
}
