#include "igofrontend.h"

#include "common.h"
#include "entity_tracker_manager.h"
#include "fe_mini_map_widget.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

VALIDATE_SIZE(IGOFrontEnd, 0x58);
VALIDATE_OFFSET(IGOFrontEnd, field_44, 0x44);

IGOFrontEnd::IGOFrontEnd()
{
    THISCALL(0x00648B40, this);
}

void IGOFrontEnd::Draw() {
    if constexpr(0)
    {

    }
    else
    {
        THISCALL(0x006358F0, this);
    }
}

void IGOFrontEnd::Init() {
    TRACE("IGOFrontEnd::Init");

    THISCALL(0x00647DE0, this);
}

void IGOFrontEnd::Update(Float a2) {
    THISCALL(0x00641600, this, a2);
}

void IGOFrontEnd::CheckPauseUnpause() {
    THISCALL(0x00629F80, this);
}

void IGOFrontEnd_patch()
{
    {
        FUNC_ADDRESS(address, &IGOFrontEnd::Init);
        REDIRECT(0x00649085, address);
    }
}
