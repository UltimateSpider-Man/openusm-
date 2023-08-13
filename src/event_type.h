#pragma once

#include "entity_base_vhandle.h"
#include "string_hash.h"

struct event_recipient_entry;
struct event;

struct event_type {
    string_hash field_0;
    event *event_to_raise;
    int field_8[8];

    bool field_28;

    //0x004E18B0
    event_type(string_hash a2, bool a3);

    //0x004EE6C0
    void raise_event(entity_base_vhandle a2, event *a3);

    //0x004EE620
    event_recipient_entry *create_recipient_entry(entity_base_vhandle a2);
};
