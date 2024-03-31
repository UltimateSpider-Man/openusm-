#include "ngl_lighting.h"

#include "func_wrapper.h"

void nglListAddDirLight(uint32_t a2,
        math::VecClass<3, 0, void, math::VecUnit<1>, math::Rep_Std<false> > a3,
        math::VecClass<4, -1, void, void, math::Rep_Std<false> > a4)
{
    CDECL_CALL(0x007760C0, a2, a3, a4);
}
