#pragma once

#include "vector4d.h"

#include <cstdio>

struct matrix4x3 {
    vector4d arr[3];

    matrix4x3() = default;

    auto &operator[](int idx) {
        return arr[idx];
    }

    const auto &operator[](int idx) const {
        return arr[idx];
    }

    const char *to_string() {
        static char str[150];

        sprintf(str,
                "mat4x3{%s, %s, %s}",
                arr[0].to_string().c_str(),
                arr[1].to_string().c_str(),
                arr[2].to_string().c_str());

        return str;
    }
};
