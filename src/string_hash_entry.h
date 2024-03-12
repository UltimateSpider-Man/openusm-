#pragma once

#include "mstring.h"
#include "string_hash.h"

struct mash_info_struct;

struct string_hash_entry {
    string_hash field_0;
    mString field_4;

    string_hash_entry() = default;

    string_hash_entry(const char *a2, const string_hash *a3);

    mString sub_50DBC0(const char *a3);

    void unmash(mash_info_struct *a1, void *a2);

    void custom_unmash(mash_info_struct *a2, void *a3);
};
