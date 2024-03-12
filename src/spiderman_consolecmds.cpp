#include "spiderman_consolecmds.h"

#include "console.h"
#include "us_lighting.h"
#include "trace.h"
#include "wds.h"

static AmbientLightCommand g_AmbientLightCommand {};

AmbientLightCommand::AmbientLightCommand()
{
    TRACE("AmbientLightCommand::AmbientLightCommand");
    this->setName("amb_light");
}

bool AmbientLightCommand::process_cmd(const std::vector<std::string> &a2)
{
    auto *hero_ptr = g_world_ptr()->get_hero_ptr(0);
    auto *mgr = hero_ptr->get_light_set();
    assert(mgr != nullptr);

    if ( a2.size() != 1 && a2.size() != 3 )
    {
        assert(0 && "This command is no supported until we figure out what to do with that damn lites structure");
        g_console->addToLog("Ambient light:");
    }

    return true;
}

static SetTimeOfDayCommand g_SetTimeOfDayCommand{};

SetTimeOfDayCommand::SetTimeOfDayCommand()
{
    this->setName("tod");
}

bool SetTimeOfDayCommand::process_cmd(const std::vector<std::string> &a2)
{
    if ( a2.size() == 1 )
    {
        auto &v2 = a2.at(0);
        auto *v6 = v2.c_str();
        auto v5 = v6[0] - '0';
        if ( v5 > 3 || v6[1] ) {
            assert("Time of day out of range!");
        }

        us_lighting_switch_time_of_day(v5);
    }
    else
    {
        auto *v3 = this->helpText();
        g_console->addToLog(v3);
    }

    return true;
}

#if 1

#include "ngl_mesh.h"
#include "ngl_scene.h"
#include "nglrendernode.h"
#include "us_person.h"

static SetBlendModeCommand g_SetBlendModeCommand {};

SetBlendModeCommand::SetBlendModeCommand()
{
    this->setName("blend");
}

bool SetBlendModeCommand::process_cmd(const std::vector<std::string> &a2)
{
    TRACE("SetBlendModeCommand::process_cmd");
    if ( a2.size() == 1 )
    {
        auto &v2 = a2.at(0);
        auto *v6 = v2.c_str();
        int mode = v6[0] - '0';

        if (mode < 0 || mode > 8)
        {
            return true;
        }

        auto *hero = g_world_ptr()->get_hero_ptr(0);
        auto *mesh = hero->get_mesh();
        sp_log("debug!!");

        for ( auto i = 0u; i < mesh->NSections; ++i )
        {
            auto *MeshSection = mesh->Sections[i].Section;

            sp_log("debug!!");
            auto *Material = MeshSection->Material;
            sp_log("debug!!");
            Material->m_blend_mode = static_cast<nglBlendModeType>(mode);
        }
    }
    else
    {
        auto *v3 = this->helpText();
        g_console->addToLog(v3);
    }

    return true;
}
#endif
