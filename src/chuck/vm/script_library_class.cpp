#include "script_library_class.h"

#include "chuck_str.h"
#include "common.h"
#include "func_wrapper.h"
#include "memory.h"
#include "script_manager.h"
#include "slab_allocator.h"
#include "utility.h"
#include "vtbl.h"
#include "variables.h"

#include <cassert>

VALIDATE_SIZE(script_library_class, 0x20);

#if NAME_FIELD
VALIDATE_SIZE(script_library_class::function, 0x8);
#else
VALIDATE_SIZE(script_library_class::function, 0x4);
#endif

Var<script_library_class *> slc_global{0x00965EC4};

Var<slc_num_t *> slc_num{0x00965ECC};

Var<slc_str_t *> slc_str{0x00965ED0};

script_library_class::script_library_class(
        const char *a2,
        int a3,
        const char *a4,
        bool a5)
{
    THISCALL(0x005AA860, this, a2, a3, a4, a5);
}

void script_library_class::store_name(const char *a2)
{
    if ( this->name != nullptr ) {
        operator delete[](this->name);
    }

    auto v3 = strlen(a2);
    this->name = new char[v3 + 1];
    chuck_strcpy(this->name, a2, v3 + 1);
}

bool script_library_class::function::operator()(vm_stack &a2,
                                                script_library_class::function::entry_t a3) const {
    bool __stdcall (
        *func)(vm_stack & a2,
               script_library_class::function::entry_t a3) = CAST(func, get_vfunc(m_vtbl, 0x4));

    return func(a2, a3);
}

const char *script_library_class::get_name() const {
    assert(name != nullptr);

    return this->name;
}

script_library_class::function *script_library_class::get_func(int index)
{
    assert(index >= 0);
    assert(index < total_funcs);
    
    return this->funcs[index];
}

void script_library_class::add_function(script_library_class::function *func) {

    if ( g_is_the_packer() || script_manager::using_chuck_old_fashioned() )
    {}
    else
    {
        assert(total_funcs > 0);

        assert(are_funcs_from_mash());

        assert(funcs != nullptr);

        bool found = false;
        for ( auto i = this->next_func_slot; i < this->total_funcs; ++i )
        {
            if ( this->funcs[i] != nullptr )
            {
                found = true;
                this->next_func_slot = i;
                break;
            }
        }

        assert(found && "invalid mash!!!!");

        assert(next_func_slot < total_funcs);

        this->funcs[this->next_func_slot++] = func;

    }
}

void __thiscall script_library_class__function__ctor(script_library_class::function *self,
                                                     const char *a1) {
    self->m_vtbl = 0x0088EAFC;

#if NAME_FIELD
    self->field_4 = a1;
#endif

    assert(slc_global() != nullptr);

    slc_global()->add_function(self);
}

void __thiscall script_library_class__function__ctor(script_library_class::function *self,
                                                     script_library_class *a2,
                                                     const char *a3) {
    self->m_vtbl = 0x0088EAFC;

#if NAME_FIELD
    self->field_4 = a3;
#endif

    assert(a2 != nullptr);

    a2->add_function(self);
}

script_library_class::function::function(const char *name) {
    if constexpr (1) {
        this->m_vtbl = 0x0088EAFC;

#if NAME_FIELD
        this->field_4 = name;
#endif

        assert(slc_global() != nullptr);

        slc_global()->add_function(this);

    } else {
        THISCALL(0x0058EE30, this, name);
    }
}

script_library_class::function::function(script_library_class *a2, const char *a3) {
    THISCALL(0x0058EDE0, this, a2, a3);
}


void *__thiscall script_library_class_function_ctor(void *s, const char *name) {
    auto *self = static_cast<script_library_class::function *>(s);

    static constexpr auto size = sizeof(script_library_class::function);

    auto *mem = mem_alloc(size);

#if 1

    sp_log("%s: old_mem = 0x%08X, mem = 0x%08X", name, self, mem);

#endif

    auto *func = new (mem) script_library_class::function{name};

    slab_allocator::deallocate(self, nullptr);

    assert(0x0088EAFC == func->m_vtbl);

    sp_log("DEBUG_1");

    return func;
}

void script_library_class_patch() {
    SET_JUMP(0x0058EE30, &script_library_class_function_ctor);
}
