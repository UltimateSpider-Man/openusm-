#pragma once

#include "float.hpp"

struct web_interface {
    web_interface();

    //0x004F2AC0
    static void frame_advance_all_web_interfaces(Float a1);
};

extern void web_interface_patch();
