#include "script_object.h"

#include "func_wrapper.h"
#include "vm_executable.h"
#include "vm_thread.h"
#include "common.h"

#include <cassert>

VALIDATE_SIZE(script_object, 0x34);

script_object::script_object()
{

}

void script_object::constructor_common()
{
    THISCALL(0x005A0750, this);
}

void script_object::sub_5AB420()
{
    this->constructor_common();
    if ( (this->field_30 & 1) != 0 )
    {
        this->create_auto_instance(0.0);
    }
}

void script_object::un_mash(generic_mash_header *a2, void *a3, void *a4, generic_mash_data_ptrs *a5)
{
    THISCALL(0x005AB350, this, a2, a3, a4, a5);
}


script_instance *script_object::create_auto_instance(Float arg0)
{
    return (script_instance *) THISCALL(0x005AAEF0, this, arg0);
}

vm_executable *script_object::get_func(int i)
{
    assert(funcs != nullptr);

    assert(i >= 0);

    assert(i < total_funcs);

    return this->funcs[i];
}

int script_object::find_func(string_hash a2) const {
    return THISCALL(0x0058EF80, this, a2);
}

int *script_instance::register_callback(
    void (*p_cb)(script_instance_callback_reason_t, script_instance *, vm_thread *, void *),
    void *a3) {
    return (int *) THISCALL(0x005A33F0, this, p_cb, a3);
}

vm_thread *script_instance::add_thread(const vm_executable *a1, const char *a2)
{
    auto *nt = this->add_thread(a1);

    assert(nt != nullptr);

    if ( a2 != nullptr )
    {
        auto v5 = a1->field_C;
        auto &v3 = nt->get_stack();
        v3.push(a2, v5);
    }

    nt->field_1AC = (const unsigned __int16 *) a1->field_10;
    return nt;
}

vm_thread *script_instance::add_thread(const vm_executable *a2)
{
    auto *a1 = this;
    auto *mem = vm_thread::pool().allocate_new_block();
    auto *nt = new (mem) vm_thread{this, a2};
    assert(nt != nullptr);

    a1->threads.push_back(nt);

    if ( (a1->field_30 & 1) != 0 )
        nt->set_suspended(true);

    return nt;
}
