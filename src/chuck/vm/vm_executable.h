#pragma once

#include "mstring.h"
#include "string_hash.h"

#include <list.hpp>

struct script_executable;

struct generic_mash_header;
struct generic_mash_data_ptrs;

struct vm_executable_param_symbol {};

struct vm_executable
{
    struct {
        int field_0;
        script_executable *field_4;
    } *owner;
    string_hash field_4;
    string_hash name;
    int parms_stacksize;
    uint16_t *field_10;
    int field_14;
    struct {
        mString field_0;
        int field_10;
        _std::list<vm_executable_param_symbol> field_14;
        void *parameters;
        int field_24;
    } *debug_info;
    uint32_t flags;
    int field_20;

    bool is_un_mashed() const {
        return (this->flags & 8) != 0;
    }

    int get_parms_stacksize() const {
        return this->parms_stacksize;
    }

    auto *get_owner()
    {
        return this->owner;
    }

    void un_mash(
            generic_mash_header *a2,
            void *a3,
            void *a4,
            generic_mash_data_ptrs *a5);
};
