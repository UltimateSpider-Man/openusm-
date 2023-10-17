#include "trigger.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"

VALIDATE_SIZE(trigger, 0x58);

trigger::trigger(string_hash a2) : signaller(true) {
    TRACE("trigger::trigger");

    this->m_vtbl = 0x008887F8;
    this->set_flag_recursive(entity_flag_t{0x2000}, true);
    assert(my_rel_po == nullptr);

    assert(my_abs_po == nullptr);

    assert(adopted_children == nullptr);

    assert(my_conglom_root == nullptr);

    this->field_10 = a2;
    this->field_48 = 0.0;
    this->m_next_trigger = nullptr;
    this->trigger_current_entities = nullptr;
    this->field_4C = 0;
}

trigger::~trigger() {
    THISCALL(0x0056FE50, this);
}

void trigger::set_multiple_entrance(bool a2) {
    THISCALL(0x0053C390, this, a2);
}
