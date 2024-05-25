#pragma once

#include "string_hash.h"

struct patrol_def {
    string_hash field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;

    string_hash get_id_hash() const {
        return this->field_0;
    }
};
