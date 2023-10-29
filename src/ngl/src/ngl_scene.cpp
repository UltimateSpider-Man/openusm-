#include "ngl_scene.h"

#include "ngl.h"
#include "common.h"
#include "error.h"
#include "func_wrapper.h"
#include "ngl_dx_scene.h"
#include "ngl_dx_core.h"
#include "ngl_params.h"
#include "variables.h"

#include <cassert>

#include <windows.h>

VALIDATE_SIZE(nglScene, 1088u);
VALIDATE_OFFSET(nglScene, field_2AC, 0x2AC);

Var<nglScene *> nglCurScene{0x00971F00};
Var<nglScene *> nglRootScene{0x00971F04};

Var<nglScene *> g_shadow_scene{0x00965960};

static Var<float> flt_93BC78 = (0x0093BC78);


bool nglIsFBPAL() {
    return false;
}

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

void nglSetDefaultSceneParams() {
    CDECL_CALL(0x0076C400);
}

void nglSetupScene(nglScene *a1, nglSceneParamType a2)
{
    nglScene *v2 = nglCurScene();
    nglCurScene() = a1;

    switch (a2) {
    case 0: {
        *a1 = {};

        nglSetDefaultSceneParams();
    } break;
    case 1:
        a1 = v2;
        break;
    case 2:
        a1 = nglRootScene();
        break;
    default:
        break;
    }

    a1->field_404 = {1};

    if (a2 == 1) {
        a1->field_404 = v2->field_404;
    } else if (a2 == 2) {
        a1->field_404 = nglRootScene()->field_404;
    }

    a1->field_30C = v2;
    a1->field_310 = nullptr;
    a1->field_314 = nullptr;
    a1->field_318 = nullptr;
    a1->field_0 = 0;
    a1->field_31C = nullptr;
    a1->field_320 = nullptr;
    a1->field_324 = nullptr;
    a1->field_328 = nullptr;
    a1->field_32C = nullptr;
    a1->field_330 = nullptr;
    if (equal(nglCurScene()->field_3F8, 0.0f)) {
        float v7 = (nglIsFBPAL() ? 20.0f : 16.666666f);

        nglCurScene()->field_3FC = static_cast<float>(nglFrameVBlankCount()) * v7 * 0.001f;
    } else {
        nglCurScene()->field_3FC = nglCurScene()->field_3F8;
    }

    auto a2a = flt_93BC78() * nglCurScene()->field_3FC;

    nglCurScene()->field_400 = static_cast<int>(a2a);
    a1->field_340 = 0;
    a1->field_344 = 0;
    a1->OpaqueListCount = 0;
    a1->TransListCount = 0;
}

void nglSceneDumpStart()
{
    //if (nglSyncDebug()[0x12])
    static auto cond = true;

    if (cond) {
        cond = !cond;

        auto nglHostOpen = [](const char *a1) -> HANDLE {
            CHAR FileName[512];

            strcpy(FileName, a1);
            auto v2 = CreateFileA(FileName, GENERIC_WRITE, 0, nullptr, 2u, 0x8000080u, nullptr);
            if (v2 != (HANDLE) -1) {
                return v2;
            }

            error("cannot open \"%s\" for writing !\n", FileName);

            return nullptr;
        };

        h_sceneDump() = nglHostOpen("scenedump.scene");
        nglHostPrintf(h_sceneDump(), "//\n");
        nglHostPrintf(h_sceneDump(), "// Midnight scene file dump.\n");
        nglHostPrintf(h_sceneDump(), "//\n");
        nglHostPrintf(h_sceneDump(), "\n");
        nglHostPrintf(h_sceneDump(), "\n");
    }
}

