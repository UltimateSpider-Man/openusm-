#include "ngl_dx_shader.h"

#include <common.h>
#include <func_wrapper.h>
#include <log.h>
#include <matrix4x3.h>
#include <mstring.h>
#include <ngl.h>
#include <ngl_mesh.h>
#include <trace.h>
#include <variables.h>
#include <vtbl.h>

#include <cassert>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstring>

#include <list.hpp>

#include <d3dx9shader.h>

Var<IDirect3DVertexDeclaration9 *[1]> dword_9738E0 { 0x009738E0 };

Var<_std::list<void *>> g_pixelShaderList{0x00972B10};

//0x007CA2E8
int __stdcall hookD3DXAssembleShader(const char *data,
                                     UINT data_len,
                                     const D3DXMACRO *defines,
                                     ID3DXInclude *include,
                                     DWORD flags,
                                     ID3DXBuffer **shader,
                                     ID3DXBuffer **error_messages) {
    //sp_log("%s %d", a1, a2);

    auto result = D3DXAssembleShader(data, data_len, defines, include, flags, shader, error_messages);

    return result;
}

int CreatePixelShader(IDirect3DPixelShader9 **a1, const DWORD *a2) {
    return CDECL_CALL(0x00772500, a1, a2);
}

void nglCreateVertexDeclarationAndShader(void *a1, const D3DVERTEXELEMENT9 *a2, const DWORD *a3)
{
    if constexpr (1)
    {
        struct {
            IDirect3DVertexShader9 *field_0;
            IDirect3DVertexDeclaration9 *field_4;
        } *v1 = static_cast<decltype(v1)>(a1);

        g_Direct3DDevice()->lpVtbl->CreateVertexDeclaration(g_Direct3DDevice(), a2, &v1->field_4);
        g_Direct3DDevice()->lpVtbl->CreateVertexShader(g_Direct3DDevice(), a3, &v1->field_0);

        auto *v3 = g_vertexShaderList().m_head;
        assert(v3 != nullptr);

        auto *v4 = (decltype(v3)) THISCALL(0x00772C60,
                                           &g_vertexShaderList(),
                                           g_vertexShaderList().m_head,
                                           g_vertexShaderList().m_head->_Prev,
                                           &v1->field_0);
        THISCALL(0x00772CE0, &g_vertexShaderList(), 1u);
        v3->_Prev = v4;
        v4->_Prev->_Next = v4;

    }
    else
    {
        CDECL_CALL(0x007724A0, a1, a2, a3);
    }
}

const DWORD *g_codes = nullptr;

void nglCreateVShader(
    const D3DVERTEXELEMENT9 *a2, void *a1, [[maybe_unused]] BOOL a3, const char *SrcCode, ...)
{
    va_list va;
    va_start(va, SrcCode);

    char Work[4096];
    vsprintf(Work, SrcCode, va);

    assert(SrcCode != nullptr);

    static const auto NGL_VS_PRECODE = "vs.1.1\n";
    assert(strlen(Work) + strlen(NGL_VS_PRECODE) + 1 < 4096 &&
           "String overflow in nglCreateVShader !");

    char Dest[4096];
    strcpy(Dest, NGL_VS_PRECODE);

    auto v4 = strlen(Work) + 1;
    char *v5 = Dest;
    v5 = v5 - 1;
    while (*++v5) {
        ;
    }

    std::memcpy(v5, Work, v4);

    ID3DXBuffer *pShader = nullptr;

    if (D3DXAssembleShader(Dest, strlen(Dest), nullptr, nullptr, 2u, &pShader, nullptr) != D3D_OK)
    {
        sp_log("Cannot assemble vertex shader. \n%s\n", Dest);

        assert(0);
    }

    auto *v7 = static_cast<const DWORD *>(pShader->lpVtbl->GetBufferPointer(pShader));
    g_codes = v7;

    nglCreateVertexDeclarationAndShader(a1, a2, v7);

    va_end(va);
}

int size_codes(const DWORD *code) {
    int size = 0;

    while (code[size] != 0xFFFF) {
        ++size;
    }

    return size;
}

bool compare_codes(const DWORD *code0, const DWORD *code1, int size)
{
    for (int i = 0; i < size; ++i)
    {
        auto c0 = code0[i];
        auto c1 = code1[i];

        if (c0 != c1) {
            sp_log("Codes not equal!: %d 0x%08X 0x%08X", i, c0, c1);
            return false;
        }
    }

    return true;
}

void log_codes(const DWORD *code) {
    mString str;

    int i = 0;

    while (code[i] != 0xFFFF) {
        str += mString{0, "%08x ", code[i]};

        ++i;
    }

    sp_log("%s", str.c_str());
}

const DWORD *AssemblePShader(const char *text) {
    ID3DXBuffer *pShader = nullptr;

    if (D3DXAssembleShader(text,
                           strlen(text),
                           nullptr,
                           nullptr,
                           D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
                           &pShader,
                           nullptr) != D3D_OK) {
        sp_log("Cannot assemble pixel shader. \n%s\n", text);

        assert(0);
    }

    auto *result = static_cast<const DWORD *>(pShader->lpVtbl->GetBufferPointer(pShader));
    return result;
}

std::vector<DWORD> CompilePShader(const char *file_name) {
    ID3DXBuffer *pShader = nullptr;
    ID3DXBuffer *error_messages = nullptr;

    const char *profile = "ps_1_1";

    if (D3DXCompileShaderFromFile(file_name,
                                  nullptr,
                                  nullptr,
                                  "main",
                                  profile,
                                  D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
                                  &pShader,
                                  &error_messages,
                                  nullptr) != D3D_OK) {
        sp_log("%s",
               static_cast<const char *>(error_messages->lpVtbl->GetBufferPointer(error_messages)));

        error_messages->lpVtbl->Release(error_messages);

        assert(0);
    }

    assert(error_messages == nullptr);

    auto buffer_size = pShader->lpVtbl->GetBufferSize(pShader);
    auto *buffer = pShader->lpVtbl->GetBufferPointer(pShader);

    std::vector<DWORD> result(buffer_size / 4);

    std::memcpy(result.data(), buffer, buffer_size);

    pShader->lpVtbl->Release(pShader);

    return result;
}

static constexpr auto MAX_BONES = 64u;

void nglSetupVShaderBonesDX(int a5, nglMeshNode *MeshNode, nglMeshSection *Section)
{
    TRACE("nglSetupVShaderBonesDX");

    if constexpr (0)
    {
        float a2[4] {3.0, a5, 1.0, 1.0};

        g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 90u, a2, 1u);

        static Var<matrix4x3[MAX_BONES]> g_boneMatrices {0x00972B20};

        auto *meshParams = MeshNode->field_90;
        if ( (meshParams->Flags & 4) != 0 )
        {
            for ( int i = 0; i < Section->NBones; ++i )
            {
                assert(i < MAX_BONES && "nglSetupVShaderBonesDX: too many bones ! Increase the MAX_BONES value.");

                auto boneIdx = Section->BonesIdx[i];
                auto v9 = MeshNode->sub_4199D0();
                matrix4x4 arg4;

                /*
                struct {
                    matrix4x3 *field_0;
                    matrix4x3 *field_4;
                } v29 {&meshParams->field_8[boneIdx], v9};
                auto *v27 = (const math::VecClass__3_1 *)(v8 + LODWORD(a2[1]));
                sub_770F30(&arg4, (matrix4x4 **)&v25);
                sub_414360(&out, v27 + 3, a3);
                sub_414360((math::VecClass__3_1 *)&arg4.m.arr[3], &out, v9);
                */

                matrix4x3 v10 = sub_413770(&arg4);
                std::memcpy(&g_boneMatrices()[i], &v10, sizeof(v10));
            }
        }
        else if ( (meshParams->Flags & 8) != 0 )
        {
            for ( int i = 0; i < Section->NBones; ++i )
            {
                assert(i < MAX_BONES && "nglSetupVShaderBonesDX: too many bones ! Increase the MAX_BONES value.");

                auto boneIdx = Section->BonesIdx[i];
                matrix4x4 arg4;
                /*
                v14 = (const math::VecClass__3_1 *)(v13 + LODWORD(a2[1]));
                v15 = (const math::MatClass__4_3 *)(v13 + LODWORD(a2[2]));
                v25 = (const math::VecClass__3_1 **)(v13 + LODWORD(a2[1]));
                v26 = (const math::MatClass__4_3 *)(v13 + LODWORD(a2[2]));
                sub_770EB0(&arg4, (float **)&v25);
                sub_414360((math::VecClass__3_1 *)&arg4.m.arr[3], v14 + 3, v15);
                */
                matrix4x3 v16 = sub_413770(&arg4);
                std::memcpy(&g_boneMatrices()[i], &v16, sizeof(v16));
            }
        }
        else if ( (meshParams->Flags & 0x10) == 0 )
        {
            for ( int i = 0; i < Section->NBones; ++i )
            {
                assert(i < MAX_BONES && "nglSetupVShaderBonesDX: too many bones ! Increase the MAX_BONES value.");

                auto boneIdx = Section->BonesIdx[i];
                matrix4x4 arg4 {};
                memcpy(&arg4, &meshParams->field_8[boneIdx], sizeof(arg4));

                
                matrix4x3 v20 = sub_413770(&arg4);
                std::memcpy(&g_boneMatrices()[i], &v20, sizeof(v20));
            }
        }
        else
        {
            for ( int i = 0; i < Section->NBones; ++i )
            {
                assert(i < MAX_BONES && "nglSetupVShaderBonesDX: too many bones ! Increase the MAX_BONES value.");

                bit_cast<matrix4x4 *>(&g_boneMatrices()[i])->sub_415740(nullptr);
            }
        }


        g_Direct3DDevice()->lpVtbl->SetVertexShaderConstantF(g_Direct3DDevice(), 0, &g_boneMatrices()[0][0].x, 3 * Section->NBones);
    }
    else
    {
        CDECL_CALL(0x00772810, a5, MeshNode, Section);
    }

    if constexpr (0) {
        matrix4x3 tmp;

        g_Direct3DDevice()->lpVtbl->GetVertexShaderConstantF(g_Direct3DDevice(),
                                                             11,
                                                             &tmp.arr[0].x,
                                                             3);

        sp_log("%s", tmp.to_string());
    }
}

void nglSetVertexDeclarationAndShader(VShader *a1) {
    TRACE("SetVertexDeclarationAndShader");

    g_Direct3DDevice()->lpVtbl->SetVertexDeclaration(g_Direct3DDevice(), a1->field_4);
    g_Direct3DDevice()->lpVtbl->SetVertexShader(g_Direct3DDevice(), a1->field_0);
}

void SetPixelShader(IDirect3DPixelShader9 **a1) {
    g_Direct3DDevice()->lpVtbl->SetPixelShader(g_Direct3DDevice(), *a1);
}

std::vector<DWORD> CompileVShader(const char *file_name, const D3DXMACRO *defines)
{
    ID3DXBuffer *pShader = nullptr;
    ID3DXBuffer *error_messages = nullptr;

    const char *profile = "vs_1_1";

    if (D3DXCompileShaderFromFile(file_name,
                                  defines,
                                  nullptr,
                                  "main",
                                  profile,
                                  D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
                                  &pShader,
                                  &error_messages,
                                  nullptr) != D3D_OK)
    {
        sp_log("%s",
               static_cast<const char *>(error_messages->lpVtbl->GetBufferPointer(error_messages)));

        error_messages->lpVtbl->Release(error_messages);
        assert(0);
    }

    auto buffer_size = pShader->lpVtbl->GetBufferSize(pShader);
    auto *buffer = pShader->lpVtbl->GetBufferPointer(pShader);

    //sp_log("buffer_size = %d", buffer_size);

    //std::unique_ptr<DWORD> out = new DWORD[buffer_size / 4];

    std::vector<DWORD> result(buffer_size / 4);
    std::memcpy(result.data(), buffer, buffer_size);

    pShader->lpVtbl->Release(pShader);
    if (error_messages != nullptr) {
        error_messages->lpVtbl->Release(error_messages);
    }

    return result;
}

const char *disassemble_shader(const DWORD *pShader) {
    ID3DXBuffer *pDisassembly;

    if (D3DXDisassembleShader(pShader, FALSE, nullptr, &pDisassembly) != D3D_OK) {
        assert(0);
    }

    auto *disBuf = (const char *) pDisassembly->lpVtbl->GetBufferPointer(pDisassembly);

    return disBuf;
}

void nglCreatePShader(IDirect3DPixelShader9 **a3, const char *SrcCode, ...) {
    assert(SrcCode != nullptr);

    static const char *NGL_PS_PRECODE = "ps.1.1\n";

    assert((strlen(SrcCode) + strlen(NGL_PS_PRECODE) + 1 < 4096) &&
           "String overflow in nglCreatePShader.");

    if constexpr (0) {
        char Dest[4096];

        va_list Args;
        va_start(Args, SrcCode);
        vsprintf(Dest, SrcCode, Args);

        char a1a[4096];
        strcpy(a1a, NGL_PS_PRECODE);
        auto v3 = strlen(Dest) + 1;

        char *v4 = a1a;
        v4 = v4 - 1;
        while (*++v4) {
            ;
        }

        std::memcpy(v4, Dest, v3);

        ID3DXBuffer *pShader = nullptr;
        if (D3DXAssembleShader(a1a, &a1a[strlen(a1a) + 1] - &a1a[1], 0, 0, 2u, &pShader, nullptr) !=
            D3D_OK) {
            sp_log("Cannot assemble pixel shader.\n");
            assert(0);
        }

        auto &v6 = g_Direct3DDevice()->lpVtbl;

        assert(pShader != nullptr);

        auto *v7 = static_cast<const DWORD *>(pShader->lpVtbl->GetBufferPointer(pShader));
        g_codes = v7;

        IDirect3DPixelShader9 *v2;
        v6->CreatePixelShader(g_Direct3DDevice(), v7, &v2);

        auto *v8 = g_pixelShaderList().m_head;
        auto *v9 = (decltype(v8)) THISCALL(0x00772C60,
                                           &g_pixelShaderList(),
                                           g_pixelShaderList().m_head,
                                           g_pixelShaderList().m_head->_Prev,
                                           a3);
        THISCALL(0x00772CE0, &g_pixelShaderList(), 1u);
        v8->_Prev = v9;
        v9->_Prev->_Next = v9;

        va_end(Args);
    } else {
        CDECL_CALL(0x007723A0, a3, SrcCode);
    }
}
