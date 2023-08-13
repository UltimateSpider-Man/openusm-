#pragma once

#include "mstring.h"

struct wds_script_manager {
    int field_0;
    int field_4;
    mString field_8;

    wds_script_manager() = default;

    //0x0054B7E0
    int hook_up_global_script_object();
};

extern void wds_script_manager_patch();
