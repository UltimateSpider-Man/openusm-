#pragma once

struct mash_info_struct;

struct ai_adv_strength_test_data
{
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;

    void unmash(mash_info_struct *a1, void *a3);
};
