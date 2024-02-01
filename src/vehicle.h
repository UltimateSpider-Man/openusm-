#pragma once

#include "vehicle_sounds.h"

#include "entity.h"
#include "entity_base_vhandle.h"
#include "mstring.h"
#include "variable.h"

struct vehicle_model {
    int field_0;
    mString field_4;
    int refcount;

    void sub_6B9F30(vhandle_type<entity> a2);
};

struct actor;

struct vehicle : vehicle_sounds {
    vhandle_type<entity> field_50;
    actor *field_54;
    uint32_t bodytype;
    int field_5C[53];

    vehicle();

    static bool terminate_vehicles();

    static inline Var<vehicle_model *[1]> models {0x0096C97C};
};
