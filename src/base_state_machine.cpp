#include "base_state_machine.h"

#include "func_wrapper.h"
#include "state_machine_shared.h"

namespace als {

base_state_machine::base_state_machine()
{

}

void base_state_machine::init(state_machine_shared *a2) {
    THISCALL(0x004995D0, this, a2);
}

} // namespace als
