#include "std_puppet_trans_state.h"

#include "func_wrapper.h"
#include "common.h"

namespace ai
{
    VALIDATE_SIZE(std_puppet_trans_state, 0x1C);

    std_puppet_trans_state::std_puppet_trans_state()
    {
        THISCALL(0x00438C80, this);
    }
}
