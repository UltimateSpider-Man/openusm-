#pragma once

#include <cstdint>

struct color {
    float r, g, b, a;

    void * operator new(size_t );
};
