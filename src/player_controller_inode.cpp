#include "player_controller_inode.h"

#include "common.h"

#include "actor.h"
#include "ai_player_controller.h"
#include "from_mash_in_place_constructor.h"
#include "func_wrapper.h"

namespace ai {

VALIDATE_SIZE(player_controller_inode, 0xEC);

player_controller_inode::player_controller_inode(from_mash_in_place_constructor *a2) {
    THISCALL(0x004813F0, this, a2);
}

game_button player_controller_inode::get_button(controller_inode::eControllerButton a3) {
    game_button result;

    auto v3 = this->field_C->m_player_controller;
    switch (a3.field_0) {
    case 0:
    case 7:
        result = v3->gb_jump;
        break;
    case 1:
    case 8:

        result = v3->gb_grab;
        break;
    case 2:
    case 9:

        result = v3->gb_attack;
        break;
    case 3:
    case 10:

        result = v3->gb_attack_secondary;
        break;
    case 4:
    case 15:

        result = v3->gb_range;
        break;
    case 5:
    case 11:
    case 12: {
        result = v3->field_1B8;
        break;
    }
    case 13:

        result = v3->field_4C;

        break;
    case 14:
        result = {};
        break;
    case 16:

        result = v3->field_254;
        break;
    case 17:

        result = v3->field_288;

        break;
    default:

        result = {};

        break;
    }

    return result;
}

} // namespace ai
