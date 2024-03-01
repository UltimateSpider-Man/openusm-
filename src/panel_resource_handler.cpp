#include "panel_resource_handler.h"

#include "combo_words.h"
#include "common.h"
#include "fe_crosshair.h"
#include "fe_distance_chase.h"
#include "fe_distance_race.h"
#include "fe_health_widget.h"
#include "fe_hotpursuit_indicator.h"
#include "fe_score_widget.h"
#include "femanager.h"
#include "igofrontend.h"
#include "medal_award_ui.h"
#include "race_announcer.h"
#include "resource_location.h"
#include "tutorial_controller_gauge.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

VALIDATE_SIZE(panel_resource_handler, 0x14);

panel_resource_handler::panel_resource_handler(worldly_pack_slot *a2)
{
    this->m_vtbl = 0x00888AC4;
    this->my_slot = a2;
    this->field_10 = RESOURCE_KEY_TYPE_PANEL;
}

bool panel_resource_handler::_handle(worldly_resource_handler::eBehavior a2, limited_timer *a3)
{
    TRACE("panel_resource_handler::handle");

    return base_engine_resource_handler::_handle(a2, a3);
}

//FIXME
bool panel_resource_handler::_handle_resource(worldly_resource_handler::eBehavior behavior,
                                             resource_location *a3)
{
    TRACE("panel_resource_handler::handle_resource");

    if constexpr (0)
    {
        if (behavior == worldly_resource_handler::UNLOAD) {
            if (g_femanager().IGO != nullptr) {
                auto v42 = a3->field_0.m_hash;
                if (v42 == string_hash{"HG_HERO_PETER"}) {
                    g_femanager().IGO->hero_health->DeInit(5);
                    ++this->field_C;
                    return false;
                }

                auto v43 = a3->field_0.m_hash;
                if (v43 == string_hash{"HG_HERO_SPIDERMAN"}) {
                    g_femanager().IGO->hero_health->DeInit(0);
                    ++this->field_C;
                    return false;
                }

                if (a3->field_0.m_hash == string_hash{"HG_HERO_SPIDERMAN_EX_01"}) {
                    g_femanager().IGO->hero_health->DeInit(1);
                    ++this->field_C;
                    return false;
                }

                if (a3->field_0.m_hash == string_hash{"HG_HERO_SPIDERMAN_EX_02"}) {
                    g_femanager().IGO->hero_health->DeInit(2);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_HERO_SPIDERMAN_EX_03"}) {
                    g_femanager().IGO->hero_health->DeInit(3);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_HERO_VENOM"}) {
                    g_femanager().IGO->hero_health->DeInit(4);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_TP_SABLE"}) {
                    g_femanager().IGO->third_party_health->DeInit(1);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_TP_SPIDERMAN"}) {
                    g_femanager().IGO->third_party_health->DeInit(0);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_TP_WOLVERINE"}) {
                    g_femanager().IGO->third_party_health->DeInit(2);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_BEETLE"}) {
                    g_femanager().IGO->boss_health->DeInit(2);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_CARNAGE"}) {
                    g_femanager().IGO->boss_health->DeInit(3);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_ELECTRO_NOSUIT"}) {
                    g_femanager().IGO->boss_health->DeInit(9);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_ELECTRO_SUIT"}) {
                    g_femanager().IGO->boss_health->DeInit(10);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_GOBLIN"}) {
                    g_femanager().IGO->boss_health->DeInit(7);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_MYSTIQUE"}) {
                    g_femanager().IGO->boss_health->DeInit(11);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_RHINO"}) {
                    g_femanager().IGO->boss_health->DeInit(5);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_SABLE"}) {
                    g_femanager().IGO->boss_health->DeInit(6);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_SHOCKER"}) {
                    g_femanager().IGO->boss_health->DeInit(8);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_SPIDERMAN"}) {
                    g_femanager().IGO->boss_health->DeInit(0);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_VENOM"}) {
                    g_femanager().IGO->boss_health->DeInit(1);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_WOLVERINE"}) {
                    g_femanager().IGO->boss_health->DeInit(4);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"COMBO_WORDS"}) {
                    g_femanager().IGO->field_48->DeInit();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"MG_HOTPURSUIT_INDICATOR"}) {
                    g_femanager().IGO->field_4C->DeInit();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HIGHSCORETRACKING"}) {
                    g_femanager().IGO->field_50->DeInit();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"MEDALS_INTERFACE"}) {
                    g_femanager().IGO->field_34->DeInit();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"RACE_ANNOUNCER"}) {
                    g_femanager().IGO->field_38->DeInit();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"TARGETING_RETICLE_VENOM"}) {
                    g_femanager().IGO->field_3C->DeInit();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CONTROLLER_TUT_GC"} ||
                    a3->field_0.m_hash == string_hash{"CONTROLLER_TUT_XB"} ||
                    a3->field_0.m_hash == string_hash{"CONTROLLER_TUT_PS"}) {
                    g_femanager().IGO->field_30->DeInit();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_BEETLE"}) {
                    g_femanager().IGO->field_18->DeInit(1);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_ELECTRO"}) {
                    g_femanager().IGO->field_18->DeInit(3);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_GOBLIN"}) {
                    g_femanager().IGO->field_18->DeInit(2);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_QUESTION"}) {
                    g_femanager().IGO->field_18->DeInit(6);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_RHINO"}) {
                    g_femanager().IGO->field_18->DeInit(0);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_SABLE"}) {
                    g_femanager().IGO->field_18->DeInit(4);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_VENOM"}) {
                    g_femanager().IGO->field_18->DeInit(5);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"RACE_METER"}) {
                    g_femanager().IGO->field_1C->DeInit();
                }
            }
        } else {
            if (a3->field_0.m_hash == string_hash{"HG_HERO_PETER"}) {
                g_femanager().IGO->hero_health->Init(5, "HG_HERO_PETER", 0);
                ++this->field_C;
                return 0;
            }

            if (a3->field_0.m_hash == string_hash{"HG_HERO_SPIDERMAN"}) {
                g_femanager().IGO->hero_health->Init(0, "HG_HERO_SPIDERMAN", false);

                static Var<bool> globaly_packed_bar_need_init{0x00922544};

                if (*globaly_packed_bar_need_init) {
                    g_femanager().IGO->hero_health->Init(1, "HG_HERO_SPIDERMAN_EX_01", false);
                    g_femanager().IGO->hero_health->Init(2, "HG_HERO_SPIDERMAN_EX_02", false);
                    g_femanager().IGO->hero_health->Init(3, "HG_HERO_SPIDERMAN_EX_03", false);
                    *globaly_packed_bar_need_init = false;
                    ++this->field_C;
                    return 0;
                }
            } else {
                if (a3->field_0.m_hash == string_hash{"HG_HERO_VENOM"}) {
                    g_femanager().IGO->hero_health->Init(4, "HG_HERO_VENOM", false);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_TP_SABLE"}) {
                    g_femanager().IGO->third_party_health->Init(1, "HG_TP_SABLE", false);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_TP_SPIDERMAN"}) {
                    g_femanager().IGO->third_party_health->Init(0, "HG_TP_SPIDERMAN", false);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_TP_WOLVERINE"}) {
                    g_femanager().IGO->third_party_health->Init(2, "HG_TP_WOLVERINE", false);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_BEETLE"}) {
                    g_femanager().IGO->boss_health->Init(2, "HG_BOSS_BEETLE", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_CARNAGE"}) {
                    g_femanager().IGO->boss_health->Init(3, "HG_BOSS_CARNAGE", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_ELECTRO_NOSUIT"}) {
                    g_femanager().IGO->boss_health->Init(9, "HG_BOSS_ELECTRO_NOSUIT", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_ELECTRO_SUIT"}) {
                    g_femanager().IGO->boss_health->Init(10, "HG_BOSS_ELECTRO_SUIT", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_GOBLIN"}) {
                    g_femanager().IGO->boss_health->Init(7, "HG_BOSS_GOBLIN", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_MYSTIQUE"}) {
                    g_femanager().IGO->boss_health->Init(11, "HG_BOSS_MYSTIQUE", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_RHINO"}) {
                    g_femanager().IGO->boss_health->Init(5, "HG_BOSS_RHINO", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_SABLE"}) {
                    g_femanager().IGO->boss_health->Init(6, "HG_BOSS_SABLE", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_SHOCKER"}) {
                    g_femanager().IGO->boss_health->Init(8, "HG_BOSS_SHOCKER", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_SPIDERMAN"}) {
                    g_femanager().IGO->boss_health->Init(0, "HG_BOSS_SPIDERMAN", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_VENOM"}) {
                    g_femanager().IGO->boss_health->Init(1, "HG_BOSS_VENOM", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HG_BOSS_WOLVERINE"}) {
                    g_femanager().IGO->boss_health->Init(4, "HG_BOSS_WOLVERINE", true);
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"COMBO_WORDS"}) {
                    g_femanager().IGO->field_48->Init();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"MG_HOTPURSUIT_INDICATOR"}) {
                    g_femanager().IGO->field_4C->Init();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"HIGHSCORETRACKING"}) {
                    g_femanager().IGO->field_50->Init();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"MEDALS_INTERFACE"}) {
                    g_femanager().IGO->field_34->Init();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"RACE_ANNOUNCER"}) {
                    g_femanager().IGO->field_38->Init();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"TARGETING_RETICLE_VENOM"}) {
                    g_femanager().IGO->field_3C->Init();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CONTROLLER_TUT_PS"} ||
                    a3->field_0.m_hash == string_hash{"CONTROLLER_TUT_XB"} ||
                    a3->field_0.m_hash == string_hash{"CONTROLLER_TUT_GC"}) {
                    g_femanager().IGO->field_30->Init();
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_BEETLE"}) {
                    g_femanager().IGO->field_18->Init(1, "CHASE_METER_BEETLE");
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_ELECTRO"}) {
                    g_femanager().IGO->field_18->Init(3, "CHASE_METER_ELECTRO");
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_GOBLIN"}) {
                    g_femanager().IGO->field_18->Init(2, "CHASE_METER_GOBLIN");
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_QUESTION"}) {
                    g_femanager().IGO->field_18->Init(6, "CHASE_METER_QUESTION");
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_RHINO"}) {
                    g_femanager().IGO->field_18->Init(0, "CHASE_METER_RHINO");
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_SABLE"}) {
                    g_femanager().IGO->field_18->Init(4, "CHASE_METER_SABLE");
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"CHASE_METER_VENOM"}) {
                    g_femanager().IGO->field_18->Init(5, "CHASE_METER_VENOM");
                    ++this->field_C;
                    return 0;
                }

                if (a3->field_0.m_hash == string_hash{"RACE_METER"}) {
                    g_femanager().IGO->field_1C->Init();
                    ++this->field_C;
                    return 0;
                }
            }
        }

        ++this->field_C;
        return 0;
    }
    else
    {
        return (bool) THISCALL(0x00571800, this, behavior, a3);
    }
}

void panel_resource_handler_patch()
{
    {
        FUNC_ADDRESS(address, &panel_resource_handler::_handle);
        set_vfunc(0x00888AC8, address);
    }

    {
        FUNC_ADDRESS(address, &panel_resource_handler::_handle_resource);
        set_vfunc(0x00888AD0, address);
    }
}
