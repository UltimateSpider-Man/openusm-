#pragma once

#include "variable.h"
#include "game_process.h"

struct hires_screenshot {
    struct params {
        static inline Var<int> width{0x0095C740};
        static inline Var<int> height{0x0095C744};
    };

    static inline Var<game_process> process{0x0092205C};
};
