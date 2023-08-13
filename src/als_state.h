#pragma once

#include <cstdint>

#include "mash_virtual_base.h"
#include "string_hash.h"

struct mash_info_struct;

namespace ai
{
struct param_block;
}

namespace als {

struct state : mash_virtual_base {
    string_hash field_4;
    string_hash field_8;
    uint32_t field_C;
    ai::param_block *field_10;

    state();

    void _unmash(mash_info_struct *, void *);

    //virtual
    int get_mash_sizeof() const;
};

} // namespace als

extern void als_state_patch();
