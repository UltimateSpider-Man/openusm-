#pragma once

#include "string_hash.h"

struct region_lookup_entry {
    string_hash field_0;
    int reg_idx;

    region_lookup_entry();

    region_lookup_entry(string_hash a2, int a3);
};
