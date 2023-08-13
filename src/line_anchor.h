#pragma once

#include "line_marker_base.h"

struct line_anchor : line_marker_base {
    line_anchor(const string_hash &a2, uint32_t a3);

    //virtual
    bool is_a_line_anchor();
};

extern void line_anchor_patch();
