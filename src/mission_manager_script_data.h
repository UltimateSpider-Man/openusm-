#pragma once

#include "mstring.h"
#include "resource_key.h"

struct mission_manager_script_data {
    mString field_0;
    int field_10;
    int field_14;
    void *field_18;
    int field_1C;
    int field_20;
    int strings;
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int markers;
    int field_48;
    int field_4C;
    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    mString field_84;
    int field_94;
    int field_98;
    int field_9C;
    int field_A0;
    resource_key field_A4;
    bool uses_script_stack;
    int filed_B0;
    int field_B4;
    mString field_B8;
    mString field_C8;
    mString field_D8;

    //0x005E9760
    mission_manager_script_data();

    ~mission_manager_script_data();

    //0x005E98A0
    void copy(const mission_manager_script_data &a2);
};
