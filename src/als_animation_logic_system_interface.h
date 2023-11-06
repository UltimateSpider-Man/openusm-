#pragma once

#include "float.hpp"

namespace als {

    struct animation_logic_system_interface 
    {
        static void frame_advance_pre_controller_all_alses(Float a1);

        void force_update();

        //0x00492FC0
        void force_update(Float a2);
    };

}


extern void als_animation_logic_system_interface_patch();
