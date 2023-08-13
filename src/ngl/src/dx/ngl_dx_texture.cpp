#include "ngl_dx_texture.h"

#include "func_wrapper.h"
#include "variable.h"
#include "variables.h"
#include "trace.h"

#include <ngl.h>

#include <cassert>

void sub_782AC0(int, nglPalette *a2) {
    if (!g_valid_texture_format()) {
        g_Direct3DDevice()->lpVtbl->SetCurrentTexturePalette(g_Direct3DDevice(), a2->m_palette_idx);
    }
}

void nglDxSetTexture(uint32_t a1, nglTexture *Tex, uint8_t a3, int a4)
{
    TRACE("nglDxSetTexture");

    if constexpr (0)
    {
        assert(Tex != nullptr && "NULL texture pointer.");

        auto *v4 = Tex;
        auto *v5 = Tex;
        if (static_cast<uint8_t>(Tex->m_format) == 16) {
            auto v6 = Tex->m_num_palettes;

            unsigned int v7;
            if (nglTextureAnimFrame() < v6) {
                v7 = nglTextureAnimFrame();
            } else {
                v7 = nglTextureAnimFrame() % v6;
            }

            v5 = Tex->field_5C[v7];
        }

        assert(v5 != nullptr && "encountered invalid IFL data.\n");

        auto *palette = v5->field_48;
        auto *v16 = palette;
        if (static_cast<uint8_t>(v5->m_format) == 17) {
            v5 = (nglTexture *) v5->m_num_palettes;
        }

        auto v9 = a1;
        auto *v10 = v5->DXTexture;
        v5->field_38 = nglFrame();

        struct {
            IDirect3DTexture9 *field_0[1];
        } tmp;

        static Var<decltype(tmp)> stru_93BD50{0x0093BD50};

        if (stru_93BD50().field_0[a1] != v10) {
            g_Direct3DDevice()->lpVtbl->SetTexture(g_Direct3DDevice(),
                                                   a1,
                                                   (IDirect3DBaseTexture9 *) v10);
            stru_93BD50().field_0[a1] = v5->DXTexture;
        }

        if (palette != nullptr) {
            if (g_valid_texture_format() && (Tex->field_34 & 8) != 0 &&
                static_cast<uint8_t>(v5->m_format) == 7) {
                if (v5->m_num_palettes) {
                    uint32_t v11 = 0;
                    int v12 = 0;
                    do {
                        v5->field_5C[v12 + 13] = (nglTexture *) ((int) v5->field_5C[v12 + 13] | 8);
                        ++v11;
                        v12 += 32;
                    } while (v11 < v5->m_num_palettes);
                }

                v5->DXTexture->lpVtbl->LockRect(v5->DXTexture, 0, &v5->field_24, 0, 0);
                auto *v17 = (char *) v5->field_24.pBits;
                for (int i = 0; i < v5->m_height; ++i) {
                    auto *v14 = (uint32_t *) &v17[i * v5->field_24.Pitch];
                    uint32_t v15 = 0;
                    if (v5->m_width) {
                        auto BYTE2 = [](uint32_t &v) -> uint8_t {
                            auto result = bit_cast<uint8_t *>(&v)[2];
                            return result;
                        };

                        do {
                            v14[v15] = *(uint32_t *) &v16
                                            ->m_palette_entries[v5->field_30[i * v5->m_width + v15]] &
                                    0xFF00FF00 |
                                ((uint8_t) *
                                     (uint32_t *) &v16
                                         ->m_palette_entries[v5->field_30[i * v5->m_width + v15]]
                                 << 16) |
                                (uint8_t) BYTE2(
                                    *(uint32_t *) &v16
                                         ->m_palette_entries[v5->field_30[i * v5->m_width + v15]]);
                            ++v15;
                        } while (v15 < v5->m_width);
                        v4 = Tex;
                        v9 = a1;
                    }
                }

                v5->DXTexture->lpVtbl->UnlockRect(v5->DXTexture, 0);
                palette = v16;
                v4->field_34 &= 0xFFFFFFF7;
            }

            sub_782AC0(v9, palette);
        }

        THISCALL(0x00401E00, &stru_93BD50(), v9, a3, a4);
    } else {
        CDECL_CALL(0x007754B0, a1, Tex, a3, a4);
    }
}

void SetSamplerState(DWORD sampler, D3DSAMPLERSTATETYPE type, DWORD value) {
    if constexpr (1) {
        auto result = type + 14 * sampler;
        auto *v4 = (DWORD *) (4 * result + 0x971FF0);

        static Var<uint32_t[1]> dword_971FF0{0x00971FF0};
        if (dword_971FF0()[result] != value) {
            result = g_Direct3DDevice()->lpVtbl->SetSamplerState(g_Direct3DDevice(),
                                                                 sampler,
                                                                 type,
                                                                 value);
            *v4 = value;
        }

    } else {
        CDECL_CALL(0x0076DC30, sampler, type, value);
    }
}

void SetTextureStageState(DWORD a1, D3DTEXTURESTAGESTATETYPE a2, DWORD a3) {
    uint32_t v3 = a2 + 33 * a1;
    auto *v4 = (DWORD *) (4 * v3 + 0x972240);

    static Var<DWORD[264]> dword_972240{0x00972240};

    if (dword_972240()[v3] != a3) {
        g_Direct3DDevice()->lpVtbl->SetTextureStageState(g_Direct3DDevice(), a1, a2, a3);
        *v4 = a3;
    }
}

void ngl_dx_texture_patch()
{
    
}
