#include "app.h"

#include "actor.h"
#include "ambient_audio_manager.h"
#include "audio_box_manager.h"
#include "collide.h"
#include "comic_panels.h"
#include "common.h"
#include "custom_math.h"
#include "cut_scene_player.h"
#include "damage_morphs.h"
#include "debug_menu.h"
#include "event_manager.h"
#include "femanager.h"
#include "fixedstring.h"
#include "frontendmenusystem.h"
#include "func_wrapper.h"
#include "gab_manager.h"
#include "game.h"
#include "geometry_manager.h"
#include "input_mgr.h"
#include "link_system.h"
#include "log.h"
#include "memory.h"
#include "mission_stack_manager.h"
#include "ngl.h"
#include "nlPlatformEnum.h"
#include "os_developer_options.h"
#include "pc_input_mgr.h"
#include "physics_system.h"
#include "resource_manager.h"
#include "scratchpad_stack.h"
#include "script_memtrack.h"
#include "script_sound_manager.h"
#include "smoke_test.h"
#include "sound_manager.h"
#include "spider_monkey.h"
#include "string_hash_dictionary.h"
#include "timer.h"
#include "tokenizer.h"
#include "trace.h"
#include "trigger_manager.h"
#include "unit_tests.h"
#include "utility.h"
#include "window_manager.h"

#include <cassert>

VALIDATE_SIZE(app, 0x3Cu);

VALIDATE_OFFSET(app, m_game, 0x30);

Var<app *> app::instance{0x009685D4};

Var<nglTexture *> g_shadow_target_blurred{0x00966EF4};

Var<int> dword_966F8C{0x00966F8C};

Var<nglTexture *> g_shadow_target_unblurred{0x00965F48};

void sub_592E40() {
    nglTexture **v0 = &g_shadow_target_blurred();
    do {
        if (*v0 != nullptr) {
            nglDestroyTexture(*v0);
        }

        v0 += 19;
    } while ((signed int) v0 < (signed int) &dword_966F8C());

    if (g_shadow_target_unblurred() != nullptr) {
        nglDestroyTexture(g_shadow_target_unblurred());
    }
}

//0x00592E80
void init_shadow_targets() {
#ifdef ENABLE_DEBUG_MENU
    debug_menu::init();
#endif

    sub_592E40();

    nglTexture **v0 = &g_shadow_target_blurred();
    tlFixedString v1;
    do {
        *v0 = nglCreateTexture(4609, 128, 128, 0, 1);
        v1 = tlFixedString{"blurred shadow texture"};
        (*v0)->field_60 = v1;
        v0 += 19;
    } while ((signed int) v0 < (signed int) &dword_966F8C());

    g_shadow_target_unblurred() = nglCreateTexture(4609u, 256, 256, 0, 1);

    g_shadow_target_unblurred()->field_60 = tlFixedString{"unblurred shadow"};
}

void set_god_mode(int a1) {
    Var<bool> god_mode_cheat{0x0095A6A8};
    Var<bool> ultra_god_mode_cheat{0x0095A6A9};
    Var<bool> mega_god_mode_cheat{0x0095A6AA};

    god_mode_cheat() = false;
    ultra_god_mode_cheat() = false;
    mega_god_mode_cheat() = false;
    switch (a1) {
    case 1:
        god_mode_cheat() = true;
        return;
    case 2:
        god_mode_cheat() = true;
        ultra_god_mode_cheat() = true;
        break;
    case 3:
        god_mode_cheat() = true;
        mega_god_mode_cheat() = true;
        break;
    case 4:
        ultra_god_mode_cheat() = true;
        break;
    case 5:
        mega_god_mode_cheat() = true;
        break;
    }
}

void colgeom_init_lists() {
    CDECL_CALL(0x00544E90);
}

void colgeom_destroy_lists()
{
    CDECL_CALL(0x005489A0);
}

app::app() : m_vtbl(0x00891634), field_4(), field_34() {
    g_platform() = NL_PLATFORM_PC;
    if (link_system::use_link_system()) {
        /*
        link_system::init();
        link_system::add_recipient(spider_monkey::link_receive);
        link_system::add_recipient(game::link_receive);
        */
        mem_print_stats("after link_system::init()");
    }

#ifdef ENABLE_DEBUG_MENU
    debug_menu::init();
#endif

    init_shadow_targets();
    mem_print_stats("after init_shadow_targets()");

    this->field_34.sub_58E230();
    this->field_38 = 0;
    geometry_manager::create_inst();
    string_hash_dictionary::create_inst();
    event_manager::create_inst();

    trigger_manager::instance() = new trigger_manager();
    pc_input_mgr::create_inst();
    input_mgr::create_inst();
    sound_manager::create_inst();
    script_sound_manager::create_inst();
    ambient_audio_manager::create_inst();
    if (!os_developer_options::instance()->get_flag(105)) { //DISABLE_AUDIO_BOXES
        audio_box_manager::create_inst();
    }

    gab_manager::create_inst();

    set_god_mode(os_developer_options::instance()->get_int(29)); //GOD_MODE

    colgeom_init_lists();
    physics_system_init();

    this->m_game = new game{};
    g_game_ptr() = this->m_game;

    resource_manager::create_inst();
    if (os_developer_options::instance()->get_int(9) > 0) { //MONKEY_MODE
        spider_monkey::start();
    }

    damage_morphs::init_memory_pools();

    {
        auto *inst = mission_stack_manager::get_instance();
        inst->start_streaming();
    }
}

void app::destructor_internal() {
    this->m_vtbl = 0x00891634;
    auto *p_game = this->m_game;
    if (p_game != nullptr) {
        delete p_game;
    }

    g_game_ptr() = nullptr;
    this->m_game = nullptr;
    cleanup();
    //debug_menu::deinit(); // link_system::un_init()
    //physics_system_shutdown();

    CDECL_CALL(0x00592CF0);

    //mString::destructor(&this->field_4.field_0);
    this->m_vtbl = 0x0088E4C8;
}

app::~app() {
    sp_log("app::~app():");

    if constexpr (1) {
        this->destructor_internal();
    } else {
        THISCALL(0x005E99D0, this);
    }
}

void app::internal::begin_screen_recording(const mString &a2, int a3) {
    if (this->field_18 != 2) {
        this->field_18 = 2;
        this->field_0 = a2;
        this->field_14 = 0;
        os_developer_options::instance()->set_int(mString{"CAMERA_CENTRIC_STREAMER"}, a3);
    }
}

void app::internal::end_screen_recording() {
    this->field_18 = 0;
    os_developer_options::instance()->set_int(mString{"CAMERA_CENTRIC_STREAMER"}, 0);
}

void app::internal::sub_5B8670() {
    if constexpr (1) {
        if (g_smoke_test() != nullptr) {
            g_smoke_test()->frame_advance();
        }
    }

    char Dest[64];

    auto v2 = this->field_18;
    if (v2) {
        if (v2 == 1) {
            sprintf(Dest, "screenshot%.4d", this->field_10++);
        } else {
            sprintf(Dest, "%s%.4d", this->field_0.c_str(), this->field_14++);
        }

        nglTexture *v6 = nglGetFrontBufferTex();
        nglSaveTexture(v6, Dest);
        if (this->field_18 == 1) {
            this->field_18 = 0;
        }
    }
}

void app::tick()
{
    TRACE("app::tick");

    if constexpr (0)
    {
        limited_timer_base local_timer;
        local_timer.sub_58E230();

        scratchpad_stack::reset();

        limited_timer_base total_timer;
        total_timer.sub_58E230();

        sub_77B2F0(0);

        float time_inc;
        for (time_inc = g_timer()->sub_5821D0(); equal(time_inc, 0.0f);
             time_inc = g_timer()->sub_5821D0()) {
            Sleep(0);
        }

        static Var<bool> byte_9682F0{0x009682F0};

        if (time_inc <= 0.0f) {
            byte_9682F0() = true;
            cut_scene_player *v2 = nullptr;

            if (g_smoke_test() != nullptr) {
                g_smoke_test()->frame_advance();
            }

            if (g_game_ptr()->flag.level_is_loaded && !g_game_ptr()->field_165 ||
                g_femanager().m_fe_menu_system != nullptr && g_femanager().m_fe_menu_system->sub_60C230() &&
                    (v2 = g_cut_scene_player(), v2->is_playing())) {
                comic_panels::render();
            } else if (g_femanager().m_fe_menu_system == nullptr || !g_femanager().m_fe_menu_system->sub_60C230()) {
                game::render_empty_list();
            }

            this->field_4.sub_5B8670();
            actor::swap_all_mesh_buffers();

        } else {
            slab_allocator::process_lists();
            script_memtrack::frame_advance();
            if (!IsWindow(window_manager::instance()->field_4)) {
                return;
            }

            event_manager::garbage_collect();
            input_mgr::instance()->poll_devices();

            assert(time_inc >= 0 && time_inc < 10.0f);

            static Var<float> dword_9682D0{0x009682D0};
            static Var<float> dword_9680A8{0x009680A8};

            dword_9682D0() = time_inc;
            dword_9680A8() = time_inc;
            nflUpdate();
            resource_manager::frame_advance(time_inc);
            link_system::frame_advance(time_inc);
            this->m_game->frame_advance(time_inc);
            byte_9682F0() = false;
        }

        if (os_developer_options::instance()->get_int(mString{"FRAME_LIMIT"}))
        {
            while (local_timer.elapsed() < 0.033333335) {
                ;
            }
        }

        this->m_game->field_278 = total_timer.elapsed();
        this->m_game->field_280 = 0;

    } else {
        THISCALL(0x005D6FC0, this);
    }
}

void app::create_inst()
{
    TRACE("app::create_inst");

#if 0
    app::instance() = new app{};
#else
    CDECL_CALL(0x005B2450);
#endif
}

void app::cleanup()
{
    TRACE("app::cleanup");

    if constexpr (0) {
        gab_manager::delete_inst();

        if ( !os_developer_options::instance()->get_flag(mString {"DISABLE_AUDIO_BOXES"}) ) { 
            audio_box_manager::delete_inst();
        }

        ambient_audio_manager::delete_inst();
        script_sound_manager::delete_inst();
        sound_manager::delete_inst();

        if ( input_mgr::instance() != nullptr )
        {
            delete input_mgr::instance();
            input_mgr::instance() = nullptr;
        }

        string_hash_dictionary::delete_inst();

        if ( pc_input_mgr::instance() != nullptr )
        {
            delete pc_input_mgr::instance();
            pc_input_mgr::instance() = nullptr;
        }

        if ( trigger_manager::instance() != nullptr )
        {
            delete trigger_manager::instance();
            trigger_manager::instance() = nullptr;
        }

        event_manager::delete_inst();
        colgeom_destroy_lists();
        resource_manager::delete_inst();
        nglReleaseAllMeshFiles();
        nglReleaseAllTextures();
    } else {
        CDECL_CALL(0x005D9430);
    }
}

void app_patch()
{

    REDIRECT(0x005AD2E9, app::create_inst);

    {
        FUNC_ADDRESS(address, &app::tick);
        REDIRECT(0x005AD495, address);
    }
    return;

    {
        FUNC_ADDRESS(address, &app::internal::sub_5B8670);
        SET_JUMP(0x005B8670, address);
    }

    if constexpr (0) {
        FUNC_ADDRESS(address, &app::destructor_internal);
        //REDIRECT(0x005E99D3, address);

        //REDIRECT(0x005E10BF, tokenizer_unit_test);
        //REDIRECT(0x005E10BF, collide_unit_test);
        REDIRECT(0x005E10BF, mString_unit_test);
    }

    REDIRECT(0x005E10EE, init_shadow_targets);

}
