#pragma once

#include "singleton.h"

#include "string_hash.h"
#include "vector3d.h"

#include "variable.h"

struct trigger;
struct entity_base;

struct trigger_manager : singleton {
    trigger *field_4;

    trigger_manager();

    void deinit();

    //0x0050CBA0
    void purge();

    //0x00541F30
    void update();

    trigger *sub_51E5B0(entity_base *a2);

    void delete_trigger(trigger *delete_me);

    void add_trigger(trigger *a2);

    trigger *new_point_trigger(vector3d a2, Float a5);

    trigger *new_entity_trigger(entity_base *a2, Float a3);

    trigger *new_box_trigger(string_hash a2, const vector3d &a3);

    trigger *new_box_trigger(string_hash a2, entity_base *a3);

    static Var<trigger_manager *> instance;
};
