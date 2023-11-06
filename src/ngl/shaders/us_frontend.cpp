#include "us_frontend.h"

#include <ngl_dx_shader.h>

#include "func_wrapper.h"
#include "log.h"

#include "common.h"
#include "ngl.h"
#include "ngl_vertexdef.h"
#include "tl_system.h"
#include "variables.h"
#include "trace.h"
#include "vtbl.h"

#include <ngl_dx_state.h>
#include <ngl_dx_texture.h>

#include <cassert>

#include <d3dx9shader.h>

VALIDATE_SIZE(FrontEnd_ShaderNode, 0x18);

FrontEnd_Shader::FrontEnd_Shader() {}

void FrontEnd_Shader::_BindMaterial(nglMaterialBase *Material)
{
    TRACE("FrontEnd_Shader::BindMaterial");

#ifdef TARGET_XBOX
    if (Material != nullptr)
    {
        Material->field_1C = nglLoadTexture(Material->field_18);
    }
    else
    {
        assert(0);
    }

#else
    if (Material != nullptr) {
        auto *tex = nglLoadTexture(*Material->field_18);
        Material->field_1C = tex;
    } else {
        assert(0);
    }
#endif
}

void FrontEnd_Shader::ReleaseMaterial(nglMaterialBase *a1) {
    nglTexture **v2 = nullptr;

    if (a1 != nullptr) {
        v2 = &a1[-1].field_20;
    }

    nglReleaseTexture(v2[8]);
    v2[8] = nullptr;
}

void FrontEnd_Shader::_RebaseMaterial([[maybe_unused]] nglMaterialBase *a1, [[maybe_unused]] uint32_t a2)
{
    TRACE("FrontEnd_Shader::RebaseMaterial");

#ifndef TARGET_XBOX
    THISCALL(0x00410550, this, a1, a2);
#endif
}

static Var<VShader> stru_970610{0x00970610};

static Var<IDirect3DPixelShader9 *> dword_9562F4{0x009562F4};

void FrontEnd_Shader::Register() {
    sp_log("FrontEnd_Shader::Register:");

    if constexpr (1) {
        nglShader::Register();

        static Var<D3DVERTEXELEMENT9> stru_91E2BC{0x0091E2BC};

        if (EnableShader()) {
            //static Var<DWORD *> off_939B90{0x00939B90};

            if constexpr (1) {
                auto pShader = CompileVShader("shaders/us_frontend_VS.hlsl");

                CreateVertexDeclarationAndShader(&stru_970610(), &stru_91E2BC(), pShader.data());
            } else {
                static const char *text =
                    "dcl_position v0\n"
                    "dcl_texcoord v1\n"
                    "dcl_color v2\n"
                    "dp4 oPos.x, v0, c0\n"
                    "dp4 oPos.y, v0, c1\n"
                    "dp4 oPos.z, v0, c2\n"
                    "dp4 oPos.w, v0, c3\n"
                    "mov oT0.xy, v1\n"
                    "mov oD0, v2\n"
                    "mov oD1, c91.x\n"
                    "mov oFog, c91.z\n";

                nglCreateVShader(&stru_91E2BC(), &stru_970610(), 0, text);
            }

            static Var<char[1]> asc_870AD8{0x00870AD8};

            if constexpr (0) {
                static const char *text =
                    "tex t0\n"
                    "mul r0, t0, v0\n";

                nglCreatePShader(&dword_9562F4(), text);
            } else {
                auto pShader = CompilePShader("shaders/us_frontend_PS.hlsl");

                CreatePixelShader(&dword_9562F4(), pShader.data());
            }

        } else {
            static Var<IDirect3DVertexDeclaration9 *> dword_973938{0x00973938};
            if (dword_973938() == nullptr)
                g_Direct3DDevice()->lpVtbl->CreateVertexDeclaration(g_Direct3DDevice(),
                                                                    &stru_91E2BC(),
                                                                    &dword_973938());
        }

    } else {
        THISCALL(0x00403AD0, this);
    }
}

void FrontEnd_ShaderNode::Render() {
    if constexpr (0) {
        static Var<int> dword_956D40{0x00956D40};

        if (dword_956D40() == 0) {
            this->sub_413AF0();

            g_renderState().setCullingMode(D3DCULL_NONE);

            g_renderState().setBlending(this->field_14[11], 0, 0);
            if (EnableShader()) {
                g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                                     0,
                                                                     &this->field_C->field_40[0][0],
                                                                     4);

                SetVertexDeclarationAndShader(&stru_970610());
            } else {
                g_Direct3DDevice()->lpVtbl->SetTransform(g_Direct3DDevice(),
                                                         (D3DTRANSFORMSTATETYPE) 256,
                                                         (const D3DMATRIX *) &this->field_C->field_0);
                g_Direct3DDevice()->lpVtbl->SetVertexDeclaration(g_Direct3DDevice(),
                                                                 dword_9738E0()[22]);
            }

            nglDxSetTexture(0, *((nglTexture **) this->field_14 + 8), 2u, 3);
            SetSamplerState(0, D3DSAMP_ADDRESSU, 2 * (this->field_14[9] != 0) + 1);
            SetSamplerState(0, D3DSAMP_ADDRESSV, 2 * (this->field_14[10] != 0) + 1);

            if (EnableShader()) {
                SetPixelShader(&dword_9562F4());
            } else {
                SetTextureStageState(0, D3DTSS_COLOROP, 4u);
                SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
                SetTextureStageState(0, D3DTSS_COLORARG2, 0);
                SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
                SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
                SetTextureStageState(0, D3DTSS_ALPHAARG2, 0);
                SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
                SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
            }

            SetStreamSourceAndDrawPrimitive(this->field_10);
        }
    } else {
        THISCALL(0x00406E50, this);
    }
}

void FrontEnd_Shader_patch()
{
    {
        FUNC_ADDRESS(address, &FrontEnd_Shader::_RebaseMaterial);
        set_vfunc(0x008714FC, address);
    }

    {
        FUNC_ADDRESS(address, &FrontEnd_Shader::_BindMaterial);
        set_vfunc(0x008714F4, address);
    }
}
