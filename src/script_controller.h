#pragma once

#include "signaller.h"

struct script_controller : signaller {
    //0x0064E300
    script_controller();

    //0x0065F8A0
    //virtual;
    void update();
};

extern Var<script_controller *> script_pad;

extern void script_controller_patch();
