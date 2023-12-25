#include "layer_state_machine.h"

namespace als {

layer_state_machine::layer_state_machine()
{
    this->m_vtbl = 0x00881538;
}

void layer_state_machine::init(layer_state_machine_shared *shared_machine)
{
    assert(shared_portion == nullptr);
    assert(shared_machine != nullptr);

    this->shared_portion = shared_machine;
    this->field_14.m_active = false;
}

} // namespace als

