#pragma once

#include "progress.h"
#include "worldly_resource_handler.h"

#include <cstdint>

struct limited_timer;
struct worldly_pack_slot;

struct base_entity_resource_handler : worldly_resource_handler {
    base_entity_resource_handler();

    /* virtual */ ~base_entity_resource_handler() = default;

    //0x0055F850
    /* virtual */ bool _handle(eBehavior behavior, limited_timer *timer) /* override */;

    /* virtual */ int get_num_resources() /* = 0 */;

    /* virtual */ bool handle_resource(eBehavior behavior) /* = 0 */;

    /* virtual */ void post_handle_resources(eBehavior behavior);
};
