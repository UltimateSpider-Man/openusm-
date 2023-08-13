#pragma once

#include "astar.h"

struct quad_path_cell_astar_search_record : astar_search_record {
    _std::vector<void *> field_24;

    //0x0048F940
    quad_path_cell_astar_search_record();

    /* virtual */ void setup(void *a2, void *a3);
};
