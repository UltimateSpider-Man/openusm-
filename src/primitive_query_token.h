#pragma once

#include "capsule.h"

namespace local_collision {
struct primitive_list_t;
}

struct primitive_query_token_t {
    capsule field_0;
    capsule field_1C;
    local_collision::primitive_list_t *field_38;

    primitive_query_token_t();
};
