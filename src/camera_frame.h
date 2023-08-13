#pragma once

#include "vector3d.h"

struct camera_frame
{
    vector3d field_0;
    vector3d field_C;
    vector3d field_18;

    bool is_valid() const;
};
