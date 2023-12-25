#pragma once

#include "animation_controller.h"
#include "als_layer_types.h"
#include "als_request_data.h"
#include "param_cache.h"
#include "param_list.h"
#include "string_hash.h"

namespace als {

struct animation_logic_system;
struct category;
struct layer_state_machine_shared;
struct state;
struct scripted_trans_group;

enum external_parameter_types {};

enum internal_parameter_types {};

struct state_machine {
    std::intptr_t m_vtbl;
    layer_state_machine_shared *shared_portion;
    struct {
        bool field_0;
        bool field_1;
        bool field_2;
        string_hash m_cat_id;
        param_list field_8;

        void clear() {
            this->field_0 = false;
            this->field_1 = false;
            this->field_2 = false;
            this->m_cat_id = {0};
            this->field_8.clear();
        }
    } field_8;
    struct {
        bool m_trans_succeed;
        bool m_request_not_satisfied;
        bool m_curr_state_interruptable;
        bool m_active;
        string_hash m_cat_id;
    } field_14;
    request_data curr_req_data;
    state *m_curr_state;
    struct {
        param_list field_0;
        string_hash field_4;

        void clear() {
            this->field_0.clear();
            this->field_4 = string_hash {0};
        }
    } field_34;
    state *m_prev_state;
    param_cache field_40;
    animation_controller::anim_ctrl_handle field_48;

    //0x004A9180
    state_machine();

    void set_pending_params(param_list &a2);

    void set_active(
        animation_logic_system *a2,
        string_hash a3);

    bool is_curr_state_interruptable(
        animation_logic_system *a2) const;

    void update_pending_params(animation_logic_system *a2);

    bool did_do_transition() const;

    auto &get_anim_handle() const
    {
        return field_48;
    }

    param_node *find_external_param(
        external_parameter_types a2) const;

    bool has_ext_param_been_set(uint32_t a2) const;

    float get_internal_param(
        animation_logic_system *a3,
        internal_parameter_types a4) const;

    float get_param(
        animation_logic_system *a2,
        unsigned int a3) const;

    void process_requests(animation_logic_system *a2);

    void do_force_state_trans(animation_logic_system *a2);

    void do_implicit_trans(animation_logic_system *a2);

    void do_explicit_trans(animation_logic_system *a2);

    void do_cat_force_trans(animation_logic_system *a2);

    state *get_curr_state() const;

    category *find_category(string_hash a2) const;

    scripted_trans_group *get_trans_group(int idx) const;

    state *find_state(string_hash a2) const;

    void change_state(
        animation_logic_system *a2,
        state *a3);

    /* virtual */ string_hash get_category_id() const;

    //virtual
    float get_time_to_signal(string_hash a2);

    /* virtual */ void request_category_transition(string_hash a2);

    //virtual
    bool is_interruptable() const;

    //virtual
    bool did_transition_succeed() const;

    //virtual
    bool is_request_satisfied() const;

    //virtual
    bool is_active() const;

    //virtual
    void force_als_state(string_hash a2, int a3);

    //virtual
    bool does_category_exist(string_hash a2) const;

    double get_time_to_end_of_anim();

    bool is_cat_our_prev_cat(string_hash a2) const;

    bool is_requesting_category(string_hash a2) const;

    //0x004A6A60
    //virtual
    void set_desired_params(param_list &a2);

    //0x004A6A80
    //virtual
    void set_desired_param(const param &a2);

    //0x00499320
    /* virtual */ string_hash get_state_id() const;

    int get_optional_pb_int(
        const string_hash &a2,
        int a3,
        bool *a4);

    //virtual
    layer_types get_layer_id();

    //virtual
    bool determine_if_request_satisfied(animation_logic_system *a2) const;
};

} // namespace als


extern void als_state_machine_patch();
