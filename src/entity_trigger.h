#pragma once

#include "trigger.h"

#include "float.hpp"
#include "string_hash.h"

struct entity_trigger : trigger {
    entity_base_vhandle field_58;
    vector3d field_5C;

    //0x0053CA70
    entity_trigger(string_hash a2, entity_base *a3, Float a4);

    entity_base *get_ent();
};
