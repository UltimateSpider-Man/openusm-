#include "state_machine.h"

#include "als_animation_logic_system.h"
#include "als_category.h"
#include "als_state.h"
#include "common.h"
#include "func_wrapper.h"
#include "layer_state_machine_shared.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

namespace als {

VALIDATE_SIZE(state_machine, 0x54);

state_machine::state_machine() {
    THISCALL(0x004A9180, this);
}

param_node *state_machine::find_external_param(
        external_parameter_types a2)
{
    if constexpr (0) {
    } else {
        return (param_node *) THISCALL(0x00493660, this, a2);
    }
}

float state_machine::get_internal_param(
        animation_logic_system *a3,
        internal_parameter_types a4)
{
    float (__fastcall *func)(void *, void *, animation_logic_system *, internal_parameter_types) = CAST(func, 0x0049CFD0);
    return func(this, nullptr, a3, a4);
}

bool state_machine::has_ext_param_been_set(uint32_t a2)
{
    return this->find_external_param(static_cast<external_parameter_types>(a2)) != nullptr;
}

float state_machine::get_param(
        animation_logic_system *a2,
        unsigned int a3)
{
    if constexpr (0) {
        auto func = [](param_cache &self, int a2) -> int
        {
            int i;
            auto num_params_in_cache = self.get_num_params_in_cache();
            for ( i = 0; i < num_params_in_cache; ++i )
            {
                if ( self.field_0[i].field_0 == a2 ) {
                    return i;
                }
            }

            return -1;
        };

        auto v5 = func(this->field_40, a3);
        if ( v5 != -1 ) {
            return this->field_40.get_from_cache(v5);
        }

        if ( a3 < 91 )
        {
            auto *external_param = this->find_external_param((external_parameter_types)a3);
            if ( external_param != nullptr ) {
                return this->field_40.cache_param(a3, external_param->field_0.field_4);
            } else {
                return 0.0;
            }
        }
        else
        {
            auto internal_param = this->get_internal_param(a2, (internal_parameter_types)a3);
            return this->field_40.cache_param(a3, internal_param);
        }

    } else {
        float (__fastcall *func)(void *, void *, animation_logic_system *, uint32_t) = CAST(func, 0x0049FB00);
        return func(this, nullptr, a2, a3);
    }
}

bool state_machine::did_do_transition() const
{
    return this->field_14;
}

void state_machine::request_category_transition(string_hash a2) {
    //return this->field_16 || !this->field_17;

    auto &func = get_vfunc(m_vtbl, 0x10);

    func(this, a2);
}

bool state_machine::is_interruptable() {
    //return this->field_16 || !this->field_17;

    auto &func = get_vfunc(m_vtbl, 0x14);

    return func(this);
}

bool state_machine::is_request_satisfied() const
{
    TRACE("als::state_machine::is_request_satisfied");

    if constexpr (1) {
        return !this->field_15;
    } else {
        bool (__fastcall *func)(const void *) = CAST(func, get_vfunc(m_vtbl, 0x1C));
        return func(this);
    }
}

bool state_machine::is_active() const
{
    if constexpr (0) {
        return this->m_active;
    } else {
        bool (__fastcall *func)(const void *) = CAST(func, get_vfunc(m_vtbl, 0x20));
        return func(this);
    }
}

void state_machine::force_als_state(string_hash a2, int )
{
    TRACE("als::state_machine::force_als_state");

    this->field_9 = true;
    this->field_A = true;
    this->field_C = a2;
}

bool state_machine::does_category_exist(string_hash a2) const
{
    TRACE("als::state_machine::does_category_exist");

    assert(this->shared_portion != nullptr);

    for ( int i = 0; i < this->shared_portion->category_list.size(); ++i)
    {
        auto *cat = this->shared_portion->category_list.at(i);
        if ( cat->field_4 == a2 ) {
            return true;
        }
    }

    return false;
}

double state_machine::get_time_to_end_of_anim()
{
    TRACE("als::state_machine::get_time_to_end_of_anim");

    if constexpr (1) {
        double (__fastcall *func)(void *) = CAST(func, 0x004993C0);
        return func(this);
    } else {
        double (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x50));
        return func(this);
    }
}

bool state_machine::is_cat_our_prev_cat(string_hash a2) const
{
    TRACE("als::state_machine::is_cat_our_prev_cat");

    if constexpr (1) {
        if ( !this->field_14 ) {
            return false;
        }

        return a2 == this->field_18
            && a2 != this->get_category_id();
    } else {
        bool (__fastcall *func)(const void *, void *, string_hash) = CAST(func, get_vfunc(m_vtbl, 0x58));
        return func(this, nullptr, a2);
    }
}

bool state_machine::is_requesting_category(string_hash a2) const
{
    TRACE("als::state_machine::is_requesting_category");

    if constexpr (1) {
        if ( this->field_9 ) {
            if ( this->field_C == a2 ) {
                return true;
            }
        }

        return false;
    } else {
        bool (__fastcall *func)(const void *, void *, string_hash) = CAST(func, get_vfunc(m_vtbl, 0x5C));
        return func(this, nullptr, a2);
    }
}

string_hash state_machine::get_category_id() const
{
    void (__fastcall *func)(const void *, void *, string_hash *) = CAST(func, get_vfunc(m_vtbl, 0x0));

    string_hash id;
    func(this, nullptr, &id);

    return id;
}

float state_machine::get_time_to_signal(string_hash a2)
{
    TRACE("als::state_machine::get_time_to_signal");

    float (__fastcall *func)(void *, void *, string_hash) = CAST(func, 0x0049F4E0);
    return func(this, nullptr, a2);
}

void state_machine::set_desired_params(param_list &a2) {
    param_list &v2 = this->field_10;
    v2.concat_list(a2);
    v2.cull_duplicates_keep_last();
}

void state_machine::set_desired_param(const param &a2) {
    if constexpr (1) {
        param_list v8{};
        auto &v7 = a2;

        v8.add_param(v7);

        auto *v4 = &this->field_10;
        v4->concat_list(v8);

        v4->cull_duplicates_keep_last();

        v8.clear();
    } else {
        THISCALL(0x004A6A80, this, &a2);
    }
}

string_hash state_machine::get_state_id()
{
    void (__fastcall *func)(const void *, void *, string_hash *) = CAST(func, get_vfunc(this->m_vtbl, 0x4));

    string_hash id;
    func(this, nullptr, &id);
    return id;
}

int state_machine::get_optional_pb_int(
        const string_hash &a2,
        int a3,
        bool *a4) {
    auto func = get_vfunc(m_vtbl, 0x68);
    return func(this, &a2, a3, a4);
}

layer_types state_machine::get_layer_id() {
    layer_types (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x7C));
    return func(this);
}

state *state_machine::get_curr_state() {
    return m_curr_state;
}

void state_machine::process_requests(animation_logic_system *a2)
{
    TRACE("als::state_machine::process_requests");

    sp_log("%d %d %d", this->field_8, this->field_9, this->field_A);
    sp_log("%s", this->field_C.to_string());

    if constexpr (1) {
        this->curr_req_data.clear();
        this->field_40.clear_cache();
        if ( this->field_8 ) {
            layer_types v4 = this->get_layer_id();
            a2->sub_4A6630(v4);
            this->field_34.clear();
        } else {
            if ( this->field_9 ) {
                if ( this->field_A ) {
                    this->do_force_state_trans(a2);
                } else {
                    auto *cat = this->find_category(this->field_C);
                    if ( cat != nullptr ) {
                        if ( cat->is_flag_set(1u) ) {
                            this->do_cat_force_trans(a2);
                        } else {
                            this->do_explicit_trans(a2);
                        }
                    } else {
                        this->do_implicit_trans(a2);
                    }
                }
            }
            else if ( this->is_active() )
            {
                this->do_implicit_trans(a2);
            }
        }
    } else {
        THISCALL(0x004A6BA0, this, a2);
    }
}

void state_machine::do_force_state_trans(animation_logic_system *a2)
{
    TRACE("als::state_machine::do_force_state_trans");

    THISCALL(0x0049F910, this, a2);
}

void state_machine::do_cat_force_trans(animation_logic_system *a2)
{
    TRACE("als::state_machine::do_cat_force_trans");

    THISCALL(0x0049F850, this, a2);
}

bool category_binary_search(string_hash a1, category **a2, int size, int *found_idx)
{
    return (bool) CDECL_CALL(0x004935B0, a1, a2, size, found_idx);
}

category *state_machine::find_category(string_hash a2)
{
    assert(this->shared_portion != nullptr);

    auto size = this->shared_portion->category_list.size();
    auto **data = this->shared_portion->category_list.m_data;
    int v8;
    if ( category_binary_search(a2, data, size, &v8) ) {
        return this->shared_portion->category_list.at(v8);
    }

    auto *v4 = a2.to_string();
    sp_log("Could not find category (%s).", v4);
    return nullptr;
}

transition_group_base *state_machine::get_trans_group(int idx)
{
    return this->shared_portion->field_2C.at(idx);
}

void state_machine::set_active(
        animation_logic_system *a2,
        string_hash a3)
{
    TRACE("als::state_machine::set_active");
    
    this->m_active = true;
    auto *the_state = this->find_state(a3);
    this->change_state(a2, the_state);
    this->field_14 = true;
    this->field_34.clear();
}

void state_machine::do_implicit_trans(animation_logic_system *a2)
{
    TRACE("als::state_machine::do_implicit_trans");

    sp_log("0x%08X", this->m_curr_state->m_vtbl);

    if constexpr (1) {
        auto func = [](const request_data &self) -> bool
        {
            return self.did_transition_occur || self.field_1;
        };

        auto v4 = this->m_curr_state->do_implicit_trans(a2, this);
        this->curr_req_data.sub_4ADF40(v4);

        sp_log("did_transition_occur = %d, %d %d %d", this->curr_req_data.did_transition_occur,
                                this->curr_req_data.field_1,
                                this->curr_req_data.field_2,
                                this->curr_req_data.field_3);
        if ( func(this->curr_req_data) || !this->curr_req_data.field_3 ) {
            if ( func(this->curr_req_data) ) {
                if (this->curr_req_data.field_2) {
                    auto *cat = this->find_category(this->curr_req_data.field_8);
                    auto v15 = cat->do_incoming_trans(a2, this);
                    this->curr_req_data.sub_4ADF40(v15);
                    if ( func(this->curr_req_data) ) {
                        auto *the_state = this->find_state(this->curr_req_data.field_8);
                        this->change_state(a2, the_state);
                    } else {
                        assert(0 && "Implicit transition to category specified failed.");
                    }
                } else {
                    auto *the_state = this->find_state(this->curr_req_data.field_8);
                    this->change_state(a2, the_state);
                }
            } else {
                this->field_14 = false;
            }

        } else {
            auto v16 = this->m_curr_state->field_8;
            auto *v6 = this->find_category(v16);
            auto v7 = v6->do_implicit_trans(a2, this);
            this->curr_req_data.sub_4ADF40(v7);
            if ( func(this->curr_req_data) ) {
                if ( this->curr_req_data.field_2 ) {
                    auto *v10 = this->find_category(this->curr_req_data.field_8);
                    this->curr_req_data.sub_4ADF40(v10->do_incoming_trans(a2, this));
                    if ( func(this->curr_req_data) ) {
                        auto *the_state = this->find_state(this->curr_req_data.field_8);
                        this->change_state(a2, the_state);
                    } else {
                        assert(0 && "Implicit transition to category specified failed.");
                    }
                }
            } else {
                this->field_14 = false;
            }
        }

    } else {
        THISCALL(0x0049CD30, this, a2);
    }
}

void state_machine::do_explicit_trans(animation_logic_system *a2)
{
    TRACE("als::state_machine::do_explicit_trans");

    THISCALL(0x0049F5A0, this, a2);
}

state *state_machine::find_state(string_hash a2)
{
    TRACE("als::state_machine::find_state", a2.to_string());

    assert(this->shared_portion != nullptr);

#if 0
    auto size = this->shared_portion->state_list.size();
    for (int i {0}; i < size ; ++i)
    {
        auto *the_state = this->shared_portion->state_list.at(i);
        if (the_state->field_4 == a2) {
            return the_state;
        }
    }
#else
    auto begin = this->shared_portion->state_list.m_data;
    auto end = begin + this->shared_portion->state_list.size();
    auto it = std::find_if(begin, end, [a2](auto *the_state)
    {
        return (the_state->field_4 == a2);
    });

    if (it != end) {
        return (*it);
    }
#endif

    auto *v5 = a2.to_string();
    error("Could not find state (%s).", v5);
    return nullptr;
}

void state_machine::change_state(
        animation_logic_system *a2,
        state *a3)
{
    TRACE("als::state_machine::change_state");

    if (a2 != nullptr) {
    }

    if ( !this->field_14 ) {
        this->field_3C = this->m_curr_state;
    }

    this->m_curr_state = a3;
    this->field_14 = true;
    this->m_active = (this->m_curr_state != nullptr);
    auto *v4 = this->field_3C;
    if ( v4 != nullptr ) {
        this->field_18 = v4->field_8;
    } else {
        this->field_18 = {0};
    }
}

} // namespace als

void als_state_machine_patch()
{
    auto REPLACE = [](auto addr, auto func) -> void {
        FUNC_ADDRESS(address, func);
        SET_JUMP(addr, address);
    };

    REPLACE(0x00493850, &als::state_machine::change_state);

    REPLACE(0x0049F9B0, &als::state_machine::set_active);

    {
        FUNC_ADDRESS(address, &als::state_machine::is_request_satisfied);
        SET_JUMP(0x00493500, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::get_time_to_end_of_anim);
        set_vfunc(0x00881428, address);
        set_vfunc(0x00881500, address);
        set_vfunc(0x00881588, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::get_time_to_signal);
        set_vfunc(0x0088142C, address);
        set_vfunc(0x00881504, address);
        set_vfunc(0x0088158C, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::force_als_state);
        SET_JUMP(0x00493520, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::does_category_exist);
        SET_JUMP(0x00499370, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::find_state);
        SET_JUMP(0x004994C0, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::is_cat_our_prev_cat);
        SET_JUMP(0x00493550, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::is_requesting_category);
        SET_JUMP(0x00493470, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::process_requests);
        REDIRECT(0x004A910D, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::do_force_state_trans);
        REDIRECT(0x004A6C04, address);

    }

    {
        FUNC_ADDRESS(address, &als::state_machine::do_implicit_trans);
        REDIRECT(0x0049F82D, address);
        REDIRECT(0x004A6C55, address);
        REDIRECT(0x004A6C72, address);
    }

    {
        FUNC_ADDRESS(address, &als::state_machine::do_explicit_trans);
        REDIRECT(0x004A6C43, address);
    }
}
