#include "script_controller.h"

#include "common.h"
#include "entity.h"
#include "fe_controller_disconnect.h"
#include "femanager.h"
#include "func_wrapper.h"
#include "game.h"
#include "input_mgr.h"
#include "log.h"
#include "pausemenusystem.h"
#include "trace.h"
#include "utility.h"

Var<script_controller *> script_pad{0x0096BB40};

VALIDATE_SIZE(script_controller, 0x48);

script_controller::script_controller() : signaller(false) {
    
}

void script_controller::update()
{
    TRACE("script_controller::update");

    if constexpr (0)
    {}
    else
    {
        THISCALL(0x0065F8A0, this);
    }
}

void script_controller_patch()
{
    {
        FUNC_ADDRESS(address, &script_controller::update);
        set_vfunc(0x0089BD50 + 0x168, address);
    }
}
