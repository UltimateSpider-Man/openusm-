#include "spawnable.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

VALIDATE_SIZE(spawnable, 0x8);

void spawnable::advance_traffic_and_peds(Float a1) {
    TRACE("spawnable::advance_traffic_and_peds");

    CDECL_CALL(0x006D8610, a1);
}

void spawnable_patch() {
    {
        REDIRECT(0x0055842F, spawnable::advance_traffic_and_peds);
    }
}
