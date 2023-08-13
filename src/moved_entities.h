#pragma once

#include "entity.h"
#include "entity_base_vhandle.h"
#include "variable.h"

struct intraframe_trajectory_t;

namespace moved_entities {

    struct trajectory_filter_t {
        std::intptr_t m_vtbl;
    };

    //0x005125D0
    void reset_all_moved();

    //0x00533D00
    void add_moved(vhandle_type<entity> a1);

    intraframe_trajectory_t *get_all_trajectories(
        Float a1, const moved_entities::trajectory_filter_t *filter);

    inline Var<int> moved_count{0x0095C890};

    inline Var<vhandle_type<entity>[600]> moved_list{0x0095EFC8};
};

extern void moved_entities_patch();
