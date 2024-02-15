#include "us_person.h"

#include <ngl_dx_shader.h>
#include <ngl_dx_state.h>
#include <ngl_dx_texture.h>

#include "comic_panels.h"
#include "common.h"
#include "func_wrapper.h"
#include "light_source.h"
#include "log.h"
#include "matrix4x3.h"
#include "mstring.h"
#include "ngl.h"
#include "ngl_mesh.h"
#include "ngl_scene.h"
#include "nglsortinfo.h"
#include "tl_system.h"
#include "trace.h"
#include "utility.h"
#include "variables.h"
#include "vtbl.h"
#include "vector3d.h"

#include <ngl_dx_scene.h>

#include <d3d9.h>
#include <d3dx9tex.h>

#include <cassert>

Var<int> USPersonParam::ID{0x0095678C};

namespace USPersonShaderSpace {

VALIDATE_SIZE(USPersonNode, 0x28);
VALIDATE_SIZE(USPersonSolidNode, 0x28);
VALIDATE_SIZE(USPersonNode::LightInfoStruct, 0x38);

VALIDATE_OFFSET(ParamStruct, field_30, 0x30);

Var<USPersonNode::LightInfoStruct> USPersonNode::DefaultLightInfo{0x0091E750};

Var<ParamStruct> DefaultParams{0x00956918};

static Var<IDirect3DPixelShader9 *> OutlinePShader{0x009707F0};

USPersonShader::USPersonShader() {}

static Var<VShader[2]> OutlineVShader{0x009707E0};

static Var<VShader[1]> stru_9707E8{0x009707E8};

static Var<VShader[4]> stru_9707F4{0x009707F4};

static Var<IDirect3DPixelShader9 *[8]> dword_9707C0 { 0x009707C0 };

void sub_4114D0(const D3DVERTEXELEMENT9 *elements) {
    if constexpr (1) {
        static Var<const DWORD *[4]> off_939D20 { 0x00939D20 };

        auto **v1 = off_939D20();
        auto *array_shaders = stru_9707F4();

        if constexpr (0) {
#include "../../shaders/us_person/0_VS.h"

            nglCreateVShader(elements, &array_shaders[0], 0, text);
        } else {
            auto shader = CompileVShader("shaders/us_person/0_VS.hlsl");

            CreateVertexDeclarationAndShader(&array_shaders[0], elements, shader.data());
        }

        if constexpr (1) {
#include "../../shaders/us_person/1_VS.h"

            nglCreateVShader(elements, &array_shaders[1], 0, text);
        } else {
            auto shader = CompileVShader("shaders/us_person/1_VS.hlsl");

            CreateVertexDeclarationAndShader(&array_shaders[1], elements, shader.data());
        }

        if constexpr (1) {
#include "../../shaders/us_person/2_VS.h"

            nglCreateVShader(elements, &array_shaders[2], 0, text);
        } else {
            auto shader = CompileVShader("shaders/us_person/3_VS.hlsl");

            CreateVertexDeclarationAndShader(&array_shaders[2], elements, shader.data());
        }

        if constexpr (0) {
            sp_log("%d %s", 3, disassemble_shader(v1[2]));

            assert(0);

            for (int i = 1; i < 3; ++i) {
                CreateVertexDeclarationAndShader(&array_shaders[i], elements, v1[i]);
            }
        }

        {
            D3DXMACRO defines[] = {{"ID", "3"}, {nullptr, nullptr}};

            auto shader = CompileVShader("shaders/us_person/3_VS.hlsl", defines);

            CreateVertexDeclarationAndShader(&array_shaders[3], elements, shader.data());
        }

    } else {
        CDECL_CALL(0x004114D0, elements);
    }
}

void sub_411550() {
    if constexpr (1) {
        if constexpr (1) {
            static Var<const DWORD *[8]> off_939D38 { 0x00939D38 };

            for (int i = 0; i < 8; ++i) {
                CreatePixelShader(&dword_9707C0()[i], off_939D38()[i]);

                //sp_log("%s", disassemble_shader(off_939D38()[i]));
            }

        } else {
            int i = 0;
            {
                static const char text[] =
                    "tex t0\n"
                    "mul r0.xyz, c2, t0\n"
                    "+mov r0.w, t0.w\n";
                nglCreatePShader(&dword_9707C0()[i++], text);

                //compare_codes(off_939D38()[i], g_codes, size_codes(off_939D38()[i]));
            }

            {
                static const char text[] =
                    "tex t0\n"
                    "mul r0.xyz, v0, t0\n"
                    "+mov r0.w, t0.w\n";

                nglCreatePShader(&dword_9707C0()[i++], text);
            }

            {
                static const char text[] =
                    "tex t0\n"
                    "tex t1\n"
                    "mul r0.xyz, c2, t0\n"
                    "+mov r0.w, t0.w\n"
                    "mad r0.xyz, r0, t1.w, c1\n";

                nglCreatePShader(&dword_9707C0()[i++], text);
            }

            {
                static const char text[] =
                    "tex t0\n"
                    "tex t1\n"
                    "mul r0.xyz, v0, t0\n"
                    "+mov r0.w, t0.w\n"
                    "mad r0.xyz, r0, t1.w, c1\n";

                nglCreatePShader(&dword_9707C0()[i++], text);
            }

            {
                static const char text[] =
                    "tex t0\n"
                    "tex t1\n"
                    "mul r0.xyz, c2, t0\n"
                    "+mov r0.w, t0.w\n"
                    "mad r0.xyz, r0, c1.w, t1\n";

                nglCreatePShader(&dword_9707C0()[i++], text);
            }

            {
                static const char text[] =
                    "tex t0\n"
                    "tex t1\n"
                    "mul r0.xyz, v0, t0\n"
                    "+mov r0.w, t0.w\n"
                    "mad r0.xyz, r0, c1.w, t1\n";

                nglCreatePShader(&dword_9707C0()[i++], text);
            }

            {
                static const char text[] =
                    "tex t0\n"
                    "tex t1\n"
                    "mul r0.xyz, c2, t0\n"
                    "+mov r0.w, t0.w\n"
                    "mad r0.xyz, r0, t1.w, t1\n";

                nglCreatePShader(&dword_9707C0()[i++], text);
            }

            {
                static const char text[] =
                    "tex t0\n"
                    "tex t1\n"
                    "mul r0.xyz, v0, t0\n"
                    //"+mov r0.w, t0.w\n"
                    "mov r0.w, t0.w\n"
                    "mad r0.xyz, r0, t1.w, t1\n";

                nglCreatePShader(&dword_9707C0()[i++], text);
            }
        }

    } else {
        CDECL_CALL(0x00411550);
    }
}

void CreateOutlineVShader(const D3DVERTEXELEMENT9 *elements) {
    if constexpr (1) {
        static Var<const DWORD *[2]> off_939D30 { 0x00939D30 };

        auto &v1 = off_939D30();
        auto &v2 = OutlineVShader();

        if constexpr (1) {
            static const char text[] =
                "def c4, 3, 11, 0, 0\n"
                "dcl_position v0\n"
                "dcl_normal v1\n"
                "dcl_texcoord v2\n"
                "dcl_blendindices v3\n"
                "dcl_blendweight v4\n"

#if 0
                "mad r0, v3, c90.x, c90.y\n"
#else
                "mul r0, v3, c4.x\n"
                "add r0, r0, c4.y\n"
#endif

                "mov a0.x, r0.x\n"
                "mul r1, v4.x, c0[a0.x]\n"
                "mul r2, v4.x, c1[a0.x]\n"
                "mul r3, v4.x, c2[a0.x]\n"
                "mov a0.x, r0.y\n"
                "mad r1, v4.y, c0[a0.x], r1\n"
                "mad r2, v4.y, c1[a0.x], r2\n"
                "mad r3, v4.y, c2[a0.x], r3\n"
                "mov a0.x, r0.z\n"
                "mad r1, v4.z, c0[a0.x], r1\n"
                "mad r2, v4.z, c1[a0.x], r2\n"
                "mad r3, v4.z, c2[a0.x], r3\n"
                "mov a0.x, r0.w\n"
                "mad r1, v4.w, c0[a0.x], r1\n"
                "mad r2, v4.w, c1[a0.x], r2\n"
                "mad r3, v4.w, c2[a0.x], r3\n"
                "dp4 r4.x, v0, r1\n"
                "dp4 r4.y, v0, r2\n"
                "dp4 r4.z, v0, r3\n"
                "dp3 r5.x, v1, r1\n"
                "dp3 r5.y, v1, r2\n"
                "dp3 r5.z, v1, r3\n"
                "dp3 r6.w, r5.xyzz, r5.xyzz\n"
                "rsq r6.w, r6.w\n"
                "mul r5.xyz, r5.xyzz, r6.w\n"
                "mov r4.w, c91.z\n"
                "mad r4.xyz, r5.xyzz, c9.w, r4.xyzz\n"
                "mov r7.xyz, r4\n"
                "mov r7.w, c91.z\n"
                "dp4 oPos.x, r7, c0\n"
                "dp4 oPos.y, r7, c1\n"
                "dp4 oPos.z, r7, c2\n"
                "dp4 oPos.w, r7, c3\n";

            nglCreateVShader(elements, &v2[0], 0, text);

            compare_codes(v1[0], g_codes, size_codes(v1[0]));

            nglCreateVShader(elements, &v2[1], 0, text);

            compare_codes(v1[1], g_codes, size_codes(v1[1]));

            //sp_log("%s", disassemble_shader(v1[0]));

        } else {
            auto shader = CompileVShader("shaders/us_person/outline_VS.hlsl");

            CreateVertexDeclarationAndShader(&v2[0], elements, shader.data());
            CreateVertexDeclarationAndShader(&v2[1], elements, shader.data());
        }

    } else {
        CDECL_CALL(0x00411510, elements);
    }
}

USPersonSolidNode::USPersonSolidNode(nglMeshNode *a2, nglMeshSection *a3, nglMaterialBase *a4)
    : USVariantShaderNode(a2, a3) {
    this->field_18 = a4;
    this->field_24 = this->sub_41DE40();

    this->field_1C = this->sub_41BE30(this->field_18->field_1C);
    this->field_20 = this->sub_41BE30(this->field_18->field_24);
}

void USPersonSolidShader::sub_41DEE0(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3) {
    THISCALL(0x0041DEE0, this, a1, a2, a3);
}

void USPersonSolidShader::sub_41E0A0(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3) {
    THISCALL(0x0041E0A0, this, a1, a2, a3);
}

void USPersonSolidShader::sub_41E290(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3) {
    THISCALL(0x0041E290, this, a1, a2, a3);
}

void USPersonSolidShader::AddNode(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3)
{
    auto *v9 = &USPersonShaderSpace::DefaultParams();
    if (a1->field_8C.IsSetParam<USPersonParam>()) {
        auto *param = a1->field_8C.Get<USPersonParam>();

        v9 = param->field_0;
    }

    nglMeshSection *v7;

    if ((a3->field_38 || v9->field_48) &&
        (comic_panels::get_panel_params() == nullptr ||
         (comic_panels::get_panel_params()->field_D1 & 1) == 0)) {
        v7 = a2;
        this->sub_41DEE0(a1, a2, a3);
        this->sub_41E0A0(a1, a2, a3);
    } else {
        auto *ptr = nglListAlloc(sizeof(USPersonSolidNode), 16);
        auto *v8 = new (ptr) USPersonSolidNode{a1, a2, a3};

        sub_40FF00(v8);
    }

    if (v9->field_40) {
        this->sub_41E290(a1, v7, a3);
    }
}

void USPersonSolidShader::_BindMaterial(nglMaterialBase *a1)
{
    TRACE("USPersonShaderSpace::USPersonSolidShader::BindMaterial");

#ifdef TARGET_XBOX
    a1->field_1C = nglLoadTexture( *bit_cast<tlHashString *>(&a1->field_18));
    a1->field_24 = nglLoadTexture( *bit_cast<tlHashString *>(&a1->field_20));
#else
    a1->field_1C = nglLoadTexture(*bit_cast<const tlFixedString *>(a1->field_18));
    a1->field_24 = nglLoadTexture(*bit_cast<const tlFixedString *>(a1->field_20));
#endif
}


void USPersonSolidShader::_RebaseMaterial(nglMaterialBase *a1, unsigned int a2)
{
    TRACE("USPersonSolidShader::RebaseMaterial");

#ifndef TARGET_XBOX
    THISCALL(0x00410C60, this, a1, a2);
#endif
}

void USPersonSolidShader::Register() {
    sp_log("USPersonSolidShader::Register:");

    if constexpr (0) {
        nglShader::Register();

        D3DVERTEXELEMENT9 elements[] = {{0, 0, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_POSITION, 0},
                                        {0, 12, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_NORMAL, 0},
                                        {0, 24, D3DDECLTYPE_FLOAT2, 0, D3DDECLUSAGE_TEXCOORD, 0},
                                        {0, 32, D3DDECLTYPE_FLOAT4, 0, D3DDECLUSAGE_BLENDINDICES, 0},
                                        {0, 48, D3DDECLTYPE_FLOAT4, 0, D3DDECLUSAGE_BLENDWEIGHT, 0},
                                        D3DDECL_END()

        };

        if (EnableShader()) {
            sub_4114D0(elements);
            sub_411550();
            CreateOutlineVShader(elements);

            {
                auto pShader = CompilePShader("shaders/us_person/outline_PS.hlsl");

                CreatePixelShader(&OutlinePShader(), pShader.data());
            }

        } else {
            D3DVERTEXELEMENT9 a3[4];
            a3[0].Type = D3DDECLTYPE_FLOAT3;
            a3[0].Stream = 0;
            a3[0].Offset = 0;
            a3[0].Method = 0;
            a3[0].Usage = D3DDECLUSAGE_POSITION;
            a3[0].UsageIndex = 0;

            a3[1].Stream = 0;
            a3[1].Offset = 12;
            a3[1].Type = D3DDECLTYPE_FLOAT2;
            a3[1].Method = 0;
            a3[1].Usage = D3DDECLUSAGE_TEXCOORD;
            a3[1].UsageIndex = 0;

            a3[2].Stream = 0;
            a3[2].Offset = 20;
            a3[2].Type = D3DDECLTYPE_FLOAT1;
            a3[2].Method = 0;
            a3[2].Usage = D3DDECLUSAGE_TEXCOORD;
            a3[2].UsageIndex = 1;

            a3[3].Stream = 255;
            a3[3].Offset = 0;
            a3[3].Type = D3DDECLTYPE_UNUSED;
            a3[3].Method = 0;
            a3[3].Usage = 0;
            a3[3].UsageIndex = 0;

            static Var<IDirect3DVertexDeclaration9 *> dword_973910{0x00973910};

            if (dword_973910() == nullptr)
                g_Direct3DDevice()->lpVtbl->CreateVertexDeclaration(g_Direct3DDevice(),
                                                                    a3,
                                                                    &dword_973910());
        }
    } else {
        THISCALL(0x00411580, this);
    }
}

void USPersonShader::Register() {
    sp_log("USPersonShader::Register:");

    if constexpr (1) {
        nglShader::Register();

        D3DVERTEXELEMENT9 elements[] = {{0, 0, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_POSITION, 0},
                                        {0, 12, D3DDECLTYPE_FLOAT3, 0, D3DDECLUSAGE_NORMAL, 0},
                                        {0, 24, D3DDECLTYPE_FLOAT2, 0, D3DDECLUSAGE_TEXCOORD, 0},
                                        {0, 32, D3DDECLTYPE_FLOAT4, 0, D3DDECLUSAGE_BLENDINDICES, 0},
                                        {0, 48, D3DDECLTYPE_FLOAT4, 0, D3DDECLUSAGE_BLENDWEIGHT, 0},
                                        D3DDECL_END()

        };

        if (EnableShader()) {
            sub_4114D0(elements);
            sub_411550();
            CreateOutlineVShader(elements);

            auto pShader = CompilePShader("shaders/us_person/outline_PS.hlsl");
            CreatePixelShader(&OutlinePShader(), pShader.data());

        } else {
            D3DVERTEXELEMENT9 a3[4];
            a3[0].Type = D3DDECLTYPE_FLOAT3;
            a3[0].Stream = 0;
            a3[0].Offset = 0;
            a3[0].Method = 0;
            a3[0].Usage = D3DDECLUSAGE_POSITION;
            a3[0].UsageIndex = 0;

            a3[1].Stream = 0;
            a3[1].Offset = 12;
            a3[1].Type = D3DDECLTYPE_FLOAT2;
            a3[1].Method = 0;
            a3[1].Usage = D3DDECLUSAGE_TEXCOORD;
            a3[1].UsageIndex = 0;

            a3[2].Stream = 0;
            a3[2].Offset = 20;
            a3[2].Type = D3DDECLTYPE_FLOAT1;
            a3[2].Method = 0;
            a3[2].Usage = D3DDECLUSAGE_TEXCOORD;
            a3[2].UsageIndex = 1;

            a3[3].Stream = 255;
            a3[3].Offset = 0;
            a3[3].Type = D3DDECLTYPE_UNUSED;
            a3[3].Method = 0;
            a3[3].Usage = 0;
            a3[3].UsageIndex = 0;

            static Var<IDirect3DVertexDeclaration9 *> dword_973910{0x00973910};

            if (dword_973910() == nullptr)
                g_Direct3DDevice()->lpVtbl->CreateVertexDeclaration(g_Direct3DDevice(),
                                                                    a3,
                                                                    &dword_973910());
        }
    } else {
        THISCALL(0x00411580, this);
    }
}

void USPersonShader::sub_41BEF0(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3) {
    THISCALL(0x0041BEF0, this, a1, a2, a3);
}

void USPersonShader::sub_41C0B0(nglMeshNode *a2, nglMeshSection *a3, nglMaterialBase *a4) {
    THISCALL(0x0041C0B0, this, a2, a3, a4);
}

void USPersonShader::sub_41C2A0(nglMeshNode *a1, nglMeshSection *a2, nglMaterialBase *a3) {
    THISCALL(0x0041C2A0, this, a1, a2, a3);
}

void USPersonShader::AddNode(nglMeshNode *a2, nglMeshSection *a3, nglMaterialBase *a4) {
    auto *v9 = &USPersonShaderSpace::DefaultParams();
    if (a2->field_8C.IsSetParam<USPersonParam>()) {
        auto *param = a2->field_8C.Get<USPersonParam>();
        v9 = param->field_0;
    }

    nglMeshSection *v7;

    if ((a4->field_38 || v9->field_48) &&
        (comic_panels::get_panel_params() == nullptr ||
         (comic_panels::get_panel_params()->field_D1 & 1) == 0)) {
        v7 = a3;
        this->sub_41BEF0(a2, a3, a4);
        this->sub_41C0B0(a2, a3, a4);
    } else {
        auto *mem = nglListAlloc(sizeof(USPersonNode), 16);

        auto *v8 = new (mem) USPersonNode{a2, a3, a4};

        sub_40FF00(v8);
    }

    if (v9->field_40) {
        this->sub_41C2A0(a2, v7, a4);
    }
}

void USPersonShader::_BindMaterial(nglMaterialBase *a1)
{
    TRACE("USPersonShaderSpace::USPersonShader::BindMaterial");

#ifdef TARGET_XBOX
    a1->field_1C = nglLoadTexture( *bit_cast<tlHashString *>(&a1->field_18));
    a1->field_24 = nglLoadTexture( *bit_cast<tlHashString *>(&a1->field_20));
#else
    a1->field_1C = nglLoadTexture(*bit_cast<const tlFixedString *>(a1->field_18));
    a1->field_24 = nglLoadTexture(*bit_cast<const tlFixedString *>(a1->field_20));
#endif
}


void USPersonShader::_RebaseMaterial(nglMaterialBase *a1, unsigned int a2)
{
    TRACE("USPersonShaderSpace::USPersonShader::RebaseMaterial");

#ifndef TARGET_XBOX
    THISCALL(0x00410C60, this, a1, a2);
#endif
}

tlFixedString USPersonShader::GetName() {
    tlFixedString result;

    if constexpr (0) {
        auto &GetName = get_vfunc(this->m_vtbl, 0x4);
        GetName(this, &result);
    } else {
        result = this->field_C;
    }

    return result;
}

void USPersonSolidNode::Render() {
#if 0

    result = dword_957034;
    v51 = 0;
    if (dword_957034)
        return result;
    if (!byte_972AB0)
        return sub_41F000(this);
    v3 = (int64_t *) (this->field_C + 140);
    v4 = &USPersonShaderSpace::DefaultParams;
    if (sub_411970(v3, USPersonParam::ID[0]))
        v4 = *(USPersonShaderSpace::Params_t **) (*(_DWORD *) v3 +
                                                  4 * *(_DWORD *) USPersonParam::ID + 8);
    v5 = v4->field_38;
    v45 = v4->field_41;
    v47 = v5;
    v43 = 0;
    if (v5) {
        v6 = this->field_18;
        if (*(_DWORD *) (v6 + 60) || *(_DWORD *) (v6 + 64))
            v43 = 1;
    }
    if (!v5 || !*(_DWORD *) (this->field_18 + 68) || (v42 = 1, !sub_41EF20(this, a2)))
        v42 = 0;
    v7 = v4->field_3C;
    if (v7)
        v8 = v7 == 2;
    else
        v8 = *(_DWORD *) (this->field_18 + 72);
    v9 = v4->field_44;
    v10 = g_Direct3DDevice()->lpVtbl;
    v46 = v4->field_49;
    v11 = this->field_C;
    v48 = v8 != 0;
    v51 = v9;
    v10->SetVertexShaderConstantF(g_Direct3DDevice(), 0, (const float *) (v11 + 64), 4);
    sub_772810(11, this->field_C, this->field_10);
    if (v9) {
        if (byte_9739A0[0] != 1) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                     D3DRS_STENCILENABLE |
                                                         D3DRS_STENCILENABLE,
                                                     1);
            byte_9739A0[0] = 1;
        }
        v12 = byte_91E74E;
        if (dword_9739B4 != byte_91E74E) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                     D3DRS_STENCILREF |
                                                         D3DRS_STENCILREF,
                                                     byte_91E74E);
            dword_9739B4 = v12;
        }
        if (dword_9739B0 != 1) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                     D3DRS_STENCILREF |
                                                         D3DRS_STENCILENABLE,
                                                     1);
            dword_9739B0 = 1;
        }
        if (dword_9739A4 != 1) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                     D3DRS_STENCILZFAIL |
                                                         D3DRS_STENCILENABLE,
                                                     1);
            dword_9739A4 = 1;
        }
        if (v51 != 1) {
            if (v51 == 2) {
                sub_401AD0(3);
                sub_401B60(byte_91E74E);
            } else {
                if (v51 != 3)
                    goto LABEL_34;
                sub_401AD0(6);
                sub_401B60(byte_91E74E);
            }
            sub_401AA0(1);
            goto LABEL_34;
        }
        sub_401AD0(8);
        g_renderState().sub_401B90(byte_91E74E);
        sub_401AA0(3);
    }
LABEL_34:
    if (v47) {
        sub_7754B0(0, (nglTexture *) this->field_1C, 8, 3);
        sub_76DC30(0, D3DSAMP_ADDRESSU, 1u);
        sub_76DC30(0, D3DSAMP_ADDRESSV, 1u);
        if (v43) {
            sub_7754B0(1u, (nglTexture *) this->field_20, 8, 3);
            sub_76DC30(1u, D3DSAMP_ADDRESSU, 3u);
            sub_76DC30(1u, D3DSAMP_ADDRESSV, 3u);
        }

        sub_774A90(byte_9739A0, *(_DWORD *) (this->field_18 + 76), 0, 0);
        if (dword_973A4C != 2) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(), D3DRS_CULLMODE, 2);
            dword_973A4C = 2;
        }

        if (v43) {
            v13 = (po *) sub_41D840(v63);
            v14 = sub_413770((vector4d *) v64, v13);
            sub_415650(v14);
            v58.field_C = (ai::param_block *) 0x3F800000;
            v15 = (const ai::state_trans_action *) sub_74B1C0((int) &out, 0.5);
            ai::state_trans_action::state_trans_action(&v58, v15);
            v59.field_C = (ai::param_block *) -1082130432;
            v16 = (const ai::state_trans_action *) sub_74B1C0((int) &out, -0.5);
            ai::state_trans_action::state_trans_action(&v59, v16);
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                               4,
                                                               (const float *) &v58,
                                                               2);
        }
        if (v42) {
            v17 = this->field_18;
            v18 = *(float *) (v17 + 52);
            v19 = *(float *) (v17 + 48);
            v20 = *(float *) (v17 + 44);
            v21 = *(float *) (v17 + 40);
            a3.arr[1] = v20;
            a3.arr[2] = v19;
            a3.arr[0] = v21;
            a3.field_C = v18;
            v22 = sub_410DF0(out.arr, v56, 0.5);
            v50[0] = *v22;
            v50[1] = v22[1];
            v50[2] = v22[2];
            v50[3] = v22[3];
            a3 = *sub_412870((vector4d *) a1, a3.arr, v50);
            v50[0] = 1.0;
            v50[1] = 1.0;
            v50[2] = 1.0;
            v50[3] = 1.0;
            v23 = sub_776EC0(out.arr, v50, a3.arr);
            v24 = v23[1];
            a1[0] = *v23;
            v25 = v23[2];
            a1[1] = v24;
            v26 = v23[3];
            a1[2] = v25;
            a1[3] = v26;
            sub_412870((vector4d *) v50, (float *) v55, a1);
            if ((v57 & 2) == 0) {
                a1[0] = v56[0];
                a1[1] = v56[1];
                a1[2] = v56[2];
                a1[3] = v56[3];
                *(vector4d *) v50 = *sub_412870(&out, v50, a1);
            }
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                               8,
                                                               (const float *) &a3,
                                                               1);
            v27 = sub_4010A0(v61, a2);
            sub_4014B0(a1, v27);
            v41 = (po *) sub_4199D0((void **) this->field_C, v63);
            v28 = (vector4d *) sub_410DF0((float *) v60, a1, v56[4]);
            v29 = sub_4139A0(&v62, v28, v41);
            sub_41CF30(v29, &out);
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                               6,
                                                               (const float *) &out,
                                                               1);
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 7, v50, 1);
        }

        sub_772270((int *) (8 * (v42 + 2 * v43) + 0x9707F4));
        sub_772250((IDirect3DPixelShader9 **) (4 *
                                                   (v42 +
                                                    2 *
                                                        (*(_DWORD *) (this->field_18 + 64) +
                                                         2 * *(_DWORD *) (this->field_18 + 60))) +
                                               9897920));
        if (!v42) {
            v30 = this->field_18;
            v31 = *(float *) (v30 + 44);
            a3.arr[0] = *(float *) (v30 + 40);
            v32 = *(float *) (v30 + 48);
            a3.arr[1] = v31;
            v33 = *(float *) (v30 + 52);
            a3.arr[2] = v32;
            a3.field_C = v33;
            a1[0] = a3.arr[0];
            a1[2] = v32;
            a1[3] = v33;
            a1[1] = a3.arr[1];
            g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(g_Direct3DDevice(), 2, a1, 1);
        }

        a3.arr[2] = 0.0;
        a3.arr[0] = 0.0;
        a1[0] = 0.0;
        a1[2] = 0.0;
        a3.field_C = 1.0;
        a1[3] = 1.0;
        a3.arr[1] = 0.0;
        a1[1] = 0.0;
        g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(g_Direct3DDevice(), 1, a1, 1);
        sub_771AF0(this->field_10);
    }

    if (v45) {
        if (dword_973A4C != 2) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(), D3DRS_CULLMODE, 2);
            dword_973A4C = 2;
        }

        sub_774A90(byte_9739A0, 0, 0, 0);
        a1[0] = 0.0;
        a1[1] = 0.0;
        a1[2] = 0.0;
        a1[3] = 0.0;
        g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 9, a1, 1);
        sub_772270(&dword_9707E0);
        sub_772250(&dword_9707F0);
        v34 = v4->field_24;
        a1[0] = v4->field_20;
        v35 = v4->field_28;
        a1[1] = v34;
        a1[3] = v4->field_2C;
        a1[2] = v35;
        g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(g_Direct3DDevice(), 0, a1, 1);
        g_renderTextureState().field_0[0] = nullptr;
        g_Direct3DDevice()->lpVtbl->SetTexture(g_Direct3DDevice(), 0, 0);
        sub_771AF0(this->field_10);
    }

    if (v48) {
        v36 = sub_41DE40(this);
        v52 = v36;
        if (v36 > float_NULL) {
            sub_401DD0(byte_9739A0, 3u);
            sub_774A90(byte_9739A0, 0, 0, 0);
            v37 = v52 * v4->field_30 * flt_91E208;
            a1[0] = 0.0;
            a1[3] = v37;
            a1[1] = 0.0;
            a1[2] = 0.0;
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 9, a1, 1);
            sub_772270(&dword_9707E0);
            sub_772250(&dword_9707F0);
            v38 = v4->field_8;
            v39 = v4->field_4;
            a1[0] = v4->field_0;
            v40 = v4->field_C;
            a1[2] = v38;
            a1[3] = v40;
            a1[1] = v39;
            g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(g_Direct3DDevice(), 0, a1, 1);
            sub_771AF0(this->field_10);
        }
    }
    if (v46) {
        if ((dword_957030 & 1) == 0) {
            dword_957030 |= 1u;
            dword_957020[0] = 0.0;
            dword_957024 = 0;
            dword_957028 = 0;
            dword_95702C = 1266679806;
        }
        if (dword_973A4C != 2) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(), D3DRS_CULLMODE, 2);
            dword_973A4C = 2;
        }
        sub_774A90(byte_9739A0, 0, 0, 0);
        if (dword_973A48) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                     D3DRS_COLORWRITEENABLE | 0x80,
                                                     0);
            dword_973A48 = 0;
        }
        if (!byte_973A14) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                     D3DRS_ZWRITEENABLE,
                                                     1);
            byte_973A14 = 1;
        }
        if (dword_973A1C != 8) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(), D3DRENDERSTATE_ZFUNC, 8);
            dword_973A1C = 8;
        }
        a1[0] = 0.0;
        a1[1] = 0.0;
        a1[2] = 0.0;
        a1[3] = 0.0;
        g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 9, a1, 1);
        g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 10, dword_957020, 1);
        sub_772270(&dword_9707E8);
        sub_772250(&dword_9707F0);
        sub_771AF0(this->field_10);
        sub_401DA0(nglCurScene->field_3B4);
        if (byte_973A14) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                     D3DRS_ZWRITEENABLE,
                                                     0);
            byte_973A14 = 0;
        }
        if (dword_973A1C != 4) {
            g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(), D3DRENDERSTATE_ZFUNC, 4);
            dword_973A1C = 4;
        }
    }
    result = v51;
    if (v51) {
        result = byte_9739A0[0];
        if (byte_9739A0[0]) {
            result = g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                              D3DRS_STENCILENABLE |
                                                                  D3DRS_STENCILENABLE,
                                                              0);
            byte_9739A0[0] = 0;
        }
        if (dword_9739AC != 8) {
            result = g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                              D3DRS_STENCILENABLE |
                                                                  D3DRS_STENCILREF,
                                                              8);
            dword_9739AC = 8;
        }
        if (dword_9739A8 != 1) {
            result = g_Direct3DDevice()->lpVtbl->SetRenderState(g_Direct3DDevice(),
                                                              D3DRS_STENCILZFAIL |
                                                                  D3DRENDERSTATE_WRAPU,
                                                              1);
            dword_9739A8 = 1;
        }
    }
    return result;

#else
    if constexpr (0) {
    } else {
        THISCALL(0x0041E4B0, this);
    }

#endif
}

void USPersonSolidNode::GetSortInfo(nglSortInfo &sortInfo) {
    auto *v4 = &this->field_C->field_8C;
    auto *v5 = &USPersonShaderSpace::DefaultParams();
    if (v4->IsSetParam<USPersonParam>()) {
        auto *param = v4->Get<USPersonParam>();
        v5 = param->field_0;
    }

    if (v5->field_49) {
        sortInfo.Type = NGLSORT_TRANS;
        sortInfo.field_4 = -1.0e10;
    } else {
        auto v6 = this->field_18->m_blend_mode;
        if (!v6 || v6 == 1) {
            sortInfo.Type = NGLSORT_OPAQUE;
            sortInfo.field_4 =
                (this->field_18->field_4->field_8 | (32 * (v5->field_44 & 0xFE | 0xFFFFFFFC)))
                << 24;
        } else {
            sortInfo.Type = NGLSORT_TRANS;
            sortInfo.field_4 = this->sub_415D10();
        }
    }
}

matrix4x3 sub_413770(const matrix4x4 *arg4) {
    matrix4x3 result;
    CDECL_CALL(0x00413770, &result, arg4);

    return result;
}

vector4d sub_4139A0(const vector4d *a2, const matrix4x4 *a3) {
    vector4d result;
    CDECL_CALL(0x004139A0, &result, a2, a3);

    return result;
}

USPersonNode::USPersonNode(nglMeshNode *a2, nglMeshSection *a3, nglMaterialBase *a4)
    : USVariantShaderNode(a2, a3) {
    this->field_18 = a4;
    this->field_24 = this->sub_41DE40();
    this->field_1C = this->sub_41BE30(this->field_18->field_1C);
    this->field_20 = this->sub_41BE30(this->field_18->field_24);
}

bool USPersonNode::GetLightInfo(USPersonNode::LightInfoStruct &lightInfo) {
    if constexpr (1) {
        bool result = false;

        auto *v4 = &this->field_C->field_8C;
        if (v4->IsSetParam<USLightParam>()) {
            auto *param = v4->Get<USLightParam>();

            auto *v5 = param->field_0;

            vector3d v8 = sub_411750(*(vector4d *) &this->field_C->field_88->field_20,
                                     this->field_C->field_0.arr[3]);
            v5->sub_41D050(&v8, &lightInfo.field_10, &lightInfo.field_20);

            lightInfo.field_0 = v5->get_dir(v8);
            lightInfo.field_0.w = 1.0;
            lightInfo.field_30 = v5->properties->field_4C;
            lightInfo.field_34 = v5->properties->field_54;
            result = true;
        } else {
            lightInfo = USPersonShaderSpace::USPersonNode::DefaultLightInfo();

            result = false;
        }

        //sp_log("lightInfoIsSet =  %d", result);

        return result;
    } else {
        auto result = (bool) THISCALL(0x0041CF70, this, &lightInfo);

        return result;
    }
}

void USPersonNode::sub_41D180() {
    THISCALL(0x0041D180, this);
}

void USPersonNode::Render() {
    //sp_log("USPersonNode::Render");

    if constexpr (0) {
        if (this->field_18->m_blend_mode == 2 &&
            (this->field_18->field_40 || this->field_18->field_3C)) {
            sp_log("Ink and Highlight features not supported with Blend mode.");

            assert(0);
        }

        if (this->field_18->m_blend_mode && this->field_18->m_outlineFeature) {
            sp_log("Outline feature only supported with Opaque mode.");

            assert(0);
        }

        static Var<int> dword_957018{0x00957018};

        if (dword_957018()) {
            return;
        }

        if (!EnableShader()) {
            this->sub_41D180();
            return;
        }

        auto &v2 = this->field_C->field_8C;
        auto *params = &USPersonShaderSpace::DefaultParams();
        if (v2.IsSetParam<USPersonParam>()) {
            params = v2.Get<USPersonParam>()->field_0;
        }

        bool v4 = params->field_38;
        bool v43 = params->field_41;
        auto v45 = v4;
        uint8_t v41 = 0;
        if (v4) {
            auto *v5 = this->field_18;
            if (v5->field_3C || v5->field_40) {
                v41 = 1;
            }
        }

        USPersonNode::LightInfoStruct lightInfo;

        uint8_t lightParamIsSet;
        if (!v4 || !this->field_18->field_44 ||
            (lightParamIsSet = 1, !this->GetLightInfo(lightInfo))) {
            lightParamIsSet = 0;
        }

        bool enableOutline;

        auto v6 = params->field_3C;
        if (v6) {
            enableOutline = (v6 == 2);
        } else {
            enableOutline = this->field_18->m_outlineFeature;
        }

        int v49 = params->field_44;

        bool v44 = params->field_49;

        g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                             0,
                                                             &this->field_C->field_40[0][0],
                                                             4);
        nglSetupVShaderBonesDX(11, this->field_C, this->field_10);

        if (v49 != 0) {
            g_renderState().setStencilCheckEnabled(true);

            static Var<uint8_t> byte_91E74C{0x0091E74C};

            {
                uint32_t v11 = byte_91E74C();

                g_renderState().setStencilRefValue(v11);
            }

            g_renderState().setStencilFailOperation(1);

            g_renderState().setStencilDepthFailOperation(1);

            switch (v49) {
            case 1: {
                g_renderState().setStencilBufferTestFunction(D3DCMP_ALWAYS);
                g_renderState().setStencilBufferWriteMask((D3DSTENCILOP) byte_91E74C());
                g_renderState().setStencilPassOperation(D3DSTENCILOP_REPLACE);
            } break;
            case 2: {
                g_renderState().setStencilBufferTestFunction(D3DCMP_EQUAL);
                g_renderState().setStencilBufferCompareMask(byte_91E74C());
                g_renderState().setStencilPassOperation(D3DSTENCILOP_KEEP);
            } break;
            case 3: {
                g_renderState().setStencilBufferTestFunction(D3DCMP_NOTEQUAL);
                g_renderState().setStencilBufferCompareMask(byte_91E74C());
                g_renderState().setStencilPassOperation(D3DSTENCILOP_KEEP);
            } break;
            default:
                break;
            }
        }

        if (v45) {
            nglDxSetTexture(0, this->field_1C, 8, 3);
            SetSamplerState(0, D3DSAMP_ADDRESSU, 1u);
            SetSamplerState(0, D3DSAMP_ADDRESSV, 1u);

            if (v41) {
                nglDxSetTexture(1u, this->field_20, 8, 3);
                SetSamplerState(1u, D3DSAMP_ADDRESSU, 3u);
                SetSamplerState(1u, D3DSAMP_ADDRESSV, 3u);
            }

            g_renderState().setBlending(this->field_18->m_blend_mode, 0, 0);

            g_renderState().setCullingMode(D3DCULL_CW);

            if (v41) {
                matrix4x4 v12 = this->field_C->sub_41D840();

                matrix4x3 v59 = sub_413770(&v12);

                matrix4x4 v53;
                v53.sub_415650(&v59);
                v53.arr[0][3] = 1.0;

                vector4d v14 = v53.arr[0].sub_74B1C0(0.5);
                v53.arr[0] = v14;

                v53.arr[1][3] = -1.0;

                vector4d v15 = v53.arr[1].sub_74B1C0(-0.5);
                v53.arr[1] = v15;

                g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                                     4,
                                                                     &v53.arr[0][0],
                                                                     2);
            }

            if (lightParamIsSet) {
                auto *material = this->field_18;

                vector4d a2 = material->field_28;

                vector4d a3 = lightInfo.field_20 * 0.5f;

                vector4d a1 = a2 * a3;

                a3 = {1.0};

                a1 = a3 - a2;

                a3 = lightInfo.field_10 * a1;

                if ((lightInfo.field_34 & 2) == 0) {
                    a1 = lightInfo.field_20;
                    a3 *= a1;
                }

                g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                                     8,
                                                                     &a2[0],
                                                                     1);

                a1 = -lightInfo.field_0;

                matrix4x4 v39 = this->field_C->sub_4199D0();

                vector4d v27 = a1 * lightInfo.field_30;

                vector4d v28 = sub_4139A0(&v27, &v39);

                vector4d v53 = v28.sub_41CF30();
                g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                                     6,
                                                                     &v53[0],
                                                                     1);

                g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                                     7,
                                                                     &a3[0],
                                                                     1);
            }

            {
                auto idx = lightParamIsSet + 2 * v41;

                SetVertexDeclarationAndShader(&stru_9707F4()[idx]);
            }

            {
                auto idx = lightParamIsSet +
                    2 * (this->field_18->field_40 + 2 * this->field_18->field_3C);

                SetPixelShader(&dword_9707C0()[idx]);
            }

            if (!lightParamIsSet) {
                auto *v28 = this->field_18;

                vector4d a1 = v28->field_28;

                g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(g_Direct3DDevice(),
                                                                    2,
                                                                    &a1[0],
                                                                    1);
            }

            vector4d a1;
            vector4d a2;

            a2[2] = 0.0;
            a2[0] = 0.0;
            a1[0] = 0.0;
            a1[2] = 0.0;
            a2[3] = 1.0;
            a1[3] = 1.0;
            a2[1] = 0.0;
            a1[1] = 0.0;
            g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(g_Direct3DDevice(), 1, &a1[0], 1);

            //sp_log("DRAW!");
            SetStreamSourceAndDrawPrimitive(this->field_10);

            if constexpr (0) {
                auto size = field_10->m_stride * 2;

                void *data = nullptr;
                this->field_10->m_vertexBuffer->lpVtbl->Lock(this->field_10->m_vertexBuffer, 0, size, &data, 0);

                struct vertexDecl_t {
                    float pos[3];
                    float normal[3];
                    float uv[2];
                    vector4d bone_indices;
                    float bone_weights[4];
                } *vertexDecl = static_cast<vertexDecl_t *>(data);

                VALIDATE_SIZE(vertexDecl_t, 64);

                sp_log("%s", vertexDecl[1].bone_indices.to_string());

                this->field_10->m_vertexBuffer->lpVtbl->Unlock(this->field_10->m_vertexBuffer);
            }
        }

        if (v43) {
            g_renderState().setCullingMode(D3DCULL_CW);

            g_renderState().setBlending(0, 0, 0);

            vector4d a1{0.0};

            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 9, &a1[0], 1);

            SetVertexDeclarationAndShader(&OutlineVShader()[0]);
            SetPixelShader(&OutlinePShader());
            a1[0] = params->field_20;
            a1[1] = params->field_24;
            a1[2] = params->field_28;
            a1[3] = params->field_2C;

            g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(g_Direct3DDevice(), 0, &a1[0], 1);

            g_renderTextureState().field_0[0] = nullptr;
            g_Direct3DDevice()->lpVtbl->SetTexture(g_Direct3DDevice(), 0, nullptr);

            SetStreamSourceAndDrawPrimitive(this->field_10);
        }

        if (enableOutline) {
            auto v34 = this->sub_41DE40();
            if (v34 > 0.0f) {
                g_renderState().setCullingMode(D3DCULL_CCW);
                g_renderState().setBlending(0, 0, 0);
                auto v35 = v34 * params->field_30 * ParamStruct::OutlineThickness;

                vector4d a1{0, 0, 0, v35};

                g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                                     9,
                                                                     &a1[0],
                                                                     1);
                SetVertexDeclarationAndShader(&OutlineVShader()[0]);
                SetPixelShader(&OutlinePShader());
                a1 = params->field_0;

                g_Direct3DDevice()->lpVtbl->SetPixelShaderConstantF(g_Direct3DDevice(),
                                                                    0,
                                                                    &a1[0],
                                                                    1);

                SetStreamSourceAndDrawPrimitive(this->field_10);
            }
        }

        if (v44) {
            static Var<float[4]> dword_957004{0x00957004};

            static Var<int> dword_957014{0x00957014};
            if ((dword_957014() & 1) == 0) {
                dword_957014() |= 1u;
                dword_957004()[0] = 0.0;
                dword_957004()[1] = 0.0;
                dword_957004()[2] = 0.0;
                dword_957004()[3] = 16777214.0;
            }

            g_renderState().setCullingMode(D3DCULL_CW);

            g_renderState().setBlending(0, 0, 0);

            g_renderState().setColourBufferWriteEnabled(0);

            g_renderState().setDepthBufferWriteEnabled(true);

            g_renderState().setDepthBufferFunction(D3DCMP_ALWAYS);

            vector4d a1{0.0};
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 9, &a1[0], 1);
            g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(),
                                                                 10,
                                                                 dword_957004(),
                                                                 1);
            SetVertexDeclarationAndShader(&OutlineVShader()[1]);
            SetPixelShader(&OutlinePShader());

            SetStreamSourceAndDrawPrimitive(this->field_10);
            g_renderState().setColourBufferWriteEnabled(nglCurScene()->field_3B4);

            g_renderState().setDepthBufferWriteEnabled(false);

            g_renderState().setDepthBufferFunction(D3DCMP_LESSEQUAL);
        }

        if (v49) {
            g_renderState().setStencilCheckEnabled(false);

            g_renderState().setStencilBufferTestFunction(D3DCMP_ALWAYS);

            g_renderState().setStencilPassOperation(D3DSTENCILOP_KEEP);
        }

    } else {
        THISCALL(0x0041C4C0, this);
    }
}

void USPersonNode::GetSortInfo(nglSortInfo &sortInfo) {
    auto *v4 = &this->field_C->field_8C;
    auto *v5 = &USPersonShaderSpace::DefaultParams();
    if (v4->IsSetParam<USPersonParam>()) {
        auto *param = v4->Get<USPersonParam>();
        v5 = param->field_0;
    }

    if (v5->field_49) {
        sortInfo.Type = NGLSORT_TRANS;
        sortInfo.field_4 = -1.0e10;
    } else {
        auto v6 = this->field_18->m_blend_mode;
        if (v6 == 0 || v6 == 1) {
            sortInfo.Type = NGLSORT_OPAQUE;
            sortInfo.field_4 =
                (this->field_18->field_4->field_8 | (32 * (v5->field_44 & 0xFE | 0xFFFFFFFC)))
                << 24;
        } else {
            sortInfo.Type = NGLSORT_TRANS;
            sortInfo.field_4 = this->sub_415D10();
        }
    }
}

} // namespace USPersonShaderSpace

void hookSetStreamSourceAndDrawPrimitive(nglMeshSection *) {}

void us_person_patch() {

    {
        FUNC_ADDRESS(address, USPersonShaderSpace::USPersonShader::_BindMaterial);
        set_vfunc(0x008717E8, address);
    }

    {
        FUNC_ADDRESS(address, USPersonShaderSpace::USPersonShader::_RebaseMaterial);
        set_vfunc(0x008717F0, address);
    }

    {
        FUNC_ADDRESS(address, USPersonShaderSpace::USPersonSolidShader::_BindMaterial);
        set_vfunc(0x00871814, address);
    }

    {
        FUNC_ADDRESS(address, USPersonShaderSpace::USPersonSolidShader::_RebaseMaterial);
        set_vfunc(0x0087181C, address);
    }
    return;

    REDIRECT(0x0041171C, USPersonShaderSpace::sub_411550);


    //USPersonNode::Render;
    {
        REDIRECT(0x0041C5CE, nglSetupVShaderBonesDX);

        {
            FUNC_ADDRESS(address, &USPersonShaderSpace::USPersonNode::GetLightInfo);
            REDIRECT(0x0041C56A, address);
        }

        {
            FUNC_ADDRESS(address, &USVariantShaderNode::sub_41DE40);
            REDIRECT(0x0041CC36, address);
        }

        REDIRECT(0x0041CA54, SetVertexDeclarationAndShader);
    }

    //REDIRECT(0x0041CB31, hookSetStreamSourceAndDrawPrimitive);

    {
        FUNC_ADDRESS(address, &RenderState_t::setCullingMode);
        REDIRECT(0x0041CC57, address);
    }

    {
        FUNC_ADDRESS(address, &USPersonShaderSpace::USPersonShader::AddNode);
        set_vfunc(0x008717E4, address);
    }

    {
        FUNC_ADDRESS(address, &USPersonShaderSpace::USPersonSolidShader::AddNode);
        set_vfunc(0x00871810, address);
    }
}
