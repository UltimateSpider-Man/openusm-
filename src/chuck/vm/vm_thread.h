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
    union argument_t {
        //vm_num_t val;
        //vm_str_t str;
        short word;
        char* sdr;
        script_library_class::function *lfr;
        vm_executable *sfr;
        unsigned binary;
    };

    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int flags;
    vm_stack dstack;
    const uint16_t *PC;
    const uint16_t *field_1B0;
    float field_1B4;
    _std::vector<unsigned short const *> PC_stack;

    int field_1C8[4];

    script_library_class::function::entry_t entry;
    void *field_1DC;
    int field_1E0;
    int field_1E4;

    //0x005A5420
    vm_thread(script_instance *a2, const vm_executable *a3);

    //0x005A5500
    vm_thread(script_instance *a2, const vm_executable *a3, void *a4);

    auto &get_data_stack()
    {
        return this->dstack;
    }

    bool is_flagged(int f) const {
        return (f & this->flags) != 0;
    }

    void set_flag(int a2, bool a3);

    void set_suspended(bool a2);

    //0x005996C0
    char *install_temp_string(const char *a1);

    //0x005ADD00
    bool run();

    //0x005A56F0
    void push_PC();

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
