#include "event.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(event, 0xC);

event::event(string_hash a2) {
    THISCALL(0x0048ABA0, this, a2);
}
