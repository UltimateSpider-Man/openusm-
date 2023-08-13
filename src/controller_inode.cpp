#include "controller_inode.h"

#include "common.h"
#include "func_wrapper.h"
#include "vtbl.h"

namespace ai {

controller_inode::controller_inode() {}

bool controller_inode::is_axis_neutral(controller_inode::eControllerAxis a2) {
    return THISCALL(0x00445CB0, this, a2);
}

vector3d controller_inode::get_axis(controller_inode::eControllerAxis a3) {
    auto &func = get_vfunc(m_vtbl, 0x50);

    vector3d result;
    func(this, &result, a3);

    return result;
}

game_button controller_inode::get_button(controller_inode::eControllerButton a3) {
    auto &func = get_vfunc(m_vtbl, 0x58);

    game_button result;
    func(this, &result, a3);

    return result;
}

} // namespace ai
