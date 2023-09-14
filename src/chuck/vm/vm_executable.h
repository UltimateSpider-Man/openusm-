#pragma once

#include "string_hash.h"

struct script_executable;

struct generic_mash_header;
struct generic_mash_data_ptrs;

struct vm_executable
{
    struct {
        int field_0;
        script_executable *field_4;
    } *owner;
    string_hash field_4;
    string_hash name;
    int field_C;
    int16_t *field_10;
    int field_14;
    int *debug_info;
    unsigned int flags;
    int field_20;

    bool is_un_mashed() const {
        return (this->flags & 8) != 0;
    }

    int sub_8D1640()
    {
        return this->field_C;
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
