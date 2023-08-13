#pragma once

#include "mvector.h"

struct token_def;
struct mash_info_struct;
struct from_mash_in_place_constructor;

struct token_def_list {
    mVector<token_def> field_0;
    int field_14[9];

    //0x005DEDA0
    token_def_list(from_mash_in_place_constructor *a2);

    //0x005DD200
    int unmash(mash_info_struct *a2, void *a3);
};
