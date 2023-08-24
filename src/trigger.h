#pragma once

#include "signaller.h"

struct entity;

struct trigger : signaller {
    float field_48;
    int field_4C;
    _std::list<vhandle_type<entity, vhandle_type<signaller, entity_base_vhandle>>>
        *trigger_current_entities;
    trigger *field_54;

    trigger();

    trigger(string_hash a2);

    //0x0053C390
    void set_multiple_entrance(bool a2);
};
