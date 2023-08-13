#pragma once

#include "device_axis.h"

#include <list.hpp>

using control_id_t = int;
using axis_id_t = int;

using device_axis_list_t = typename _std::list<device_axis>;

enum control_t
{
    CT_BOOLEAN,
    CT_RATIONAL
};

struct game_control {
    control_id_t name;
    control_t type;
    device_axis_list_t mapping;

    game_control();
};
