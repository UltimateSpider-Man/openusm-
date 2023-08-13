#pragma once

#include "mashable_vector.h"

struct sin_district_container;

struct sin_strip_container {
    char *field_0;
    mashable_vector<sin_district_container> field_4;
    int field_C;

    sin_strip_container();
};
