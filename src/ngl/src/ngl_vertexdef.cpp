#include "ngl_vertexdef.h"

#include "common.h"
#include "func_wrapper.h"
#include "ngl.h"
#include "ngl_dx_vertexdef.h"
#include "trace.h"
#include "vector4d.h"
#include "vtbl.h"

using def_t = nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>;
using iterator_type = typename nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::Iterator;

VALIDATE_SIZE(def_t, 0x8);
VALIDATE_SIZE(iterator_type, 0xC);

void nglVertexDef::Destroy() {
    auto &func = get_vfunc(m_vtbl, 0xC);
    func(this);
}

template<>
nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::Iterator::Iterator(
    const nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::Iterator &iter) {
    THISCALL(0x004121E0, this, &iter);
}

template<>
nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::Iterator nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::CreateIterator()
{
    TRACE("nglVertexDef::CreateIterator");

    Iterator result;
    THISCALL(0x00413C60, this, &result);

    return result;
}

template<>
void nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::Iterator::BeginStrip(uint32_t nVerts)
{
    sub_40FD50(nVerts, 0x18);
}

template<>
void nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::Iterator::Write(vector3d a2, int color, Float a6, Float a7)
{
    TRACE("nglVertexDef::Iterator::Write");

    if constexpr (1)
    {
        struct {
            int field_0;
            nglVertexDef *field_4;
            int field_8;
        } *self = CAST(self, this);

        struct {
            vector3d field_0;
            float field_C;
            float field_10;
            int field_14;
        } *v5 = CAST(v5, &static_cast<char *>(self->field_4->field_4->m_vertices)[sizeof(*v5) * self->field_8 + self->field_4->field_4->field_4C]);
        v5->field_0 = a2;
        v5->field_C = a6;
        v5->field_10 = a7;
        v5->field_14 = color;
    }
    else
    {
        THISCALL(0x00501EE0, this, a2, color, a6, a7);
    }
}


void nglVertexDef_MultipassMesh_Base::AddMeshSection(nglVertexDef *a1, nglMaterialBase *a2, int a3, int a4, int a5, const void *a6, unsigned int a7, int a8, bool a9)
{
    TRACE("nglVertexDef_MultipassMesh_Base::AddMeshSection");

    CDECL_CALL(0x00771D10, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

nglVertexDef::IteratorBase *__fastcall nglVertexDef__GetIterator(void *self, int, nglVertexDef::IteratorBase *a1)
{
    TRACE("nglVertexDef::GetIterator");

    THISCALL(0x00412460, self, a1, 0);
    return a1;
}

void sub_733030(nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::Iterator *iter, const vector4d &a2, const vector4d &a3, const vector4d &a4, const vector4d &a5, int a6, int p_color)
{
    TRACE("sub_733030");

    sub_40FD50(4u, 24u);
    auto v7 = iter->field_4->field_4;
    auto v8 = a2[3];
    auto v10 = v7->field_4C + 0x18 * iter->field_8;
    struct VertexData {
        char field_0[4];
        char field_4[4];
        char field_8[4];
        char field_C[4];
        char field_10[4];
        char field_14[4];
    };

    VALIDATE_SIZE(VertexData, 0x18);

    auto *v11 = bit_cast<VertexData*>(v7->m_vertices);

    *(float *)&v11->field_0[v10] = a2[0];
    *(float *)&v11->field_4[v10] = a2[1];
    *(float *)&v11->field_C[v10] = a2[2];
    *(DWORD *)&v11->field_8[v10] = a6;
    *(float *)&v11->field_10[v10] = v8;
    *(DWORD *)&v11->field_14[v10] = p_color;
    ++iter->field_8;
    auto v14 = iter->field_8;
    v14 *= 3;

    auto *v13 = iter->field_4;
    VertexData *v18 = CAST(v18, static_cast<char *>(v13->field_4->m_vertices) + v13->field_4->field_4C);

    *(float *)&v18->field_0[8 * v14] = a3[0];
    *(float *)&v18->field_4[8 * v14] = a3[1];
    *(float *)&v18->field_C[8 * v14] = a3[2];
    *(DWORD *)&v18->field_8[8 * v14] = a6;
    *(float *)&v18->field_10[8 * v14] = a3[3];
    *(DWORD *)&v18->field_14[8 * v14] = p_color;

    ++iter->field_8;

    auto *v19 = iter->field_4;
    int v20 = iter->field_8;
    VertexData *v24 = CAST(v24, static_cast<char *>(v19->field_4->m_vertices) + 0x18 * v20 + v19->field_4->field_4C);

    *(float *)v24->field_0 = a4[0];
    *(float *)v24->field_4 = a4[1];
    *(float *)v24->field_C = a4[2];
    *(DWORD *)v24->field_8 = a6;
    *(float *)v24->field_10 = a4[3];
    *(DWORD *)v24->field_14 = p_color;

    ++iter->field_8;

    auto v25 = iter->field_8;
    VertexData *v29 = CAST(v29, static_cast<char *>(iter->field_4->field_4->m_vertices) + 0x18 * v25 + iter->field_4->field_4->field_4C);

    *(float *)v29->field_0 = a5[0];
    *(float *)v29->field_4 = a5[1];
    *(float *)v29->field_C = a5[2];
    *(DWORD *)v29->field_8 = a6;
    *(float *)v29->field_10 = a5[3];
    *(DWORD *)v29->field_14 = p_color;
    ++iter->field_8;
}

void ngl_vertexdef_patch()
{
    {
        REDIRECT(0x00507962, nglVertexDef_MultipassMesh_Base::AddMeshSection);
    }

    SET_JUMP(0x00733030, sub_733030);

    {
        SET_JUMP(0x00413C60, nglVertexDef__GetIterator);
    }

    {
        FUNC_ADDRESS(address, &nglVertexDef_MultipassMesh<nglVertexDef_PCUV_Base>::Iterator::Write);
        SET_JUMP(0x00501EE0, address);
    }
}
