#include "state_machine.h"

#include "common.h"
#include "func_wrapper.h"
#include "vtbl.h"

namespace als {

VALIDATE_SIZE(state_machine, 0x54);

state_machine::state_machine() {
    THISCALL(0x004A9180, this);
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

string_hash state_machine::get_category_id() {
    auto &func = get_vfunc(m_vtbl, 0x0);

    string_hash id;
    func(this, &id);

    return id;
}

float als::state_machine::get_time_to_signal(string_hash a2) {
    float __thiscall (*func)(void *, string_hash) = CAST(func, 0x0049F4E0);

    return func(this, a2);
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

} // namespace als
