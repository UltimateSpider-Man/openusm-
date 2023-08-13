#pragma once

#include "entity_base_vhandle.h"

struct entity;

struct entity_tracker {
    entity_base_vhandle field_0;

    entity_tracker();

    //0x0060BC40
    entity *get_entity();
};
