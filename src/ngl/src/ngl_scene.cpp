#include "ngl_scene.h"

#include "common.h"
#include "ngl_dx_scene.h"
#include "ngl_params.h"

#include <cassert>

VALIDATE_SIZE(nglScene, 1088u);
VALIDATE_OFFSET(nglScene, field_2AC, 0x2AC);

Var<nglScene *> nglCurScene{0x00971F00};
Var<nglScene *> nglRootScene{0x00971F04};

Var<nglScene *> g_shadow_scene{0x00965960};

void nglSetPerspectiveMatrix(Float a1, Float nearz, Float farz) {
    assert(nearz > 0.0f && farz > nearz && "Invalid projection parameters.");

    nglCurScene()->field_33C = 1;
    nglCurScene()->field_3EC = a1;
    nglCurScene()->m_nearz = nearz;
    nglCurScene()->m_farz = farz;
    nglCurScene()->field_3E4 = true;
}

void nglSetSceneCallBack(nglSceneCallbackType a1, void (*Fn)(unsigned int *&, void *), void *a3) {
    if (a1) {
        if (a1 == 1) {
            nglCurScene()->field_324 = Fn;
            nglCurScene()->field_328 = a3;
        } else if (a1 == 2) {
            nglCurScene()->field_32C = Fn;
            nglCurScene()->field_330 = a3;
        }

    } else {
        nglCurScene()->field_31C = Fn;
        nglCurScene()->field_320 = a3;
    }
}
