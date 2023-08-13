#pragma once

#include "attach_action_trigger_enum.h"
#include "mvector.h"
#include "mstring.h"

struct mash_info_struct;

struct attach_node
{
    mVectorBasic<attach_action_trigger_enum> field_0;
    mString field_10;
    int field_20;
    int field_24;

    void unmash(mash_info_struct *a1, void *);
};
