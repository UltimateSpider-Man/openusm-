#pragma once

#include <cstdint>

struct BaseComponent;

namespace nalComp {

struct nalCompSkeleton {
    std::intptr_t m_vtbl;
    int Version;
    char field_8[0x5C];

    int m_iNumComponents;
    int field_68;
    int field_6C;
    char *field_70;
    char *field_74;
    int field_78;

    void UnMash(void *a2, BaseComponent **a3, unsigned int iNumComponents);
};

struct nalCompPose {
    std::intptr_t m_vtbl;
    const nalCompSkeleton *field_4;
    void *field_8;
    int field_C;

    nalCompPose(const nalCompSkeleton *);
};

} // namespace nalComp
