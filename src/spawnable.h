#pragma once

#include "entity.h"
#include "entity_base_vhandle.h"
#include "float.hpp"
#include "traffic_path_graph.h"
#include "variable.h"

#include <cstdint>

struct actor;

struct spawnable {
    std::intptr_t m_vtbl;
    bool field_4;
    bool field_5;

    spawnable(vhandle_type<entity>);

    //virtual
    void un_spawn();

    //virtual
    actor *get_my_actor();

    //0x006D8610
    static void advance_traffic_and_peds(Float a1);

    static inline Var<_std::vector<traffic_path_graph::laneInfoStruct> *> 
        spawnable_lanes {0x0096C9B0};
};

extern void spawnable_patch();
