#pragma once

#include <cstdint>

#include <hashstring.h>

struct nalBaseSkeleton {
    std::intptr_t m_vtbl;
    char field_4[0x24];
    tlHashString field_28;
};

//0x0078DC80
extern void *nalConstructSkeleton(void *a1);
