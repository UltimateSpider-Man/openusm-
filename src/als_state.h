#pragma once

#include <cstdint>

#include "als_request_data.h"
#include "mash_virtual_base.h"
#include "string_hash.h"

struct mash_info_struct;

namespace ai
{
struct param_block;
}

namespace als {

struct animation_logic_system;
struct state_machine;

enum state_flags {};

struct state : mash_virtual_base {
    string_hash field_4;
    string_hash field_8;
    uint16_t field_C;
    uint16_t field_E;
    ai::param_block *field_10;

    state();

    bool is_flag_set(state_flags a2) const
    {
        return static_cast<uint16_t>(a2 & this->field_C) != 0;
    }

    void _unmash(mash_info_struct *, void *);

    request_data do_implicit_trans(
        animation_logic_system *a4,
        state_machine *a5);

    //virtual
    string_hash get_nal_anim_name() const;

    //virtual
    int get_mash_sizeof() const;
};

} // namespace als

extern void als_state_patch();
