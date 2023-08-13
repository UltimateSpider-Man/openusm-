#include "ai_tentacle_dangle.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(ai_tentacle_dangle, 0x24);

ai_tentacle_dangle::ai_tentacle_dangle(ai_tentacle_info *a2) {
    THISCALL(0x00470B70, this, a2);
}
