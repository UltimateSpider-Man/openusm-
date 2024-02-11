#pragma once

#include "singleton.h"

#include "input_device.h"
#include "variable.h"

struct pc_joypad_device;

struct pc_input_mgr : singleton {
    pc_joypad_device *pad[4];

    //0x0059B930
    pc_input_mgr();

    static inline Var<pc_input_mgr *> instance{0x00967BB0};

    //0x005E2C30
    static void create_inst();
};
