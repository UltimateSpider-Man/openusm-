#pragma once

#include "vector3d.h"

namespace ai {

struct als_inode;

struct crawl_params_record {
    int field_0;
    bool field_4;
    float field_8;
    float field_C;
    vector3d field_10;
    vector3d field_1C;
    float field_28;

    void update_crawl_transition_als_params(
        ai::als_inode *a2);
};

}
