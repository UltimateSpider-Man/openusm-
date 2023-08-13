#include "mission_table_container.h"

#include "entity_base_vhandle.h"
#include "wds.h"
#include "actor.h"
#include "ai_player_controller.h"

bool mission_table_container::append_script_info(_std::vector<mission_table_container::script_info> *info)
{
    assert(info != nullptr);

    bool v9 = false;
    for ( auto &v6 : this->field_38 )
    {
        if ( v6.applies_to_current_hero() )
        {
            auto v5 = v6.instances.size();
            for ( auto i = 0u; i < v5; ++i )
            {
                script_info v3;
                v3.field_0 = v6.field_18;
                v3.field_4 = &v6.instances.at(i);
                v3.field_8 = i;
                info->push_back(v3);
                v9 = true;
            }
        }
    }

    return v9;
}

void mission_table_container::un_mash(generic_mash_header *a2, void *a3, void *a4, generic_mash_data_ptrs *a5)
{
    THISCALL(0x005C6010, this, a2, a3, a4, a5);
}

bool mission_condition::applies_to_current_hero()
{
    //entity_base_vhandle INVALID_HANDLE {0};
    //assert(g_world_ptr()->get_hero_ptr( 0 ) != INVALID_HANDLE);

    assert(g_world_ptr()->get_hero_ptr( 0 ) != nullptr);

    assert(bit_cast<actor*>(g_world_ptr()->get_hero_ptr( 0 ))->get_player_controller() != nullptr);

    auto *v8 = bit_cast<actor*>(g_world_ptr()->get_hero_ptr( 0 ))->get_player_controller();
    auto v15 = v8->field_420;
    if ( v15 == 1 )
    {
        if ( this->is_flag_set(0x8000) )
        {
            return true;
        }
    }
    else if ( v15 == 2 )
    {
        if ( this->is_flag_set(0x4000) )
        {
            return true;
        }
    }
    else if ( v15 == 3 && this->is_flag_set(0x10000) )
    {
        return true;
    }

    return false;
}

const char *mission_condition_instance::get_script_data_name()
{
    if ( !this->is_flag_set(8) )
    {
        return nullptr;
    }

    //assert(script_data_name != nullptr);

    return this->script_data_name;
}
