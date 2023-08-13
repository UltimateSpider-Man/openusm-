#pragma once

#include "trigger.h"

#include "float.hpp"
#include "string_hash.h"
#include "vector3d.h"

struct point_trigger : trigger {
    vector3d field_58;

    point_trigger();

    point_trigger(string_hash a2, const vector3d &a3, Float a4);
};
