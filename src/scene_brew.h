#pragma once

#include "scene_entity_brew.h"
#include "scene_spline_path_brew.h"
#include "timed_progress.h"
#include "resource_key.h"

struct limited_timer;

struct scene_brew {
    timed_progress field_0;
    resource_key field_8;
    scene_entity_brew field_10;
    scene_spline_path_brew field_50;
    timed_progress field_B4;
    timed_progress field_BC;
    timed_progress field_C4;
    timed_progress field_CC;

    scene_brew(const resource_key &, limited_timer *);
};
