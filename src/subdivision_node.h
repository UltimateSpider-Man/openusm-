#pragma once

#include "variable.h"

struct subdivision_node {
    enum type_t {
        PROXIMITY_MAP_NODE = 1,
        DYNAMIC_LEAF_LIST_NODE = 3,
        AABB_LEAF_NODE = 4,
        AABB_LARGE_LEAF_NODE = 5,
        OBB_LEAF_NODE = 6,
        OBB_LARGE_LEAF_NODE = 7,
        AUDIO_OBB_LEAF_NODE = 8,
        LEGO_LEAF_NODE = 9,
        STATIC_REGION_LIST_NODE = 11,
        DYNAMIC_ENTITY_LIST_NODE = 12,
        AABSP_NODE = 13,
        TOTAL_TYPES = 15

    };

    static inline auto & methods = var<void *[13]>(0x00960980);
};
