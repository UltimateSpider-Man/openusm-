#pragma once

#include "float.hpp"

namespace als {

    namespace animation_logic_system_interface 
    {
        void frame_advance_pre_controller_all_alses(Float a1);

        //0x00492FC0
        void force_update(Float a2);
    }

}


extern void als_animation_logic_system_interface_patch();
