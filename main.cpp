#include "forwards.h"

#include "aeps.h"
#include "ai_find_best_swing_anchor.h"
#include "ai_interact_resource_handler.h"
#include "ai_interaction_data.h"
#include "ai_path.h"
#include "ai_player_controller.h"
#include "ai_state_graph_resource_handler.h"
#include "ai_state_jump.h"
#include "ai_state_run.h"
#include "ai_state_swing.h"
#include "ai_state_web_zip.h"
#include "ai_std_hero.h"
#include "als_animation_logic_system.h"
#include "als_animation_logic_system_shared.h"
#include "als_animation_logic_system_interface.h"
#include "als_basic_rule_data.h"
#include "als_category.h"
#include "als_inode.h"
#include "als_meta_anim_base.h"
#include "als_meta_anim_swing.h"
#include "als_meta_aimed_shot_vert.h"
#include "als_meta_anim_table_shared.h"
#include "als_mocomp.h"
#include "als_motion_compensator.h"
#include "als_resource_handler.h"
#include "als_res_data.h"
#include "als_simple_orientation.h"
#include "als_state.h"
#include "als_scripted_category.h"
#include "als_scripted_state.h"
#include "als_transition_group_base.h"
#include "alternate_costumes.h"
#include "anchor_query_visitor.h"
#include "animation_controller.h"
#include "animation_interface.h"
#include "anim_handle.h"
#include "anim_resource_handler.h"
#include "anim_record.h"
#include "app.h"
#include "base_ai_core.h"
#include "base_ai_res_state_graph.h"
#include "base_ai_resource_handler.h"
#include "base_ai_state_machine.h"
#include "base_tl_resource_handler.h"
#include "beam.h"
#include "box_trigger_resource_handler.h"
#include "cached_special_effect.h"
#include "camera.h"
#include "camera_mode.h"
#include "camera_target_info.h"
#include "character_anim_controller.h"
#include "character_pose_skel.h"
#include "character_viewer.h"
#include "charcomponentbase.h"
#include "chuck_callbacks.h"
#include "city_lights.h"
#include "city_lod.h"
#include "console.h"
#include "collide_aux.h"
#include "collision_capsule.h"
#include "colmesh.h"
#include "combat_state.h"
#include "combo_system.h"
#include "combo_system_move.h"
#include "common.h"
#include "conglom.h"
#include "core_ai_resource.h"
#include "cursor.h"
#include "custom_math.h"
#include "cut_scene.h"
#include "cut_scene_player.h"
#include "cut_scene_resource_handler.h"
#include "damage_interface.h"
#include "daynight.h"
#include "debug_struct.h"
#include "eligible_pack.h"
#include "eligible_pack_streamer.h"
#include "enhanced_state.h"
#include "entity_base.h"
#include "entity_base_vhandle.h"
#include "entity_handle_manager.h"
#include "entity_mash.h"
#include "event_manager.h"
#include "fe_dialog_text.h"
#include "fe_mini_map_widget.h"
#include "fe_mission_text.h"
#include "fefloatingtext.h"
#include "femanager.h"
#include "femenuentry.h"
#include "femultilinetext.h"
#include "fe_menu_nav_bar.h"
#include "filespec.h"
#include "fileusm.h"
#include "frontendmenusystem.h"
#include "func_wrapper.h"
#include "fx_cache.h"
#include "gab_database_resource_handler.h"
#include "game.h"
#include "game_camera.h"
#include "game_data_meat.h"
#include "game_settings.h"
#include "gamepadinput.h"
#include "geometry_manager.h"
#include "ghetto_mash_file_header.h"
#include "glass_house_manager.h"
#include "glass_house_resource_handler.h"
#include "hero_base_state.h"
#include "hierarchical_entity_proximity_map.h"
#include "igofrontend.h"
#include "igozoomoutmap.h"
#include "item_resource_handler.h"
#include "info_node_desc_list.h"
#include "ini_parser.h"
#include "input_action.h"
#include "input_mgr.h"
#include "inputsettings.h"
#include "interactable_interface.h"
#include "interaction_inode.h"
#include "interaction_state.h"
#include "layer_state_machine_shared.h"
#include "line_anchor.h"
#include "link_system.h"
#include "localized_string_table.h"
#include "local_collision.h"
#include "lookat_target_controller.h"
#include "mAvlTree.h"
#include "main_menu_keyboard.h"
#include "main_menu_options.h"
#include "mash_info_struct.h"
#include "mash_virtual_base.h"
#include "matrix4x4.h"
#include "memory.h"
#include "mesh_file_resource_handler.h"
#include "material_file_resource_handler.h"
#include "message_board.h"
#include "meta_anim_interact.h"
#include "motion_effect_struct.h"
#include "mission_manager.h"
#include "morph_file_resource_handler.h"
#include "moved_entities.h"
#include "mouselook_controller.h"
#include "mstring.h"
#include "multilinestring.h"
#include "nal_anim_controller.h"
#include "nal_system.h"
#include "nfl_driver.h"
#include "nfl_system.h"
#include "ngl.h"
#include "ngl_math.h"
#include "ngl_mesh.h"
#include "ngl_vertexdef.h"
#include "nslbank.h"
#include "oldmath_po.h"
#include "os_developer_options.h"
#include "os_file.h"
#include "panel_resource_handler.h"
#include "panelanimfile.h"
#include "panelfile.h"
#include "panelquad.h"
#include "panelquadsection.h"
#include "panelmeshsection.h"
#include "param_block.h"
#include "param_list.h"
#include "path_resource_handler.h"
#include "patrol_def_resource_handler.h"
#include "pause_menu_controller.h"
#include "pause_menu_message_log.h"
#include "pause_menu_root.h"
#include "pause_menu_save_load_display.h"
#include "pause_menu_status.h"
#include "pause_menu_transition.h"
#include "pause_menu_options_display.h"
#include "pausemenusystem.h"
#include "pc_joypad_device.h"
#include "ped_spawner.h"
#include "physical_interface.h"
#include "physics_inode.h"
#include "physics_system.h"
#include "pick_up_state.h"
#include "player_controller_inode.h"
#include "plr_loco_crawl_state.h"
#include "plr_loco_crawl_transition_state.h"
#include "pole_swing_state.h"
#include "polytube.h"
#include "quaternion.h"
#include "quick_anchor_info.h"
#include "rbc_def_contact.h"
#include "region.h"
#include "resource_amalgapak_header.h"
#include "resource_directory.h"
#include "resource_manager.h"
#include "resource_pack_standalone.h"
#include "resource_pack_streamer.h"
#include "return_address.h"
#include "rigid_body.h"
#include "rumble_manager.h"
#include "scene_anim.h"
#include "scene_anim_resource_handler.h"
#include "scratchpad_stack.h"
#include "script.h"
#include "script_access.h"
#include "script_object.h"
#include "script_data_interface.h"
#include "script_executable.h"
#include "script_controller.h"
#include "script_manager.h"
#include "script_memtrack.h"
#include "script_var_container.h"
#include "settings.h"
#include "sin_container.h"
#include "skeleton_resource_handler.h"
#include "slc_manager.h"
#include "sound_alias_database.h"
#include "sound_alias_database_resource_handler.h"
#include "sound_bank_slot.h"
#include "sound_interface.h"
#include "sound_manager.h"
#include "spawnable.h"
#include "spiderman_camera.h"
#include "spider_monkey.h"
#include "spidey_base_state.h"
#include "spline.h"
#include "state_machine.h"
#include "subdivision_static_region_list.h"
#include "string_hash.h"
#include "string_hash_dictionary.h"
#include "swing_anchor_obbfilter.h"
#include "terrain.h"
#include "texture_resource_handler.h"
#include "texturehandle.h"
#include "textureinputpack.h"
#include "timer.h"
#include "tl_system.h"
#include "tl_instance_bank.h"
#include "tlresourcedirectory.h"
#include "tlresource_directory.h"
#include "traffic.h"
#include "traffic_path_lane.h"
#include "trigger_manager.h"
#include "tx_system.h"
#include "unlockables_menu.h"
#include "us_decal.h"
#include "us_frontend.h"
#include "us_lod.h"
#include "us_person.h"
#include "us_simpleshader.h"
#include "us_translucentshader.h"
#include "us_variant.h"
#include "usm_anim_player.h"
#include "utility.h"
#include "variables.h"
#include "vector3d.h"
#include "variant_interface.h"
#include "vm.h"
#include "vm_executable.h"
#include "vm_thread.h"
#include "vtbl.h"
#include "wds.h"
#include "web_interface.h"
#include "web_polytube.h"
#include "window_manager.h"
#include "worldly_pack_slot.h"

#include "input.h"

#include <ngl_dx_scene.h>
#include <ctime>
#include <corecrt_startup.h>

//
#include <list.hpp>
#include <vector.hpp>

#include <cassert>
#include <cmath>
#include <cstdio>
#include <dinput.h>
#include <direct.h>

#include <float.h>
#include <windows.h>

#include <dsound.h>

void register_class_and_create_window(LPCSTR lpClassName,
                                      LPCSTR lpWindowName,
                                      int X,
                                      int Y,
                                      int a5,
                                      int a6,
                                      WNDPROC a7,
                                      HINSTANCE hInstance,
                                      int a9,
                                      DWORD dwStyle);

#define TEXT_START 0x00401000
#define TEXT_END 0x00988000

DWORD old_perms = 0;
BOOL set_text_to_writable() {
    return VirtualProtect((void *) TEXT_START, TEXT_END - TEXT_START, PAGE_READWRITE, &old_perms);
}

BOOL restore_text_perms() {
    return VirtualProtect((void*)(TEXT_START), TEXT_END - TEXT_START, old_perms, &old_perms);
}

BOOL install_patches()
{
    sp_log("Installing patches\n");

    sp_log("Patches have been installed\n");

    return TRUE;
}

static constexpr uint32_t NOP = 0x90;

void set_nop(ptrdiff_t address, size_t num_bytes) {
    for (size_t i = 0u; i < num_bytes; ++i) {
        *bit_cast<uint8_t *>(static_cast<size_t>(address) + i) = NOP;
    }
}

#define REDIRECT_WITH_NOP(addr, my_func)                                          \
    {                                                                             \
        *(uint8_t *) addr = 0xE8;                                                 \
        *(uint32_t *) ((uint8_t *) (addr + 1)) = ((uint32_t) my_func) - addr - 5; \
        *(uint8_t *) (addr + 5) = NOP;                                            \
        sp_log("Patched function sub_%08X with %s", addr, #my_func);              \
    }

#define MOVE(addr, my_func)                                            \
    {                                                                  \
        *bit_cast<uint8_t *>(addr) = 0xB9;                             \
        *(uint32_t *) ((uint8_t *) (addr + 1)) = ((uint32_t) my_func); \
        *bit_cast<uint8_t *>(addr + 5) = NOP;                          \
    }

void sub_76F320() {
    if constexpr (1) {
        struct Vtbl {
            int empty[7];
            void (__fastcall *field_1C)(void *, void *, int, int, int);
        };

        auto address = get_vtbl(nglMeshFileDirectory());

        if (bit_cast<std::ptrdiff_t>(address) != 0x008B8180) {
            sp_log("Invalid address of vtable = 0x%08X", address);

            set_vtbl(nglMeshFileDirectory(), 0x008B8180);

            address = get_vtbl(nglMeshFileDirectory());
        }

        Vtbl *vtbl = CAST(vtbl, address);

        vtbl->field_1C(nglMeshFileDirectory(), nullptr, 1, 1, 1); // 0x008B8180 -> sub_560770
    } else {
        CDECL_CALL(0x0076F320);
    }
}

bool sub_5A3AA0(const char *a1, char *a2) {
    return (bool) CDECL_CALL(0x005A3AA0, a1, a2);
}

static Var<bool> ALLOW_ERROR_POPUPS{0x00922A30};

void sub_597720(LPCSTR lpText) {
    char Dest[2048];
    char Format[2056];

    sprintf(Dest, "%s\n", lpText);
    OutputDebugStringA(Dest);

    {
        mString v1{Dest};
        CDECL_CALL(0x0051AB90, &v1);
    }

    sprintf(Format, "Error: \r\n%s", Dest);
    CDECL_CALL(0x005975C0, Format, 1, 1);
    if (ALLOW_ERROR_POPUPS()) {
        MessageBoxA(window_manager::instance()->field_4, lpText, "Error", 0x11010u);
    }

    link_system::send_command();
    _flushall();
    exit(-1);
}

LONG __stdcall TopLevelExceptionFilter(EXCEPTION_POINTERS *pExceptionInfo) {
    return (LONG) STDCALL(0x00597830, pExceptionInfo);
}

void sub_81E130(int *a1) {
    CDECL_CALL(0x0081E130, a1);
}

void sub_81C1A0() {
    CDECL_CALL(0x0081C1A0);
}

void init_assert_handler() {
    CDECL_CALL(0x005BC9B0);
}

void sub_5C9EA0() {
    CDECL_CALL(0x005C9EA0);
}

void create_directory(const char *str) {
    if constexpr (1) {
        char Dest[260];

        strncpy(Dest, str, 260u);
        if (Dest[0]) {
            auto *v1 = Dest;
            char v2;
            do {
                if (*v1 == '\\') {
                    *v1 = 0;
                    mkdir(Dest);
                    *v1 = '\\';
                }
                v2 = (v1++)[1];
            } while (v2);
        }

        mkdir(Dest);
    } else {
        CDECL_CALL(0x0081BD80, str);
    }
}

//0x005B2240
void replace_if_find(char *begin, char *end, const char &a3, const char &a4) {
    if constexpr (0) {
        for (auto *i = begin; i != end; ++i) {
            if (*i == a3) {
                *i = a4;
            }
        }
    } else {
        std::replace(begin, end, a3, a4);
    }
}

void parse_cmd(const char *str)
{
    TRACE("parse_cmd");

    if constexpr (1) {
        char Dest[1024]{};
        strncpy(Dest, str, 1023u);
        for (auto *i = strtok(Dest, " "); i != nullptr; i = strtok(nullptr, " ")) {
            if (strnicmp(i, "pack", strlen(i)) == 0 || strnicmp(i, "repack", strlen(i)) == 0) {
                g_is_the_packer() = true;
            } else if (strnicmp(i, "smokelevel", strlen(i)) == 0 ||
                       strnicmp(i, "runlevel", strlen(i)) == 0) {
                strcpy(g_scene_name(), strtok(nullptr, " "));
                if (strnicmp(i, "smokelevel", strlen(i)) == 0) {
                    os_developer_options::instance->set_flag(75, true);
                }

                os_developer_options::instance->set_flag(76, true);
            } else if (strnicmp(i, "smoketest", strlen(i)) == 0) {
                os_developer_options::instance->set_flag(75, true);
            } else if (strnicmp(i, "-entityids", strlen(i))) {
                if (strlen(i) > 2 && strnicmp(i, "-f", 2u) == 0) {
                    mString v13{i};

                    auto v2 = v13.find({2}, '=');
                    auto v3 = v2;
                    if (v2 != -1) {
                        mString v16 = v13.slice(2, v2);

                        mString v17 = v13.slice(v3 + 1, v13.size());

                        if (v16.size() && v17.size() == 1) {
                            if (*v17.c_str() == '1') {
                                os_developer_options::instance->set_flag(v16, true);
                            } else if (*v17.c_str() == '0') {
                                os_developer_options::instance->set_flag(v16, false);
                            }
                        }
                    }

                } else if (strlen(i) > 2 && strnicmp(i, "-i", 2u) == 0) {
                    mString v15{i};

                    auto v4 = v15.find({2}, '=');
                    if (v4 != -1) {
                        mString v20 = v15.slice(2, v4);

                        mString v21 = v15.slice(v4 + 1, v15.size());

                        if (v20.size() && v21.size()) {
                            auto v7 = atoi(v21.c_str());
                            os_developer_options::instance->set_int(v20, v7);
                        }
                    }

                } else if (strlen(i) > 2 && strnicmp(i, "-s", 2u) == 0) {
                    char v22[260]{};
                    copy_str(v22, i, 260u);

                    char v11 = ' ';
                    char v12 = '#';
                    replace_if_find(v22, &v22[strlen(v22)], v12, v11);
                    mString v14{v22};

                    auto v8 = v14.find({2}, '=');
                    if (v8 != -1) {
                        mString v19 = v14.slice(2, v8);

                        mString v18 = v14.slice(v8 + 1, v14.size());

                        if (v19.size() && v18.size()) {
                            os_developer_options::instance->set_string(v19, v18);
                        }
                    }
                }
            }
        }
    } else {
        CDECL_CALL(0x005948B0, str);
    }
}

void create_sound_ifc(HWND a1) {
    if constexpr (1) {
        static Var<LPDIRECTSOUND8> dword_987518 = {0x00987518};

        auto &v1 = dword_987518();
        if (dword_987518() != nullptr ||
            (DirectSoundCreate8(&IID_IDirectSound8, &dword_987518(), nullptr),
             (v1 = dword_987518()) != nullptr)) {
            v1->lpVtbl->SetCooperativeLevel(v1, a1, DISCL_NONEXCLUSIVE);
        }
    } else {
        CDECL_CALL(0x0081E2D0, a1);
    }
}

void sub_581780() {
    _controlfp(0x300u, 0x300u);
    _controlfp(_PC_24, _MCW_PC);
}

bool sub_81C2A0(unsigned int a1, unsigned int a2, char a3) {
    return (bool) CDECL_CALL(0x0081C2A0, a1, a2, a3);
}

Var<bool> byte_965BF7{0x00965BF7};

void sub_5BCA60(int a1, int a2) {
    if constexpr (1) {
        static Var<int (*)(int, int, int)> dword_9680A0{0x009680A0};

        static Var<int> dword_9682CC{0x009682CC};

        if (dword_9680A0() != nullptr) {
            sp_log("dword_9680A0 = 0x%08X", dword_9680A0());

            dword_9680A0()(a1, a2, dword_9682CC());
        }
    } else {
        CDECL_CALL(0x005BCA60, a1, a2);
    }
}

void sub_5BCA80(int a1) {
    if constexpr (1) {
        static Var<cdecl_call> dword_9680A4{0x009680A4};

        static Var<int> dword_9682D8{0x009682D8};

        if (dword_9680A4() != nullptr) {
            sp_log("dword_9680A4 = 0x%08X", dword_9680A4());

            dword_9680A4()(a1, dword_9682D8());
        }
    } else {
        CDECL_CALL(0x005BCA80, a1);
    }
}

static Var<char[]> byte_88CC68 = {0x0088CC68};

LRESULT __stdcall WindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    if constexpr (1) {
        LRESULT result;

        if (Msg <= WM_KEYUP) {
            if (Msg != WM_KEYUP) {
                switch (Msg) {
                case WM_DESTROY: {
                    ClipCursor(nullptr);
                    PostQuitMessage(0);
                    return 0;
                }
                case WM_CLOSE: {
                    if (byte_965BF7()) {
                        byte_922994() = true;
                        dword_922908() = 2;
                        g_cursor()->sub_5B0D70();
                        g_cursor()->field_120 = true;
                    }

                    return 0;
                }
                case WM_ACTIVATEAPP: {
                    if (byte_965BF9() == (wParam != 0)) {
                        return DefWindowProcA(hWnd, Msg, wParam, lParam);
                    }

                    byte_965BF9() = (wParam != 0);
                    if (os_developer_options::instance != nullptr &&
                        os_developer_options::instance->get_flag(static_cast<os_developer_options::flags_t>(117))) {
                        byte_965BF9() = true;
                    }

                    if (g_game_ptr == nullptr || !byte_965BF9()) {
                        return DefWindowProcA(hWnd, Msg, wParam, lParam);
                    }

                    g_timer()->sub_582180();
                    return DefWindowProcA(hWnd, Msg, wParam, lParam);
                }
                case WM_SETCURSOR: {
                    if (!hCursor()) {
                        return DefWindowProcA(hWnd, Msg, wParam, lParam);
                    }

                    SetCursor(hCursor());
                    return 0;
                }
                case WM_KEYDOWN: {
                    g_cursor()->sub_5B0D70();
                    goto LABEL_5;
                }
                default:
                    return DefWindowProcA(hWnd, Msg, wParam, lParam);
                }

                return DefWindowProcA(hWnd, Msg, wParam, lParam);
            }

            sub_5BCA60(0, byte_88CC68()[static_cast<uint16_t>(wParam)]);

            if (g_femanager.m_pause_menu_system != nullptr && g_femanager.m_pause_menu_system->m_index != -1)
            {
            LABEL_24:

                auto *pause_menu_system = g_femanager.m_pause_menu_system;

                auto *vtbl = bit_cast<fastcall_call(*)[10]>(pause_menu_system->m_vtbl);

                auto *func = (*vtbl)[9];

                func(pause_menu_system, nullptr, 257, wParam, lParam);

                return DefWindowProcA(hWnd, Msg, wParam, lParam);
            }

            if (g_femanager.m_fe_menu_system != nullptr && g_femanager.m_fe_menu_system->m_index != -1)
            {
                if (g_femanager.m_pause_menu_system->m_index == -1)
                {
                    auto *frontend_menu_system = g_femanager.m_fe_menu_system;

                    auto *vtbl = bit_cast<fastcall_call(*)[10]>(frontend_menu_system->m_vtbl);

                    auto *func = (*vtbl)[9];
                    func(frontend_menu_system, nullptr, 257, wParam, lParam);

                    return DefWindowProcA(hWnd, Msg, wParam, lParam);
                }
                goto LABEL_24;
            }

            return DefWindowProcA(hWnd, Msg, wParam, lParam);
        }

        if (Msg > WM_SYSCOMMAND) {
            switch (Msg) {
            case WM_MOUSEMOVE:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_MOUSEWHEEL: {
                if (g_femanager.m_pause_menu_system != nullptr && g_femanager.m_pause_menu_system->m_index != -1) {
                    goto LABEL_43;
                }

                if (g_femanager.m_fe_menu_system != nullptr && g_femanager.m_fe_menu_system->m_index != -1)
                {
                    if (g_femanager.m_pause_menu_system->m_index == -1)
                    {
                        auto *frontend_menu_system = g_femanager.m_fe_menu_system;

                        auto *vtbl = bit_cast<fastcall_call(*)[10]>(frontend_menu_system->m_vtbl);

                        auto *func = (*vtbl)[9];
                        //assert(bit_cast<std::intptr_t>(func) == 0x0060B6E0);

                        func(frontend_menu_system, nullptr, Msg, wParam, lParam);

                    } else {
                    LABEL_43:

                        auto *pause_menu_system = g_femanager.m_pause_menu_system;

                        auto *vtbl = bit_cast<fastcall_call(*)[10]>(pause_menu_system->m_vtbl);

                        auto *func = (*vtbl)[9];
                        //assert(bit_cast<std::intptr_t>(func) == 0x0060B6E0);

                        func(pause_menu_system, nullptr, Msg, wParam, lParam);
                    }
                }

                if (g_femanager.IGO != nullptr) {
                    auto v6 = g_femanager.IGO->field_44;
                    if (v6->sub_55F320())
                        v6->sub_638AD0(Msg, wParam, lParam);
                }
                break;
            }
            default:
                return DefWindowProcA(hWnd, Msg, wParam, lParam);
            }
            return DefWindowProcA(hWnd, Msg, wParam, lParam);
        }

        if (Msg == WM_SYSCOMMAND) {
            if ((wParam & 0xFFF0) == SC_KEYMENU || (wParam & 0xFFF0) == SC_SCREENSAVE ||
                (wParam & 0xFFF0) == SC_MONITORPOWER) {
                return 0;
            }

            return DefWindowProcA(hWnd, Msg, wParam, lParam);
        }

        switch (Msg) {
        case WM_CHAR:
            sub_5BCA80(wParam);
            result = DefWindowProcA(hWnd, Msg, wParam, lParam);
            break;
        case WM_SYSKEYDOWN:
        LABEL_5:
            sub_5BCA60(1, byte_88CC68()[(uint16_t) wParam]);
            result = DefWindowProcA(hWnd, Msg, wParam, lParam);
            break;
        case WM_SYSKEYUP:
            sub_5BCA60(0, byte_88CC68()[(uint16_t) wParam]);
            result = DefWindowProcA(hWnd, Msg, wParam, lParam);
            break;
        case WM_SYSCHAR:
            if (wParam != 121) {
                return DefWindowProcA(hWnd, Msg, wParam, lParam);
            }
            result = 0;
            break;
        default:
            return DefWindowProcA(hWnd, Msg, wParam, lParam);
        }
        return result;
    } else {
        return (LRESULT) STDCALL(0x005941A0, hWnd, Msg, wParam, lParam);
    }
}

void sub_79DFF0() {
    CDECL_CALL(0x0079DFF0);
}

void sub_81C230() {
    CDECL_CALL(0x0081C230);
}

void sub_81D700() {
    CDECL_CALL(0x0081D700);
}

void sub_81E300() {
    CDECL_CALL(0x0081E300);
}

//0x0081C5A0
void free_file(FileUSM *file) {
    if (file != nullptr) {
        free(file->field_0);
        free(file->field_4);
        free(file);
    }
}

void sub_4DDEC0() {
    CDECL_CALL(0x004DDEC0);
}

void bink_set_sound_system() {
    CDECL_CALL(0x0060BBA0);
    //BinkSetSoundSystem(BinkOpenDirectSound, pUnkOuter());
}

bool get_path(const char *a1, const char *a2, char *out, unsigned int str_len) {
    if constexpr (1) {
        char Buffer[260]{};

        char v12[260]{};

        char v8[260]{};

        if (GetSystemDirectoryA(Buffer, 260u)) {
            Buffer[259] = '\0';

            char Dest[268];
            std::sprintf(Dest, "%s\\shell32.dll", Buffer);
            auto hModule = LoadLibraryA(Dest);

            if (hModule != nullptr) {
                auto *SHGetFolderPathA =
                    bit_cast<HRESULT(__stdcall *)(HWND, int, HANDLE, DWORD, LPSTR)>(
                        GetProcAddress(hModule, "SHGetFolderPathA"));
                if (SHGetFolderPathA != nullptr &&
                    SHGetFolderPathA(nullptr, 5, nullptr, 0, v12) >= 0) {
                    sprintf(v8, "%s\\%s", v12, a1);
                    if (strlen(v8) >= str_len) {
                        return false;
                    }

                    strcpy(out, v8);
                }

                FreeLibrary(hModule);
            }
        }

        if (&v12[strlen(v12) + 1] == &v12[1]) {
            if (strlen(a2) >= str_len) {
                return false;
            }

            strcpy(out, a2);
        }

        return true;
    } else {
        return (bool) CDECL_CALL(0x0081BE00, a1, a2, out, str_len);
    }
}

bool sub_586FA0(unsigned char a1) {
    bool result;

    switch (a1) {
    case 224:
    case 228:
    case 231:
    case 232:
    case 233:
    case 236:
    case 241:
    case 242:
    case 246:
    case 249:
    case 252:
        result = true;
        break;
    default:
        result = false;
        break;
    }

    return result;
}

void sub_5952D0()
{
    TRACE("sub_5952D0");

    if constexpr (0)
    {
        operator delete(dword_965C24()[0]);
        operator delete(dword_965C24()[1]);
        operator delete(dword_965C24()[2]);
        operator delete(dword_965C24()[3]);
        operator delete(dword_965C24()[4]);
        operator delete(dword_965C24()[5]);
        operator delete(dword_965C24()[6]);
        operator delete(dword_965C24()[7]);
        operator delete(dword_965C24()[8]);
        operator delete(dword_965C24()[9]);
        operator delete(dword_965C24()[10]);
        operator delete(dword_965C24()[11]);
        operator delete(dword_965C24()[12]);
        operator delete(dword_965C24()[13]);

        Input::instance()->sub_821490(true);

        struct {
            char field_0[16];
            int field_10[8];
            int field_30;
            bool field_34;
            int field_38;
            bool field_3C;
            int field_40;
            int field_44;
        } v29;

        VALIDATE_SIZE(v29, 0x48);

        static constexpr decltype(v29) input_value[18] = {
            {"Forward",      {0, 0, 0, 0, 0, 0, 0, 0},  65553, false, 65736, false, 196612, 0},
            {"Backward",     {0, 0, 0, 0, 0, 0, 0, 0},  65567, false, 65744, false, 196611, 0},
            {"TurnLeft",     {0, 0, 0, 0, 0, 0, 0, 0},  65566, false, 65739, false, 196610, 0},
            {"TurnRight",    {0, 0, 0, 0, 0, 0, 0, 0},  65568, false, 65741, false, 196609, 0},
            {"Jump",         {0, 0, 0, 0, 0, 0, 0, 0}, 0x10000 + DIK_SPACE, false, 65535, false, 196629, 0},
            {"StickToWalls", {0, 0, 0, 0, 0, 0, 0, 0},  65569, false, 65578, false, 196630, 0},
            {"Punch",        {0, 0, 0, 0, 0, 0, 0, 0}, 0x10000 + DIK_Q, false, 65565, false, 196631, 0},
            {"Kick",         {0, 0, 0, 0, 0, 0, 0, 0}, 0x10000 + DIK_E, false, 65592, false, 196632, 0},
            {"ThrowWeb",     {0, 0, 0, 0, 0, 0, 0, 0}, 131082, false, 65582, false,  65535, 0},
            {"BlackButton",  {0, 0, 0, 0, 0, 0, 0, 0}, 131081, false, 65583, false,  65535, 0},
            {"CameraUp",     {0, 0, 0, 0, 0, 0, 0, 0},  65608, false, 65737, false,  65535, 0},
            {"CameraDown",   {0, 0, 0, 0, 0, 0, 0, 0},  65616, false, 65745, false,  65535, 0},
            {"CameraLeft",   {0, 0, 0, 0, 0, 0, 0, 0},  65611, false, 65535, false,  65535, 0},
            {"CameraRight",  {0, 0, 0, 0, 0, 0, 0, 0},  65613, false, 65535, false,  65535, 0},
            {"CameraCenter", {0, 0, 0, 0, 0, 0, 0, 0}, 0x10000 + 48, false, 65535, false,  65535, 0},
            {"Pause",        {0, 0, 0, 0, 0, 0, 0, 0},  65537, true,  65535, false,  65535, 0},
            {"BackButton",   {0, 0, 0, 0, 0, 0, 0, 0},  65586, false, 65535, false,  65535, 0},
            {"ScreenShot",   {0, 0, 0, 0, 0, 0, 0, 0},  65623, false, 65535, false,  65535, 0}
        };

        //0x00922940
        static constexpr InputAction input_actions[18] = {
                       InputAction::Forward,
                       InputAction::Backward,
                       InputAction::TurnLeft,
                       InputAction::TurnRight,
                       InputAction::Jump,
                       InputAction::StickToWalls,
                       InputAction::Punch,
                       InputAction::Kick,
                       InputAction::ThrowWeb,
                       InputAction::BlackButton,
                       InputAction::CameraUp,
                       InputAction::CameraDown,
                       InputAction::CameraLeft,
                       InputAction::CameraRight,
                       InputAction::CameraCenter,
                       InputAction::Pause,
                       InputAction::BackButton,
                       InputAction::ScreenShot
        };

        for (auto i = 0u; i < std::size(input_actions); ++i)
        {
            auto &v22 = input_actions[i];

            v29 = input_value[i];

            char Dest[264];
            sprintf(Dest, "Controls\\Player%d\\%s1", 1, v29.field_0);

            uint32_t v0 = ( v29.field_34 
                            ? v29.field_30
                            : g_settings()->sub_81D010(Dest, v29.field_30)
                            );

            const uint16_t v23 = v0;

            sprintf(Dest, "Controls\\Player%d\\%s2", 1, v29.field_0);
            uint32_t v1 = ( v29.field_3C
                            ? v29.field_38
                            : g_settings()->sub_81D010(Dest, v29.field_38));

            const uint16_t v27 = v1;

            sprintf(Dest, "Controls\\Player%d\\%s3", 1, v29.field_0);
            uint32_t v2 = g_settings()->sub_81D010(Dest, 0);
            if (v2 == 0 && Input::instance()->sub_820080() > 0) {
                v2 = v29.field_40;
            }

            const uint16_t v28 = v2;

            InputType v4 = static_cast<InputType>(HIWORD(v0));
            sp_log("%d, %d, %d", v4, v0, v23);

            g_inputSettingsInGame()->field_18.set(v22, 0, v4, v23);

            InputType v5 = static_cast<InputType>(HIWORD(v1));
            g_inputSettingsInGame()->field_18.set(v22, 1u, v5, v27);

            InputType v6 = static_cast<InputType>(HIWORD(v2));
            g_inputSettingsInGame()->field_18.set(v22, 2u, v6, v28);

            if (v22 == InputAction::Pause)
            {
                g_inputSettingsMenu()->field_18.set(InputAction::Kick, 0, v4, v23);
                g_inputSettingsMenu()->field_18.set(InputAction::Kick, 1u, v5, v27);
                g_inputSettingsMenu()->field_18.set(InputAction::Kick, 2u, v6, v28);
            }

            if (v22 == InputAction::Forward && v4 == InputType::Key && v23 != 200)
            {
                g_inputSettingsMenu()->field_18.set_key(v22, 1u, v23);
            }
            else
            {
                uint16_t v8;
                if (v22 == InputAction::Backward && v4 == InputType::Key)
                {
                    v8 = v23;
                    if (v23 != 208) {
                        g_inputSettingsMenu()->field_18.set_key(v22, 1u, v23);
                    }

                } else {
                    v8 = v23;
                }

                if ((v22 == InputAction::TurnLeft && v4 == InputType::Key && v8 != 203) ||
                    (v22 == InputAction::TurnRight && v4 == InputType::Key && v8 != 205)) {
                    g_inputSettingsMenu()->field_18.set_key(v22, 1u, v23);
                }
            }

            if (v22 == InputAction::Pause)
            {
                if (v4 == InputType::Joy && v23 != 21 && v23 != 24) {
                    g_inputSettingsMenu()->field_18.set(InputAction::Pause, 1u, InputType::Joy, v23);
                }

                if (v22 == InputAction::Pause)
                {
                    if (v5 == InputType::Joy && v23 != 21 && v27 != 24) {
                        g_inputSettingsMenu()->field_18.set(InputAction::Pause,
                                                            1u,
                                                            InputType::Joy,
                                                            v27);
                    }

                    if (v22 == InputAction::Pause
                            && v6 == InputType::Joy
                            && v23 != 21
                            && v28 != 24)
                    {
                        g_inputSettingsMenu()->field_18.set(InputAction::Pause,
                                                            1u,
                                                            InputType::Joy,
                                                            v28);
                    }
                }
            }

            const char *v10;
            auto *v9 = Input::instance()->get_string(v4, v23);
            if (v9 != nullptr || (v9 = Input::instance()->get_string(v5, v27)) != nullptr ||
                (v9 = Input::instance()->get_string(v6, v28)) != nullptr) {
                v10 = v9;
            } else {
                v10 = get_msg(g_fileUSM(), "NONE");
            }

            auto *v12 = static_cast<char *>(operator new(255u));

            if (v10 != nullptr) {
                v9 = v10;
            }

            sprintf(v12, "\"%s\"", v9);
            if (strlen(v12) == 3 && sub_586FA0(v12[1])) {
                auto v13 = v12[1] - ' ';

                v12[1] = v13;

            }
            else if (strlen(v12) == 3)
            {
                unsigned char v14 = v12[1];
                if (v14 > '`' && v14 < '{')
                {
                    auto v13 = toupper(v14);
                    v12[1] = v13;
                }
            }

            switch (v22) {
            case InputAction::Jump:
                dword_965C24()[GamepadInput::Cross] = v12;
                break;
            case InputAction::StickToWalls:
                dword_965C24()[GamepadInput::Circle] = v12;
                break;
            case InputAction::Punch:
                dword_965C24()[GamepadInput::Square] = v12;
                break;
            case InputAction::Kick:
                dword_965C24()[GamepadInput::Triangle] = v12;
                break;
            case InputAction::BlackButton:
                dword_965C24()[GamepadInput::L2] = v12;
                break;
            case InputAction::ThrowWeb:
                dword_965C24()[GamepadInput::R2] = v12;
                break;
            case InputAction::Pause:
                dword_965C24()[GamepadInput::Start] = v12;
                break;
            case InputAction::BackButton:
                dword_965C24()[GamepadInput::Select] = v12;
                break;
            case InputAction::CameraCenter:
                dword_965C24()[GamepadInput::R3] = v12;
                break;
            case InputAction::Forward:
                dword_965C24()[GamepadInput::Forward] = v12;
                break;
            case InputAction::TurnLeft:
                dword_965C24()[GamepadInput::Left] = v12;
                break;
            case InputAction::TurnRight:
                dword_965C24()[GamepadInput::Right] = v12;
                break;
            default:
                break;
            }
        }

        sub_5828B0();
        g_inputSettingsMenu()->field_18.set_key(InputAction::Jump, 0, DIK_RETURN);
        g_inputSettingsMenu()->field_18.set_key(InputAction::Kick, 0, DIK_ESCAPE);
        g_inputSettingsMenu()->field_18.set_key(InputAction::Pause, 0, DIK_SPACE);
        g_inputSettingsMenu()->field_18.set_key(InputAction::Forward, 0, DIK_UP);
        g_inputSettingsMenu()->field_18.set_key(InputAction::Backward, 0, DIK_DOWN);
        g_inputSettingsMenu()->field_18.set_key(InputAction::TurnLeft, 0, DIK_LEFT);
        g_inputSettingsMenu()->field_18.set_key(InputAction::TurnRight, 0, DIK_RIGHT);

        *g_inputSettings2() = *g_inputSettingsInGame();
        g_inputSettings2()->field_18.find_and_clear(InputType::Mouse, 9);
        g_inputSettings2()->field_18.find_and_clear(InputType::Mouse, 10);

        *g_inputSettings4() = *g_inputSettingsInGame();
        g_inputSettings4()->field_18.find_and_clear(InputType::Key);
        g_inputSettings4()->field_18.set_key(InputAction::Jump, 3u, DIK_RETURN);
        g_inputSettings4()->field_18.set_key(InputAction::Kick, 3u, DIK_ESCAPE);
        g_inputSettings4()->field_18.set_key(InputAction::Pause, 3u, DIK_SPACE);
        g_inputSettings4()->field_18.set_key(InputAction::Forward, 3u, DIK_UP);
        g_inputSettings4()->field_18.set_key(InputAction::Backward, 3u, DIK_DOWN);
        g_inputSettings4()->field_18.set_key(InputAction::TurnLeft, 3u, DIK_LEFT);
        g_inputSettings4()->field_18.set_key(InputAction::TurnRight, 3u, DIK_RIGHT);
        g_inputSettings4()->field_18.find_and_clear(InputType::Mouse, 9);
        g_inputSettings4()->field_18.find_and_clear(InputType::Mouse, 10);
    } 
    else
    {
        CDECL_CALL(0x005952D0);
    }
}

int __stdcall myWinMain(HINSTANCE hInstance,
                        [[maybe_unused]] HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        [[maybe_unused]] int nShowCmd) {
    if (!CreateMutexA(nullptr, true, "USM") || GetLastError() == ERROR_ALREADY_EXISTS) {
        return 0;
    }

    g_settings() = new Settings{"Activision", "Ultimate Spider-Man"};

    char v6;
    switch (g_settings()->sub_81D010("Settings\\Language", 0)) {
    case 1:
        v6 = 'f';
        break;
    case 2:
        v6 = 'g';
        break;
    case 3:
        v6 = 's';
        break;
    case 4:
        v6 = 'i';
        break;
    default:
        v6 = 'e';
        break;
    }

    char Dest[100];
    sprintf(Dest, "data\\usm_lt%c.usm", v6);

    g_fileUSM() = create_usm_file(Dest, nullptr);

    static Var<CHAR[]> DirectoryName{0x0088FAF8};
    ULARGE_INTEGER TotalNumberOfFreeBytes;
    GetDiskFreeSpaceExA(DirectoryName(), nullptr, nullptr, &TotalNumberOfFreeBytes);
    if (TotalNumberOfFreeBytes.QuadPart < 0xA00000) {
        auto *v162 = get_msg(g_fileUSM(), "MSGBOX_ERROR");
        auto *v7 = get_msg(g_fileUSM(), "MSGBOX_SPACE");

        MessageBoxA(nullptr, v7, v162, 0x10u);
        return 0;
    }

    if (!sub_81C2A0(9u, 0, 99u)) {
        auto *v162 = get_msg(g_fileUSM(), "MSGBOX_ERROR");
        auto *v7 = get_msg(g_fileUSM(), "MSGBOX_DX9");

        MessageBoxA(nullptr, v7, v162, 0x10u);
        return 0;
    }

    static Var<char> byte_965C08 = {0x00965C08};
    byte_965C08() = 1;

    init_assert_handler();

#if 0
    _controlfp(1u, 0x8001Fu);
    sub_581780();
#endif

    static Var<int> dword_965BFC = {0x00965BFC};
    dword_965BFC() = (int) hInstance;

    create_window_handle();

    os_developer_options::os_developer_init();
    ini_parser::parse("game.ini", os_developer_options::instance);

    sub_5C9EA0();

    g_timer() = new Timer{30.0, 30.0};

    sub_81C1A0();

    sub_81E130(nullptr);

    Input::create_inst();

    char Str[12];
    g_settings()->sub_81CFA0("Settings\\Resolution", "800x600", Str, 10u);

    char *v11 = strtok(Str, "x");
    g_cx() = atoi(v11);
    char *v12 = strtok(nullptr, "x");
    g_cy() = atoi(v12);

    flt_965BDC() = (double) g_cy() * 0.011029412 - 5.29;

    byte_95C718() = g_settings()->sub_81D050("Settings\\DistanceClipping", 0);
    dword_95C2F8() = g_settings()->sub_81D010("Settings\\Distance", 50);
    g_player_shadows_enabled() = g_settings()->sub_81D050("Settings\\DetailedShadows", 1);
    g_enable_stencil_shadows() = g_player_shadows_enabled();
    ChromeEffect() = g_settings()->sub_81D050("Settings\\ChromeEffect", 1);

    register_class_and_create_window("Render Window",
                                     "Ultimate Spider-Man",
                                     0,
                                     0,
                                     g_cx(),
                                     g_cy(),
                                     WindowProc,
                                     hInstance,
                                     80,
                                     1u);

    ShowWindow(g_appHwnd(), 3);

    g_Windowed() = 0;
    UpdateWindow(g_appHwnd());
    SetWindowPos(g_appHwnd(), nullptr, 0, 0, g_cx(), g_cy(), 4u);

    create_sound_ifc(g_appHwnd());
    ShowCursor(0);
    os_developer_options::instance->set_int(mString {"ALLOW_SCREENSHOT"}, 1);

    window_manager::instance()->field_4 = g_appHwnd();

    parse_cmd(lpCmdLine);

    if (os_developer_options::instance->get_flag(mString {"HALT_ON_ASSERTS"})) {
        g_debug().field_1 |= 1;
    } else {
        g_debug().field_1 &= 0xFE;
    }

    if (g_is_the_packer() || !os_developer_options::instance->get_flag(mString {"SCREEN_ASSERTS"})) {
        g_debug().field_1 &= 0xFD;
    } else {
        g_debug().field_1 |= 2;
    }

    nflInitParams a1;
    a1.field_0[0] = 32;
    a1.field_0[1] = 32;
    a1.field_0[2] = 32;
    a1.field_0[0] = 1024;
    a1.field_0[3] = 3;
    a1.field_0[4] = 0;

    static Var<size_t> dword_965C04 = {0x00965C04};
    dword_965C04() = nflInit(&a1);

    static Var<char *> dword_965C00 = {0x00965C00};
    dword_965C00() = new char[dword_965C04()];

    //EnableLog l{};

    nflStart(dword_965C00());

    int v17 = os_developer_options::instance->get_int(mString {"RANDOM_SEED"});
    if (v17) {
        srand(v17);
    } else {
        auto v18 = time(nullptr);
        srand(v18);
    }

    char v173[260];

    sprintf(v173, "%s\\%s\\Screenshot", "Activision", "Ultimate Spider-Man");
    get_path(v173, "Screenshot", byte_9659B8(), 260u);
    create_directory(byte_9659B8());

    char v174[260];
    sprintf(v174, "%s\\%s\\Save", "Activision", "Ultimate Spider-Man");

    static Var<char[260]> byte_965AD0 = {0x00965AD0};
    get_path(v174, "Save", byte_965AD0(), 260u);
    create_directory(byte_965AD0());

    Input::instance()->field_129D0 = 1;

    g_inputSettingsMenu() = new InputSettings{};
    g_inputSettingsInGame() = new InputSettings{};
    g_inputSettings2() = new InputSettings{};
    g_inputSettings3() = new InputSettings{};
    g_inputSettings4() = new InputSettings{};

    g_inputSettingsInGame()->field_18.sub_821E70();

    char Source[260];
    char Type[40];

    for (int i{0}; i < 10; ++i) {
        sprintf(Source, "Controls\\Gamepads\\PadID%d", i + 1);
        g_settings()->sub_81CFA0(Source, "00000000-0000-0000-0000-000000000000", Type, 37u);

        Input::instance()->sub_81FC00(i, Type);
    }

    Input::instance()->initialize(g_appHwnd());

    auto *v30 = get_msg(g_fileUSM(), "MouseWheelDown");
    auto *v31 = get_msg(g_fileUSM(), "MouseWheelUp");
    auto *v32 = get_msg(g_fileUSM(), "MouseAxis");
    auto *v33 = get_msg(g_fileUSM(), "MouseBtn");
    auto *v34 = get_msg(g_fileUSM(), "MouseMiddle");
    auto *v35 = get_msg(g_fileUSM(), "MouseRight");
    auto *v36 = get_msg(g_fileUSM(), "MouseLeft");

    Input::instance()->set_mouse(v36, v35, v34, v33, v32, v31, v30);

    auto *v38 = get_msg(g_fileUSM(), "GamepadBtn");
    auto *v39 = get_msg(g_fileUSM(), "GamepadPoV");
    auto *v40 = get_msg(g_fileUSM(), "GamepadAxis");
    Input::instance()->set_gamepad(v40, v39, v38);

    auto *v42 = get_msg(g_fileUSM(), "ESC");

    Input::instance()->set_key(1, v42);

    auto *v44 = get_msg(g_fileUSM(), "BACK");
    Input::instance()->set_key(14, v44);

    auto *v46 = get_msg(g_fileUSM(), "TAB");
    Input::instance()->set_key(15, v46);

    auto *v48 = get_msg(g_fileUSM(), "ENTER");
    Input::instance()->set_key(28, v48);

    auto *v50 = get_msg(g_fileUSM(), "RCTRL");
    Input::instance()->set_key(157, v50);

    auto *v52 = get_msg(g_fileUSM(), "LCTRL");
    Input::instance()->set_key(29, v52);

    auto *v54 = get_msg(g_fileUSM(), "LSHIFT");
    Input::instance()->set_key(42, v54);

    auto *v56 = get_msg(g_fileUSM(), "RSHIFT");
    Input::instance()->set_key(54, v56);

    auto *v58 = get_msg(g_fileUSM(), "SPACE");
    Input::instance()->set_key(57, v58);

    auto *v60 = get_msg(g_fileUSM(), "CAPSL");
    Input::instance()->set_key(58, v60);

    auto *v62 = get_msg(g_fileUSM(), "SCROLL");
    Input::instance()->set_key(70, v62);

    auto *v64 = get_msg(g_fileUSM(), "LALT");
    Input::instance()->set_key(56, v64);

    auto *v66 = get_msg(g_fileUSM(), "RALT");
    Input::instance()->set_key(184, v66);

    auto *v68 = get_msg(g_fileUSM(), "PAUSE");
    Input::instance()->set_key(197, v68);

    auto *v70 = get_msg(g_fileUSM(), "HOME");
    Input::instance()->set_key(199, v70);

    auto *v72 = get_msg(g_fileUSM(), "PGUP");
    Input::instance()->set_key(201, v72);

    auto *v74 = get_msg(g_fileUSM(), "UP");
    Input::instance()->set_key(200, v74);

    auto *v76 = get_msg(g_fileUSM(), "LEFT");
    Input::instance()->set_key(203, v76);

    auto *v78 = get_msg(g_fileUSM(), "DOWN");
    Input::instance()->set_key(208, v78);

    auto *v80 = get_msg(g_fileUSM(), "RIGHT");
    Input::instance()->set_key(205, v80);

    auto *v82 = get_msg(g_fileUSM(), "DEL");
    Input::instance()->set_key(211, v82);

    auto *v84 = get_msg(g_fileUSM(), "INS");
    Input::instance()->set_key(210, v84);

    auto *v86 = get_msg(g_fileUSM(), "END");
    Input::instance()->set_key(207, v86);

    auto *v88 = get_msg(g_fileUSM(), "PGDWN");
    Input::instance()->set_key(209, v88);

    auto *v90 = get_msg(g_fileUSM(), "MENU");
    Input::instance()->set_key(221, v90);

    auto *v92 = get_msg(g_fileUSM(), "KP,");
    Input::instance()->set_key(179, v92);

    auto *v94 = get_msg(g_fileUSM(), "KP.");
    Input::instance()->set_key(83, v94);

    auto *v96 = get_msg(g_fileUSM(), "KPEnter");
    Input::instance()->set_key(156, v96);

    auto *v98 = get_msg(g_fileUSM(), "NumL");
    Input::instance()->set_key(69, v98);

    auto *v100 = get_msg(g_fileUSM(), "KP0");
    Input::instance()->set_key(82, v100);

    auto *v102 = get_msg(g_fileUSM(), "KP1");
    Input::instance()->set_key(79, v102);

    auto *v104 = get_msg(g_fileUSM(), "KP2");
    Input::instance()->set_key(80, v104);

    auto *v106 = get_msg(g_fileUSM(), "KP3");
    Input::instance()->set_key(81, v106);

    auto *v108 = get_msg(g_fileUSM(), "KP4");
    Input::instance()->set_key(75, v108);

    auto *v110 = get_msg(g_fileUSM(), "KP5");
    Input::instance()->set_key(76, v110);

    auto *v112 = get_msg(g_fileUSM(), "KP6");
    Input::instance()->set_key(77, v112);

    auto *v114 = get_msg(g_fileUSM(), "KP7");
    Input::instance()->set_key(71, v114);

    auto *v116 = get_msg(g_fileUSM(), "KP8");
    Input::instance()->set_key(72, v116);

    auto *v118 = get_msg(g_fileUSM(), "KP9");
    Input::instance()->set_key(73, v118);

    auto *v120 = get_msg(g_fileUSM(), "F1");
    Input::instance()->set_key(59, v120);

    auto *v122 = get_msg(g_fileUSM(), "F2");
    Input::instance()->set_key(60, v122);

    auto *v124 = get_msg(g_fileUSM(), "F3");
    Input::instance()->set_key(61, v124);

    auto *v126 = get_msg(g_fileUSM(), "F4");
    Input::instance()->set_key(62, v126);

    auto *v128 = get_msg(g_fileUSM(), "F5");
    Input::instance()->set_key(63, v128);

    auto *v130 = get_msg(g_fileUSM(), "F6");
    Input::instance()->set_key(64, v130);

    auto *v132 = get_msg(g_fileUSM(), "F7");
    Input::instance()->set_key(65, v132);

    auto *v134 = get_msg(g_fileUSM(), "F8");
    Input::instance()->set_key(66, v134);

    auto *v136 = get_msg(g_fileUSM(), "F9");
    Input::instance()->set_key(67, v136);

    auto *v138 = get_msg(g_fileUSM(), "F10");
    Input::instance()->set_key(68, v138);

    auto *v140 = get_msg(g_fileUSM(), "F11");
    Input::instance()->set_key(87, v140);

    auto *v142 = get_msg(g_fileUSM(), "F12");
    Input::instance()->set_key(88, v142);

    auto *v144 = get_msg(g_fileUSM(), "F13");
    Input::instance()->set_key(100, v144);

    auto *v146 = get_msg(g_fileUSM(), "F14");
    Input::instance()->set_key(101, v146);

    auto *v148 = get_msg(g_fileUSM(), "F15");
    Input::instance()->set_key(102, v148);

    sub_5952D0();

    static Var<RTL_CRITICAL_SECTION> CriticalSection = {0x009618F4};
    InitializeCriticalSection(&CriticalSection());

    Input::instance()->sub_8203F0(0, g_inputSettingsMenu());
    Input::instance()->sub_81FB90(1);

    Settings::MouseLook() = g_settings()->sub_81D010("Settings\\MouseLook", 1) != 0;
    if (Settings::MouseLook()) {
        Settings::InvertCameraH() = g_settings()->sub_81D050("Settings\\InvertCameraH", 0);

        g_inputSettingsInGame()->field_18.set_mouse(InputAction::CameraRight,
                                                    3,
                                                    InputMouse::LookRight);
        g_inputSettingsInGame()->field_18.set_mouse(InputAction::CameraLeft,
                                                    3,
                                                    InputMouse::LookLeft);

        Settings::InvertCameraV() = g_settings()->sub_81D050("Settings\\InvertCameraV", 0);
        g_inputSettingsInGame()->field_18.set_mouse(InputAction::CameraUp, 3, InputMouse::LookUp);
        g_inputSettingsInGame()->field_18.set_mouse(InputAction::CameraDown,
                                                    3,
                                                    InputMouse::LookDown);
    }

    Input::instance()->m_sensitivity = g_settings()->sub_81D010("Settings\\Sensitivity", 50) *
            0.001f +
        0.001f;

    Settings::SoundMode() = g_settings()->sub_81D010("Settings\\SoundMode", 2);
    Settings::GameSoundVolume() = g_settings()->sub_81D010("Settings\\GameSoundVolume",
                                                                    10) *
        0.1;
    Settings::MusicVolume() = g_settings()->sub_81D010("Settings\\MusicVolume", 10) * 0.1f;

    if (os_developer_options::instance->get_flag(mString {"EXCEPTION_HANDLER"})) {
        SetUnhandledExceptionFilter(TopLevelExceptionFilter);
    }

    ALLOW_ERROR_POPUPS() = os_developer_options::instance->get_flag(mString {"ALLOW_ERROR_POPUPS"});
    if (!ALLOW_ERROR_POPUPS()) {
        SetErrorMode(2u);
    }

    static tlSystemCallbacks ngl_callbacks{ngl_readfile_callback,
                                           ngl_releasefile_callback,
                                           0,
                                           0,
                                           ngl_memalloc_callback,
                                           ngl_memfree_callback

    };

    tlSetSystemCallbacks(ngl_callbacks);

    nWidth() = g_cx();
    nHeight() = g_cy();

    nglInit(g_appHwnd());
    nalInit(nullptr);

    g_cursor() = new Cursor(L"data\\ump.dat", g_cx(), g_cy());
    set_tl_system_directories();

    static Var<nglFrameLockType> g_frame_lock{0x00922920};
    nglSetFrameLock(g_frame_lock());

    auto list_buffer = os_developer_options::instance->get_int(mString{"PCLISTBUFFER"});
    nglSetBufferSize(static_cast<nglBufferType>(0), list_buffer << 10, true);
    auto scratch_buffer = os_developer_options::instance->get_int(mString{"PCSCRATCHBUFFER"});
    nglSetBufferSize(static_cast<nglBufferType>(1), scratch_buffer << 10, true);
    auto v154 = os_developer_options::instance->get_int(mString{"PCSCRATCHINDEXBUFFER"});
    nglSetBufferSize(static_cast<nglBufferType>(2), 2 * v154, true);
    auto v155 = os_developer_options::instance->get_int(mString{"PCSCRATCHVERTEXBUFFER"});
    nglSetBufferSize(static_cast<nglBufferType>(3), v155 << 10, true);

    aeps::Init();

    //application_startup
    {
        entity_handle_manager::create_inst();
        app::create_inst();
        bink_set_sound_system();
        cut_scene::init_stream_scene_anims();
    }

    if (g_is_the_packer()) {
        //sub_748E10();
    } else {
        if (!g_master_clock_is_up()) {
            timeBeginPeriod(1u);
        }

        auto v163 = timeGetTime();
        auto v165 = (double) os_developer_options::instance->get_int(mString{"RUN_LENGTH"});
        auto v164 = (os_developer_options::instance->get_int(mString{"RUN_LENGTH"}) != -1);

        g_timer()->sub_582180();

        g_game_ptr->gamefile->field_340.m_invert_camera_horz = Settings::InvertCameraH();
        g_game_ptr->gamefile->field_340.m_invert_camera_vert = Settings::InvertCameraV();
        auto *rumble_ptr = input_mgr::instance->rumble_ptr;
        if (rumble_ptr != nullptr) {
            rumble_ptr->disable_vibration();
        }

        if (!bExit()) {

            while (1) {
                MSG Msg;

                auto res = PeekMessageA(&Msg, nullptr, 0, 0, 1u);

                while (res != 0) {
                    if (Msg.message == WM_QUIT) {
                        bExit() = true;
                    }

                    TranslateMessage(&Msg);
                    DispatchMessageA(&Msg);
                    res = PeekMessageA(&Msg, nullptr, 0, 0, 1u);
                }

                if (v164 && v165 < 0.0) {
                    break;
                }

                if (bExit()) {
                    goto LABEL_94;
                }

                if (byte_965BF9()) {
                    if (!g_master_clock_is_up()) {
                        timeBeginPeriod(1u);
                    }

                    DWORD v158 = timeGetTime();
                    DWORD v159 = timeGetTime();
                    auto v160 = (double) (v159 - v163);
                    v163 = v159;
                    v165 = v165 - v160 * 0.001;
                    app::instance->tick();
                    DWORD v168 = timeGetTime() - v158;
                    app::instance->m_game->field_278 = v168 * 0.001f;

                    if (g_inputSettingsInGame()->field_18.get_state(InputAction::ScreenShot) <=
                        0.0)
                    {
                        if (!byte_965BF5() && byte_965BF6()) {
                            byte_965BF5() = true;
                            byte_965BF6() = false;
                        }

                    } else {
                        byte_965BF6() = true;
                    }

                    if (dword_922908()) {
                        if (dword_922908() >= 0 && !byte_965C21()) {
                            --dword_922908();
                        }
                    } else if (!byte_965C21()) {
                        if (byte_965BF8()) {
                            ClipCursor(nullptr);
                            break;
                        }

                        if (sub_5A3AA0("CONFIRMQUIT_MSG", nullptr)) {
                            ClipCursor(nullptr);
                            bExit() = true;
                            dword_922908() = -1;
                        } else {
                            g_cursor()->field_120 = 0;
                            if (!g_cursor()->field_120) {
                                g_cursor()->field_114 = 1;
                            }

                            dword_922908() = -1;
                        }
                    }

                    if (bExit()) {
                        goto LABEL_94;
                    }
                }
            }

            bExit() = true;
        }
    }
LABEL_94:

    if (app::instance != nullptr) {
        auto *vtbl = bit_cast<int(*)[1]>(app::instance->m_vtbl);

        assert((*vtbl)[0] == 0x005E99D0);

        delete app::instance;

        app::instance = nullptr;
    }

    entity_handle_manager::delete_inst();

    sub_732D60(1);

    sub_4DDEC0();

    if (g_cursor() != nullptr) {
        auto *vtbl = bit_cast<int(*)[1]>(g_cursor()->m_vtbl);

        assert((*vtbl)[0] == 0x005B7BC0);

        delete g_cursor();
    }

    sub_76DF40();
    nalExit();
    sub_77B2F0(1);

    if (g_timer() != nullptr) {
        operator delete(g_timer());
    }

    free_file(g_fileUSM());

    sub_81E300();

    if (Input::instance() != nullptr) {
        Input::instance()->sub_820C60();
        operator delete(Input::instance());
        Input::instance() = nullptr;
    }

    sub_81E300();
    sub_81D700();

    delete g_inputSettingsMenu();
    delete g_inputSettingsInGame();
    delete g_inputSettings2();
    delete g_inputSettings3();
    delete g_inputSettings4();
    delete g_settings();

    sub_81C230();

    DestroyWindow(window_manager::instance()->field_4);

    if (window_manager::instance() != nullptr) {
        delete window_manager::instance();
        window_manager::instance() = nullptr;
    }

    if (os_developer_options::instance != nullptr) {
        delete os_developer_options::instance;
        os_developer_options::instance = nullptr;
    }

    sub_79DFF0();

    delete[] dword_965C00();

    return 0;
}

void redirect_winmain() {
    REDIRECT(0x00822556, myWinMain);
}

HANDLE __stdcall HookCreateFileA(LPCSTR lpFileName,
                                 DWORD dwDesiredAccess,
                                 DWORD dwShareMode,
                                 LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                 DWORD dwCreationDisposition,
                                 DWORD dwFlagsAndAttributes,
                                 HANDLE hTemplateFile) {
    //sp_log("HookCreateFileA %s, return_address = 0x%08X", lpFileName, getReturnAddress);

    return CreateFileA(lpFileName,
                       dwDesiredAccess,
                       dwShareMode,
                       lpSecurityAttributes,
                       dwCreationDisposition,
                       dwFlagsAndAttributes,
                       hTemplateFile);
}

BOOL __stdcall HookReadFile(HANDLE hFile,
                            LPVOID lpBuffer,
                            DWORD nNumberOfBytesToRead,
                            LPDWORD lpNumberOfBytesRead,
                            LPOVERLAPPED lpOverlapped) {
    //sp_log("HookReadFile 0x%08X, return_address = 0x%08X", hFile, getReturnAddress);

    return ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}

//0x0081BFB0
void register_class(LPCSTR lpClassName, WNDPROC windowProc, HINSTANCE hInstance, int a4) {
    static ATOM g_wndClass{};

    if (g_wndClass) {
        UnregisterClassA(lpClassName, hInstance);
    }

#if 0
    WNDCLASSEXA desc;
    memset(&desc, 0, sizeof(desc));
#else
    WNDCLASSEXA desc{};
#endif

    desc.lpfnWndProc = windowProc;
    desc.cbSize = 48;
    desc.style = 64;
    desc.hInstance = hInstance;
    desc.lpszClassName = lpClassName;
    if (a4) {
        desc.hIcon = LoadIconA(hInstance, MAKEINTRESOURCE(a4));
    }

    g_wndClass = RegisterClassExA(&desc);
}

//0x0081C030
void create_window(LPCSTR lpClassName,
                   LPCSTR lpWindowName,
                   HINSTANCE hInstance,
                   DWORD dwExStyle,
                   int p_y,
                   int a6,
                   int a7,
                   DWORD dwStyle) {
    int w;
    int h;
    DWORD dwStylea;

    int y = p_y;
    int x = dwExStyle;
    DWORD dwExStylea = 0;
    if ((uint8_t) dwStyle) {
        dwStylea = 0x80000000;
        dwExStylea = 8;
        x = 0;
        y = 0;
        w = GetSystemMetrics(SM_CXSCREEN);
        h = GetSystemMetrics(SM_CYSCREEN);
    } else {
        RECT Rect;
        Rect.left = 0;
        Rect.top = 0;
        dwStylea = 0x80C80000;
        Rect.right = a6;
        Rect.bottom = a7;
        AdjustWindowRectEx(&Rect, 0x80C80000, 0, 0);
        w = Rect.right - Rect.left;
        h = Rect.bottom - Rect.top;

        Var<int> dword_9874D4 = {0x009874D4};
        Var<int> dword_955158 = {0x00955158};
        dword_9874D4() = -Rect.left;
        dword_955158() = -Rect.top;
        if (x == -1) {
            x = (GetSystemMetrics(SM_CXSCREEN) - w) / 2;
        }

        if (y == -1) {
            y = (GetSystemMetrics(SM_CYSCREEN) - h) / 2;
        }
    }
    SetLastError(0);

    sp_log("create_window");

    g_appHwnd() =
        CreateWindowA(
        //CreateWindowExA(dwExStylea,
                              lpClassName,
                              lpWindowName,
                              dwStylea,
                              x,
                              y,
                              w,
                              h,
                              nullptr,
                              nullptr,
                              hInstance,
                              nullptr);

}

//0x0081C140
void register_class_and_create_window(LPCSTR lpClassName,
                                      LPCSTR lpWindowName,
                                      int X,
                                      int Y,
                                      int a5,
                                      int a6,
                                      WNDPROC windowProc,
                                      HINSTANCE hInstance,
                                      int a9,
                                      DWORD dwStyle) {
    if (g_appHwnd()) {
        DestroyWindow(g_appHwnd());
        g_appHwnd() = nullptr;
    }

    register_class(lpClassName, windowProc, hInstance, a9);
    create_window(lpClassName, lpWindowName, hInstance, X, Y, a5, a6, dwStyle);
}

unsigned int hook_controlfp(unsigned int, unsigned int) {
    return {};
}

void initterm(const _PVFV *ppfn, const _PVFV *end) {
    if constexpr (1) {
        do {
            if (auto pfn = *++ppfn) {
                pfn();
            }

        } while (ppfn < end);

    } else {
        CDECL_CALL(0x00822840, ppfn, end);
    }
}

void start() {
    __asm("add esp, 4\n");

    int v22;
    int v3;
    bool v4;
    int v2;

    IMAGE_NT_HEADERS32 *nt_header;

    BOOL v21 = 0;
    auto module_handle = GetModuleHandleA(nullptr);

    uint8_t *module_base = CAST(module_base, module_handle);
    IMAGE_DOS_HEADER *dos_header = CAST(dos_header, module_base);
    if (dos_header->e_magic != IMAGE_DOS_SIGNATURE) {
        goto LABEL_5;
    }

    nt_header = CAST(nt_header, module_base + dos_header->e_lfanew);

    if (nt_header->Signature != IMAGE_NT_SIGNATURE) {
        goto LABEL_5;
    }

    v2 = nt_header->OptionalHeader.Magic;
    if (v2 == 0x10B) {
        if (nt_header->OptionalHeader.NumberOfRvaAndSizes > 14) {
            v3 = 0;
            v4 = nt_header->OptionalHeader.DataDirectory[14].VirtualAddress == 0;
            goto LABEL_10;
        }
    LABEL_5:
        v22 = 0;
        goto LABEL_11;
    }

    if (v2 != 0x20B || nt_header->OptionalHeader.DataDirectory[1].Size <= 14) {
        goto LABEL_5;
    }

    v3 = 0;
    v4 = nt_header[1].Signature == 0;
LABEL_10:
    v3 = !v4;
    v22 = v3;
LABEL_11:
    //ms_exc.registration.TryLevel = 0;

    Var<int (*)(DWORD)> _set_app_type = {0x0086F254};
    _set_app_type()(2);

    static Var<int> dword_987BE0{0x00987BE0};
    static Var<int> dword_987BE4{0x00987BE4};

    dword_987BE0() = -1;
    dword_987BE4() = -1;

    static Var<int> dword_987BD4{0x00987BD4};
    static Var<int> dword_987BD8{0x00987BD8};
    static Var<int> dword_987BDC{0x00987BDC};

    _fmode = dword_987BD8();

    Var<int *(*) (void)> _p__commode{0x0086F240};
    *_p__commode()() = dword_987BD4();

    Var<DWORD> adjust_fdiv{0x0086F2BC};
    dword_987BDC() = adjust_fdiv();
    CDECL_CALL(0x008227B8);

    int (*sub_822858)() = CAST(sub_822858, 0x00822858);
    CDECL_CALL(0x00822858);

    static Var<int> dword_956284{0x00956284};
    if (!dword_956284()) {
        Var<int (*)(DWORD)> _setusermatherr{0x0086F238};

        _setusermatherr()((DWORD) sub_822858);
    }

    auto _setdefaultprecision = []() -> unsigned int { return _controlfp(0x10000u, 0x30000u); };

    _setdefaultprecision();

    Var<_PVFV> dword_91D934{0x0091D934};
    Var<_PVFV> dword_91D938{0x0091D938};
    initterm(&dword_91D934(), &dword_91D938());

    auto sub_8227FC = []() -> void { CDECL_CALL(0x008227FC); };

    atexit(sub_8227FC);

    Var<int> dword_987BD0{0x00987BD0};
    auto v19 = dword_987BD0();

    Var<int (*)(int *, char ***, char ***, int, void *)> _getmainargs{0x0086F230};

    int v16;
    char **v17;
    char **v18;
    Var<int> dword_987BCC{0x00987BCC};

    auto v15 = _getmainargs()(&v16, &v17, &v18, dword_987BCC(), &v19);
    if (v15 < 0) {
        auto amsg_exit = [](int a1) -> int {
            //
            return CDECL_CALL(0x008227B2, a1);
        };

        amsg_exit(8);
    }

    Var<_PVFV> dword_91B000{0x0091B000};
    Var<_PVFV> dword_91D930{0x0091D930};

    initterm(&dword_91B000(), &dword_91D930());

    char *i;
    char *v20;
    for (i = _acmdln;; ++i) {
        v20 = i;
        auto v6 = *i;
        if ((uint8_t) *i <= ' ' && (!v6 || !v21)) {
            break;
        }

        if (v6 == 34) {
            v21 = !v21;
        }

        Var<int (*)(unsigned int)> ismbblead{0x0086F2B0};
        if (ismbblead()(v6)) {
            v20 = ++i;
        }
    }

    while (*i != '\0' && *i <= ' ') {
        v20 = ++i;
    }

    STARTUPINFOA StartupInfo;
    StartupInfo.dwFlags = 0;
    GetStartupInfoA(&StartupInfo);

    int nShowCmd = (((StartupInfo.dwFlags & 1) != 0) ? StartupInfo.wShowWindow : 10);

    auto v8 = GetModuleHandleA(nullptr);

    int __stdcall (*WinMain)(HINSTANCE, HINSTANCE, LPSTR, int) = CAST(WinMain, 0x005AC1E0);

    auto v9 = WinMain(v8, nullptr, i, nShowCmd);

    if (!v22) {
        exit(v9);
    }

    Var<void (*)()> cexit{0x0086F2B4};

    cexit()();
    //ms_exc.registration.TryLevel = -1;
}

static void *HookVTableFunction(void *pVTable, void *fnHookFunc, int nOffset) {
    intptr_t ptrVtable = *((intptr_t *) pVTable); // Pointer to our chosen vtable
    intptr_t ptrFunction = ptrVtable +
        sizeof(intptr_t) *
            nOffset; // The offset to the function (remember it's a zero indexed array with a size of four bytes)
    intptr_t ptrOriginal = *((intptr_t *) ptrFunction); // Save original address

    // Edit the memory protection so we can modify it
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery((LPCVOID) ptrFunction, &mbi, sizeof(mbi));
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);

    // Overwrite the old function with our new one
    *((intptr_t *) ptrFunction) = (intptr_t) fnHookFunc;

    // Restore the protection
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

    // Return the original function address incase we want to call it
    return (void *) ptrOriginal;
}

uint32_t keys[256];

void GetDeviceStateHandleKeyboardInput(LPVOID lpvData) {
	BYTE* keysCurrent = (BYTE *) lpvData;

	for (auto i = 0u; i < 256u; ++i) {

		if (keysCurrent[i] != 0) {
			++keys[i];
		} else {
			keys[i] = 0;
		}
	}
}


typedef int (__stdcall* GetDeviceState_ptr)(IDirectInputDevice8*, DWORD, LPVOID);
GetDeviceState_ptr GetDeviceStateOriginal = nullptr;

HRESULT __stdcall GetDeviceStateHook(IDirectInputDevice8* self, DWORD cbData, LPVOID lpvData) {

	HRESULT res = GetDeviceStateOriginal(self, cbData, lpvData);

	printf("cbData %d %d %d\n", cbData, sizeof(DIJOYSTATE), sizeof(DIJOYSTATE2));

	//keyboard time babyyy
    if (cbData == 256)
    {
        GetDeviceStateHandleKeyboardInput(lpvData);
    }

    auto g_state = []() -> game_state {
        if (g_game_ptr != nullptr)
        {
            return g_game_ptr->get_cur_state();
        }

        return static_cast<game_state>(0);
    }();

    if (g_state != game_state::RUNNING && g_console == nullptr)
    {
        return res;
    }

    static constexpr struct {
        int key;
        char sym;
    } char_keys[] = {{DIK_A, 'a'}, {DIK_B, 'b'}, {DIK_C, 'c'}, {DIK_D, 'd'}, {DIK_E, 'e'}, {DIK_F, 'f'},
                     {DIK_G, 'g'}, {DIK_H, 'h'}, {DIK_I, 'i'}, {DIK_J, 'j'}, {DIK_K, 'k'}, {DIK_L, 'l'},
                     {DIK_M, 'm'}, {DIK_N, 'n'}, {DIK_O, 'o'}, {DIK_P, 'p'}, {DIK_Q, 'q'}, {DIK_R, 'r'},
                     {DIK_S, 's'}, {DIK_T, 't'}, {DIK_U, 'u'}, {DIK_V, 'v'}, {DIK_W, 'w'}, {DIK_X, 'x'},
                     {DIK_Y, 'y'}, {DIK_Z, 'z'}};

    static constexpr struct {
        int key;
        char sym;
    } num_keys[] = {{DIK_1, '1'},
                    {DIK_2, '2'},
                    {DIK_3, '3'},
                    {DIK_4, '4'},
                    {DIK_5, '5'},
                    {DIK_6, '6'},
                    {DIK_7, '7'},
                    {DIK_8, '8'},
                    {DIK_9, '9'},
                    {DIK_0, '0'}};

    auto key_is_pressed = [](int i) -> bool {
        auto res = (keys[i] == 2);
        if (res) keys[i] = 0;

        return res;
    };

    auto char_key_is_pressed = []() -> char {
        for (auto &k : char_keys) {
            if (keys[k.key] == 2) {
                keys[k.key] = 0;
                return k.sym;
            }
        }

        return 0;
    };

    auto num_key_is_pressed = []() -> char {
        for (auto &k : num_keys) {
            if (keys[k.key] == 2) {
                keys[k.key] = 0;
                return k.sym;
            }
        }

        return 0;
    };

    if (key_is_pressed(DIK_GRAVE)) {
        _kbevcb(KeyEvent::Press, KB_TILDE);
    }

    if (g_console == nullptr) {
        return res;
    }

    if (g_console->isVisible())
    {
        if (key_is_pressed(DIK_TAB))
        {
            _kbevcb(KeyEvent::Press, KB_TAB);
        }
        else if (key_is_pressed(DIK_RETURN)) {
            _kbevcb(KeyEvent::Press, KB_RETURN);
        } else if (key_is_pressed(DIK_HOME)) {
            _kbevcb(KeyEvent::Press, KB_HOME);
        } else if (key_is_pressed(DIK_END)) {
            _kbevcb(KeyEvent::Press, KB_END);
        } else if (key_is_pressed(DIK_PGUP)) {
            _kbevcb(KeyEvent::Press, KB_PAGEUP);
        } else if (key_is_pressed(DIK_PGDN)) {
            _kbevcb(KeyEvent::Press, KB_PAGEDOWN);
        } else if (key_is_pressed(DIK_UP)) {
            _kbevcb(KeyEvent::Press, KB_UP);
        } else if (key_is_pressed(DIK_DOWN)) {
            _kbevcb(KeyEvent::Press, KB_DOWN);
        }
        else if(key_is_pressed(DIK_BACKSPACE))
        {
            _kbevcb(KeyEvent::Press, KB_BACKSPACE);
        }
        else if (key_is_pressed(DIK_MINUS)) {
            _kbchcb('_');
        } else if (key_is_pressed(DIK_SPACE)) {
            _kbchcb(' ');
        }
        else if (char ch = char_key_is_pressed(); ch != 0)
        {
            if (GetKeyState(VK_SHIFT) & 0x8000) {
                _kbchcb(toupper(ch));
            } else {
                _kbchcb(ch);
            }
        }
        else if (char ch = num_key_is_pressed(); ch != 0)
        {
            if ((GetKeyState(VK_SHIFT) & 0x8000))
            {
                if (ch == '9')
                {
                    _kbchcb('(');
                }
                else if (ch == '0')
                {
                    _kbchcb(')');
                }
            }
            else
            {
                _kbchcb(ch);
            }

        }
    }

	if (g_console->isVisible()) {
        memset(lpvData, 0, cbData);
	}

	//printf("Device State called %08X %d\n", this, cbData);

	return res;
}

typedef HRESULT(__stdcall* GetDeviceData_ptr)(IDirectInputDevice8*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
GetDeviceData_ptr GetDeviceDataOriginal = nullptr;

HRESULT __stdcall GetDeviceDataHook(IDirectInputDevice8* self, DWORD cbObjectData, LPDIDEVICEOBJECTDATA rgdod, LPDWORD pdwInOut, DWORD dwFlags) {

	HRESULT res = GetDeviceDataOriginal(self, cbObjectData, rgdod, pdwInOut, dwFlags);

	printf("data\n");
	if (res == DI_OK) {

		printf("All gud\n");
		for (auto i = 0u; i < *pdwInOut; ++i) {

			if (LOBYTE(rgdod[i].dwData) > 0) {

				if (rgdod[i].dwOfs == DIK_ESCAPE) {

					printf("Pressed escaped\n");
					__debugbreak();
				}
			}
		}
	}
	//printf("Device Data called %08X\n", this);

	return res;
}

typedef HRESULT(__stdcall* IDirectInput8CreateDevice_ptr)(IDirectInput8W*, const GUID*, LPDIRECTINPUTDEVICE8W*, LPUNKNOWN);
IDirectInput8CreateDevice_ptr createDeviceOriginal = nullptr;

HRESULT  __stdcall IDirectInput8CreateDeviceHook(IDirectInput8W* self, const GUID* guid, LPDIRECTINPUTDEVICE8W* device, LPUNKNOWN unk) {

	//printf("CreateDevice %d %d %d %d %d %d %d\n", *guid, GUID_SysMouse, GUID_SysKeyboard, GUID_SysKeyboardEm, GUID_SysKeyboardEm2, GUID_SysMouseEm, GUID_SysMouseEm2);
	sp_log("Guid = {%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}\n",
		guid->Data1, guid->Data2, guid->Data3,
		guid->Data4[0], guid->Data4[1], guid->Data4[2], guid->Data4[3],
		guid->Data4[4], guid->Data4[5], guid->Data4[6], guid->Data4[7]);

	HRESULT res = createDeviceOriginal(self, guid, device, unk);

	if (IsEqualGUID(GUID_SysMouse, *guid))
		return res; // ignore mouse

	if (IsEqualGUID(GUID_SysKeyboard, *guid))
    {
		sp_log("Found the keyboard");
    }
	else
    {
		sp_log("Hooking something different...maybe a controller");
    }

    if (GetDeviceStateOriginal == nullptr) {
        GetDeviceStateOriginal = (GetDeviceState_ptr)
            HookVTableFunction((void *) *device, (void *) GetDeviceStateHook, 9);
    }

    if (GetDeviceDataOriginal == nullptr) {
        GetDeviceDataOriginal = (GetDeviceData_ptr) HookVTableFunction((void *) *device,
                                                                       (void *) GetDeviceDataHook,
                                                                       10);
    }

	return res;
}

typedef HRESULT(__stdcall* DirectInput8Create_ptr)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter);
HRESULT __stdcall HookDirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID* ppvOut, LPUNKNOWN punkOuter)
{
	DirectInput8Create_ptr caller = (decltype(caller)) *(void**)0x00987944;
	HRESULT res = caller(hinst, dwVersion, riidltf, ppvOut, punkOuter);

	IDirectInput8* iDir = (IDirectInput8 *) (*ppvOut);

    if (createDeviceOriginal == nullptr) {
        createDeviceOriginal = (IDirectInput8CreateDevice_ptr)
            HookVTableFunction((void *) iDir, (void *) IDirectInput8CreateDeviceHook, 3);
    }

	return res;
}

BOOL install_redirects()
{
    sp_log("Installing redirects\n");

    //fix invalid float operation
    {
        set_nop(0x005AC34C, 6);

        REDIRECT(0x005AC347, hook_controlfp);
    }

    REDIRECT(0x005AC52F, parse_cmd);

    {
        DWORD hookDirectInputAddress = (DWORD) HookDirectInput8Create;
        REDIRECT(0x008218B0, hookDirectInputAddress);
        set_nop(0x008218B5, 1);
        sp_log("Patching the DirectInput8Create call\n");
    }

    Timer_patch();

    //REDIRECT(0, sub_5952D0);

    if constexpr (1)
    {
        moved_entities_patch();

        pc_joypad_device_patch();

        player_controller_inode_patch();

        camera_mode_patch();

        game_button_patch();

        mouselook_controller_patch();

        web_zip_state_patch();

        lookat_target_controller_patch();

        controller_patch();

        scene_anim_patch();

        camera_patch();

        comic_panels_patch();

        us_person_patch();

        script_controller_patch();

        nal_anim_controller_patch();

        geometry_manager_patch();

        input_mgr_patch();
    }

    if constexpr (1) {
        console_patch();
    } else {
        game_patch();
    }

    city_lights_patch();

    return true;

    wds_render_manager_patch();

    wds_camera_manager_patch();

    resource_directory_patch();

    tlresource_directory_patch();


    input_settings_patch();

    game_settings_patch();

    ngl_patch();

    //standalone patches
    if constexpr (1)
    {
        slc_manager_patch();
    
        tl_patch();

        resource_manager_patch();

        script_manager_patch();

        slab_allocator_patch();

        nfl_system_patch();
    }

    if constexpr (0)
    {
        vm_patch();

        vm_thread_patch();

        vm_executable_patch();
    }

    if constexpr (0)
    {
        us_decal_patch();

        us_lod_patch();

        us_translucentshader_patch();

        us_simpleshader_patch();
    }

    if constexpr (1)
    {
        sound_manager_patch();

        string_hash_dictionary_patch();

        fx_cache_patch();

        cached_special_effect_patch();

        damage_interface_patch();

        mashable_vector_patch();

        core_ai_resource_patch();

        sound_bank_slot_patch();

        settings_patch();

        static_region_list_methods_patch();

        aeps_patch();

        game_camera_patch();

        region_patch();
        
        matrix4x4_patch();

        ai_interaction_data_patch();

        animation_controller_patch();

        collision_capsule_patch();

        city_lod_patch();

        swing_inode_patch();

        swing_state_patch();

        jump_state_patch();

        polytube_patch();

        web_interface_patch();

        web_polytube_patch();

        entity_patch();

        wds_token_manager_patch();

        beam_patch();

        motion_effect_struct_patch();

        ngl_vertexdef_patch();

        actor_patch();

        app_patch();

        camera_target_info_patch();

        spiderman_camera_patch();

        script_data_interface_patch();

        animation_interface_patch();

        conglomerate_patch();

        entity_base_patch();

        entity_mash_patch();

        anim_record_patch();

        sound_interface_patch();
    }

    if constexpr (0)
    {
        script_executable_patch();

        script_patch();

        script_instance_patch();

        script_access_patch();
    }

    if constexpr (1)
    {
        combo_system_patch();

        combo_system_move_patch();

        meta_anim_interact_patch();

        Input_patch();

        sin_container_patch();

        daynight_patch();

        FrontEnd_Shader_patch();

        nglShader_patch();

        mission_manager_patch();
    }

    if constexpr (0)
    {
        resource_pack_streamer_patch();

        resource_partition_patch();

        resource_pack_slot_patch();

        resource_pack_standalone_patch();

        resource_key_patch();
    }

    if constexpr (0)
    {
        tlResourceDirectory_patch();
        
        PanelMeshSection_patch();

        fe_mini_map_widget_patch();

        IGOFrontEnd_patch();

        spider_monkey_patch();

        FEManager_patch();

        MultiLineString_patch();

        menu_nav_bar_patch();
    }

    if constexpr (0)
    {
        pause_menu_message_log_patch();

        pause_menu_save_load_display_patch();

        pause_menu_controller_patch();

        pause_menu_options_display_patch();

        pause_menu_transition_patch();

        pause_menu_status_patch();

        pause_menu_root_patch();

        unlockables_menu_patch();
    }

    if constexpr (0)
    {
        PauseMenuSystem_patch();

        cg_mesh_patch();

        FEFloatingText_patch();

        FEMultiLineText_patch();

        mash_virtual_base_patch();

        PanelAnimFile_patch();

        fe_dialog_text_patch();

        PanelQuad_patch();

        FEText_patch();

        PanelFile_patch();

        localized_string_table_patch();

        animation_logic_system_shared_patch();

        mash_info_struct_patch();
    }

    if constexpr (1)
    {
        worldly_pack_slot_patch();

        nsl_patch();

        wds_script_manager_patch();

        world_dynamics_system_patch();

        entity_handle_manager_patch();

        eligible_pack_patch();

        terrain_patch();

        chuck_callbacks_patch();
    }

    if constexpr (1)
    {
        os_file_patch();

        traffic_patch();

        traffic_path_lane_patch();

        spawnable_patch();

        ai_path_patch();

        ai_core_patch();
    }

    animation_logic_system_patch();

    if constexpr (1)
    {
        interactable_interface_patch();

        event_manager_patch();

        trigger_manager_patch();

        variant_interface_patch();
    }

    if constexpr (1)
    {
        nalStreamInstance_patch();

        script_memtrack_patch();

        scratchpad_stack_patch();

        hero_inode_patch();

        cut_scene_player_patch();
    }

    if constexpr (1)
    {
        character_anim_controller_patch();

        usm_anim_player_patch();

        anim_handle_patch();

        plr_loco_crawl_state_patch();

        plr_loco_crawl_transition_state_patch();

        ai_player_controller_patch();

        ai_state_machine_patch();

        line_info_patch();
        
        local_collision_patch();

        hierarchical_entity_proximity_map_patch();

        spidey_base_state_patch();

        hero_base_state_patch();
        
        enhanced_state_patch();

        CharComponentBase_patch();
        
        nalChar_patch();

        ped_spawner_patch();
    }

    //resource handler patches
    if constexpr (0)
    {
        ai_interact_resource_handler_patch();

        cut_scene_resource_handler_patch();

        patrol_def_resource_handler_patch();

        item_resource_handler_patch();

        box_trigger_resource_handler_patch();

        path_resource_handler_patch();

        ai_state_graph_resource_handler_patch();

        scene_anim_resource_handler_patch();

        anim_resource_handler_patch();

        base_ai_resource_handler_patch();

        skeleton_resource_handler_patch();

        sound_alias_database_resource_handler_patch();

        glass_house_resource_handler_patch();

        material_file_resource_handler_patch();

        morph_file_resource_handler_patch();

        mesh_file_resource_handler_patch();

        panel_resource_handler_patch();

        texture_resource_handler_patch();

        gab_database_resource_handler_patch();

        als_resource_handler_patch();
    }

    //als
    if constexpr (0)
    {
        als_meta_anim_base_patch();

        als_meta_anim_swing_patch();

        als_meta_aimed_shot_vert_patch();

        als_animation_logic_system_interface_patch();

        als_inode_patch();

        als_state_machine_patch();

        als_meta_anim_table_shared_patch();

        als_state_machine_shared_patch();

        als_transition_group_base_patch();

        als_scripted_category_patch();

        als_category_patch();

        als_simple_orientation_patch();

        als_scripted_state_patch();

        als_state_patch();

        als_layer_state_machine_shared_patch();

        als_basic_rule_data_patch();
        
        als_res_data_patch();

        als_mocomp_patch();

        als_motion_compensator_patch();
    }

    return TRUE;

    tlInstanceBank_patch();

    mission_stack_manager_patch();

    SET_JUMP(0x008223D8, start);

    {
        //REDIRECT(0x008224B1, initterm);
        REDIRECT(0x00822500, initterm);
    }

    REDIRECT(0x005AC4A9, register_class_and_create_window);

    os_developer_options_patch();


    //rbc_contact_patch();

    //spline_patch();


    if constexpr (0) {

        anchor_query_visitor_patch();


        PanelQuadSection_patch();


        rigid_body_patch();

        swing_anchor_finder_patch();

        USVariantShaderNode_patch();

        script_library_class_patch();

        po_patch();

        wds_entity_manager_patch();

        info_node_desc_list_patch();

        FEMenu_patch();

        main_menu_keyboard_patch();

        main_menu_options_patch();

        FrontEndMenuSystem_patch();

        game_data_meat_patch();

        TextureInputPack_patch();

        FEMenuEntry_patch();

        IGOZoomOutMap_patch();

        run_state_patch();
    }

#define ORIGINAL_DLL 0
#if ORIGINAL_DLL
    {
        if constexpr (0)
        {
            if constexpr (0) {
                //EnableLog l{};

                sp_log("Ints:");

                mString ints{"{"};

                for (size_t i{0}; i < std::size(flag_names()); ++i) {
                    //sp_log("%d %s", i, int_names()[i]);

                    ints += mString{0, "%d \"%s\", \n", i, flag_names()[i]};
                }

                sp_log("%s", ints.c_str());

                assert(0);

                sp_log("\nFlags:");

                for (size_t i{0}; i < std::size(flag_names()); ++i) {
                    sp_log("%d %s", i, flag_names()[i]);
                }

                sp_log("\nStrings:");
                for (size_t i{0}; i < std::size(string_names()); ++i) {
                    sp_log("%d %s", i, string_names()[i]);
                }
            }

            sp_log("\nentity_flavor_names:");

            std::string str{};
            str.reserve(400);

            {
                str += "\n";

                for (int i = 0; i < 28; ++i) {
                    str += entity_flavor_names()[i];
                    str += "\n";
                }

                sp_log(str.c_str());
            }

            sp_log("resource_key_type_ext:");

            {
                str.clear();

                str += "\n";

                //for (auto &ext : resource_key_type_ext())
                auto &ext = resource_key_type_ext()[3];
                {
                    for (size_t i{0}; i < 70u; ++i) {
                        auto Src = ext[i];

                        str += Src;
                        str += ' ';
                        str += std::to_string(i);
                        str += "\n";
                    }

                    str += "\n";
                }

                sp_log(str.c_str());
            }

            assert(0);
        }

        //redirect_winmain();

#if 0
        

        FEMenuSystem_patch();

        character_viewer_patch();

        ghetto_mash_file_header_patch();

        string_hash_patch();

        mAvlTree_patch();

        resource_pack_header_patch();

        nfl_driver_patch();

        memory_patch();

#endif

        if constexpr (0) {
            set_nop(0x0076ECF0, 2);

            set_nop(0x0076EA57, 2);
            set_nop(0x0076EA64, 2);
        }

        collide_aux_patch();

        physical_interface_patch();


        nglRenderList_patch();

        swing_anchor_obbfilter_patch();

        quick_anchor_info_patch();

        glass_house_manager_patch();

        TextureHandle_patch();

        FileUSM_patch();

        ai_state_machine_patch();

        state_graph_patch();

        character_viewer_patch();

        filespec_patch();

        entity_base_patch();

        fe_mission_text_patch();

        alternate_costumes_patch();

        combat_state_patch();

        line_anchor_patch();

        resource_partition_patch();

        eligible_pack_streamer_patch();

        nglMesh_patch();

        pole_swing_state_patch();

        physics_inode_patch();

        interaction_inode_patch();

        pick_up_state_patch();

        cursor_patch();

        //message_board_patch();

#if 0

        
        

        param_block_patch();

        physics_system_patch();
#endif
    }

#endif //ORIGINAL_DLL

    sp_log("Redirects have been installed\n");

    return TRUE;
}

BOOL install_hooks() {
    return set_text_to_writable() && install_redirects() && install_patches() &&
        restore_text_perms();
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, [[maybe_unused]] LPVOID lpvReserved) {
    //printf("DLLMain %lu 0x%08X\n", fdwReason, (int) lpvReserved);

    if (fdwReason == DLL_PROCESS_ATTACH) {
        char *args = GetCommandLine();
        if (strstr(args, " -console")) {
            AllocConsole();
            if (!freopen("CONOUT$", "w", stdout)) {
                MessageBoxA(NULL, "Error", "Couldn't allocate console...Closing", 0);
                return FALSE;
            }
        }

        return install_hooks();

    } else if (fdwReason == DLL_PROCESS_DETACH) {
        FreeConsole();
    }

    return TRUE;
}
