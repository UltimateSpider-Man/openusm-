#include "anim_handle.h"

#include "nal_system.h"
#include "trace.h"
#include "utility.h"
#include "wds.h"

nal_anim_control *anim_handle_t::get_anim()
{
    TRACE("anim_handle_t::get_anim");

    auto *result = g_world_ptr->get_anim_ctrl(this->field_0);
    sp_log("0x%08X", result->m_vtbl);

    return result;
}

void anim_handle_patch()
{
    FUNC_ADDRESS(address, &anim_handle_t::get_anim);
    SET_JUMP(0x00492440, address);
}
