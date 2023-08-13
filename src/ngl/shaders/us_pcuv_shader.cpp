#include "us_pcuv_shader.h"

#include "femanager.h"
#include "func_wrapper.h"
#include "log.h"
#include "ngl.h"
#include "ngl_scene.h"
#include "tl_system.h"
#include "utility.h"
#include "variables.h"
#include "vtbl.h"

#include <ngl_dx_shader.h>
#include <ngl_dx_state.h>
#include <ngl_dx_texture.h>

static Var<IDirect3DPixelShader9 *> PCUV_PShader{0x009562C8};

static Var<VShader> dword_970AD0{0x00970AD0};

PCUV_Shader::PCUV_Shader() {}

void PCUV_Shader::Register() {
    if constexpr (1) {
        nglShader::Register();

        static Var<D3DVERTEXELEMENT9> stru_91E1B4{0x0091E1B4};

        static Var<IDirect3DVertexDeclaration9 *> dword_973918{0x00973918};

        if (EnableShader()) {
            if constexpr (1) {
                auto pShader = CompileVShader("shaders/us_pcuv_VS.hlsl");

                //static Var<DWORD *> off_939FB0{0x00939FB0};
                CreateVertexDeclarationAndShader(&dword_970AD0(), &stru_91E1B4(), pShader.data());
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

                nglCreateVShader(&stru_91E1B4(), &dword_970AD0(), 0, text);
            }

            if constexpr (0) {
                static const char *text =
                    "tex t0\n"
                    "mul r0, t0, v0\n";

                nglCreatePShader(&PCUV_PShader(), text);
            } else {
                auto pShader = CompilePShader("shaders/us_pcuv_PS.hlsl");
                CreatePixelShader(&PCUV_PShader(), pShader.data());
            }

        } else if (dword_973918() == nullptr) {
            g_Direct3DDevice()->lpVtbl->CreateVertexDeclaration(g_Direct3DDevice(),
                                                                &stru_91E1B4(),
                                                                &dword_973918());
        }
    } else {
        THISCALL(0x00402BC0, this);
    }
}

void PCUV_ShaderNode::Render() {
    static Var<int> dword_956D34{0x00956D34};

    if (dword_956D34() == 0) {
        THISCALL(0x00413AF0, this);

        g_renderState().setCullingMode(D3DCULL_NONE);

        g_renderState().setBlending(this->field_14[9], this->field_14[11], 0);
        if (EnableShader()) {
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                                 0,
                                                                 this->field_C->field_40,
                                                                 4);

            SetVertexDeclarationAndShader(&dword_970AD0());
        } else {
            g_Direct3DDevice()->lpVtbl->SetTransform(g_Direct3DDevice(),
                                                     (D3DTRANSFORMSTATETYPE) 256,
                                                     (const D3DMATRIX *) &this->field_C->field_0);
            g_Direct3DDevice()->lpVtbl->SetVertexDeclaration(g_Direct3DDevice(), dword_9738E0()[14]);
        }

        static Var<int> dword_956D30{0x00956D30};

        if (dword_956D30() == 1) {
            g_renderState().setCullingMode(D3DCULL_CW);
        } else if (dword_956D30() == 2) {
            g_renderState().setCullingMode(D3DCULL_CCW);
        }

        nglDxSetTexture(0, *((nglTexture **) this->field_14 + 8), 2u, 3);
        uint32_t v2 = this->field_14[10];
        SetSamplerState(0, D3DSAMP_ADDRESSU, ((v2 & 0x40) | 0x20u) >> 5);
        SetSamplerState(0, D3DSAMP_ADDRESSV, ((v2 & 0x80) | 0x40u) >> 6);

        if (EnableShader()) {
            SetPixelShader(&PCUV_PShader());
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

        if (byte_95C718() && nglCurScene()->field_3BA && !sub_581C30()) {
            g_renderState().setFogEnable(false);
        }

        SetStreamSourceAndDrawPrimitive(this->field_10);

        if (byte_95C718() && nglCurScene()->field_3BA) {
            g_renderState().setFogEnable(true);
        }
    }
}

void us_pcuv_patch() {
    {
        FUNC_ADDRESS(address, &PCUV_ShaderNode::Render);
        set_vfunc(0x00871BF8, address);
    }
}
