#include "trigger.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "vtbl.h"

VALIDATE_SIZE(trigger, 0x58);

trigger::trigger(string_hash a2) : signaller(true) {
    TRACE("trigger::trigger");

    this->m_vtbl = 0x008887F8;
    this->set_flag_recursive(static_cast<entity_flag_t>(0x2000), true);
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

bool trigger::is_point_trigger() const
{
    bool (__fastcall *func)(const void *) = CAST(func, get_vfunc(m_vtbl, 0x170));
    return func(this);
}

bool trigger::is_box_trigger() const
{
    bool (__fastcall *func)(const void *) = CAST(func, get_vfunc(m_vtbl, 0x174));
    return func(this);
}

bool trigger::is_entity_trigger() const
{
    bool (__fastcall *func)(const void *) = CAST(func, get_vfunc(m_vtbl, 0x178));
    return func(this);
}
