#include "ngl_dx_scene.h"

#include "ngl.h"
#include "nglrendernode.h"
#include "nglshader.h"

#include <func_wrapper.h>
#include <trace.h>
#include <utility.h>
#include <vtbl.h>

namespace nglRenderList {

void sub_77DFB0(void *begin, void *end, int a3, int a4) {
    CDECL_CALL(0x0077DFB0, begin, end, a3, a4);
}

template<>
void nglOpaqueCompare<nglRenderNode>(nglRenderNode *node, int count, int a3)
{
    TRACE("nglRenderList::nglOpaqueCompare<nglRenderNode>");

    if constexpr (1) {
        struct {
            nglRenderNode *field_0;
            nglTexture *field_4;
        } *list = static_cast<decltype(list)>(nglListAlloc(8 * count, 16));

        auto sub_FE1420 = [](auto *a1, nglRenderNode *a2) -> void {
            while (a2) {
                a1->field_0 = a2;
                a1->field_4 = a2->field_8;
                ++a1;
                a2 = a2->field_4;
            }
        };

        sub_FE1420(list, node);

        sub_77DFB0(list, list + 8 * count, (8 * count) >> 3, a3);

        auto sub_FE1480 = [](auto *begin, nglRenderNode *&a2, int count) -> void {
            auto end = begin + count;

            nglRenderNode *v3 = nullptr;
            std::for_each(
                    std::make_reverse_iterator(end),
                    std::make_reverse_iterator(begin),
                    [&v3](auto &n) {
                        n.field_0->field_4 = v3;
                        v3 = n.field_0;
                    });

            a2 = v3;
        };

        sub_FE1480(list, node, count);

        static Var<nglRenderNode *> nglPrevNode{0x00971F18};

        for ( auto *v9 = node; v9 != nullptr; v9 = v9->field_4 ) {
            v9->Render();

            nglPrevNode() = v9;
        }
    } else {
        CDECL_CALL(0x0077E190, node, count, a3);
    }
}

} // namespace nglRenderList

void *nglListAlloc(int size, int align) {
    TRACE("nglListAlloc");

    if constexpr (0) {
        auto *v3 = (uint8_t *) (~(align - 1) & ((int) nglListWorkPos() + align - 1));

        nglListWorkPos() = &v3[size];
        void *result = v3;

        return result;
    } else {
        return (void *) CDECL_CALL(0x00401A20, size, align);
    }
}

void nglRenderList_patch() {
    auto *address = &nglRenderList::nglOpaqueCompare<nglRenderNode>;

    REDIRECT(0x0077D162, address);
}
