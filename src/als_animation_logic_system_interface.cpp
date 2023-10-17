#include "als_animation_logic_system_interface.h"

#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

namespace als {
void animation_logic_system_interface::frame_advance_pre_controller_all_alses(Float a1)
{
    TRACE("als::animation_logic_system_interface::frame_advance_pre_controller_all_alses");

    CDECL_CALL(0x0049ED90, a1);
}

void animation_logic_system_interface::force_update(Float a2) {
#if 0
    if ( this->m_vtbl->frame_advance_should_do_frame_advance(this, a2) || a2 == EPSILON )
    {
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_main_als_advance)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_post_request_processing)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_on_layer_trans)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_post_logic_processing)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_play_new_animations)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_update_pending_params)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_change_mocomp)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_run_mocomp_pre_anim)(
            this,
            LODWORD(a2));
        ((void (__thiscall *)(als::animation_logic_system *, _DWORD))this->m_vtbl->frame_advance_controller)(
            this,
            LODWORD(a2));
        this->m_vtbl->frame_advance_post_controller(this, a2);
    }
#endif
}

}

void als_animation_logic_system_interface_patch() {
    REDIRECT(0x00537181, als::animation_logic_system_interface::frame_advance_pre_controller_all_alses);

    {
        //SET_JUMP(0x00492FC0, als::animation_logic_system_interface::force_update);
    }
}

