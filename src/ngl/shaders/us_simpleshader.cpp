#include "us_simpleshader.h"

#include "ngl.h"
#include "trace.h"
#include "utility.h"
#include "us_interior.h"

namespace USSimpleShaderSpace
{
    template<>
    void USSimpleShader<USInteriorMaterial>::_BindMaterial(nglMaterialBase *a1)
    {
        TRACE("USSimpleShader<USInteriorMaterial>::BindMaterial");

#ifdef TARGET_XBOX
        a1->field_20 = nglLoadTexture(*bit_cast<tlHashString *>(&a1->field_1C));
#else
        a1->field_20 = nglLoadTexture(*bit_cast<tlFixedString *>(a1->field_1C));
#endif
    }

    template<>
    void USSimpleShader<USInteriorMaterial>::_RebaseMaterial(nglMaterialBase *a1, unsigned int a2)
    {
        TRACE("USSimpleShader<USInteriorMaterial>::RebaseMaterial");

        auto *v2 = a1->field_1C;
        if ( v2 != nullptr )
        {
            a1->field_1C = (nglTexture *)((char *)v2 + a2);
        }
    }
}

void us_simpleshader_patch()
{
    {
        auto func = &USSimpleShaderSpace::USSimpleShader<USInteriorMaterial>::_BindMaterial;
        FUNC_ADDRESS(address, func);
        set_vfunc(0x00871658, address);
    }

    {
        auto func = &USSimpleShaderSpace::USSimpleShader<USInteriorMaterial>::_RebaseMaterial;
        FUNC_ADDRESS(address, func);
        set_vfunc(0x00871660, address);
    }
}
