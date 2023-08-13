#pragma once

#include "enhanced_state.h"

#include "float.hpp"
#include "string_hash.h"
#include "variable.h"
#include "vector3d.h"

struct plr_loco_crawl_state : ai::enhanced_state {
    int field_30;
    float m_wallrun_deviation;
    vector3d field_38;
    int field_44;

    plr_loco_crawl_state();

    static const inline string_hash default_id{to_hash("crawl")};

    //0x0044B760
    //virtual
    void update_wallrun(Float a2);
};
