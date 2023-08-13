#pragma once

#include "vector3d.h"

struct ai_quad_path_cell {
    int field_0[20];

    ai_quad_path_cell();

    //0x004648C0
    vector3d get_edge_midpoint(ai_quad_path_cell *a3);

    //0x00452C60
    void un_mash(void *a2, int a3, int a4);
};
