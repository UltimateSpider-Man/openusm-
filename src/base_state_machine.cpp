#include "base_state_machine.h"

#include "als_state.h"
#include "func_wrapper.h"
#include "state_machine_shared.h"

namespace als {

base_state_machine::base_state_machine()
{

}

void base_state_machine::init(state_machine_shared *shared_machine)
{
    THISCALL(0x004995D0, this, shared_machine);
}

bool base_state_machine::is_curr_state_biped_physics() const
{
    return this->m_curr_state != nullptr
            && this->m_curr_state->is_flag_set(static_cast<state_flags>(0x800));
}

} // namespace als
