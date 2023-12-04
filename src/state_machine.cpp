#include "state_machine.h"

#include "common.h"
#include "func_wrapper.h"
#include "vtbl.h"

namespace als {

VALIDATE_SIZE(state_machine, 0x54);

state_machine::state_machine() {
    THISCALL(0x004A9180, this);
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

bool state_machine::is_active() const
{
    if constexpr (0) {
        return this->m_active;
    } else {
        auto func = get_vfunc(m_vtbl, 0x20);
        return (bool) func(this);
    }
}

double state_machine::get_time_to_end_of_anim()
{
    double (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x50));
    return func(this);
}

bool state_machine::is_cat_our_prev_cat(string_hash a2) const
{
    bool (__fastcall *func)(const void *, void *, string_hash) = CAST(func, get_vfunc(m_vtbl, 0x58));
    return func(this, nullptr, a2);
}

bool state_machine::is_requesting_category(string_hash a2) const
{
    bool (__fastcall *func)(const void *, void *, string_hash) = CAST(func, get_vfunc(m_vtbl, 0x5C));
    return func(this, nullptr, a2);
}

string_hash state_machine::get_category_id() {
    auto &func = get_vfunc(m_vtbl, 0x0);

    string_hash id;
    func(this, &id);

    return id;
}

float als::state_machine::get_time_to_signal(string_hash a2) {
    float (__fastcall *func)(void *, void *, string_hash) = CAST(func, 0x0049F4E0);

    return func(this, nullptr, a2);
}

void state_machine::set_desired_params(param_list &a2) {
    als::param_list &v2 = this->field_10;
    v2.concat_list(a2);
    v2.cull_duplicates_keep_last();
}

void state_machine::set_desired_param(const als::param &a2) {
    if constexpr (1) {
        als::param_list v8{};
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

string_hash als::state_machine::get_state_id() {
    auto &get_state_id = get_vfunc(this->m_vtbl, 0x4);

    string_hash id;
    get_state_id(this, &id);
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

als::state *state_machine::get_curr_state() {
    return field_30;
}

} // namespace als
