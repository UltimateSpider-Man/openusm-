#pragma once

#include <variable.h>

#include <d3d9.h>

#include <vector>

struct nglMeshNode;
struct nglMeshSection;

struct VShader {
    IDirect3DVertexShader9 *field_0;
    IDirect3DVertexDeclaration9 *field_4;
};

extern Var<IDirect3DVertexDeclaration9 *[1]> dword_9738E0;

extern void log_codes(const DWORD *code);

//0x00772270
extern void SetVertexDeclarationAndShader(VShader *a1);

//0x00772250
extern void SetPixelShader(IDirect3DPixelShader9 **a1);

//0x00772550
extern void nglCreateVShader(
    const D3DVERTEXELEMENT9 *a2, void *a1, [[maybe_unused]] BOOL a3, const char *SrcCode, ...);

extern void nglCreatePShader(IDirect3DPixelShader9 **a3, const char *SrcCode, ...);

//0x00772500
extern int CreatePixelShader(IDirect3DPixelShader9 **a1, const DWORD *a2);

//0x007724A0
extern void CreateVertexDeclarationAndShader(void *a1, const D3DVERTEXELEMENT9 *a2, const DWORD *a3);

extern int size_codes(const DWORD *code);

extern bool compare_codes(const DWORD *code0, const DWORD *code1, int size);

extern std::vector<DWORD> CompilePShader(const char *file_name);

struct _D3DXMACRO;
using D3DXMACRO = struct _D3DXMACRO;

extern std::vector<DWORD> CompileVShader(const char *file_name, const D3DXMACRO *defines = nullptr);

extern const char *disassemble_shader(const DWORD *pShader);

extern const DWORD *AssemblePShader(const char *text);

//0x00772810
extern HRESULT nglSetupVShaderBonesDX(int a5, nglMeshNode *a6, nglMeshSection *Section);

extern const DWORD *g_codes;
