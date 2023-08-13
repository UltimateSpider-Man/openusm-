#include "worldly_resource_handler.h"

#include "common.h"
#include "vtbl.h"

VALIDATE_SIZE(worldly_resource_handler, 0x10);

bool worldly_resource_handler::handle(eBehavior behavior, limited_timer *a5) {
    bool (__fastcall *func)(void *, int, eBehavior, limited_timer *) =
        CAST(func, get_vfunc(m_vtbl, 0x4));

    return func(this, 0, behavior, a5);
}
