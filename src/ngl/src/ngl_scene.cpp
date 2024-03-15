#include "ngl_scene.h"

#include "common.h"
#include "error.h"
#include "func_wrapper.h"
#include "ngl.h"
#include "ngl_dx_scene.h"
#include "ngl_dx_core.h"
#include "ngl_params.h"
#include "osassert.h"
#include "trace.h"
#include "variables.h"

#include <cassert>

#include <windows.h>

VALIDATE_SIZE(nglScene, 0x440u);
VALIDATE_OFFSET(nglScene, field_1CC, 0x1CC);
VALIDATE_OFFSET(nglScene, field_24C, 0x24C);

Var<nglScene *> nglCurScene{0x00971F00};
Var<nglScene *> nglRootScene{0x00971F04};

Var<nglScene *> g_shadow_scene{0x00965960};

static Var<float> flt_93BC78 = (0x0093BC78);


void * nglScene::operator new(size_t size)
{
    auto *mem = nglListAlloc(size, 64);
    return mem;
}

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

void sub_77C9B0(int a1)
{
    nglCurScene()->field_4 = a1;
}

void nglSetLightContext(nglLightContext *a1)
{
    nglCurScene()->field_350 = a1;
}

void nglSetDefaultSceneParams()
{
    TRACE("nglSetDefaultSceneParams");
    
    if constexpr (1) {
        auto *BackBufferTex = nglGetBackBufferTex();
        nglSetRenderTarget(BackBufferTex);
        auto v4 = (float)(nglGetScreenHeight() - 1);
        auto v6 = nglGetScreenWidth() - 1;
        auto v3 = (float)v6;
        nglSetViewport(0.0, 0.0, v3, v4);
        nglCurScene()->field_3E8 = 1.3333334;
        nglCurScene()->field_3E4 = 1;
        if ( g_distance_clipping_enabled() ) {
            auto v1 = (double)g_distance_clipping() * LARGE_EPSILON * (2000.0 - 100.0) + 100.0;
            if ( v1 < 100.0 ) {
                v1 = 100.0;
            }

            nglSetPerspectiveMatrix(50.0, 0.1, v1);
        } else {
            nglSetPerspectiveMatrix(50.0, 0.1, 10000.0);
        }

        char v5;
        math::MatClass<4,3> a2;
        a2.sub_415740(&v5);
        
        static Var<vector4d> stru_8B7964 {0x008B7964};
        a2[3] = stru_8B7964();
        nglCurScene()->field_14C = sub_4150E0(a2);
        nglCurScene()->field_3E4 = true;
        nglCurScene()->field_39C = 6;
        float *v2 = nglCurScene()->field_3A4;
        v2[0] = 0.0;
        v2[1] = 0.0;
        v2[2] = 0.0;
        v2[3] = 0.0;

        nglCurScene()->field_3A0 = 1.0;
        sub_77C9B0(0);
        nglCurScene()->field_3B4 = 15;
        nglCurScene()->field_3B8 = true;
        nglCurScene()->field_3B9 = true;
        nglCurScene()->field_3DC = false;
        nglCurScene()->field_3E0 = 0;
        nglCurScene()->field_3F8 = 0.0;
        nglSetLightContext(nglDefaultLightContext());
        nglCurScene()->field_408 = 0;
        nglCalculateMatrices(1);
    } else {
        CDECL_CALL(0x0076C400);
    }
}

void nglSetupScene(nglScene *a1, nglSceneParamType a2)
{
    TRACE("nglSetupScene", std::to_string(a2).c_str());

    if constexpr (0) {
        nglScene *v2 = nglCurScene();
        nglCurScene() = a1;

        switch (a2) {
        case 0: {
            a1 = new nglScene {};

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

#if 0
        a1->field_404 = {1};
#else
        auto *v5 = bit_cast<nglParam *>((unsigned int)(nglListWorkPos() + 7) & 0xFFFFFFF8);
        nglListWorkPos() = bit_cast<uint8_t *>(&v5[1].field_0 + nglSceneParamSet_Pool::NextID());
        v5->field_0 = 0;
        v5->field_4 = 0;
        a1->field_404.field_0 = v5;
#endif

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
    } else {
        CDECL_CALL(0x0076C700, a1, a2);
    }
}

void nglSceneDumpStart()
{
    if (nglSyncDebug().DumpSceneFile) {

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

