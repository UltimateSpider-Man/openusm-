#include "spawnable.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(spawnable, 0x8);

void spawnable::advance_traffic_and_peds(Float a1) {
    CDECL_CALL(0x006D8610, a1);
}
