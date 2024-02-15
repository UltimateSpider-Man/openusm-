#include "us_outline.h"

#include <ngl_dx_shader.h>
#include <ngl_dx_state.h>
#include <ngl_dx_texture.h>

#include "func_wrapper.h"
#include "ngl.h"
#include "ngl_mesh.h"
#include "ngl_scene.h"
#include "trace.h"
#include "utility.h"
#include "variable.h"
#include "variables.h"

static Var<IDirect3DPixelShader9 *> dword_970770{0x00970770};

static Var<VShader> stru_970760 {0x00970760};

void sub_411830() {
    int i = 0;

    //static Var<const DWORD *> off_939CD8{0x00939CD8};

    {
        static const char text[] =
            "tex t0\n"
            "mul r0, t0, c0\n";

        nglCreatePShader(&(&dword_970770())[i++], text);
    }

    {
        static const char text[] = "mov r0, c0\n";
        nglCreatePShader(&(&dword_970770())[i++], text);
    }
}

static Var<VShader> stru_970768 {0x00970768};

static Var<IDirect3DPixelShader9 *> dword_970774 {0x00970774};

double calc_outline_thickness(const math::VecClass<3,1> &a1)
{
    double (*func)(const void *) = CAST(func, 0x00406B60);
    return func(&a1);
}

namespace USOutlineShaderSpace
{

template<>
void Outline_ShaderNode<USExteriorMaterial>::Render()
{
    TRACE("Outline_ShaderNode<USExteriorMaterial>::Render");

    static Var<int> dword_956FFC {0x00956FFC};
    if ( dword_956FFC() == 0 ) {
        auto *v2 = this->field_14;
        auto v14 = v2->field_6C[0];
        auto v15 = v2->field_6C[1];
        auto v16 = v2->field_6C[2];
        this->sub_413AF0();
        auto v3 = this->field_C->sub_4199D0();
        auto v17 = sub_414360(*(math::VecClass<3, 1> *)&nglCurScene()->field_28C, v3);
        v17 = sub_414360(this->field_C->field_88->field_20, this->field_C->field_0);
        auto v4 = g_renderState().field_74;
        auto v5 = g_renderState().field_7C;
        g_renderState().setBlending(0, 0, 0);
        if ( g_renderState().field_A8 != 7 )
        {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(),
                    D3DRS_COLORWRITEENABLE,
                    7);
            g_renderState().field_A8 = 7;
        }

        if ( g_renderState().field_7C != 4 ) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(),
                    D3DRS_ZFUNC,
                    4);
            g_renderState().field_7C = (D3DCMPFUNC) 4;
        }

        if ( !g_renderState().field_74 ) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(),
                    D3DRS_ZWRITEENABLE,
                    1);
            g_renderState().field_74 = 1;
        }

        if ( g_renderState().m_cullingMode != D3DCULL_CW )
        {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(),
                    D3DRS_CULLMODE,
                    2);
            g_renderState().m_cullingMode = D3DCULL_CW;
        }

        g_renderTextureState().setSamplerState(0, 8u, 3u);
        nglDxSetTexture(0, this->field_18, 8u, 3);
        SetSamplerState(0, D3DSAMP_ADDRESSU, 1u);
        SetSamplerState(0, D3DSAMP_ADDRESSV, 1u);
        if ( EnableShader() )
        {
            SetVertexDeclarationAndShader(&stru_970760());
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(
                    g_Direct3DDevice(),
                    0,
                    &this->field_C->field_40[0][0],
                    4);
        }
        else
        {
            g_Direct3DDevice()->lpVtbl->SetTransform(
                g_Direct3DDevice(),
                (D3DTRANSFORMSTATETYPE)256,
                (const D3DMATRIX *)this->field_C);
            g_Direct3DDevice()->lpVtbl->SetVertexDeclaration(
                    g_Direct3DDevice(), dword_9738E0()[9]);
        }

        color v18 {};
        if ( EnableShader() )
        {
            SetPixelShader(&dword_970770());
            sub_413F80(&v18, this->field_14, &this->field_C->field_8C, 9u);
            v17.field_0[0] = v18.r;
            v17.field_0[1] = v18.g;
            v17.field_0[2] = v18.b;
            v17.field_0[3] = v18.a;
            g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(
                    g_Direct3DDevice(),
                    0,
                    v17.field_0,
                    1);
        }
        else
        {
            sub_413F80(&v18, this->field_14, &this->field_C->field_8C, 9u);
            SetTextureStageState(0, D3DTSS_COLOROP, 4u);
            SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
            SetTextureStageState(0, D3DTSS_COLORARG2, 3u);
            SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
            SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
            SetTextureStageState(0, D3DTSS_ALPHAARG2, 3u);
            SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
            SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
        }

        SetStreamSourceAndDrawPrimitive(this->field_10);
        if ( g_renderState().field_7C != v5 ) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(),
                    D3DRS_ZFUNC,
                    v5);

            g_renderState().field_7C = v5;
        }

        if ( g_renderState().field_74 != v4 ) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(),
                    D3DRS_ZWRITEENABLE,
                    v4);

            g_renderState().field_74 = v4;
        }

        auto *v8 = this->field_14;
        if ( LOBYTE(v8->field_68) && EnableShader() )
        {
            auto v10 = this->field_C->field_0[3][1];

            math::VecClass<3, 1> v17 {};
            v17.field_0[0] = this->field_C->field_0[3][0];
            auto v11 = this->field_C->field_0[3][2];
            v17.field_0[1] = v10;
            auto v12 = this->field_C->field_0[3][3];
            v17.field_0[2] = v11;
            v17.field_0[3] = v12;
            auto v13 = calc_outline_thickness(v17);
            if ( v8->field_7C > 1.f ) {
                v13 *= v8->field_7C;
            }

            if ( g_renderState().field_A8 != 7 )
            {
                g_Direct3DDevice()->lpVtbl->SetRenderState(
                        g_Direct3DDevice(),
                        D3DRS_COLORWRITEENABLE,
                        7);
                g_renderState().field_A8 = 7;
            }

            if ( g_renderState().m_cullingMode != D3DCULL_CCW )
            {
                g_Direct3DDevice()->lpVtbl->SetRenderState(
                        g_Direct3DDevice(),
                        D3DRS_CULLMODE,
                        3);
                g_renderState().m_cullingMode = D3DCULL_CCW;
            }

            SetVertexDeclarationAndShader(&stru_970768());
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(
                    g_Direct3DDevice(),
                    0,
                    &this->field_C->field_40[0][0],
                    4);

            v17.field_0[3] = v13;
            memset(&v17, 0, 12);
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(
                    g_Direct3DDevice(), 8, (const float *)&v17, 1);

            SetPixelShader(&dword_970774());
            v17.field_0[0] = v14;
            v17.field_0[1] = v15;
            v17.field_0[2] = v16;
            v17.field_0[3]= 1.0;
            g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(
                    g_Direct3DDevice(), 0, v17.field_0, 1);
            SetStreamSourceAndDrawPrimitive(this->field_10);
        }
    }
}

vector4d sub_41BA70(nglMaterialBase *a1, int *a2, unsigned int a4)
{
    vector4d result;
    CDECL_CALL(0x0041BA70, &result, a1, a2, a4);
    return result;
}

template<>
void Outline_ShaderNode<USInteriorMaterial>::Render()
{
    static Var<int> dword_957000 {0x00957000};
    if ( !dword_957000() ) {
        auto *v2 = this->field_14;
        auto v14 = v2->field_28[0];
        auto v15 = v2->field_28[1];
        auto v16 = v2->field_28[2];
        this->sub_413AF0();
        auto v3 = this->field_C->sub_4199D0();
        auto v17 = sub_414360(*(math::VecClass<3,1> *)&nglCurScene()->field_28C, v3);
        v17 = sub_414360(this->field_C->field_88->field_20, this->field_C->field_0);
        auto v4 = g_renderState().field_74;
        auto v5 = g_renderState().field_7C;
        g_renderState().setBlending(0, 0, 0);
        if ( g_renderState().field_A8 != 7 )
        {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(),
                    D3DRS_COLORWRITEENABLE,
                    7);
            g_renderState().field_A8 = 7;
        }

        if ( g_renderState().field_7C != 4 )
        {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(), D3DRS_ZFUNC, 4);
            g_renderState().field_7C = (D3DCMPFUNC) 4;
        }

        if ( !g_renderState().field_74 )
        {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(), D3DRS_ZWRITEENABLE, 1);
            g_renderState().field_74 = 1;
        }

        if ( g_renderState().m_cullingMode != D3DCULL_CW )
        {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(), D3DRS_CULLMODE, 2);
            g_renderState().m_cullingMode = D3DCULL_CW;
        }

        g_renderTextureState().setSamplerState(0, 8u, 3u);
        nglDxSetTexture(0, this->field_18, 8u, 3);
        SetSamplerState(0, D3DSAMP_ADDRESSU, 1u);
        SetSamplerState(0, D3DSAMP_ADDRESSV, 1u);

        if ( EnableShader() ) {
            SetVertexDeclarationAndShader(&stru_970760());
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(
                    g_Direct3DDevice(),
                    0,
                    &this->field_C->field_40[0][0],
                    4);
        } else {
            g_Direct3DDevice()->lpVtbl->SetTransform(
                g_Direct3DDevice(),
                (D3DTRANSFORMSTATETYPE)256,
                (const D3DMATRIX *)this->field_C);
            g_Direct3DDevice()->lpVtbl->SetVertexDeclaration(
                    g_Direct3DDevice(), dword_9738E0()[9]);
        }

        if ( EnableShader() ) {
            SetPixelShader(&dword_970770());
            auto v6 = sub_41BA70(this->field_14, (int *)&this->field_C->field_8C, 9u);
            v17.field_0[0] = v6[0];
            v17.field_0[1] = v6[1];
            v17.field_0[2] = v6[2];
            v17.field_0[3] = v6[3];
            g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(
                    g_Direct3DDevice(), 0, (const float *)&v17, 1);
        } else
        {
            [[maybe_unused]] auto v18 = sub_41BA70(this->field_14, (int *)&this->field_C->field_8C, 9u);
            SetTextureStageState(0, D3DTSS_COLOROP, 4u);
            SetTextureStageState(0, D3DTSS_COLORARG1, 2u);
            SetTextureStageState(0, D3DTSS_COLORARG2, 3u);
            SetTextureStageState(0, D3DTSS_ALPHAOP, 4u);
            SetTextureStageState(0, D3DTSS_ALPHAARG1, 2u);
            SetTextureStageState(0, D3DTSS_ALPHAARG2, 3u);
            SetTextureStageState(1u, D3DTSS_COLOROP, 1u);
            SetTextureStageState(1u, D3DTSS_ALPHAOP, 1u);
        }

        SetStreamSourceAndDrawPrimitive(this->field_10);
        if ( g_renderState().field_7C != v5 )
        {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(), D3DRS_ZFUNC, v5);
            g_renderState().field_7C = v5;
        }

        if ( g_renderState().field_74 != v4 )
        {
            g_Direct3DDevice()->lpVtbl->SetRenderState(
                    g_Direct3DDevice(), D3DRS_ZWRITEENABLE, v4);
            g_renderState().field_74 = v4;
        }

        auto *v8 = this->field_14;
        if ( LOBYTE(v8->field_24) && EnableShader() )
        {
            auto v10 = this->field_C->field_0[3][1];
            v17.field_0[0] = this->field_C->field_0[3][0];
            auto v11 = this->field_C->field_0[3][2];
            v17.field_0[1] = v10;
            auto v12 = this->field_C->field_0[3][3];
            v17.field_0[2] = v11;
            v17.field_0[3] = v12;
            auto v13 = calc_outline_thickness(v17);
            if ( v8->field_38 > 1.f ) {
                v13 *= v8->field_38;
            }

            if ( g_renderState().field_A8 != 7 ) {
                g_Direct3DDevice()->lpVtbl->SetRenderState(
                        g_Direct3DDevice(), D3DRS_COLORWRITEENABLE, 7);
                g_renderState().field_A8 = 7;
            }

            if ( g_renderState().m_cullingMode != D3DCULL_CCW ) {
                g_Direct3DDevice()->lpVtbl->SetRenderState(
                        g_Direct3DDevice(), D3DRS_CULLMODE, 3);
                g_renderState().m_cullingMode = D3DCULL_CCW;
            }

            SetVertexDeclarationAndShader(&stru_970768());
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(
                    g_Direct3DDevice(),
                    0,
                    &this->field_C->field_40[0][0],
                    4);
            v17.field_0[3] = v13;
            memset(&v17, 0, 12);
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(
                    g_Direct3DDevice(), 8, v17.field_0, 1);
            SetPixelShader(&dword_970774());
            v17.field_0[0] = v14;
            v17.field_0[1] = v15;
            v17.field_0[2] = v16;
            v17.field_0[3] = 1.0;
            g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(
                    g_Direct3DDevice(), 0, v17.field_0, 1);
            SetStreamSourceAndDrawPrimitive(this->field_10);
        }
    }
}

} // USOutlineShaderSpace

void us_outline_patch() {
    REDIRECT(0x004118D9, sub_411830);

    {
        auto func = &USOutlineShaderSpace::Outline_ShaderNode<USExteriorMaterial>::Render;
        FUNC_ADDRESS(address, func);
        set_vfunc(0x00871B24, address);
    }

    {
        auto func = &USOutlineShaderSpace::Outline_ShaderNode<USInteriorMaterial>::Render;
        FUNC_ADDRESS(address, func);
        set_vfunc(0x00871B30, address);
    }
}
