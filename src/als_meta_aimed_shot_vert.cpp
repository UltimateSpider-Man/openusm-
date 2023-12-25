#include "als_meta_aimed_shot_vert.h"

#include "common.h"
#include "nal_system.h"
#include "trace.h"
#include "utility.h"

namespace als {

VALIDATE_SIZE(meta_aimed_shot_vert, 0x30);

float meta_aimed_shot_vert::get_anim_duration() const
{
    TRACE("als::meta_aimed_shot_vert::get_anim_duration");

    auto *v1 = this->field_28;
    if ( v1 != nullptr ) {
        return v1->field_38;
    }
    
    return 1.0f;
}

}

void als_meta_aimed_shot_vert_patch()
{
    {
        FUNC_ADDRESS(address, &als::meta_aimed_shot_vert::get_anim_duration);
        SET_JUMP(0x004518D0, address);
    }
}


