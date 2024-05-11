#pragma once

#include "entity_base_vhandle.h"
#include "string_hash.h"

struct event;
struct event_callback;
struct event_recipient_entry;

struct event_type {
    string_hash field_0;
    event *event_to_raise;
    _std::vector<event_recipient_entry *> field_8;
    bool field_18;
    _std::list<event_callback *> field_1C;
    bool field_28;

    //0x004E18B0
    event_type(string_hash a2, bool a3);

    event_recipient_entry * sub_4EE580(entity_base_vhandle a2);

    //0x004EE6C0
    void raise_event(entity_base_vhandle a2, event *a3);

    //0x004EE620
    event_recipient_entry *create_recipient_entry(entity_base_vhandle a2);

    //0x004CFB90
    bool callback_exists(int a2) const;
};
