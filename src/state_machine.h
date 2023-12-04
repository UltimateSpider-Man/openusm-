#pragma once

#include "animation_controller.h"
#include "als_layer_types.h"
#include "param_list.h"
#include "string_hash.h"

namespace als {

struct layer_state_machine_shared;
struct state;

struct state_machine {
    std::intptr_t m_vtbl;
    als::layer_state_machine_shared *field_4;
    bool field_8;
    bool field_9;
    string_hash field_C;
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
    animation_controller::anim_ctrl_handle field_48;

    //0x004A9180
    state_machine();

    bool did_do_transition() const;

    auto &get_anim_handle() {
        return field_48;
    }

    state *get_curr_state();

    /* virtual */ string_hash get_category_id();

    //virtual
    float get_time_to_signal(string_hash a2);

    /* virtual */ void request_category_transition(string_hash a2);

    //virtual
    bool is_interruptable();

    bool is_active() const;

    double get_time_to_end_of_anim();

    bool is_cat_our_prev_cat(string_hash a2) const;

    bool is_requesting_category(string_hash a2) const;

    //0x004A6A60
    //virtual
    void set_desired_params(param_list &a2);

    //0x004A6A80
    //virtual
    void set_desired_param(const als::param &a2);

    //0x00499320
    /* virtual */ string_hash get_state_id();

    int get_optional_pb_int(
        const string_hash &a2,
        int a3,
        bool *a4);

    layer_types get_layer_id();
};
} // namespace als
