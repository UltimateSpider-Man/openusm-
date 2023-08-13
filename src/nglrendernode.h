#pragma once

#include <cstdint>

struct nglSortInfo;

struct nglRenderNode {
    std::intptr_t m_vtbl;
    nglRenderNode *field_4;
    int field_8;

    /* virtual */ void Render() /* = 0 */;

    /* virtual */ void GetSortInfo(nglSortInfo &) {}

    /* virtual */ ~nglRenderNode() = default;
};
