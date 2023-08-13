#include "ngl_dx_vertexdef.h"

#include "func_wrapper.h"
#include "ngl.h"
#include "trace.h"
#include "variable.h"

static Var<nglMeshSection *> dword_972A10 {0x00972A10};

void sub_40FD00(int16_t *a1, unsigned int a2, int16_t a3)
{
    for ( auto i = 0u; i < a2; ++nglScratchBuffer().field_30 )
    {
        a1[nglScratchBuffer().field_30] = a3 + (i++);
    }
}


void sub_40FD50(int nVerts, unsigned int a2)
{
    TRACE("nglVertexDef::Iterator::BeginStrip");

    assert(nVerts > 2 && "BeginStrip: a strip must have at least 3 vertices !");

    if constexpr (1)
    {
        auto *v2 = nglScratchBuffer().field_20;
        auto IndexCount = nVerts;
        auto v4 = dword_972A10()->NVertices + nglScratchBuffer().field_2C / a2;
        if ( dword_972A10()->NIndices != 0 )
        {
            auto v5 = (nglScratchBuffer().field_24 & 1) == 0;
            IndexCount = nVerts + 2;
            if ( (nglScratchBuffer().field_24 & 1) != 0 )
            {
                IndexCount = nVerts + 3;
            }

            nglScratchBuffer().field_20[nglScratchBuffer().field_30] = nglScratchBuffer().field_20[nglScratchBuffer().field_30 - 1];
            v2[++nglScratchBuffer().field_30] = v4;
            auto v6 = ++nglScratchBuffer().field_30;
            if ( !v5 )
            {
                v2[v6] = v4;
                ++nglScratchBuffer().field_30;
            }
        }

        sub_40FD00(v2, nVerts, v4);
        nglScratchBuffer().field_24 = nVerts;
        dword_972A10()->NIndices += IndexCount;
        dword_972A10()->NVertices += nVerts;
    }
    else
    {
        CDECL_CALL(0x0040FD50, nVerts, a2);
    }
}
