#pragma once

#include "entity.h"
#include "signaller.h"


struct trigger : signaller {
    float field_48;
    int field_4C;
    _std::list<vhandle_type<entity>> *trigger_current_entities;
    trigger *m_next_trigger;

    //0x0050CBD0
    trigger(string_hash a2);

    //0x0056FE50
    ~trigger();

    //0x0053C390
    void set_multiple_entrance(bool a2);

    //virtual
    bool is_point_trigger() const;

    //virtual
    bool is_box_trigger() const;

    //virtual
    bool is_entity_trigger() const;
};
