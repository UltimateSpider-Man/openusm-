#pragma once

#include "script_library_class.h"
#include "vm_stack.h"
#include "fixed_pool.h"

#include <variable.h>

#include <vector.hpp>

struct script_instance;
struct vm_executable;

inline constexpr auto OP_ARG_NULL = 0;
inline constexpr auto OP_ARG_WORD = 4;
inline constexpr auto OP_ARG_PCR = 5;
inline constexpr auto OP_ARG_SFR = 9;
inline constexpr auto OP_ARG_LFR = 10;
inline constexpr auto OP_ARG_SIG = 15;
inline constexpr auto OP_ARG_PSIG = 16;

struct opcode_arg_t {
    int value;

    operator int() const {
        return value;
    }
};

struct vm_thread {
    struct argument_t {
        script_library_class::function *field_0;
    };

    int field_0[7];
    int field_1C;
    vm_stack field_20;
    const uint16_t *field_1AC;
    const uint16_t *field_1B0;
    float field_1B4;
    _std::vector<unsigned short const *> field_1B8;

    int field_1C8[4];

    script_library_class::function::entry_t field_1D8;
    void *field_1DC;
    int field_1E0;
    int field_1E4;

    //0x005A5420
    vm_thread(script_instance *a2, const vm_executable *a3);

    //0x005A5500
    vm_thread(script_instance *a2, const vm_executable *a3, void *a4);

    auto &get_stack()
    {
        return this->field_20;
    }

    bool sub_B49B80(int a2)
    {
        return (a2 & this->field_1C) != 0;
    }

    void set_flag(int a2, bool a3);

    void set_suspended(bool a2);

    //0x005996C0
    char *install_temp_string(const char *a1);

    //0x005ADD00
    bool run();

    //0x00599710
    void raise_event(const vm_thread::argument_t &a2, opcode_arg_t arg_type);

    //0x0058F960
    void raise_all_event(const vm_thread::argument_t &a2, opcode_arg_t arg_type);

    //0x0058F7E0
    bool call_script_library_function(const vm_thread::argument_t &a2, const uint16_t *a3);

    static Var<char[64][256]> string_registers;

    static Var<fixed_pool> pool;
};

extern void vm_thread_patch();
