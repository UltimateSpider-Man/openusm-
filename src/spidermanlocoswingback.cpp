#include "spidermanlocoswingback.h"

#include "common.h"
#include "func_wrapper.h"

namespace ai {

VALIDATE_SIZE(SpidermanLocoSwingBack, 0x10);

SpidermanLocoSwingBack::SpidermanLocoSwingBack() {
    THISCALL(0x0045D2C0, this);
}

SpidermanLocoSwingBack::~SpidermanLocoSwingBack() {
    THISCALL(0x00438EC0, this);
}

} // namespace ai
