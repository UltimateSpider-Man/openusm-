#include "nglrendernode.h"

#include "common.h"
#include "vtbl.h"

VALIDATE_SIZE(nglRenderNode, 0xC);

void nglRenderNode::Render()
{
    void (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x0));
    func(this);
}
