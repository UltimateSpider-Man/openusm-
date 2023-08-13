#pragma once

#include <cstdint>

#include "vector3d.h"
#include "float.hpp"

struct nglMeshSection;

struct nglVertexDef {
    struct IteratorBase {
        std::intptr_t m_vtbl;
    };

    std::intptr_t m_vtbl;
    nglMeshSection *field_4;

    /* virtual */ void Destroy();

};

struct nglVertexDef_Debug_Base {
    struct Iterator : nglVertexDef::IteratorBase {
        int field_4;
        int field_8;
    };
};

struct nglVertexDef_PCUV_Base {
    struct Iterator : nglVertexDef::IteratorBase {
        nglVertexDef *field_4;
        int field_8;
    };
};

struct nglMaterialBase;

template<typename T>
struct nglVertexDef_MultipassMesh : nglVertexDef {
    struct Iterator : T::Iterator {
        Iterator() = default;

        Iterator(const Iterator &iter);

        Iterator *Clone() {
            auto *mem = operator new(0xCu);

            auto *result = new (mem) Iterator{*this};

            return result;
        }

        void BeginStrip(uint32_t );

        void Write(vector3d a2, int color, Float a6, Float a7);

    };

    Iterator CreateIterator();

};

struct nglVertexDef_MultipassMesh_Base : nglVertexDef
{
    static void AddMeshSection(nglVertexDef *a1, nglMaterialBase *a2, int a3, int a4, int a5, const void *a6, unsigned int a7, int a8, bool a9);

};

extern nglVertexDef::IteratorBase *__fastcall nglVertexDef__GetIterator(void *self, int, nglVertexDef::IteratorBase *a1);

extern void ngl_vertexdef_patch(); 
