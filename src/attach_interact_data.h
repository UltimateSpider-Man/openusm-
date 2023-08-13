#pragma once

#include "mvector.h"

struct attach_node;
struct mash_info_struct;

struct attach_interact_data
{
    mVector<attach_node> field_0;

    void unmash(mash_info_struct *a1, void *);
};
