#pragma once

#include "entity_base_vhandle.h"

struct vm_executable;
struct script_instance;
struct event;

struct event_recipient_entry {
    event_recipient_entry();

    //0x004C02A0
    int add_callback(script_instance *a2, const vm_executable *a3, char *a4, bool a5);

    //0x004D6260
    int add_callback(void (*cb)(event *, entity_base_vhandle, void *), void *a3, bool a4);
};
