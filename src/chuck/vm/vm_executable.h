#pragma once

#include "mstring.h"
#include "string_hash.h"

#include <list.hpp>

struct script_executable;
struct script_object;

struct generic_mash_header;
struct generic_mash_data_ptrs;

struct vm_executable_param_symbol {};

struct vm_executable
{
    script_object *owner;
    string_hash fullname;
    string_hash name;
    int parms_stacksize;
    uint16_t *buffer;
    int buffer_len;
    struct {
        mString field_0;
        int field_10;
        _std::list<vm_executable_param_symbol> field_14;
        void *parameters;
        int field_24;
    } *debug_info;
    uint32_t flags;
    int field_20;

    int get_size() const {
        return buffer_len;
    }

    auto &get_name() const {
        return name;
    }

    auto &get_fullname() const {
        return fullname;
    }

    const auto *get_start() const {
        return buffer;
    }

    bool is_un_mashed() const {
        return (this->flags & 8) != 0;
    }

    int get_parms_stacksize() const {
        return this->parms_stacksize;
    }

    auto *get_owner() const {
        return this->owner;
    }

    void un_mash(
            generic_mash_header *a2,
            void *a3,
            void *a4,
            generic_mash_data_ptrs *a5);
};
