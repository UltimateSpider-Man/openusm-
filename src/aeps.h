#pragma once

#include "variable.h"

#include "float.hpp"

struct aeps {
    //0x004D3980
    static void FrameAdvance(Float a1);

    //0x004CDFC0
    static void RefreshDevOptions();

    static Var<void *> s_activeStructs;

    //0x004D91A0
    static int Reset();

    static void Init();
};

extern void aeps_patch();
