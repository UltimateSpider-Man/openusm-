#pragma once

#include "resource_pack_slot.h"

#include <vector.hpp>

struct entity;
struct item;
struct limited_timer;
struct box_trigger;
struct worldly_resource_handler;
struct sound_alias_database_resource;

struct worldly_pack_slot : resource_pack_slot {
    progress field_94;
    progress field_98;
    worldly_resource_handler *m_handlers[21];
    _std::vector<entity *> *entity_instances;
    _std::vector<item *> *item_instances;
    _std::vector<box_trigger *> *box_trigger_instances;

    //0x00532220
    worldly_pack_slot();

    //0x00558DF0
    _std::vector<item *> *get_item_instances();

    //0x00558DC0
    _std::vector<entity *> *get_entity_instances();

    void clear_progress();

    //0x0050ED20
    //virtual
    bool _on_load(limited_timer *a2) /*override*/;

    //0x0052AC90
    //virtual
    bool _on_unload(limited_timer *a2) /*override*/;

    //0x005327E0
    //virtual
    ~worldly_pack_slot();

    //0x0050ECE0
    //virtual
    void clear_slot() /*override*/;

    //0x0052AC40
    //virtual
    void clear_pack() /*override*/;

    void sub_531C70();

    //0x005382F0
    _std::vector<box_trigger *> *get_box_trigger_instances();
};

extern void worldly_pack_slot_patch();
