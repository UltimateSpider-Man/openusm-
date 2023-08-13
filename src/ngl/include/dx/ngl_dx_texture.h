#pragma once

#include <cstdint>

#include <windows.h>

#include <d3d9types.h>

struct nglTexture;

//0x007754B0
extern void nglDxSetTexture(uint32_t a1, nglTexture *Tex, uint8_t a3, int a4);

//0x0076DC30
extern void SetSamplerState(DWORD sampler, D3DSAMPLERSTATETYPE type, DWORD value);

//0x0076DC70
extern void SetTextureStageState(DWORD a1, D3DTEXTURESTAGESTATETYPE a2, DWORD a3);
