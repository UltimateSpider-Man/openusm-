#include "game_settings.h"

#include "common.h"
#include "damage_interface.h"
#include "func_wrapper.h"
#include "game.h"
#include "memory.h"
#include "mission_manager.h"
#include "mstring.h"
#include "os_developer_options.h"
#include "resource_key.h"
#include "rumble_manager.h"
#include "script_manager.h"
#include "settings.h"
#include "sound_manager.h"
#include "trace.h"
#include "utility.h"
#include "variables.h"
#include "wds.h"

#include <cassert>

VALIDATE_SIZE(game_settings, 0x4CCu);

#if USE_CXX_CONSTRUCTOR

void __stdcall vector_constructor(void *a1,
                                  uint32_t size,
                                  int count,
                                  thiscall_call constructor,
                                  [[maybe_unused]] thiscall_call destructor) {
    FUNC_ADDRESS(address, &game_data_essentials::initialize);

    constructor = bit_cast<decltype(constructor)>(address);

    for (int i{0}; i < count; ++i) {
        constructor(static_cast<int *>(a1));
        a1 = static_cast<char *>(a1) + size;
    }
}
#endif

game_settings::game_settings() : field_4{""} {
    if constexpr (1) {
        this->m_vtbl = 0x0088B234;

        auto *v2 = this->field_4BC;
        v2[0] = false;
        v2[1] = false;
        v2[2] = false;
        this->field_4BF = 0;
        this->field_4C0 = 0;
        this->field_4C1 = false;
        this->field_4C2 = 0;
        this->field_4BF = 0;
        this->field_494 = nullptr;
        this->field_498 = nullptr;
        this->field_4BC[0] = false;
        this->field_49C[0] = nullptr;
        this->field_4BC[1] = false;
        this->field_49C[1] = nullptr;
        this->field_4BC[2] = false;
        this->field_49C[2] = nullptr;

        MemoryUnitManager::Initialize(0);

        [[maybe_unused]] auto v4 = os_developer_options::instance()->get_string(os_developer_options::strings_t::SKU);

        MemoryUnitManager::RegisterObserver(bit_cast<MemoryUnitManager::Observer *>(this));

        this->set_script_buffer_size();

        //this->set_cur_name(Source());
        strncpy(this->field_4A8, "", 12u);
        this->field_4A8[11] = '\0';

        this->field_4C0 = 0;
        this->field_4B8 = 0;
        this->field_4C2 = 0;
        this->m_slot_num = 0;
        this->field_4C8 = 0;
    } else {
        THISCALL(0x0057BF50, this);
    }
}

void game_settings::Callback(MemoryUnitManager::eOperation a2) {
    THISCALL(0x0057C0B0, this, a2);
}

void game_settings::init_script_buffer()
{
    if constexpr (1) {
        this->sub_579990();
        script_manager::save_game_var_buffer(this->field_494);
        script_manager::save_game_var_buffer(this->field_498);

    } else {
        THISCALL(0x005799E0, this);
    }
}

void game_settings::update_miles_crawled_venom(Float a2)
{
    this->field_340.field_C0 += a2 * 0.0006213712;
}

void game_settings::update_miles_crawled_spidey(Float a2)
{
    this->field_340.field_98 += a2 * 0.0006213712;
}

void game_settings::start_new_game() {
    THISCALL(0x0057EAB0, this);
}

void game_settings::frame_advance(Float a2)
{
    TRACE("game_settings::frame_advance");

    if constexpr (1)
    {
        if (this->field_4C2 && ++this->field_4C8 > 2) {
            this->load_game(this->m_slot_num);
        }

    } else {
        THISCALL(0x005802D0, this, a2);
    }
}

void game_settings::export_game_options() {
    sound_manager::set_source_type_volume(0, Settings::GameSoundVolume(), 0.0);
    sound_manager::set_source_type_volume(1u, Settings::GameSoundVolume(), 0.0);
    sound_manager::set_source_type_volume(2u, Settings::MusicVolume(), 0.0);
    sound_manager::set_source_type_volume(3u, Settings::GameSoundVolume(), 0.0);
    sound_manager::set_source_type_volume(4u, Settings::GameSoundVolume(), 0.0);
    sound_manager::set_source_type_volume(5u, Settings::GameSoundVolume(), 0.0);
    sound_manager::set_source_type_volume(6u, Settings::GameSoundVolume(), 0.0);
    sound_manager::set_source_type_volume(7u, Settings::GameSoundVolume(), 0.0);
    auto *v2 = input_mgr::instance()->rumble_ptr;
    if (this->field_340.field_31) {
        v2->enable_vibration();
    } else {
        v2->disable_vibration();
    }

    if (g_world_ptr()->get_hero_ptr(0) != nullptr) {
        mString a1{"gv_hero_spawn_point"};

        auto *v3 = (const vector3d *) script_manager::get_game_var_address(a1, nullptr, nullptr);

        g_world_ptr()->sub_530460(*v3, 0, 0);
    }
}

void game_settings::export_game_settings() {
    if (g_world_ptr() != nullptr) {
        auto *v1 = g_world_ptr()->get_hero_ptr(0);
        if (v1 != nullptr) {
            if (v1->has_damage_ifc()) {
                auto &v3 = v1->damage_ifc()->field_1FC[2];
                auto *v2 = v1->damage_ifc();
                v2->field_1FC.sub_48BFB0(v3);
            }
        }
    }
}

static constexpr auto NUM_SOFT_SAVE_BUFFERS = 2;

void game_settings::soft_load(uint32_t soft_save_type) {
    if constexpr (1) {
        assert(soft_save_type < NUM_SOFT_SAVE_BUFFERS);

        if (soft_save_type == 1) {
            std::memcpy(this->field_494, this->field_498, this->field_4B4);
        }

        g_game_ptr()->field_15D = false;
        this->field_4C0 = false;
        this->export_game_settings();
        script_manager::load_game_var_buffer((&this->field_494)[soft_save_type]);
        mission_manager::s_inst()->set_real_time();

    } else {
        THISCALL(0x0057C1E0, this, soft_save_type);
    }
}

void game_settings::update_miles_run_venom(Float a2) {
    this->field_340.field_BC += a2 * 0.0006213712f;
}

void game_settings::update_miles_web_zipping(Float a2) {
    this->field_340.m_miles_web_zipping += a2 * 0.0006213712f;
}

void game_settings::update_miles_run_spidey(Float a2) {
    this->field_340.field_94 += a2 * 0.0006213712f;
}

void game_settings::set_script_buffer_size() {
    this->field_4B4 = script_manager::save_game_var_buffer(nullptr);
}

void game_settings::update_web_fluid_used(Float a2) {
    this->field_340.m_web_fluid_used += a2;
}

void game_settings::load_game(int slot_num) {
    if constexpr (1) {
        if (this->field_4C2) {
            if (this->field_4C8 > 2) {
                this->field_4C2 = false;
                this->start_new_game();
                mission_manager::s_inst()->lock();
                this->field_4C1 = 1;
                this->field_4C1 = 0;
                std::memcpy(&this->field_340,
                            this->field_49C[slot_num] + 60,
                            sizeof(this->field_340));
                this->sub_579990();
                std::memcpy(this->field_494, this->field_49C[slot_num] + 400, this->field_4B4);
                std::memcpy(this->field_498,
                            &this->field_49C[slot_num][this->field_4B4 + 400],
                            this->field_4B4);
                this->field_4BF = true;
                this->soft_load(0);
                this->export_game_settings();
                this->export_game_options();

                std::memcpy(this->field_4A8,
                            this->field_28C[slot_num].field_2E,
                            sizeof(this->field_4A8));

                this->field_4B8 = slot_num;
                auto *v4 = g_world_ptr()->get_chase_cam_ptr(0);
                g_game_ptr()->set_current_camera(v4, true);
            }
        } else {
            this->field_4C2 = true;
            this->field_4C8 = 0;
            this->m_slot_num = slot_num;
            mission_manager::s_inst()->unload_script_now();
            auto v3 = g_world_ptr()->num_players;
            if (v3 > 0) {
                g_world_ptr()->remove_player(v3 - 1);
            }
        }

    } else {
        THISCALL(0x0057F410, this, slot_num);
    }
}

void game_settings::load_most_recent_game() {
    THISCALL(0x0057F580, this);
}

int *GetSystemDate(int *out) {
    return (int *) CDECL_CALL(0x00573510, out);
}

void game_settings::collect_game_settings() {
    if constexpr (1) {
        if (g_world_ptr() != nullptr) {
            auto *hero_ptr = g_world_ptr()->get_hero_ptr(0);
            if (hero_ptr != nullptr) {
                if (hero_ptr->has_damage_ifc()) {
                    this->field_340.m_hero_health = hero_ptr->damage_ifc()->field_1FC[0];
                    this->field_4BF = true;
                    return;
                }

                this->field_340.m_hero_health = 0.0;
            }
        }

        this->field_4BF = true;

    } else {
        THISCALL(0x00579B90, this);
    }
}

void game_settings::sub_579990() {
    if constexpr (1) {
        if (this->field_494 == nullptr) {
            if (this->field_4B4 == 0) {
                this->set_script_buffer_size();
            }

            this->field_494 = static_cast<char *>(arch_malloc(this->field_4B4));
            this->field_498 = static_cast<char *>(arch_malloc(this->field_4B4));
        }

    } else {
        THISCALL(0x00579990, this);
    }
}

void game_settings::collect_game_options() {
    THISCALL(0x00579BF0, this);
}

char *game_settings::get_buffer(int a2) {
    return this->field_49C[a2];
}

void game_settings::save(int slot_num) {
    if constexpr (1) {
        static constexpr auto MAX_GAMEFILE_SLOTS = 3;

        assert(slot_num >= 0 && slot_num <= MAX_GAMEFILE_SLOTS);

        auto &v1 = this->field_28C[slot_num];

        strncpy(v1.field_14, "02:29:05", 25u);
        strncpy(v1.field_2E, this->field_4A8, 12u);

        auto a2a = *(float *) script_manager::get_game_var_address(mString{"real_world_timer"},
                                                                   nullptr,
                                                                   nullptr);

        v1.field_C = (int) a2a;

        int v7[3];
        auto *v5 = GetSystemDate(v7);

        *((int *) &v1.field_0) = v5[0];
        *((int *) &v1.field_4) = v5[1];
        *((int *) &v1.field_8) = v5[2];
        v1.field_10 = this->field_4B4;
        this->field_4BC[slot_num] = true;
        this->collect_game_settings(); // game_settings::soft_save()
        this->sub_579990();
        script_manager::save_game_var_buffer((char *) this->field_494);
        this->collect_game_options();
        if (!this->field_4B4) { // game_settings::get_game_size()
            this->field_4B4 = script_manager::save_game_var_buffer(nullptr);
        }

        auto size = 2 * this->field_4B4 + 400;

        static constexpr auto MAX_GAME_SIZE = 16384;
        assert(size <= MAX_GAME_SIZE &&
               "Uh-oh!!  We've exceeded the maximum size for our save game!!!");

        if (size < 16384) {
            size = 16384;
        }

        memset(this->field_49C[slot_num], 0, MemoryUnitManager::GetGameSaveSize(size));
        std::memcpy(this->field_49C[slot_num], &v1, sizeof(game_data_essentials));
        std::memcpy(this->field_49C[slot_num] + sizeof(game_data_essentials),
                    &this->field_340,
                    sizeof(game_data_meat));
        std::memcpy(this->field_49C[slot_num] + sizeof(game_data_essentials) +
                        sizeof(game_data_essentials),
                    this->field_494,
                    this->field_4B4);
        std::memcpy(&this->field_49C[slot_num][this->field_4B4 + 400],
                    this->field_498,
                    this->field_4B4);

        if (!MemoryUnitManager::SaveGame(this->field_4)) {
            g_game_ptr()->field_15D = false;
        }

        this->field_4B8 = slot_num;

    } else {
        THISCALL(0x0057D460, this, slot_num);
    }
}

bool game_settings::set_num(const resource_key &att, Float a3) {
    assert(att.get_type() == RESOURCE_KEY_TYPE_IFC_ATTRIBUTE);

    return (bool) THISCALL(0x00573AE0, this, &att, a3);
}

bool game_settings::get_num(const resource_key &att, float &a3, bool a4) {
    assert(att.get_type() == RESOURCE_KEY_TYPE_IFC_ATTRIBUTE);

    return (bool) THISCALL(0x00575930, this, &att, &a3, a4);
}

void game_settings_patch() {
    {
        FUNC_ADDRESS(address, &game_settings::frame_advance);
        REDIRECT(0x0055D770, address);
    }

    if constexpr (0) {
        {
            FUNC_ADDRESS(address, &game_settings::load_game);
            //REDIRECT(0x005802F8, address);
        }
    }
}
