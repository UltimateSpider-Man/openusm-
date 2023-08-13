#pragma once

#include "mash_virtual_base.h"

#include "mvector.h"

struct mash_info_struct;

namespace als {

struct state;
struct category;
struct transition_group_base;

struct state_machine_shared : mash_virtual_base {
    state_machine_shared();

    mVector<als::state> field_4;
    mVector<als::category> field_18;
    mVector<als::transition_group_base> field_2C;

    void destruct_mashed_class();

    void _unmash(mash_info_struct *a2, void *a3);

    int get_mash_sizeof() const;
};
} // namespace als

extern void als_state_machine_shared_patch();
