#pragma once

#include "string_hash.h"
#include "variable.h"

struct plr_loco_crawl_transition_state {
    plr_loco_crawl_transition_state();

    static const inline string_hash default_id{to_hash("crawl_transition")};
};
