#pragma once

#include "param_list.h"
#include "string_hash.h"

namespace als {

struct state;

struct state_machine {
    std::intptr_t m_vtbl;
    int empty[3];
    param_list field_10;
    bool field_14;
    bool field_15;
    bool field_16;
    bool m_active;
    string_hash field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    int field_2C;
    state *field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    int field_50;

    //0x004A9180
    state_machine();

    /* virtual */ string_hash get_category_id();

    //virtual
    float get_time_to_signal(string_hash a2);

    /* virtual */ void request_category_transition(string_hash a2);

    //virtual
    bool is_interruptable();

    //0x004A6A60
    //virtual
    void set_desired_params(param_list &a2);

    //0x004A6A80
    //virtual
    void set_desired_param(const als::param &a2);

    //0x00499320
    /* virtual */ string_hash get_state_id();
};
} // namespace als
