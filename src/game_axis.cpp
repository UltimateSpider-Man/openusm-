#include "game_axis.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(game_axis, 0x30);

game_axis::game_axis() {}

void game_axis::update(Float a2) {
    THISCALL(0x0051D900, this, a2);
}
