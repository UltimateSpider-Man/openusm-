#include "ai_pedestrian.h"

#include "ai_std_combat_target.h"
#include "ai_team.h"
#include "base_ai_core.h"

namespace ai {

bool pedestrian_inode::is_a_pedestrian(ai::ai_core *a1)
{
    if ( a1 != nullptr )
    {
        auto *p_pb = a1->get_param_block();
        if ( p_pb->does_parameter_exist(combat_target_inode::team_hash()) )
        {
            auto pb_hash = p_pb->get_pb_hash(combat_target_inode::team_hash());
            if ( team::manager::get_team_enum_by_hash(pb_hash) == 14 ) {
                return true;
            }
        }
    }
    return false;
}

}
