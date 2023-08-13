#pragma once

#include "entity_base_vhandle.h"
#include "entity.h"
#include "vector3d.h"

struct signaller;

struct anchor_storage_class {
    vhandle_type<entity, vhandle_type<signaller, entity_base_vhandle>> field_0;
    int field_4;

    anchor_storage_class();

    bool is_valid() const;

    vector3d get_origin() const;

    //0x00464370
    vector3d get_target() const;
};
