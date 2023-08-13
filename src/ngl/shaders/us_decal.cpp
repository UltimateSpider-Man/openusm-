#include "us_decal.h"

#include "trace.h"
#include "utility.h"
#include "ngl.h"

void US_Decal3DShader::_BindMaterial(nglMaterialBase *a1)
{
    TRACE("US_Decal3DShader::BindMaterial");
    
#ifdef TARGET_XBOX
    a1->field_64 = nglLoadTexture(*bit_cast<tlHashString *>(&a1->field_60));
#else
    a1->field_64 = nglLoadTexture(*bit_cast<tlFixedString *>(a1->field_60));
#endif
}

void US_Decal3DShader::_RebaseMaterial(nglMaterialBase *a1, unsigned int a2)
{
    TRACE("US_Decal3DShader::RebaseMaterial");

#ifndef TARGET_XBOX
    auto v2 = a1->field_60;
    if ( v2 != 0 )
    {
        a1->field_60 = a2 + v2;
    }
#endif
}

void us_decal_patch()
{
    {
        FUNC_ADDRESS(address, &US_Decal3DShader::_BindMaterial);
        set_vfunc(0x00870CA0, address);
    }

    {
        FUNC_ADDRESS(address, &US_Decal3DShader::_RebaseMaterial);
        set_vfunc(0x00870CA8, address);
    }
}
