#pragma once

#include <vector.hpp>

struct astar_node;

struct astar_priority_queue {
    _std::vector<astar_node *> field_0;

    astar_priority_queue();
};
