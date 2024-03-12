#pragma once

#include <cstdint>

struct nglSortInfo;
struct nglTexture;

struct nglRenderNode {
    std::intptr_t m_vtbl;
    nglRenderNode *m_next_node;
    nglTexture *m_tex;

    /* virtual */ void Render() /* = 0 */;

    /* virtual */
    void GetSortInfo(nglSortInfo &);

    /* virtual */ ~nglRenderNode() = default;
};
