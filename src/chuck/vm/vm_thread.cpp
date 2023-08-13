#include "vm_thread.h"

#include "chuck_str.h"

#include <cassert>
#include <common.h>
#include <utility.h>
#include <vtbl.h>

#include <func_wrapper.h>
#include <script_manager.h>

VALIDATE_SIZE(vm_thread, 0x1E8);
VALIDATE_OFFSET(vm_thread, field_20, 0x20);
VALIDATE_OFFSET(vm_thread, field_1D8, 0x1D8);

Var<char[64][256]> vm_thread::string_registers{0x00961940};

Var<fixed_pool> vm_thread::pool {0x00922D58};

vm_thread::vm_thread(script_instance *a2, const vm_executable *a3) {
    THISCALL(0x005A5420, this, a2, a3);
}

vm_thread::vm_thread(script_instance *a2, const vm_executable *a3, void *a4) {
    THISCALL(0x005A5500, this, a2, a3, a4);
}

void vm_thread::set_flag(int a2, bool a3)
{
    this->field_1C = ( a3 ? (a2 | this->field_1C) : (this->field_1C & ~a2) );
}

void vm_thread::set_suspended(bool a2)
{
    if ( !a2 || this->sub_B49B80(2) )
    {
        this->set_flag(1, a2);
    }
}

bool vm_thread::run() {
    return (bool) THISCALL(0x005ADD00, this);
}

void vm_thread::raise_event(const vm_thread::argument_t &a2, opcode_arg_t arg_type) {
    assert(arg_type == OP_ARG_SIG || arg_type == OP_ARG_PSIG);

    THISCALL(0x00599710, this, &a2, arg_type);
}

void vm_thread::raise_all_event(const vm_thread::argument_t &a2, opcode_arg_t arg_type) {
    assert(arg_type == OP_ARG_SIG);

    THISCALL(0x0058F960, this, &a2, arg_type);
}

char *vm_thread::install_temp_string(const char *a1) {
    static Var<int> index_18926{0x00967E0C};

    auto v2 = index_18926()++;
    if (index_18926() >= 64) {
        index_18926() = 0;
    }

    auto *v3 = vm_thread::string_registers()[v2];
    chuck_strcpy(v3, a1, 256u);
    return v3;
}

bool vm_thread::call_script_library_function(const vm_thread::argument_t &a2, const uint16_t *a3) {
    if constexpr (1) {
        auto *sp = this->field_20.m_stack_pointer;

        if (a2.field_0->operator()(this->field_20, this->field_1D8)) {
            this->field_1D8.field_0 = 0;
            this->field_1B0 = nullptr;

            return true;
        }

        auto v5 = (a3 == this->field_1B0);
        this->field_1AC = a3;
        this->field_20.m_stack_pointer = sp;
        this->field_1D8.field_0 = 1;
        if (v5) {
            this->field_1B4 += script_manager_time_inc();
            if (this->field_1B4 > 10.0f) {
                this->field_1B4 = 0.0;
            }

        } else {
            this->field_1B0 = a3;
            this->field_1B4 = 0.0;
        }

        return false;

    } else {
        return (bool) THISCALL(0x0058F7E0, this, &a2, a3);
    }
}

void vm_thread_patch() {
    {
        FUNC_ADDRESS(address, &vm_thread::call_script_library_function);

        SET_JUMP(0x0058F7E0, address);
    }
}
