#include "tentacle_interface.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"

VALIDATE_SIZE(tentacle_interface, 0x38);

void tentacle_interface::initialize_polytubes()
{
    TRACE("tentacle_interface::initialize_polytubes");

    THISCALL(0x004E0460, this);
}
