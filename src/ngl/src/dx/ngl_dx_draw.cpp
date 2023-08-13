#include "ngl_dx_draw.h"

#include <ngl.h>
#include <variables.h>

#include <cstdint>

static Var<int> g_MinVertexIndex{0x009729B0};

HRESULT sub_7719D0(D3DPRIMITIVETYPE PrimitiveType,
                   IDirect3DIndexBuffer9 *a2,
                   UINT startIndex,
                   UINT NumIndices,
                   UINT NumVertices) {
    //sp_log("sub_7719D0: %u", NumVertices);

    UINT primCount;

    static Var<IDirect3DIndexBuffer9 *> dword_972968{0x00972968};

    if (a2 != dword_972968()) {
        g_Direct3DDevice()->lpVtbl->SetIndices(g_Direct3DDevice(), a2);
        dword_972968() = a2;
    }

    switch (PrimitiveType) {
    case D3DPT_POINTLIST:
        primCount = NumIndices;
        break;
    case D3DPT_LINELIST:
        primCount = NumIndices >> 1;
        break;
    case D3DPT_LINESTRIP:
        primCount = NumIndices - 1;
        break;
    case D3DPT_TRIANGLELIST:
        primCount = NumIndices / 3;
        break;
    case D3DPT_TRIANGLESTRIP:
    case D3DPT_TRIANGLEFAN:
        primCount = NumIndices - 2;
        break;
    default:
        primCount = 0;
        break;
    }
    return g_Direct3DDevice()->lpVtbl->DrawIndexedPrimitive(g_Direct3DDevice(),
                                                            PrimitiveType,
                                                            0,
                                                            g_MinVertexIndex(),
                                                            NumVertices,
                                                            startIndex,
                                                            primCount);
}

HRESULT sub_771A70(D3DPRIMITIVETYPE PrimitiveType, int a2, UINT a3) {
    UINT v3;

    switch (PrimitiveType) {
    case D3DPT_POINTLIST:
        v3 = a3;
        break;
    case D3DPT_LINELIST:
        v3 = a3 >> 1;
        break;
    case D3DPT_LINESTRIP:
        v3 = a3 - 1;
        break;
    case D3DPT_TRIANGLELIST:
        v3 = a3 / 3;
        break;
    case D3DPT_TRIANGLESTRIP:
    case D3DPT_TRIANGLEFAN:
        v3 = a3 - 2;
        break;
    default:
        v3 = 0;
        break;
    }

    return g_Direct3DDevice()->lpVtbl->DrawPrimitive(g_Direct3DDevice(),
                                                     PrimitiveType,
                                                     a2 + g_MinVertexIndex(),
                                                     v3);
}

HRESULT SetStreamSourceAndDrawPrimitive(nglMeshSection *MeshSection) {
    uint32_t stride = MeshSection->m_stride;
    g_MinVertexIndex() = MeshSection->field_4C / stride;
    g_Direct3DDevice()->lpVtbl->SetStreamSource(g_Direct3DDevice(),
                                                0,
                                                MeshSection->m_vertexBuffer,
                                                0,
                                                stride);

    Var<IDirect3DVertexBuffer9 *> dword_972964{0x00972964};

    dword_972964() = MeshSection->m_vertexBuffer;

    HRESULT result;

    auto numIndices = MeshSection->NIndices;
    if (numIndices != 0)
    {
        result = sub_7719D0(MeshSection->m_primitiveType,
                            MeshSection->m_indexBuffer,
                            MeshSection->field_58,
                            numIndices,
                            MeshSection->NVertices);
    } else {
        result = sub_771A70(MeshSection->m_primitiveType, 0, MeshSection->NVertices);
    }

    return result;
}

