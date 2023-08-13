#include "wds_ai_manager.h"

#include "func_wrapper.h"
#include "resource_key.h"

#include <cassert>

wds_ai_manager::wds_ai_manager()
{

}

path_graph *wds_ai_manager::get_path_graph(const resource_key &id) {
    assert(id.get_type() == RESOURCE_KEY_TYPE_PATH);

    return (path_graph *) THISCALL(0x0053CE80, this, &id);
}

void wds_ai_manager::add_path_graph(path_graph *pg) {
    assert(pg != nullptr);

    THISCALL(0x00537330, this, pg);
}
