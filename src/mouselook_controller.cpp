#include "mouselook_controller.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(mouselook_controller, 0x18u);

Var<mouselook_controller *> g_mouselook_controller{0x0095C17C};

mouselook_controller::mouselook_controller()
{

}

void mouselook_controller::frame_advance(Float a2) {
    THISCALL(0x00528BB0, this, a2);
}
