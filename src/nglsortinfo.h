#pragma once

inline constexpr auto NGLSORT_OPAQUE = 0;
inline constexpr auto NGLSORT_TRANS = 1;

struct nglSortInfo {
    int Type;
    float field_4;

    nglSortInfo();
};
