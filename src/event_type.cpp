#include "event_type.h"
#include "common.h"
#include "event_recipient_entry.h"
#include "func_wrapper.h"

VALIDATE_SIZE(event_type, 0x2C);

event_type::event_type(string_hash a2, bool a3) {
    THISCALL(0x004E18B0, this, a2, a3);
}

event_recipient_entry *event_type::create_recipient_entry(entity_base_vhandle a2) {
    return (event_recipient_entry *) THISCALL(0x004EE620, this, a2);
}

void event_type::raise_event(entity_base_vhandle a2, event *a3) {
    THISCALL(0x004EE6C0, this, a2, a3);
}
