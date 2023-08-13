#include "wds_script_manager.h"

#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

int wds_script_manager::hook_up_global_script_object()
{
    TRACE("wds_script_manager::hook_up_global_script_object");
    return THISCALL(0x0054B7E0, this);
}

void wds_script_manager_patch()
{
    FUNC_ADDRESS(address, &wds_script_manager::hook_up_global_script_object);
    REDIRECT(0x0055CC79, address);
}
