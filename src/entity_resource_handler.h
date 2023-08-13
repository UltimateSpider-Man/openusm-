#pragma once

#include "base_entity_resource_handler.h"

#include "worldly_resource_handler.h"

#include <cstdint>

struct worldly_pack_slot;

struct entity_resource_handler : base_entity_resource_handler {
    entity_resource_handler(worldly_pack_slot *a2);

    //0x00563130
    /* virtual */ int get_num_resources() /* override */;

    //0x0056BFA0
    /* virtual */ bool handle_resource(worldly_resource_handler::eBehavior behavior) /* override */;

    //0x00572FF0
    /* virtual */ void post_handle_resources(eBehavior) /* override */;
};

extern void entity_resource_handler_patch();
