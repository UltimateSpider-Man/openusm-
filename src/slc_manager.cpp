#include "slc_manager.h"

#include "func_wrapper.h"
#include "memory.h"
#include "utility.h"
#include "resource_key.h"
#include "resource_manager.h"
#include "script_manager.h"
#include "script_library_class.h"
#include "trace.h"
#include "variables.h"

#if !SLC_MANAGER_STANDALONE
Var<_std::vector<script_library_class *> *> slc_manager_class_array{0x00965EC8};
#else

static std::vector<script_library_class *> *g_slc_manager_class_array {nullptr};
Var<std::vector<script_library_class *> *>
    slc_manager_class_array {(int) &g_slc_manager_class_array};

#endif

void register_standard_script_libs() {
    CDECL_CALL(0x005AB800);
}

void construct_client_script_libs() {
    CDECL_CALL(0x0058F9C0);
}

void destruct_client_script_libs()
{
    CDECL_CALL(0x0058FA50);
}


#define BUILD_SLC_NAME(type) slc_ ## type ## _t

#define DECLARE_SLC(type, base_type, vtbl)                          \
    struct BUILD_SLC_NAME(type) : script_library_class {          \
        BUILD_SLC_NAME(type) ()                                   \
            : script_library_class(#type, 4u, #base_type, false) {  \
                m_vtbl = vtbl;                                      \
            }                                                       \
    }

#define BUILD_SLF_NAME(klass, type) slf__ ## klass ## __ ## type ## __t

#define BUILD_GLOBAL_SLF_NAME(type) slf__ ## type ## __t

DECLARE_SLC(pfx, "\0", 0x0089C878);

DECLARE_SLC(interactable_interface, "\0", 0x0089B5A8);

DECLARE_SLC(anim, "\0", 0x0089AAB0);

DECLARE_SLC(beam, entity, 0x0089AAF8);

DECLARE_SLC(entity, signaller, 0x0089A4C0);

DECLARE_SLC(cut_scene, "\0", 0x0089B7A8);

DECLARE_SLC(debug_menu_entry, "\0", 0x0089C6FC);

DECLARE_SLC(entity_list, "\0", 0x0089AA70);

DECLARE_SLC(entity_list_iterator, "\0", 0x0089AA78);

DECLARE_SLC(entity_tracker, "\0", 0x0089ABC4);

DECLARE_SLC(glamour_cam, "\0", 0x0089B778);

DECLARE_SLC(gun, item, 0x0089B57C);

DECLARE_SLC(item, entity, 0x0089AA44);

DECLARE_SLC(line_info, "\0", 0x0089B6FC);

DECLARE_SLC(mission_camera_marker, "\0", 0x0089C310);

DECLARE_SLC(mission_camera_transform_marker, "\0", 0x0089C328);

DECLARE_SLC(mission_transform_marker, "\0", 0x0089C31C);

DECLARE_SLC(num_list, "\0", 0x0089AA60);

DECLARE_SLC(num_list_iterator, "\0", 0x0089AA68);

DECLARE_SLC(panel, "\0", 0x0089B770);

DECLARE_SLC(polytube, entity, 0x0089C0EC);

DECLARE_SLC(script_controller, signaller, 0x0089BCCC);

DECLARE_SLC(signaller, "\0", 0x0089AAA8);

DECLARE_SLC(sound_inst, "\0", 0x0089B1EC);

DECLARE_SLC(str_list, "\0", 0x0089AA80);

DECLARE_SLC(str_list_iterator, "\0", 0x0089AA88);

DECLARE_SLC(switch_obj, entity, 0x0089B8D0);

DECLARE_SLC(tam, "\0", 0x0089C6C4);

DECLARE_SLC(taunt_entry, "\0", 0x0089BEBC);

DECLARE_SLC(taunt_exchange, "\0", 0x0089BEC4);

DECLARE_SLC(taunt_exchange_list, "\0", 0x0089AA90);

DECLARE_SLC(trigger, signaller, 0x0089B914);

DECLARE_SLC(vector3d, "\0", 0x0089A4CC);

DECLARE_SLC(position3d, vector3d, 0x0089A4D8);

DECLARE_SLC(posfacing3d, "\0", 0x0089A4E4);

DECLARE_SLC(vector3d_list, "\0", 0x0089AA50);

DECLARE_SLC(vector3d_list_iterator, "\0", 0x0089AA58);

DECLARE_SLC(string_hash, "\0", 0x0089A4F0);

DECLARE_SLC(critical_section, "\0", 0x0089C7DC);

DECLARE_SLC(district, signaller, 0x0089A4FC);


void chuck_register_script_libs()
{
    TRACE("chuck_register_script_libs");

    if constexpr (1) {
        std::vector<script_library_class *> classes(39u);
        auto class_idx = 0u;

#define CREATE_SLC(var, type) \
    auto *var = new (mem_alloc(sizeof(type))) type {}; \
    classes[class_idx++] = var;

        CREATE_SLC(local_5c, slc_pfx_t);

        CREATE_SLC(local_38, slc_interactable_interface_t);

        CREATE_SLC(local_20, slc_anim_t);

        CREATE_SLC(local_18, slc_beam_t);

        CREATE_SLC(local_94, slc_entity_t);

        CREATE_SLC(local_2c, slc_cut_scene_t);

        CREATE_SLC(puVar3, slc_debug_menu_entry_t);

        CREATE_SLC(local_30, slc_entity_list_t);

        CREATE_SLC(local_8c, slc_entity_list_iterator_t);

        CREATE_SLC(local_4c, slc_entity_tracker_t);

        CREATE_SLC(local_84, slc_glamour_cam_t);

        CREATE_SLC(local_28, slc_gun_t);

        CREATE_SLC(local_7c, slc_item_t);

        CREATE_SLC(local_44, slc_line_info_t);

        CREATE_SLC(local_74, slc_mission_camera_marker_t);

        CREATE_SLC(local_1c, slc_mission_camera_transform_marker_t);

        CREATE_SLC(local_6c, slc_mission_transform_marker_t);

        CREATE_SLC(local_3c, slc_num_list_t);

        CREATE_SLC(local_64, slc_num_list_iterator_t);

        CREATE_SLC(local_a8, slc_panel_t);

        CREATE_SLC(local_24, slc_polytube_t);

        CREATE_SLC(local_54, slc_script_controller_t);

        CREATE_SLC(local_98, slc_signaller_t);

        CREATE_SLC(local_90, slc_sound_inst_t);

        CREATE_SLC(local_88, slc_str_list_t);

        CREATE_SLC(local_80, slc_str_list_iterator_t);

        CREATE_SLC(local_78, slc_switch_obj_t);

        CREATE_SLC(local_70, slc_tam_t);

        CREATE_SLC(local_68, slc_taunt_entry_t);

        CREATE_SLC(local_60, slc_taunt_exchange_t);

        CREATE_SLC(local_58, slc_taunt_exchange_list_t);

        CREATE_SLC(local_50, slc_trigger_t);

        CREATE_SLC(local_48, slc_vector3d_t);

        CREATE_SLC(local_9c, slc_position3d_t);

        CREATE_SLC(local_34, slc_posfacing3d_t);

        CREATE_SLC(local_14, slc_vector3d_list_t);

        CREATE_SLC(local_10, slc_vector3d_list_iterator_t);

        CREATE_SLC(local_40, slc_string_hash_t);

        CREATE_SLC(local_a4, slc_critical_section_t);

        CREATE_SLC(local_a0, slc_district_t);

        if (!g_is_the_packer() && !script_manager::using_chuck_old_fashioned()) {
            slc_manager::un_mash_all_funcs();
        }

#define CREATE_SLF(TYPE, vtbl, NAME)                                              \
    struct BUILD_SLF_NAME(KLASS, TYPE) : script_library_class::function { \
        BUILD_SLF_NAME(KLASS, TYPE) (                                   \
            script_library_class *slc,                                  \
            const char *a3) : function(slc, a3)  {                      \
            m_vtbl = vtbl;                                              \
        }                                                               \
    };                                                                  \
    new (mem_alloc(sizeof(BUILD_SLF_NAME(KLASS, TYPE)))) BUILD_SLF_NAME(KLASS, TYPE) {SLC_VAR, NAME}


#define CREATE_GLOBAL_SLF(TYPE, vtbl, NAME)                                              \
    struct BUILD_GLOBAL_SLF_NAME(TYPE) : script_library_class::function { \
        BUILD_GLOBAL_SLF_NAME(TYPE) (                                   \
            const char *a3) : function(a3)  {                      \
            m_vtbl = vtbl;                                              \
        }                                                               \
    };                                                                  \
    new (mem_alloc(sizeof(BUILD_GLOBAL_SLF_NAME(TYPE)))) \
        BUILD_GLOBAL_SLF_NAME(TYPE) {NAME}

        {
            CREATE_GLOBAL_SLF(stru_89A724, 0x0089A724, "abs_delay(num)");

            CREATE_GLOBAL_SLF(stru_89A91C, 0x0089A91C, "acos(num)");

            CREATE_GLOBAL_SLF(stru_89A860, 0x0089A860, "add_2d_debug_str(vector3d,vector3d,num,str)");

            CREATE_GLOBAL_SLF(stru_89A858, 0x0089A858, "add_2d_debug_str(vector3d,vector3d,num,str,num)");

            CREATE_GLOBAL_SLF(stru_89A850, 0x0089A850, "add_3d_debug_str(vector3d,vector3d,num,str)");

            CREATE_GLOBAL_SLF(stru_89C5BC, 0x0089C5BC, "add_civilian_info(vector3d,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89C5CC, 0x0089C5CC, "add_civilian_info_entity(entity,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A774, 0x0089A774, "add_debug_cyl(vector3d,vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A77C, 0x0089A77C, "add_debug_cyl(vector3d,vector3d,num,vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A764, 0x0089A764, "add_debug_line(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89A76C, 0x0089A76C, "add_debug_line(vector3d,vector3d,vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A754, 0x0089A754, "add_debug_sphere(vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A75C, 0x0089A75C, "add_debug_sphere(vector3d,num,vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A548, 0x0089A548, "add_glass_house(str)");

            CREATE_GLOBAL_SLF(stru_89A550, 0x0089A550, "add_glass_house(str,num)");

            CREATE_GLOBAL_SLF(stru_89A560, 0x0089A560, "add_glass_house(str,num,vector3d)");

            CREATE_GLOBAL_SLF(stru_89A558, 0x0089A558, "add_glass_house(str,vector3d)");

            CREATE_GLOBAL_SLF(stru_89A834, 0x0089A834, "add_to_console(str)");

            CREATE_GLOBAL_SLF(stru_89C5A4, 0x0089C5A4, "add_traffic_model(num,str)");

            CREATE_GLOBAL_SLF(stru_89A594, 0x0089A594, "allow_suspend_thread(num)");

            CREATE_GLOBAL_SLF(stru_89BA50, 0x0089BA50, "angle_between(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89A804, 0x0089A804, "apply_donut_damage(vector3d,num,num,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A7FC, 0x0089A7FC, "apply_radius_damage(vector3d,num,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A80C, 0x0089A80C, "apply_radius_subdue(vector3d,num,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A518, 0x0089A518, "assert(num,str)");

            CREATE_GLOBAL_SLF(stru_89A9FC, 0x0089A9FC, "attach_decal(str,vector3d,num,vector3d,entity)");

            CREATE_GLOBAL_SLF(stru_89B7B0, 0x0089B7B0, "begin_screen_recording(str,num)");

            CREATE_GLOBAL_SLF(stru_89BCAC, 0x0089BCAC, "blackscreen_off(num)");

            CREATE_GLOBAL_SLF(stru_89BCA0, 0x0089BCA0, "blackscreen_on(num)");

            CREATE_GLOBAL_SLF(stru_89BC28, 0x0089BC28, "bring_up_dialog_box(num,num,...)");

            CREATE_GLOBAL_SLF(stru_89BC38, 0x0089BC38, "bring_up_dialog_box_debug(str,num,str)");

            CREATE_GLOBAL_SLF(stru_89BC30, 0x0089BC30, "bring_up_dialog_box_title(num,num,num,...)");

            CREATE_GLOBAL_SLF(stru_89BB10, 0x0089BB10, "bring_up_medal_award_box(num)");

            CREATE_GLOBAL_SLF(stru_89BB08, 0x0089BB08, "bring_up_race_announcer()");

            CREATE_GLOBAL_SLF(stru_89A98C, 0x0089A98C, "calc_launch_vector(vector3d,vector3d,num,entity)");

            CREATE_GLOBAL_SLF(stru_89C3F4, 0x0089C3F4, "can_load_pack(str)");

            CREATE_GLOBAL_SLF(stru_89AF04, 0x0089AF04, "chase_cam()");

            CREATE_GLOBAL_SLF(stru_89A95C, 0x0089A95C, "clear_all_grenades()");

            CREATE_GLOBAL_SLF(stru_89C5E4, 0x0089C5E4, "clear_civilians_within_radius(vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89BD48, 0x0089BD48, "clear_controls()");

            CREATE_GLOBAL_SLF(stru_89A79C, 0x0089A79C, "clear_debug_all()");

            CREATE_GLOBAL_SLF(stru_89A794, 0x0089A794, "clear_debug_cyls()");

            CREATE_GLOBAL_SLF(stru_89A78C, 0x0089A78C, "clear_debug_lines()");

            CREATE_GLOBAL_SLF(stru_89A784, 0x0089A784, "clear_debug_spheres()");

            CREATE_GLOBAL_SLF(stru_89A944, 0x0089A944, "clear_screen()");

            CREATE_GLOBAL_SLF(stru_89C5DC, 0x0089C5DC, "clear_traffic_within_radius(vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A868, 0x0089A868, "col_check(vector3d,vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A83C, 0x0089A83C, "console_exec(str)");

            CREATE_GLOBAL_SLF(stru_89BED4, 0x0089BED4, "copy_vector3d_list(vector3d_list,vector3d_list)");

            CREATE_GLOBAL_SLF(stru_89A90C, 0x0089A90C, "cos(num)");

            CREATE_GLOBAL_SLF(stru_89ABB4, 0x0089ABB4, "create_beam()");

            CREATE_GLOBAL_SLF(stru_89BAE8, 0x0089BAE8, "create_credits()");

            CREATE_GLOBAL_SLF(stru_89B7C0, 0x0089B7C0, "create_cut_scene(str)");

            CREATE_GLOBAL_SLF(stru_89C704, 0x0089C704, "create_debug_menu_entry(str)");

            CREATE_GLOBAL_SLF(stru_89C70C, 0x0089C70C, "create_debug_menu_entry(str,str)");

            CREATE_GLOBAL_SLF(stru_89A9F4, 0x0089A9F4, "create_decal(str,vector3d,num,vector3d)");

            CREATE_GLOBAL_SLF(stru_89AF0C, 0x0089AF0C, "create_entity(str)");

            CREATE_GLOBAL_SLF(stru_89AF14, 0x0089AF14, "create_entity(str,str)");

            CREATE_GLOBAL_SLF(stru_89AF2C, 0x0089AF2C, "create_entity_in_hero_region(str)");

            CREATE_GLOBAL_SLF(stru_89BFCC, 0x0089BFCC, "create_entity_list()");

            CREATE_GLOBAL_SLF(stru_89C594, 0x0089C594, "create_entity_tracker(entity)");

            CREATE_GLOBAL_SLF(stru_89B6B4, 0x0089B6B4, "create_item(str)");

            CREATE_GLOBAL_SLF(stru_89B708, 0x0089B708, "create_line_info(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89B818, 0x0089B818, "create_lofi_stereo_sound_inst(str)");

            CREATE_GLOBAL_SLF(stru_89BF54, 0x0089BF54, "create_num_list()");

            CREATE_GLOBAL_SLF(stru_89C904, 0x0089C904, "create_pfx(str)");

            CREATE_GLOBAL_SLF(stru_89C90C, 0x0089C90C, "create_pfx(str,vector3d)");

            CREATE_GLOBAL_SLF(stru_89C228, 0x0089C228, "create_polytube()");

            CREATE_GLOBAL_SLF(stru_89C230, 0x0089C230, "create_polytube(str)");

            CREATE_GLOBAL_SLF(stru_89C714, 0x0089C714, "create_progression_menu_entry(str,str)");

            CREATE_GLOBAL_SLF(stru_89B7F8, 0x0089B7F8, "create_sound_inst()");

            CREATE_GLOBAL_SLF(stru_89B800, 0x0089B800, "create_sound_inst(str)");

            CREATE_GLOBAL_SLF(stru_89B808, 0x0089B808, "create_stompable_music_sound_inst(str)");

            CREATE_GLOBAL_SLF(stru_89C044, 0x0089C044, "create_str_list()");

            CREATE_GLOBAL_SLF(stru_89C63C, 0x0089C63C, "create_taunt_entry(entity,str,num)");

            CREATE_GLOBAL_SLF(stru_89C6B4, 0x0089C6B4, "create_taunt_exchange(entity,entity,num,num,num,num,...)");

            CREATE_GLOBAL_SLF(stru_89C0DC, 0x0089C0DC, "create_taunt_exchange_list()");

            CREATE_GLOBAL_SLF(stru_89C6CC, 0x0089C6CC, "create_threat_assessment_meter()");

            CREATE_GLOBAL_SLF(stru_89AF3C, 0x0089AF3C, "create_time_limited_entity(str,num)");

            CREATE_GLOBAL_SLF(stru_89B970, 0x0089B970, "create_trigger(entity,num)");

            CREATE_GLOBAL_SLF(stru_89B968, 0x0089B968, "create_trigger(str,vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89B960, 0x0089B960, "create_trigger(vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89B810, 0x0089B810, "create_unstompable_script_cutscene_sound_inst(str)");

            CREATE_GLOBAL_SLF(stru_89BECC, 0x0089BECC, "create_vector3d_list()");

            CREATE_GLOBAL_SLF(stru_89BA38, 0x0089BA38, "cross(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89A510, 0x0089A510, "debug_breakpoint()");

            CREATE_GLOBAL_SLF(stru_89A528, 0x0089A528, "debug_print(num,str)");

            CREATE_GLOBAL_SLF(stru_89A530, 0x0089A530, "debug_print(num,vector3d,str)");

            CREATE_GLOBAL_SLF(stru_89A520, 0x0089A520, "debug_print(str)");

            CREATE_GLOBAL_SLF(stru_89A538, 0x0089A538, "debug_print_set_background_color(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A71C, 0x0089A71C, "delay(num)");

            CREATE_GLOBAL_SLF(stru_89BAF0, 0x0089BAF0, "destroy_credits()");

            CREATE_GLOBAL_SLF(stru_89C71C, 0x0089C71C, "destroy_debug_menu_entry(debug_menu_entry)");

            CREATE_GLOBAL_SLF(stru_89AF34, 0x0089AF34, "destroy_entity(entity)");

            CREATE_GLOBAL_SLF(stru_89BFD4, 0x0089BFD4, "destroy_entity_list(entity_list)");

            CREATE_GLOBAL_SLF(stru_89C59C, 0x0089C59C, "destroy_entity_tracker(entity_tracker)");

            CREATE_GLOBAL_SLF(stru_89B710, 0x0089B710, "destroy_line_info(line_info)");

            CREATE_GLOBAL_SLF(stru_89BF5C, 0x0089BF5C, "destroy_num_list(num_list)");

            CREATE_GLOBAL_SLF(stru_89C914, 0x0089C914, "destroy_pfx(pfx)");

            CREATE_GLOBAL_SLF(stru_89C04C, 0x0089C04C, "destroy_str_list(str_list)");

            CREATE_GLOBAL_SLF(stru_89C644, 0x0089C644, "destroy_taunt_entry(taunt_entry)");

            CREATE_GLOBAL_SLF(stru_89C6BC, 0x0089C6BC, "destroy_taunt_exchange(taunt_exchange)");

            CREATE_GLOBAL_SLF(stru_89C0E4, 0x0089C0E4, "destroy_taunt_exchange_list(taunt_exchange_list)");

            CREATE_GLOBAL_SLF(stru_89C6D4, 0x0089C6D4, "destroy_threat_assessment_meter(tam)");

            CREATE_GLOBAL_SLF(stru_89B978, 0x0089B978, "destroy_trigger(trigger)");

            CREATE_GLOBAL_SLF(stru_89BEDC, 0x0089BEDC, "destroy_vector3d_list(vector3d_list)");

            CREATE_GLOBAL_SLF(stru_89A72C, 0x0089A72C, "dilated_delay(num)");

            CREATE_GLOBAL_SLF(stru_89A5F4, 0x0089A5F4, "disable_marky_cam(num)");

            CREATE_GLOBAL_SLF(stru_89A5E4, 0x0089A5E4, "disable_nearby_occlusion_only_obb(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A614, 0x0089A614, "disable_player_shadows()");

            CREATE_GLOBAL_SLF(stru_89A93C, 0x0089A93C, "disable_subtitles()");

            CREATE_GLOBAL_SLF(stru_89A7DC, 0x0089A7DC, "disable_vibrator()");

            CREATE_GLOBAL_SLF(stru_89BBF0, 0x0089BBF0, "disable_zoom_map(num)");

            CREATE_GLOBAL_SLF(stru_89BA48, 0x0089BA48, "distance3d(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89BB88, 0x0089BB88, "distance_chase_widget_set_pos(num)");

            CREATE_GLOBAL_SLF(stru_89BB80, 0x0089BB80, "distance_chase_widget_turn_off()");

            CREATE_GLOBAL_SLF(stru_89BB78, 0x0089BB78, "distance_chase_widget_turn_on(num,num)");

            CREATE_GLOBAL_SLF(stru_89BBA8, 0x0089BBA8, "distance_race_widget_set_boss_pos(num)");

            CREATE_GLOBAL_SLF(stru_89BBA0, 0x0089BBA0, "distance_race_widget_set_hero_pos(num)");

            CREATE_GLOBAL_SLF(stru_89BBB0, 0x0089BBB0, "distance_race_widget_set_types(num,num)");

            CREATE_GLOBAL_SLF(stru_89BB98, 0x0089BB98, "distance_race_widget_turn_off()");

            CREATE_GLOBAL_SLF(stru_89BB90, 0x0089BB90, "distance_race_widget_turn_on()");

            CREATE_GLOBAL_SLF(stru_89C47C, 0x0089C47C, "district_id(str)");

            CREATE_GLOBAL_SLF(stru_89C484, 0x0089C484, "district_name(num)");

            CREATE_GLOBAL_SLF(stru_89BA30, 0x0089BA30, "dot(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89A994, 0x0089A994, "dump_searchable_region_list(str)");

            CREATE_GLOBAL_SLF(stru_89A6CC, 0x0089A6CC, "enable_ai(num)");

            CREATE_GLOBAL_SLF(stru_89C5EC, 0x0089C5EC, "enable_civilians(num)");

            CREATE_GLOBAL_SLF(stru_89BD40, 0x0089BD40, "enable_controls(num)");

            CREATE_GLOBAL_SLF(stru_89B05C, 0x0089B05C, "enable_entity_fading(num)");

            CREATE_GLOBAL_SLF(stru_89A6C4, 0x0089A6C4, "enable_interface(num)");

            CREATE_GLOBAL_SLF(stru_89A5BC, 0x0089A5BC, "enable_marky_cam(num)");

            CREATE_GLOBAL_SLF(stru_89BBE8, 0x0089BBE8, "enable_mini_map(num)");

            CREATE_GLOBAL_SLF(stru_89A5DC, 0x0089A5DC, "enable_nearby_occlusion_only_obb(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A588, 0x0089A588, "enable_obb(vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A6AC, 0x0089A6AC, "enable_pause(num)");

            CREATE_GLOBAL_SLF(stru_89A6DC, 0x0089A6DC, "enable_physics(num)");

            CREATE_GLOBAL_SLF(stru_89A61C, 0x0089A61C, "enable_player_shadows()");

            CREATE_GLOBAL_SLF(stru_89A6EC, 0x0089A6EC, "enable_pois(num)");

            CREATE_GLOBAL_SLF(stru_89A578, 0x0089A578, "enable_quad_path_connector(district,num,district,num,num)");

            CREATE_GLOBAL_SLF(stru_89A934, 0x0089A934, "enable_subtitles()");

            CREATE_GLOBAL_SLF(stru_89B54C, 0x0089B54C, "enable_tokens_of_type(num,num)");

            CREATE_GLOBAL_SLF(stru_89C5FC, 0x0089C5FC, "enable_traffic(num)");

            CREATE_GLOBAL_SLF(stru_89A5D4, 0x0089A5D4, "enable_user_camera(num)");

            CREATE_GLOBAL_SLF(stru_89A7E4, 0x0089A7E4, "enable_vibrator()");

            CREATE_GLOBAL_SLF(stru_89C4FC, 0x0089C4FC, "end_current_patrol()");

            CREATE_GLOBAL_SLF(stru_89B7C8, 0x0089B7C8, "end_cut_scenes()");

            CREATE_GLOBAL_SLF(stru_89B7B8, 0x0089B7B8, "end_screen_recording()");

            CREATE_GLOBAL_SLF(stru_89A88C, 0x0089A88C, "entity_col_check(entity,entity)");

            CREATE_GLOBAL_SLF(stru_89AF24, 0x0089AF24, "entity_exists(str)");

            CREATE_GLOBAL_SLF(stru_89B034, 0x0089B034, "entity_get_entity_tracker(entity)");

            CREATE_GLOBAL_SLF(stru_89B02C, 0x0089B02C, "entity_has_entity_tracker(entity)");

            CREATE_GLOBAL_SLF(stru_89A604, 0x0089A604, "exit_water(entity)");

            CREATE_GLOBAL_SLF(stru_89A570, 0x0089A570, "find_closest_point_on_a_path_to_point(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A81C, 0x0089A81C, "find_district_for_point(vector3d)");

            CREATE_GLOBAL_SLF(stru_89B46C, 0x0089B46C, "find_entities_in_radius(entity_list,vector3d,num,num)");

            CREATE_GLOBAL_SLF(stru_89AF1C, 0x0089AF1C, "find_entity(str)");

            CREATE_GLOBAL_SLF(stru_89A824, 0x0089A824, "find_innermost_district(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A82C, 0x0089A82C, "find_outermost_district(vector3d)");

            CREATE_GLOBAL_SLF(stru_89B950, 0x0089B950, "find_trigger(entity)");

            CREATE_GLOBAL_SLF(stru_89B948, 0x0089B948, "find_trigger(str)");

            CREATE_GLOBAL_SLF(stru_89B958, 0x0089B958, "find_trigger_in_district(district,str)");

            CREATE_GLOBAL_SLF(stru_89A74C, 0x0089A74C, "float_random(num)");

            CREATE_GLOBAL_SLF(stru_89C3B4, 0x0089C3B4, "force_mission(district,str,num)");

            CREATE_GLOBAL_SLF(stru_89C4AC, 0x0089C4AC, "force_streamer_refresh()");

            CREATE_GLOBAL_SLF(stru_89BC74, 0x0089BC74, "format_time_string(num)");

            CREATE_GLOBAL_SLF(stru_89A5FC, 0x0089A5FC, "freeze_hero(num)");

            CREATE_GLOBAL_SLF(stru_89A97C, 0x0089A97C, "game_ini_get_flag(str)");

            CREATE_GLOBAL_SLF(stru_89C4DC, 0x0089C4DC, "game_time_advance(num,num)");

            CREATE_GLOBAL_SLF(stru_89A9EC, 0x0089A9EC, "get_all_execs_thread_count(str)");

            CREATE_GLOBAL_SLF(stru_89A9E4, 0x0089A9E4, "get_all_instances_thread_count(str)");

            CREATE_GLOBAL_SLF(stru_89AA24, 0x0089AA24, "get_attacker_entity()");

            CREATE_GLOBAL_SLF(stru_89AA2C, 0x0089AA2C, "get_attacker_member()");

            CREATE_GLOBAL_SLF(stru_89C4EC, 0x0089C4EC, "get_available_stack_size()");

            CREATE_GLOBAL_SLF(stru_89C354, 0x0089C354, "get_character_packname_list()");

            CREATE_GLOBAL_SLF(stru_89C61C, 0x0089C61C, "get_closest_point_on_lane_with_facing(num,vector3d,vector3d_list)");

            CREATE_GLOBAL_SLF(stru_89A884, 0x0089A884, "get_col_hit_ent()");

            CREATE_GLOBAL_SLF(stru_89A87C, 0x0089A87C, "get_col_hit_norm()");

            CREATE_GLOBAL_SLF(stru_89A874, 0x0089A874, "get_col_hit_pos()");

            CREATE_GLOBAL_SLF(stru_89A7F4, 0x0089A7F4, "get_control_state(num)");

            CREATE_GLOBAL_SLF(stru_89A7EC, 0x0089A7EC, "get_control_trigger(num)");

            CREATE_GLOBAL_SLF(stru_89A9DC, 0x0089A9DC, "get_current_instance_thread_count(str)");

            CREATE_GLOBAL_SLF(stru_89A5B4, 0x0089A5B4, "get_current_view_cam_pos()");

            CREATE_GLOBAL_SLF(stru_89A59C, 0x0089A59C, "get_current_view_cam_x_facing()");

            CREATE_GLOBAL_SLF(stru_89A5A4, 0x0089A5A4, "get_current_view_cam_y_facing()");

            CREATE_GLOBAL_SLF(stru_89A5AC, 0x0089A5AC, "get_current_view_cam_z_facing()");

            CREATE_GLOBAL_SLF(stru_89A8F4, 0x0089A8F4, "get_fog_color()");

            CREATE_GLOBAL_SLF(stru_89A8FC, 0x0089A8FC, "get_fog_distance()");

            CREATE_GLOBAL_SLF(stru_89A8C4, 0x0089A8C4, "get_game_info_num(str)");

            CREATE_GLOBAL_SLF(stru_89A8D4, 0x0089A8D4, "get_game_info_str(str)");

            CREATE_GLOBAL_SLF(stru_89B780, 0x0089B780, "get_glam_cam(num)");

            CREATE_GLOBAL_SLF(stru_89A894, 0x0089A894, "get_global_time_dilation()");

            CREATE_GLOBAL_SLF(stru_89A94C, 0x0089A94C, "get_ini_flag(str)");

            CREATE_GLOBAL_SLF(stru_89A954, 0x0089A954, "get_ini_num(str)");

            CREATE_GLOBAL_SLF(stru_89A92C, 0x0089A92C, "get_int_num(num)");

            CREATE_GLOBAL_SLF(stru_89C414, 0x0089C414, "get_mission_camera_marker(num)");

            CREATE_GLOBAL_SLF(stru_89C454, 0x0089C454, "get_mission_camera_transform_marker(num)");

            CREATE_GLOBAL_SLF(stru_89C38C, 0x0089C38C, "get_mission_entity()");

            CREATE_GLOBAL_SLF(stru_89C36C, 0x0089C36C, "get_mission_key_posfacing3d()");

            CREATE_GLOBAL_SLF(stru_89C364, 0x0089C364, "get_mission_key_position()");

            CREATE_GLOBAL_SLF(stru_89C40C, 0x0089C40C, "get_mission_marker(num)");

            CREATE_GLOBAL_SLF(stru_89C3AC, 0x0089C3AC, "get_mission_nums()");

            CREATE_GLOBAL_SLF(stru_89C384, 0x0089C384, "get_mission_patrol_waypoint()");

            CREATE_GLOBAL_SLF(stru_89C39C, 0x0089C39C, "get_mission_positions()");

            CREATE_GLOBAL_SLF(stru_89C3A4, 0x0089C3A4, "get_mission_strings()");

            CREATE_GLOBAL_SLF(stru_89C42C, 0x0089C42C, "get_mission_transform_marker(num)");

            CREATE_GLOBAL_SLF(stru_89C394, 0x0089C394, "get_mission_trigger()");

            CREATE_GLOBAL_SLF(stru_89C3BC, 0x0089C3BC, "get_missions_key_position_by_index(district,str,num)");

            CREATE_GLOBAL_SLF(stru_89C3CC, 0x0089C3CC, "get_missions_nums_by_index(district,str,num,num_list)");

            CREATE_GLOBAL_SLF(stru_89C3C4, 0x0089C3C4, "get_missions_patrol_waypoint_by_index(district,str,num)");

            CREATE_GLOBAL_SLF(stru_89C54C, 0x0089C54C, "get_neighborhood_name(num)");

            CREATE_GLOBAL_SLF(stru_89C3E4, 0x0089C3E4, "get_num_free_slots(str)");

            CREATE_GLOBAL_SLF(stru_89C434, 0x0089C434, "get_num_mission_transform_marker()");

            CREATE_GLOBAL_SLF(stru_89C3EC, 0x0089C3EC, "get_pack_group(str)");

            CREATE_GLOBAL_SLF(stru_89C4E4, 0x0089C4E4, "get_pack_size(str)");

            CREATE_GLOBAL_SLF(stru_89C534, 0x0089C534, "get_patrol_difficulty(str)");

            CREATE_GLOBAL_SLF(stru_89C52C, 0x0089C52C, "get_patrol_node_position_by_index(str,num)");

            CREATE_GLOBAL_SLF(stru_89C524, 0x0089C524, "get_patrol_start_position(str)");

            CREATE_GLOBAL_SLF(stru_89C53C, 0x0089C53C, "get_patrol_unlock_threshold(str)");

            CREATE_GLOBAL_SLF(stru_89A508, 0x0089A508, "get_platform()");

            CREATE_GLOBAL_SLF(stru_89A8E4, 0x0089A8E4, "get_render_opt_num(str)");

            CREATE_GLOBAL_SLF(stru_89CAC4, 0x0089CAC4, "get_spider_reflexes_spiderman_time_dilation()");

            CREATE_GLOBAL_SLF(stru_89CAD4, 0x0089CAD4, "get_spider_reflexes_world_time_dilation()");

            CREATE_GLOBAL_SLF(stru_89A7A4, 0x0089A7A4, "get_time_inc()");

            CREATE_GLOBAL_SLF(stru_89A974, 0x0089A974, "get_time_of_day()");

            CREATE_GLOBAL_SLF(stru_89A96C, 0x0089A96C, "get_time_of_day_rate()");

            CREATE_GLOBAL_SLF(stru_89B554, 0x0089B554, "get_token_index_from_id(num,num)");

            CREATE_GLOBAL_SLF(stru_89AA98, 0x0089AA98, "get_traffic_spawn_point_near_camera(vector3d_list)");

            CREATE_GLOBAL_SLF(stru_89BC90, 0x0089BC90, "greater_than_or_equal_rounded(num,num)");

            CREATE_GLOBAL_SLF(stru_89AA1C, 0x0089AA1C, "hard_break()");

            CREATE_GLOBAL_SLF(stru_89A580, 0x0089A580, "has_substring(str,str)");

            CREATE_GLOBAL_SLF(stru_89AED4, 0x0089AED4, "hero()");

            CREATE_GLOBAL_SLF(stru_89AEDC, 0x0089AEDC, "hero_exists()");

            CREATE_GLOBAL_SLF(stru_89AEE4, 0x0089AEE4, "hero_type()");

            CREATE_GLOBAL_SLF(stru_89BB20, 0x0089BB20, "hide_controller_gauge()");

            CREATE_GLOBAL_SLF(stru_89AA0C, 0x0089AA0C, "initialize_encounter_object()");

            CREATE_GLOBAL_SLF(stru_89AA04, 0x0089AA04, "initialize_encounter_objects()");

            CREATE_GLOBAL_SLF(stru_89C3D4, 0x0089C3D4, "insert_pack(str)");

            CREATE_GLOBAL_SLF(stru_89BC98, 0x0089BC98, "invoke_pause_menu_unlockables()");

            CREATE_GLOBAL_SLF(stru_89A6D4, 0x0089A6D4, "is_ai_enabled()");

            CREATE_GLOBAL_SLF(stru_89B7D0, 0x0089B7D0, "is_cut_scene_playing()");

            CREATE_GLOBAL_SLF(stru_89C49C, 0x0089C49C, "is_district_loaded(num)");

            CREATE_GLOBAL_SLF(stru_89A60C, 0x0089A60C, "is_hero_frozen()");

            CREATE_GLOBAL_SLF(stru_89AEFC, 0x0089AEFC, "is_hero_peter_parker()");

            CREATE_GLOBAL_SLF(stru_89AEEC, 0x0089AEEC, "is_hero_spidey()");

            CREATE_GLOBAL_SLF(stru_89AEF4, 0x0089AEF4, "is_hero_venom()");

            CREATE_GLOBAL_SLF(stru_89A5C4, 0x0089A5C4, "is_marky_cam_enabled()");

            CREATE_GLOBAL_SLF(stru_89C50C, 0x0089C50C, "is_mission_active()");

            CREATE_GLOBAL_SLF(stru_89C514, 0x0089C514, "is_mission_loading()");

            CREATE_GLOBAL_SLF(stru_89C404, 0x0089C404, "is_pack_available(str)");

            CREATE_GLOBAL_SLF(stru_89C3FC, 0x0089C3FC, "is_pack_loaded(str)");

            CREATE_GLOBAL_SLF(stru_89C34C, 0x0089C34C, "is_pack_pushed(str)");

            CREATE_GLOBAL_SLF(stru_89AAA0, 0x0089AAA0, "is_path_graph_inside_glass_house(str)");

            CREATE_GLOBAL_SLF(stru_89C504, 0x0089C504, "is_patrol_active()");

            CREATE_GLOBAL_SLF(stru_89C544, 0x0089C544, "is_patrol_node_empty(num)");

            CREATE_GLOBAL_SLF(stru_89A6B4, 0x0089A6B4, "is_paused()");

            CREATE_GLOBAL_SLF(stru_89A6E4, 0x0089A6E4, "is_physics_enabled()");

            CREATE_GLOBAL_SLF(stru_89A540, 0x0089A540, "is_point_inside_glass_house(vector3d)");

            CREATE_GLOBAL_SLF(stru_89AA3C, 0x0089AA3C, "is_point_under_water(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A5CC, 0x0089A5CC, "is_user_camera_enabled()");

            CREATE_GLOBAL_SLF(stru_89AAF0, 0x0089AAF0, "load_anim(str)");

            CREATE_GLOBAL_SLF(stru_89A8AC, 0x0089A8AC, "load_level(str,vector3d)");

            CREATE_GLOBAL_SLF(stru_89C4C4, 0x0089C4C4, "lock_all_districts()");

            CREATE_GLOBAL_SLF(stru_89C494, 0x0089C494, "lock_district(num)");

            CREATE_GLOBAL_SLF(stru_89C51C, 0x0089C51C, "lock_mission_manager(num)");

            CREATE_GLOBAL_SLF(stru_89A814, 0x0089A814, "los_check(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89BAE0, 0x0089BAE0, "lower_hotpursuit_indicator_level()");

            CREATE_GLOBAL_SLF(stru_89A984, 0x0089A984, "malor(vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89BA40, 0x0089BA40, "normal(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A6BC, 0x0089A6BC, "pause_game(num)");

            CREATE_GLOBAL_SLF(stru_89BAF8, 0x0089BAF8, "play_credits()");

            CREATE_GLOBAL_SLF(stru_89A8B4, 0x0089A8B4, "play_prerender(str)");

            CREATE_GLOBAL_SLF(stru_89C344, 0x0089C344, "pop_pack(str)");

            CREATE_GLOBAL_SLF(stru_89A73C, 0x0089A73C, "post_message(str,num)");

            CREATE_GLOBAL_SLF(stru_89AA34, 0x0089AA34, "pre_roll_all_pfx(num)");

            CREATE_GLOBAL_SLF(stru_89BB28, 0x0089BB28, "press_controller_gauge(num)");

            CREATE_GLOBAL_SLF(stru_89BB30, 0x0089BB30, "press_controller_gauge(num,num,num)");

            CREATE_GLOBAL_SLF(stru_89C4BC, 0x0089C4BC, "purge_district(num)");

            CREATE_GLOBAL_SLF(stru_89C334, 0x0089C334, "push_pack(str)");

            CREATE_GLOBAL_SLF(stru_89C33C, 0x0089C33C, "push_pack_into_district_slot(str)");

            CREATE_GLOBAL_SLF(stru_89BAD8, 0x0089BAD8, "raise_hotpursuit_indicator_level()");

            CREATE_GLOBAL_SLF(stru_89A744, 0x0089A744, "random(num)");

            CREATE_GLOBAL_SLF(stru_89C5C4, 0x0089C5C4, "remove_civilian_info(num)");

            CREATE_GLOBAL_SLF(stru_89C5D4, 0x0089C5D4, "remove_civilian_info_entity(entity,num)");

            CREATE_GLOBAL_SLF(stru_89A568, 0x0089A568, "remove_glass_house(str)");

            CREATE_GLOBAL_SLF(stru_89AFFC, 0x0089AFFC, "remove_item_entity_from_world(entity)");

            CREATE_GLOBAL_SLF(stru_89C3DC, 0x0089C3DC, "remove_pack(str)");

            CREATE_GLOBAL_SLF(stru_89C5AC, 0x0089C5AC, "remove_traffic_model(num)");

            CREATE_GLOBAL_SLF(stru_89B064, 0x0089B064, "reset_externed_alses()");

            CREATE_GLOBAL_SLF(stru_89CAEC, 0x0089CAEC, "set_all_anchors_activated(num)");

            CREATE_GLOBAL_SLF(stru_89A63C, 0x0089A63C, "set_blur(num)");

            CREATE_GLOBAL_SLF(stru_89A664, 0x0089A664, "set_blur_blend_mode(num)");

            CREATE_GLOBAL_SLF(stru_89A644, 0x0089A644, "set_blur_color(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A654, 0x0089A654, "set_blur_offset(num,num)");

            CREATE_GLOBAL_SLF(stru_89A65C, 0x0089A65C, "set_blur_rot(num)");

            CREATE_GLOBAL_SLF(stru_89A64C, 0x0089A64C, "set_blur_scale(num,num)");

            CREATE_GLOBAL_SLF(stru_89A6F4, 0x0089A6F4, "set_clear_color(vector3d)");

            CREATE_GLOBAL_SLF(stru_89CADC, 0x0089CADC, "set_current_mission_objective_caption(num)");

            CREATE_GLOBAL_SLF(stru_89C614, 0x0089C614, "set_default_traffic_hitpoints(num)");

            CREATE_GLOBAL_SLF(stru_89BC5C, 0x0089BC5C, "set_dialog_box_flavor(num)");

            CREATE_GLOBAL_SLF(stru_89BC6C, 0x0089BC6C, "set_dialog_box_lockout_time(num)");

            CREATE_GLOBAL_SLF(stru_89A99C, 0x0089A99C, "set_engine_property(str,num)");

            CREATE_GLOBAL_SLF(stru_89A62C, 0x0089A62C, "set_fov(num)");

            CREATE_GLOBAL_SLF(stru_89A8BC, 0x0089A8BC, "set_game_info_num(str,num)");

            CREATE_GLOBAL_SLF(stru_89A8CC, 0x0089A8CC, "set_game_info_str(str,str)");

            CREATE_GLOBAL_SLF(stru_89A89C, 0x0089A89C, "set_global_time_dilation(num)");

            CREATE_GLOBAL_SLF(stru_89A5EC, 0x0089A5EC, "set_marky_cam_lookat(vector3d)");

            CREATE_GLOBAL_SLF(stru_89C4B4, 0x0089C4B4, "set_max_streaming_distance(num)");

            CREATE_GLOBAL_SLF(stru_89C37C, 0x0089C37C, "set_mission_key_pos_facing(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89C374, 0x0089C374, "set_mission_key_position(vector3d)");

            CREATE_GLOBAL_SLF(stru_89BBF8, 0x0089BBF8, "set_mission_text(num,...)");

            CREATE_GLOBAL_SLF(stru_89BC64, 0x0089BC64, "set_mission_text_box_flavor(num)");

            CREATE_GLOBAL_SLF(stru_89BC00, 0x0089BC00, "set_mission_text_debug(str)");

            CREATE_GLOBAL_SLF(stru_89C60C, 0x0089C60C, "set_parking_density(num)");

            CREATE_GLOBAL_SLF(stru_89C5F4, 0x0089C5F4, "set_pedestrian_density(num)");

            CREATE_GLOBAL_SLF(stru_89A8DC, 0x0089A8DC, "set_render_opt_num(str,num)");

            CREATE_GLOBAL_SLF(stru_89BAC8, 0x0089BAC8, "set_score_widget_score(num)");

            CREATE_GLOBAL_SLF(stru_89A9D4, 0x0089A9D4, "set_sound_category_volume(num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A674, 0x0089A674, "set_spider_reflexes_blur(num)");

            CREATE_GLOBAL_SLF(stru_89A69C, 0x0089A69C, "set_spider_reflexes_blur_blend_mode(num)");

            CREATE_GLOBAL_SLF(stru_89A67C, 0x0089A67C, "set_spider_reflexes_blur_color(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A68C, 0x0089A68C, "set_spider_reflexes_blur_offset(num,num)");

            CREATE_GLOBAL_SLF(stru_89A694, 0x0089A694, "set_spider_reflexes_blur_rot(num)");

            CREATE_GLOBAL_SLF(stru_89A684, 0x0089A684, "set_spider_reflexes_blur_scale(num,num)");

            CREATE_GLOBAL_SLF(stru_89CAB4, 0x0089CAB4, "set_spider_reflexes_hero_meter_depletion_rate(num)");

            CREATE_GLOBAL_SLF(stru_89CABC, 0x0089CABC, "set_spider_reflexes_spiderman_time_dilation(num)");

            CREATE_GLOBAL_SLF(stru_89CACC, 0x0089CACC, "set_spider_reflexes_world_time_dilation(num)");

            CREATE_GLOBAL_SLF(stru_89CAE4, 0x0089CAE4, "set_state_of_the_story_caption(num)");

            CREATE_GLOBAL_SLF(stru_89B6C4, 0x0089B6C4, "set_target_info(entity,vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89A964, 0x0089A964, "set_time_of_day(num)");

            CREATE_GLOBAL_SLF(stru_89C604, 0x0089C604, "set_traffic_density(num)");

            CREATE_GLOBAL_SLF(stru_89C5B4, 0x0089C5B4, "set_traffic_model_usage(num,num)");

            CREATE_GLOBAL_SLF(stru_89A7D4, 0x0089A7D4, "set_vibration_resume(num)");

            CREATE_GLOBAL_SLF(stru_89B504, 0x0089B504, "set_whoosh_interp_rate(num)");

            CREATE_GLOBAL_SLF(stru_89B4FC, 0x0089B4FC, "set_whoosh_pitch_range(num,num)");

            CREATE_GLOBAL_SLF(stru_89B4EC, 0x0089B4EC, "set_whoosh_speed_range(num,num)");

            CREATE_GLOBAL_SLF(stru_89B4F4, 0x0089B4F4, "set_whoosh_volume_range(num,num)");

            CREATE_GLOBAL_SLF(stru_89A624, 0x0089A624, "set_zoom(num)");

            CREATE_GLOBAL_SLF(stru_89BB18, 0x0089BB18, "show_controller_gauge()");

            CREATE_GLOBAL_SLF(stru_89BAD0, 0x0089BAD0, "show_hotpursuit_indicator(num)");

            CREATE_GLOBAL_SLF(stru_89BAC0, 0x0089BAC0, "show_score_widget(num)");

            CREATE_GLOBAL_SLF(stru_89B50C, 0x0089B50C, "shut_up_all_ai_voice_boxes()");

            CREATE_GLOBAL_SLF(stru_89A904, 0x0089A904, "sin(num)");

            CREATE_GLOBAL_SLF(stru_89A924, 0x0089A924, "sin_cos(num)");

            CREATE_GLOBAL_SLF(stru_89BCBC, 0x0089BCBC, "soft_load(num)");

            CREATE_GLOBAL_SLF(stru_89BCB4, 0x0089BCB4, "soft_save(num)");

            CREATE_GLOBAL_SLF(stru_89CAA4, 0x0089CAA4, "spiderman_add_hero_points(num)");

            CREATE_GLOBAL_SLF(stru_89C91C, 0x0089C91C, "spiderman_bank_stylepoints()");

            CREATE_GLOBAL_SLF(stru_89C9E4, 0x0089C9E4, "spiderman_break_web()");

            CREATE_GLOBAL_SLF(stru_89CB34, 0x0089CB34, "spiderman_camera_add_shake(num,num,num)");

            CREATE_GLOBAL_SLF(stru_89C924, 0x0089C924, "spiderman_camera_autocorrect(num)");

            CREATE_GLOBAL_SLF(stru_89CAFC, 0x0089CAFC, "spiderman_camera_clear_fixedstatic()");

            CREATE_GLOBAL_SLF(stru_89CB24, 0x0089CB24, "spiderman_camera_enable_combat(num)");

            CREATE_GLOBAL_SLF(stru_89CB1C, 0x0089CB1C, "spiderman_camera_enable_lookaround(num)");

            CREATE_GLOBAL_SLF(stru_89CAF4, 0x0089CAF4, "spiderman_camera_set_fixedstatic(vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89CB2C, 0x0089CB2C, "spiderman_camera_set_follow(entity)");

            CREATE_GLOBAL_SLF(stru_89CB3C, 0x0089CB3C, "spiderman_camera_set_hero_underwater(num)");

            CREATE_GLOBAL_SLF(stru_89CB14, 0x0089CB14, "spiderman_camera_set_interpolation_time(num)");

            CREATE_GLOBAL_SLF(stru_89CB04, 0x0089CB04, "spiderman_camera_set_lockon_min_distance(num)");

            CREATE_GLOBAL_SLF(stru_89CB0C, 0x0089CB0C, "spiderman_camera_set_lockon_y_offset(num)");

            CREATE_GLOBAL_SLF(stru_89C98C, 0x0089C98C, "spiderman_charged_jump()");

            CREATE_GLOBAL_SLF(stru_89CA94, 0x0089CA94, "spiderman_enable_control_button(num,num)");

            CREATE_GLOBAL_SLF(stru_89C9AC, 0x0089C9AC, "spiderman_enable_lockon(num)");

            CREATE_GLOBAL_SLF(stru_89C9B4, 0x0089C9B4, "spiderman_engage_lockon(num)");

            CREATE_GLOBAL_SLF(stru_89C9BC, 0x0089C9BC, "spiderman_engage_lockon(num,entity)");

            CREATE_GLOBAL_SLF(stru_89CA9C, 0x0089CA9C, "spiderman_get_hero_points()");

            CREATE_GLOBAL_SLF(stru_89C9DC, 0x0089C9DC, "spiderman_get_max_zip_length()");

            CREATE_GLOBAL_SLF(stru_89C99C, 0x0089C99C, "spiderman_get_spidey_sense_level()");

            CREATE_GLOBAL_SLF(stru_89C934, 0x0089C934, "spiderman_is_crawling()");

            CREATE_GLOBAL_SLF(stru_89C964, 0x0089C964, "spiderman_is_falling()");

            CREATE_GLOBAL_SLF(stru_89C96C, 0x0089C96C, "spiderman_is_jumping()");

            CREATE_GLOBAL_SLF(stru_89C944, 0x0089C944, "spiderman_is_on_ceiling()");

            CREATE_GLOBAL_SLF(stru_89C94C, 0x0089C94C, "spiderman_is_on_ground()");

            CREATE_GLOBAL_SLF(stru_89C93C, 0x0089C93C, "spiderman_is_on_wall()");

            CREATE_GLOBAL_SLF(stru_89C95C, 0x0089C95C, "spiderman_is_running()");

            CREATE_GLOBAL_SLF(stru_89C984, 0x0089C984, "spiderman_is_sprint_crawling()");

            CREATE_GLOBAL_SLF(stru_89C974, 0x0089C974, "spiderman_is_sprinting()");

            CREATE_GLOBAL_SLF(stru_89C954, 0x0089C954, "spiderman_is_swinging()");

            CREATE_GLOBAL_SLF(stru_89C97C, 0x0089C97C, "spiderman_is_wallsprinting()");

            CREATE_GLOBAL_SLF(stru_89CA24, 0x0089CA24, "spiderman_lock_spider_reflexes_off()");

            CREATE_GLOBAL_SLF(stru_89CA1C, 0x0089CA1C, "spiderman_lock_spider_reflexes_on()");

            CREATE_GLOBAL_SLF(stru_89CA0C, 0x0089CA0C, "spiderman_lockon_camera_engaged()");

            CREATE_GLOBAL_SLF(stru_89CA04, 0x0089CA04, "spiderman_lockon_mode_engaged()");

            CREATE_GLOBAL_SLF(stru_89CA14, 0x0089CA14, "spiderman_set_camera_target(entity)");

            CREATE_GLOBAL_SLF(stru_89C9EC, 0x0089C9EC, "spiderman_set_desired_mode(num,vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89C9F4, 0x0089C9F4, "spiderman_set_health_beep_min_max_cooldown_time(num,num)");

            CREATE_GLOBAL_SLF(stru_89C9FC, 0x0089C9FC, "spiderman_set_health_beep_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CB44, 0x0089CB44, "spiderman_set_hero_meter_empty_rate(num)");

            CREATE_GLOBAL_SLF(stru_89C9CC, 0x0089C9CC, "spiderman_set_max_height(num)");

            CREATE_GLOBAL_SLF(stru_89C9D4, 0x0089C9D4, "spiderman_set_max_zip_length(num)");

            CREATE_GLOBAL_SLF(stru_89C9C4, 0x0089C9C4, "spiderman_set_min_height(num)");

            CREATE_GLOBAL_SLF(stru_89C994, 0x0089C994, "spiderman_set_spidey_sense_level(num)");

            CREATE_GLOBAL_SLF(stru_89C9A4, 0x0089C9A4, "spiderman_set_swing_anchor_max_sticky_time(num)");

            CREATE_GLOBAL_SLF(stru_89CAAC, 0x0089CAAC, "spiderman_subtract_hero_points(num)");

            CREATE_GLOBAL_SLF(stru_89CA74, 0x0089CA74, "spiderman_td_set_alternating_wall_run_occurrence_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA6C, 0x0089CA6C, "spiderman_td_set_alternating_wall_run_time_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA34, 0x0089CA34, "spiderman_td_set_big_air_height_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA4C, 0x0089CA4C, "spiderman_td_set_continuous_air_swings_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA54, 0x0089CA54, "spiderman_td_set_gain_altitude_height_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA84, 0x0089CA84, "spiderman_td_set_near_miss_trigger_radius(num)");

            CREATE_GLOBAL_SLF(stru_89CA8C, 0x0089CA8C, "spiderman_td_set_near_miss_velocity_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA3C, 0x0089CA3C, "spiderman_td_set_orbit_min_radius_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA5C, 0x0089CA5C, "spiderman_td_set_soft_landing_velocity_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA7C, 0x0089CA7C, "spiderman_td_set_super_speed_speed_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA64, 0x0089CA64, "spiderman_td_set_swinging_wall_run_time_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA44, 0x0089CA44, "spiderman_td_set_wall_sprint_time_threshold(num)");

            CREATE_GLOBAL_SLF(stru_89CA2C, 0x0089CA2C, "spiderman_unlock_spider_reflexes()");

            CREATE_GLOBAL_SLF(stru_89CB4C, 0x0089CB4C, "spiderman_wait_add_threat(entity,str,num,num)");

            CREATE_GLOBAL_SLF(stru_89C92C, 0x0089C92C, "spidey_can_see(vector3d)");

            CREATE_GLOBAL_SLF(stru_89A914, 0x0089A914, "sqrt(num)");

            CREATE_GLOBAL_SLF(stru_89C4F4, 0x0089C4F4, "start_patrol(str)");

            CREATE_GLOBAL_SLF(stru_89B514, 0x0089B514, "stop_all_sounds()");

            CREATE_GLOBAL_SLF(stru_89BB00, 0x0089BB00, "stop_credits()");

            CREATE_GLOBAL_SLF(stru_89A7CC, 0x0089A7CC, "stop_vibration()");

            CREATE_GLOBAL_SLF(stru_89BCC4, 0x0089BCC4, "subtitle(num,num,num,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89C4D4, 0x0089C4D4, "swap_hero_costume(str)");

            CREATE_GLOBAL_SLF(stru_89A7AC, 0x0089A7AC, "text_width(str)");

            CREATE_GLOBAL_SLF(stru_89BB70, 0x0089BB70, "timer_widget_get_count_up()");

            CREATE_GLOBAL_SLF(stru_89BB60, 0x0089BB60, "timer_widget_get_time()");

            CREATE_GLOBAL_SLF(stru_89BB68, 0x0089BB68, "timer_widget_set_count_up(num)");

            CREATE_GLOBAL_SLF(stru_89BB58, 0x0089BB58, "timer_widget_set_time(num)");

            CREATE_GLOBAL_SLF(stru_89BB48, 0x0089BB48, "timer_widget_start()");

            CREATE_GLOBAL_SLF(stru_89BB50, 0x0089BB50, "timer_widget_stop()");

            CREATE_GLOBAL_SLF(stru_89BB40, 0x0089BB40, "timer_widget_turn_off()");

            CREATE_GLOBAL_SLF(stru_89BB38, 0x0089BB38, "timer_widget_turn_on()");

            CREATE_GLOBAL_SLF(stru_89ABBC, 0x0089ABBC, "to_beam(entity)");

            CREATE_GLOBAL_SLF(stru_89B5A0, 0x0089B5A0, "to_gun(entity)");

            CREATE_GLOBAL_SLF(stru_89B6BC, 0x0089B6BC, "to_item(entity)");

            CREATE_GLOBAL_SLF(stru_89C238, 0x0089C238, "to_polytube(entity)");

            CREATE_GLOBAL_SLF(stru_89B8E4, 0x0089B8E4, "to_switch(entity)");

            CREATE_GLOBAL_SLF(stru_89AA14, 0x0089AA14, "trace(str)");

            CREATE_GLOBAL_SLF(stru_89B9B8, 0x0089B9B8, "trigger_is_valid(trigger)");

            CREATE_GLOBAL_SLF(stru_89BBD0, 0x0089BBD0, "turn_off_boss_health()");

            CREATE_GLOBAL_SLF(stru_89BBD8, 0x0089BBD8, "turn_off_hero_health()");

            CREATE_GLOBAL_SLF(stru_89BC20, 0x0089BC20, "turn_off_mission_text()");

            CREATE_GLOBAL_SLF(stru_89BBE0, 0x0089BBE0, "turn_off_third_party_health()");

            CREATE_GLOBAL_SLF(stru_89BBB8, 0x0089BBB8, "turn_on_boss_health(num,entity)");

            CREATE_GLOBAL_SLF(stru_89BBC0, 0x0089BBC0, "turn_on_hero_health(num,entity)");

            CREATE_GLOBAL_SLF(stru_89BBC8, 0x0089BBC8, "turn_on_third_party_health(num,entity)");

            CREATE_GLOBAL_SLF(stru_89C35C, 0x0089C35C, "unload_script()");

            CREATE_GLOBAL_SLF(stru_89C4CC, 0x0089C4CC, "unlock_all_exterior_districts()");

            CREATE_GLOBAL_SLF(stru_89C48C, 0x0089C48C, "unlock_district(num)");

            CREATE_GLOBAL_SLF(stru_89A7C4, 0x0089A7C4, "vibrate_controller(num)");

            CREATE_GLOBAL_SLF(stru_89A7BC, 0x0089A7BC, "vibrate_controller(num,num)");

            CREATE_GLOBAL_SLF(stru_89A7B4, 0x0089A7B4, "vibrate_controller(num,num,num,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A734, 0x0089A734, "vo_delay(num,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A6FC, 0x0089A6FC, "wait_animate_fog_color(vector3d,num)");

            CREATE_GLOBAL_SLF(stru_89A704, 0x0089A704, "wait_animate_fog_distance(num,num)");

            CREATE_GLOBAL_SLF(stru_89A70C, 0x0089A70C, "wait_animate_fog_distances(num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A66C, 0x0089A66C, "wait_change_blur(num,vector3d,num,num,num,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89A6A4, 0x0089A6A4, "wait_change_spider_reflexes_blur(num,vector3d,num,num,num,num,num,num)");

            CREATE_GLOBAL_SLF(stru_89C4A4, 0x0089C4A4, "wait_for_streamer_to_reach_equilibrium()");

            CREATE_GLOBAL_SLF(stru_89A8EC, 0x0089A8EC, "wait_fps_test(num,num,vector3d,vector3d)");

            CREATE_GLOBAL_SLF(stru_89A714, 0x0089A714, "wait_frame()");

            CREATE_GLOBAL_SLF(stru_89A8A4, 0x0089A8A4, "wait_set_global_time_dilation(num,num)");

            CREATE_GLOBAL_SLF(stru_89A634, 0x0089A634, "wait_set_zoom(num,num)");

            CREATE_GLOBAL_SLF(stru_89A844, 0x0089A844, "write_to_file(str,str)");
#undef KLASS
#undef SLC_VAR

#define KLASS anim
#define SLC_VAR local_20
            CREATE_SLF(stru_89AAE8, 0x0089AAE8, "kill_anim()");

            CREATE_SLF(stru_89AAB8, 0x0089AAB8, "pause()");

            CREATE_SLF(stru_89AAD8, 0x0089AAD8, "play()");

            CREATE_SLF(stru_89AAC8, 0x0089AAC8, "set_fade_time(num)");

            CREATE_SLF(stru_89AAD0, 0x0089AAD0, "set_time(num)");

            CREATE_SLF(stru_89AAC0, 0x0089AAC0, "set_timescale(num)");

            CREATE_SLF(stru_89AAE0, 0x0089AAE0, "wait_finished()");
#undef KLASS
#undef SLC_VAR

#define KLASS beam
#define SLC_VAR local_18
            CREATE_SLF(stru_89AB9C, 0x0089AB9C, "add_alpha_effect(num,num,num,num,num,num)");

            CREATE_SLF(stru_89AB8C, 0x0089AB8C, "add_color_effect(num,num,num,num,num,num,num,num,num,num)");

            CREATE_SLF(stru_89AB94, 0x0089AB94, "add_width_effect(num,num,num,num,num,num)");

            CREATE_SLF(stru_89AB1C, 0x0089AB1C, "get_impact_normal()");

            CREATE_SLF(stru_89AB14, 0x0089AB14, "get_impact_point()");

            CREATE_SLF(stru_89AB0C, 0x0089AB0C, "hit_hero()");

            CREATE_SLF(stru_89AB04, 0x0089AB04, "hit_world()");

            CREATE_SLF(stru_89ABAC, 0x0089ABAC, "kill_all_effects(num)");

            CREATE_SLF(stru_89ABA4, 0x0089ABA4, "kill_effect(num,num)");

            CREATE_SLF(stru_89AB64, 0x0089AB64, "set_additive(num)");

            CREATE_SLF(stru_89AB54, 0x0089AB54, "set_collide_beamable(num)");

            CREATE_SLF(stru_89AB44, 0x0089AB44, "set_collide_hero(num)");

            CREATE_SLF(stru_89AB4C, 0x0089AB4C, "set_collide_world(num)");

            CREATE_SLF(stru_89AB34, 0x0089AB34, "set_color(num,num,num,num)");

            CREATE_SLF(stru_89AB3C, 0x0089AB3C, "set_detect_stealth(num)");

            CREATE_SLF(stru_89AB84, 0x0089AB84, "set_material(str)");

            CREATE_SLF(stru_89AB2C, 0x0089AB2C, "set_max_length(num)");

            CREATE_SLF(stru_89AB5C, 0x0089AB5C, "set_no_collision()");

            CREATE_SLF(stru_89AB6C, 0x0089AB6C, "set_point_to_point(vector3d,vector3d)");

            CREATE_SLF(stru_89AB24, 0x0089AB24, "set_thickness(num)");

            CREATE_SLF(stru_89AB7C, 0x0089AB7C, "set_tiles_per_meter(num)");

            CREATE_SLF(stru_89AB74, 0x0089AB74, "set_uv_anim(num,num)");
#undef KLASS
#undef SLC_VAR

#define KLASS critical_section
#define SLC_VAR local_a4

            CREATE_SLF(stru_89C7E8, 0x0089C7E8, "critical_section(num)");

#undef KLASS
#undef SLC_VAR

#define KLASS cut_scene
#define SLC_VAR local_2c
            CREATE_SLF(stru_89B7D8, 0x0089B7D8, "wait_play()");

            CREATE_SLF(stru_89B7E0, 0x0089B7E0, "wait_play(entity_list)");
#undef KLASS
#undef SLC_VAR

#define KLASS debug_menu_entry
#define SLC_VAR puVar3
            CREATE_SLF(stru_89C744, 0x0089C744, "get_handler()");

            CREATE_SLF(stru_89C734, 0x0089C734, "get_id()");

            CREATE_SLF(stru_89C784, 0x0089C784, "get_max_value()");

            CREATE_SLF(stru_89C774, 0x0089C774, "get_min_value()");

            CREATE_SLF(stru_89C724, 0x0089C724, "get_name()");

            CREATE_SLF(stru_89C7A4, 0x0089C7A4, "get_step_scale()");

            CREATE_SLF(stru_89C794, 0x0089C794, "get_step_size()");

            CREATE_SLF(stru_89C754, 0x0089C754, "get_value()");

            CREATE_SLF(stru_89C764, 0x0089C764, "get_value_type()");

            CREATE_SLF(stru_89C74C, 0x0089C74C, "set_handler(str)");

            CREATE_SLF(stru_89C73C, 0x0089C73C, "set_id(num)");

            CREATE_SLF(stru_89C78C, 0x0089C78C, "set_max_value(num)");

            CREATE_SLF(stru_89C77C, 0x0089C77C, "set_min_value(num)");

            CREATE_SLF(stru_89C72C, 0x0089C72C, "set_name(str)");

            CREATE_SLF(stru_89C7AC, 0x0089C7AC, "set_step_scale(num)");

            CREATE_SLF(stru_89C79C, 0x0089C79C, "set_step_size(num)");

            CREATE_SLF(stru_89C75C, 0x0089C75C, "set_value(num)");

            CREATE_SLF(stru_89C76C, 0x0089C76C, "set_value_type(num)");
#undef KLASS
#undef SLC_VAR

#define KLASS district
#define SLC_VAR local_a0
            CREATE_SLF(stru_89C838, 0x0089C838, "contains_point(vector3d)");

            CREATE_SLF(stru_89C7F0, 0x0089C7F0, "district(num)");

            CREATE_SLF(stru_89C7F8, 0x0089C7F8, "district(str)");

            CREATE_SLF(stru_89C818, 0x0089C818, "get_id()");

            CREATE_SLF(stru_89C850, 0x0089C850, "get_name()");

            CREATE_SLF(stru_89C868, 0x0089C868, "get_neighborhood()");

            CREATE_SLF(stru_89C860, 0x0089C860, "get_num_missions(str)");

            CREATE_SLF(stru_89C840, 0x0089C840, "get_variant()");

            CREATE_SLF(stru_89C848, 0x0089C848, "get_variant_count()");

            CREATE_SLF(stru_89C870, 0x0089C870, "is_in_neighborhood(num)");

            CREATE_SLF(stru_89C820, 0x0089C820, "is_loaded()");

            CREATE_SLF(stru_89C828, 0x0089C828, "is_locked()");

            CREATE_SLF(stru_89C800, 0x0089C800, "lock()");

            CREATE_SLF(stru_89C810, 0x0089C810, "purge()");

            CREATE_SLF(stru_89C858, 0x0089C858, "set_variant(num)");

            CREATE_SLF(stru_89C808, 0x0089C808, "unlock()");

            CREATE_SLF(stru_89C830, 0x0089C830, "wait_for_load()");
#undef KLASS
#undef SLC_VAR

#define KLASS entity
#define SLC_VAR local_94
            CREATE_SLF(stru_89AE34, 0x0089AE34, "abs_snap_to(entity)");

            CREATE_SLF(stru_89AF94, 0x0089AF94, "add_collision_ignorance(entity)");

            CREATE_SLF(stru_89B5C4, 0x0089B5C4, "add_exclusive_interactor(string_hash,interactable_interface)");

            CREATE_SLF(stru_89AF44, 0x0089AF44, "add_item(entity)");

            CREATE_SLF(stru_89B17C, 0x0089B17C, "add_selectable_target(entity)");

            CREATE_SLF(stru_89B474, 0x0089B474, "add_vehicle_to_traffic_system(num)");

            CREATE_SLF(stru_89B3F4, 0x0089B3F4, "ai_get_viseme_morph_set(str,str)");

            CREATE_SLF(stru_89B3EC, 0x0089B3EC, "ai_get_viseme_stream(str)");

            CREATE_SLF(stru_89B40C, 0x0089B40C, "ai_is_speaking()");

            CREATE_SLF(stru_89B3E4, 0x0089B3E4, "ai_run_lip_sync(str)");

            CREATE_SLF(stru_89B3CC, 0x0089B3CC, "ai_say_file(str,num,num)");

            CREATE_SLF(stru_89B424, 0x0089B424, "ai_say_gab(str,num,num)");

            CREATE_SLF(stru_89B414, 0x0089B414, "ai_say_sound_group(str,num,num)");

            CREATE_SLF(stru_89B404, 0x0089B404, "ai_shut_up()");

            CREATE_SLF(stru_89B2EC, 0x0089B2EC, "ai_traffic_come_on_camera(vector3d,num)");

            CREATE_SLF(stru_89B2F4, 0x0089B2F4, "ai_traffic_come_on_camera(vector3d,vector3d,num)");

            CREATE_SLF(stru_89B2FC, 0x0089B2FC, "ai_traffic_follow_entity(entity,num)");

            CREATE_SLF(stru_89B304, 0x0089B304, "ai_traffic_follow_vehicle(entity)");

            CREATE_SLF(stru_89B2BC, 0x0089B2BC, "ai_traffic_get_value(num)");

            CREATE_SLF(stru_89B2B4, 0x0089B2B4, "ai_traffic_get_value(num,num)");

            CREATE_SLF(stru_89B2CC, 0x0089B2CC, "ai_traffic_goto(vector3d,num,num,num)");

            CREATE_SLF(stru_89B2C4, 0x0089B2C4, "ai_traffic_set_value(num,num)");

            CREATE_SLF(stru_89B2DC, 0x0089B2DC, "ai_traffic_spawn_away_from(vector3d,num)");

            CREATE_SLF(stru_89B2E4, 0x0089B2E4, "ai_traffic_spawn_behind(entity)");

            CREATE_SLF(stru_89B2D4, 0x0089B2D4, "ai_traffic_spawn_near(vector3d)");

            CREATE_SLF(stru_89B3C4, 0x0089B3C4, "ai_voice_box_set_team_respect(string_hash,num)");

            CREATE_SLF(stru_89B3D4, 0x0089B3D4, "ai_wait_say_file(str,num,num)");

            CREATE_SLF(stru_89B42C, 0x0089B42C, "ai_wait_say_gab(str,num,num)");

            CREATE_SLF(stru_89B3DC, 0x0089B3DC, "ai_wait_say_preregistered_file(str,num,num)");

            CREATE_SLF(stru_89B41C, 0x0089B41C, "ai_wait_say_sound_group(str,num,num)");

            CREATE_SLF(stru_89AEC4, 0x0089AEC4, "anim_finished()");

            CREATE_SLF(stru_89AECC, 0x0089AECC, "anim_finished(num)");

            CREATE_SLF(stru_89ACA4, 0x0089ACA4, "apply_continuous_rotation(vector3d,num,num)");

            CREATE_SLF(stru_89ADBC, 0x0089ADBC, "apply_damage(num)");

            CREATE_SLF(stru_89ADD4, 0x0089ADD4, "apply_directed_damage(num,vector3d)");

            CREATE_SLF(stru_89ADDC, 0x0089ADDC, "apply_directed_damage_cat(num,vector3d,str,num)");

            CREATE_SLF(stru_89ADE4, 0x0089ADE4, "apply_explosive_damage(num,vector3d)");

            CREATE_SLF(stru_89ADEC, 0x0089ADEC, "apply_explosive_damage(num,vector3d,vector3d)");

            CREATE_SLF(stru_89ADC4, 0x0089ADC4, "apply_subdue(num)");

            CREATE_SLF(stru_89AE44, 0x0089AE44, "camera_get_target()");

            CREATE_SLF(stru_89AE74, 0x0089AE74, "camera_orbit(vector3d,num,num,num)");

            CREATE_SLF(stru_89AE5C, 0x0089AE5C, "camera_set_collide_with_world(num)");

            CREATE_SLF(stru_89AE4C, 0x0089AE4C, "camera_set_roll(num)");

            CREATE_SLF(stru_89AE3C, 0x0089AE3C, "camera_set_target(vector3d)");

            CREATE_SLF(stru_89AE64, 0x0089AE64, "camera_slide_to(vector3d,vector3d,num,num)");

            CREATE_SLF(stru_89AE6C, 0x0089AE6C, "camera_slide_to_orbit(vector3d,num,num,num,num)");

            CREATE_SLF(stru_89B1D4, 0x0089B1D4, "cancel_tether()");

            CREATE_SLF(stru_89B1C4, 0x0089B1C4, "car_random_body_and_color()");

            CREATE_SLF(stru_89B144, 0x0089B144, "change_ai_base_machine(str)");

            CREATE_SLF(stru_89B43C, 0x0089B43C, "collisions_enabled()");

            CREATE_SLF(stru_89ABE4, 0x0089ABE4, "compute_sector()");

            CREATE_SLF(stru_89B34C, 0x0089B34C, "create_damage_interface()");

            CREATE_SLF(stru_89B5B4, 0x0089B5B4, "create_interactable_ifc()");

            CREATE_SLF(stru_89B344, 0x0089B344, "create_physical_interface()");

            CREATE_SLF(stru_89B334, 0x0089B334, "create_script_data_interface()");

            CREATE_SLF(stru_89B534, 0x0089B534, "create_web_ifc(str,num,num)");

            CREATE_SLF(stru_89B14C, 0x0089B14C, "disable_as_target()");

            CREATE_SLF(stru_89AF84, 0x0089AF84, "disable_collisions()");

            CREATE_SLF(stru_89ADB4, 0x0089ADB4, "disable_fading()");

            CREATE_SLF(stru_89AF74, 0x0089AF74, "disgorge_items()");

            CREATE_SLF(stru_89B154, 0x0089B154, "enable_as_target()");

            CREATE_SLF(stru_89AF8C, 0x0089AF8C, "enable_collisions()");

            CREATE_SLF(stru_89B434, 0x0089B434, "enable_collisions(num)");

            CREATE_SLF(stru_89B054, 0x0089B054, "eye_check_ent(entity)");

            CREATE_SLF(stru_89B04C, 0x0089B04C, "eye_check_pos(vector3d)");

            CREATE_SLF(stru_89B62C, 0x0089B62C, "force_activate_interaction(string_hash,interactable_interface)");

            CREATE_SLF(stru_89AD24, 0x0089AD24, "force_current_region()");

            CREATE_SLF(stru_89AD1C, 0x0089AD1C, "force_region(entity)");

            CREATE_SLF(stru_89ABCC, 0x0089ABCC, "get_abs_position()");

            CREATE_SLF(stru_89B16C, 0x0089B16C, "get_ai_base_machine_name()");

            CREATE_SLF(stru_89B074, 0x0089B074, "get_ai_param_float(str)");

            CREATE_SLF(stru_89B08C, 0x0089B08C, "get_ai_param_hash(str)");

            CREATE_SLF(stru_89B07C, 0x0089B07C, "get_ai_param_int(str)");

            CREATE_SLF(stru_89B084, 0x0089B084, "get_ai_param_str(str)");

            CREATE_SLF(stru_89B094, 0x0089B094, "get_ai_param_vector3d(str)");

            CREATE_SLF(stru_89AF6C, 0x0089AF6C, "get_ai_signaller()");

            CREATE_SLF(stru_89AC1C, 0x0089AC1C, "get_anchor_point()");

            CREATE_SLF(stru_89B19C, 0x0089B19C, "get_carry_slave()");

            CREATE_SLF(stru_89B044, 0x0089B044, "get_current_animation_name()");

            CREATE_SLF(stru_89ABD4, 0x0089ABD4, "get_damage_force()");

            CREATE_SLF(stru_89B444, 0x0089B444, "get_debug_name()");

            CREATE_SLF(stru_89ABDC, 0x0089ABDC, "get_detonate_position()");

            CREATE_SLF(stru_89B024, 0x0089B024, "get_district()");

            CREATE_SLF(stru_89ABEC, 0x0089ABEC, "get_facing()");

            CREATE_SLF(stru_89B1AC, 0x0089B1AC, "get_fade_timer()");

            CREATE_SLF(stru_89AC4C, 0x0089AC4C, "get_first_child()");

            CREATE_SLF(stru_89B44C, 0x0089B44C, "get_hash_name()");

            CREATE_SLF(stru_89AC2C, 0x0089AC2C, "get_hidey_pos(vector3d,num)");

            CREATE_SLF(stru_89B284, 0x0089B284, "get_ifc_num(str)");

            CREATE_SLF(stru_89B2A4, 0x0089B2A4, "get_ifc_str(str)");

            CREATE_SLF(stru_89B294, 0x0089B294, "get_ifc_vec(str)");

            CREATE_SLF(stru_89B03C, 0x0089B03C, "get_ifl_frame()");

            CREATE_SLF(stru_89B0DC, 0x0089B0DC, "get_inode_param_float(str,str)");

            CREATE_SLF(stru_89B0F4, 0x0089B0F4, "get_inode_param_hash(str,str)");

            CREATE_SLF(stru_89B0E4, 0x0089B0E4, "get_inode_param_int(str,str)");

            CREATE_SLF(stru_89B0EC, 0x0089B0EC, "get_inode_param_str(str,str)");

            CREATE_SLF(stru_89B0FC, 0x0089B0FC, "get_inode_param_vector3d(str,str)");

            CREATE_SLF(stru_89B5BC, 0x0089B5BC, "get_interactable_ifc()");

            CREATE_SLF(stru_89AF54, 0x0089AF54, "get_item(num)");

            CREATE_SLF(stru_89AF5C, 0x0089AF5C, "get_item_by_name(str)");

            CREATE_SLF(stru_89AF64, 0x0089AF64, "get_item_quantity(num)");

            CREATE_SLF(stru_89AC0C, 0x0089AC0C, "get_last_anchor()");

            CREATE_SLF(stru_89AC14, 0x0089AC14, "get_last_attacker()");

            CREATE_SLF(stru_89B20C, 0x0089B20C, "get_last_item_used()");

            CREATE_SLF(stru_89AE8C, 0x0089AE8C, "get_member(str)");

            CREATE_SLF(stru_89AC54, 0x0089AC54, "get_next_sibling()");

            CREATE_SLF(stru_89AF4C, 0x0089AF4C, "get_num_items()");

            CREATE_SLF(stru_89AC44, 0x0089AC44, "get_parent()");

            CREATE_SLF(stru_89B3B4, 0x0089B3B4, "get_pendulum_length()");

            CREATE_SLF(stru_89AC24, 0x0089AC24, "get_rel_position()");

            CREATE_SLF(stru_89AD04, 0x0089AD04, "get_rel_velocity(entity)");

            CREATE_SLF(stru_89B254, 0x0089B254, "get_render_alpha()");

            CREATE_SLF(stru_89B24C, 0x0089B24C, "get_render_color()");

            CREATE_SLF(stru_89B194, 0x0089B194, "get_scripted_target()");

            CREATE_SLF(stru_89AD14, 0x0089AD14, "get_sector_name()");

            CREATE_SLF(stru_89B56C, 0x0089B56C, "get_state(num)");

            CREATE_SLF(stru_89B314, 0x0089B314, "get_time_dilation()");

            CREATE_SLF(stru_89B324, 0x0089B324, "get_time_mode()");

            CREATE_SLF(stru_89ABF4, 0x0089ABF4, "get_x_facing()");

            CREATE_SLF(stru_89ABFC, 0x0089ABFC, "get_y_facing()");

            CREATE_SLF(stru_89AC04, 0x0089AC04, "get_z_facing()");

            CREATE_SLF(stru_89B1A4, 0x0089B1A4, "has_carry_slave()");

            CREATE_SLF(stru_89AE94, 0x0089AE94, "has_member(str)");

            CREATE_SLF(stru_89B33C, 0x0089B33C, "has_script_data_interface()");

            CREATE_SLF(stru_89B51C, 0x0089B51C, "hates(entity)");

            CREATE_SLF(stru_89B004, 0x0089B004, "ifl_damage_lock(num)");

            CREATE_SLF(stru_89B00C, 0x0089B00C, "ifl_lock(num)");

            CREATE_SLF(stru_89B014, 0x0089B014, "ifl_pause()");

            CREATE_SLF(stru_89B01C, 0x0089B01C, "ifl_play()");

            CREATE_SLF(stru_89AD0C, 0x0089AD0C, "in_sector(vector3d,vector3d,num)");

            CREATE_SLF(stru_89B174, 0x0089B174, "inhibit_universal_soldier_ability(str,num)");

            CREATE_SLF(stru_89B3FC, 0x0089B3FC, "invoke_facial_expression(num,num,num,num)");

            CREATE_SLF(stru_89AD5C, 0x0089AD5C, "is_a_car()");

            CREATE_SLF(stru_89AE1C, 0x0089AE1C, "is_picked_up()");

            CREATE_SLF(stru_89B45C, 0x0089B45C, "is_suspended()");

            CREATE_SLF(stru_89AD64, 0x0089AD64, "is_throwable()");

            CREATE_SLF(stru_89B464, 0x0089B464, "is_valid()");

            CREATE_SLF(stru_89AD74, 0x0089AD74, "is_visible()");

            CREATE_SLF(stru_89AEBC, 0x0089AEBC, "kill_anim_in_slot(num)");

            CREATE_SLF(stru_89B524, 0x0089B524, "likes(entity)");

            CREATE_SLF(stru_89AC7C, 0x0089AC7C, "look_at(vector3d)");

            CREATE_SLF(stru_89ADFC, 0x0089ADFC, "motion_blur_off()");

            CREATE_SLF(stru_89ADF4, 0x0089ADF4, "motion_blur_on(num,num,num)");

            CREATE_SLF(stru_89AE14, 0x0089AE14, "motion_trail_off()");

            CREATE_SLF(stru_89AE04, 0x0089AE04, "motion_trail_on(entity,entity,vector3d,num,num,num,num)");

            CREATE_SLF(stru_89AE0C, 0x0089AE0C, "motion_trail_on(entity,str,num,num,vector3d,num,num,num,num)");

            CREATE_SLF(stru_89B52C, 0x0089B52C, "neutral(entity)");

            CREATE_SLF(stru_89AD3C, 0x0089AD3C, "operator!=(entity)");

            CREATE_SLF(stru_89AD34, 0x0089AD34, "operator==(entity)");

            CREATE_SLF(stru_89B4A4, 0x0089B4A4, "physical_ifc_add_particle(str)");

            CREATE_SLF(stru_89B354, 0x0089B354, "physical_ifc_apply_force(vector3d,num)");

            CREATE_SLF(stru_89B36C, 0x0089B36C, "physical_ifc_cancel_all_velocity()");

            CREATE_SLF(stru_89B3A4, 0x0089B3A4, "physical_ifc_clear_pendulum()");

            CREATE_SLF(stru_89B4BC, 0x0089B4BC, "physical_ifc_get_attached_particle_name()");

            CREATE_SLF(stru_89B4AC, 0x0089B4AC, "physical_ifc_get_bounce_particle_name()");

            CREATE_SLF(stru_89B374, 0x0089B374, "physical_ifc_is_biped_physics_running()");

            CREATE_SLF(stru_89B35C, 0x0089B35C, "physical_ifc_is_effectively_standing()");

            CREATE_SLF(stru_89B4CC, 0x0089B4CC, "physical_ifc_is_prop_physics_at_rest()");

            CREATE_SLF(stru_89B4D4, 0x0089B4D4, "physical_ifc_is_prop_physics_running()");

            CREATE_SLF(stru_89B364, 0x0089B364, "physical_ifc_manage_standing(num)");

            CREATE_SLF(stru_89B38C, 0x0089B38C, "physical_ifc_set_allow_biped_physics(num)");

            CREATE_SLF(stru_89B4C4, 0x0089B4C4, "physical_ifc_set_attached_particle_name(str)");

            CREATE_SLF(stru_89B4B4, 0x0089B4B4, "physical_ifc_set_bounce_particle_name(str)");

            CREATE_SLF(stru_89B39C, 0x0089B39C, "physical_ifc_set_pendulum(entity,num)");

            CREATE_SLF(stru_89B394, 0x0089B394, "physical_ifc_set_pendulum(vector3d,num)");

            CREATE_SLF(stru_89B37C, 0x0089B37C, "physical_ifc_start_biped_physics()");

            CREATE_SLF(stru_89B494, 0x0089B494, "physical_ifc_start_prop_physics(vector3d,num)");

            CREATE_SLF(stru_89B384, 0x0089B384, "physical_ifc_stop_biped_physics()");

            CREATE_SLF(stru_89B49C, 0x0089B49C, "physical_ifc_stop_prop_physics()");

            CREATE_SLF(stru_89AEA4, 0x0089AEA4, "play_anim(str)");

            CREATE_SLF(stru_89AEAC, 0x0089AEAC, "play_anim(str,num,num)");

            CREATE_SLF(stru_89B1DC, 0x0089B1DC, "poison(num,num)");

            CREATE_SLF(stru_89B164, 0x0089B164, "pop_ai_base_machine()");

            CREATE_SLF(stru_89B55C, 0x0089B55C, "pre_roll(num)");

            CREATE_SLF(stru_89B15C, 0x0089B15C, "push_ai_base_machine(str)");

            CREATE_SLF(stru_89B4DC, 0x0089B4DC, "randomize_position(vector3d,num,num,num)");

            CREATE_SLF(stru_89B1E4, 0x0089B1E4, "regenerate(num,num)");

            CREATE_SLF(stru_89AC34, 0x0089AC34, "rel_angle(vector3d)");

            CREATE_SLF(stru_89AF9C, 0x0089AF9C, "remove_collision_ignorance(entity)");

            CREATE_SLF(stru_89B5CC, 0x0089B5CC, "remove_exclusive_interactor(string_hash,interactable_interface)");

            CREATE_SLF(stru_89B184, 0x0089B184, "remove_selectable_target(entity)");

            CREATE_SLF(stru_89B47C, 0x0089B47C, "remove_vehicle_from_traffic_system()");

            CREATE_SLF(stru_89B06C, 0x0089B06C, "reset_ai()");

            CREATE_SLF(stru_89B564, 0x0089B564, "restart()");

            CREATE_SLF(stru_89ADCC, 0x0089ADCC, "seriously_kill()");

            CREATE_SLF(stru_89AC94, 0x0089AC94, "set_abs_xz_facing(vector3d)");

            CREATE_SLF(stru_89AD9C, 0x0089AD9C, "set_active(num)");

            CREATE_SLF(stru_89B09C, 0x0089B09C, "set_ai_param_float(str,num)");

            CREATE_SLF(stru_89B0A4, 0x0089B0A4, "set_ai_param_float_variance(str,num,num)");

            CREATE_SLF(stru_89B0C4, 0x0089B0C4, "set_ai_param_hash(str,num)");

            CREATE_SLF(stru_89B0BC, 0x0089B0BC, "set_ai_param_hash(str,str)");

            CREATE_SLF(stru_89B0CC, 0x0089B0CC, "set_ai_param_hash(str,string_hash)");

            CREATE_SLF(stru_89B0AC, 0x0089B0AC, "set_ai_param_int(str,num)");

            CREATE_SLF(stru_89B0B4, 0x0089B0B4, "set_ai_param_str(str,str)");

            CREATE_SLF(stru_89B0D4, 0x0089B0D4, "set_ai_param_vector3d(str,vector3d)");

            CREATE_SLF(stru_89B32C, 0x0089B32C, "set_ambient_factor(vector3d)");

            CREATE_SLF(stru_89AFA4, 0x0089AFA4, "set_anchor_activated(num)");

            CREATE_SLF(stru_89B1BC, 0x0089B1BC, "set_car_combat_info(num,num,num,num,num,num,num,num)");

            CREATE_SLF(stru_89AD84, 0x0089AD84, "set_crawlable(num)");

            CREATE_SLF(stru_89B544, 0x0089B544, "set_default_variant()");

            CREATE_SLF(stru_89ADAC, 0x0089ADAC, "set_distance_clip(num)");

            CREATE_SLF(stru_89B224, 0x0089B224, "set_entity_blur(num)");

            CREATE_SLF(stru_89AC8C, 0x0089AC8C, "set_facing(vector3d,vector3d)");

            CREATE_SLF(stru_89B1B4, 0x0089B1B4, "set_fade_timer(num)");

            CREATE_SLF(stru_89AD4C, 0x0089AD4C, "set_hires_shadow(num)");

            CREATE_SLF(stru_89B28C, 0x0089B28C, "set_ifc_num(str,num)");

            CREATE_SLF(stru_89B2AC, 0x0089B2AC, "set_ifc_str(str,str)");

            CREATE_SLF(stru_89B29C, 0x0089B29C, "set_ifc_vec(str,vector3d)");

            CREATE_SLF(stru_89B4E4, 0x0089B4E4, "set_ignore_limbo(num)");

            CREATE_SLF(stru_89B484, 0x0089B484, "set_immobile(num)");

            CREATE_SLF(stru_89B11C, 0x0089B11C, "set_inode_param_entity(str,str,entity)");

            CREATE_SLF(stru_89B104, 0x0089B104, "set_inode_param_float(str,str,num)");

            CREATE_SLF(stru_89B10C, 0x0089B10C, "set_inode_param_float_variance(str,str,num,num)");

            CREATE_SLF(stru_89B134, 0x0089B134, "set_inode_param_hash(str,str,num)");

            CREATE_SLF(stru_89B12C, 0x0089B12C, "set_inode_param_hash(str,str,str)");

            CREATE_SLF(stru_89B114, 0x0089B114, "set_inode_param_int(str,str,num)");

            CREATE_SLF(stru_89B124, 0x0089B124, "set_inode_param_str(str,str,str)");

            CREATE_SLF(stru_89B13C, 0x0089B13C, "set_inode_param_vector3d(str,str,vector3d)");

            CREATE_SLF(stru_89AD44, 0x0089AD44, "set_invulnerable(num)");

            CREATE_SLF(stru_89B48C, 0x0089B48C, "set_kill_ent_on_destroy(num)");

            CREATE_SLF(stru_89AE9C, 0x0089AE9C, "set_member_hidden(num)");

            CREATE_SLF(stru_89AC3C, 0x0089AC3C, "set_parent(entity)");

            CREATE_SLF(stru_89AC5C, 0x0089AC5C, "set_parent_rel(entity)");

            CREATE_SLF(stru_89B214, 0x0089B214, "set_path_graph(str)");

            CREATE_SLF(stru_89B21C, 0x0089B21C, "set_path_graph_start_node(num)");

            CREATE_SLF(stru_89B3BC, 0x0089B3BC, "set_pendulum_attach_limb(num)");

            CREATE_SLF(stru_89B3AC, 0x0089B3AC, "set_pendulum_length(num)");

            CREATE_SLF(stru_89ADA4, 0x0089ADA4, "set_physical(num)");

            CREATE_SLF(stru_89AC9C, 0x0089AC9C, "set_po_facing(vector3d)");

            CREATE_SLF(stru_89AC64, 0x0089AC64, "set_rel_position(vector3d)");

            CREATE_SLF(stru_89B244, 0x0089B244, "set_render_alpha(num)");

            CREATE_SLF(stru_89B23C, 0x0089B23C, "set_render_color(vector3d)");

            CREATE_SLF(stru_89B22C, 0x0089B22C, "set_render_scale(vector3d)");

            CREATE_SLF(stru_89B274, 0x0089B274, "set_scale(num)");

            CREATE_SLF(stru_89B18C, 0x0089B18C, "set_scripted_target(entity)");

            CREATE_SLF(stru_89AD94, 0x0089AD94, "set_see_thru(num)");

            CREATE_SLF(stru_89B454, 0x0089B454, "set_special_target(num)");

            CREATE_SLF(stru_89B574, 0x0089B574, "set_state(num,num)");

            CREATE_SLF(stru_89AD54, 0x0089AD54, "set_targetting(num)");

            CREATE_SLF(stru_89AD6C, 0x0089AD6C, "set_throwable(num)");

            CREATE_SLF(stru_89B30C, 0x0089B30C, "set_time_dilation(num)");

            CREATE_SLF(stru_89B31C, 0x0089B31C, "set_time_mode(num)");

            CREATE_SLF(stru_89B53C, 0x0089B53C, "set_variant(string_hash)");

            CREATE_SLF(stru_89AC74, 0x0089AC74, "set_velocity(vector3d)");

            CREATE_SLF(stru_89AD7C, 0x0089AD7C, "set_visible(num)");

            CREATE_SLF(stru_89AD8C, 0x0089AD8C, "set_visible_and_disable_fading(num)");

            CREATE_SLF(stru_89AC84, 0x0089AC84, "set_xz_facing(vector3d)");

            CREATE_SLF(stru_89B1CC, 0x0089B1CC, "setup_tether(vector3d,num)");

            CREATE_SLF(stru_89AE2C, 0x0089AE2C, "snap_to(entity)");

            CREATE_SLF(stru_89AF7C, 0x0089AF7C, "suspend()");

            CREATE_SLF(stru_89AC6C, 0x0089AC6C, "teleport_to_point(vector3d)");

            CREATE_SLF(stru_89AD2C, 0x0089AD2C, "unforce_regions()");

            CREATE_SLF(stru_89AFAC, 0x0089AFAC, "unsuspend()");

            CREATE_SLF(stru_89B1FC, 0x0089B1FC, "use_item(str)");

            CREATE_SLF(stru_89B204, 0x0089B204, "use_item_by_id(str)");

            CREATE_SLF(stru_89AE54, 0x0089AE54, "wait_camera_set_roll(num,num)");

            CREATE_SLF(stru_89AE7C, 0x0089AE7C, "wait_change_color(vector3d,vector3d,num)");

            CREATE_SLF(stru_89AE84, 0x0089AE84, "wait_change_range(num,num,num)");

            CREATE_SLF(stru_89B25C, 0x0089B25C, "wait_change_render_color(vector3d,num,num)");

            CREATE_SLF(stru_89B234, 0x0089B234, "wait_change_render_scale(vector3d,num)");

            CREATE_SLF(stru_89AFEC, 0x0089AFEC, "wait_for_not_sector(str)");

            CREATE_SLF(stru_89AFB4, 0x0089AFB4, "wait_for_pickup()");

            CREATE_SLF(stru_89AFE4, 0x0089AFE4, "wait_for_sector(str)");

            CREATE_SLF(stru_89B26C, 0x0089B26C, "wait_lookat(vector3d,num)");

            CREATE_SLF(stru_89B264, 0x0089B264, "wait_lookat2(entity,entity,vector3d,num)");

            CREATE_SLF(stru_89B1F4, 0x0089B1F4, "wait_looping_anim(str,num,num)");

            CREATE_SLF(stru_89AEB4, 0x0089AEB4, "wait_play_anim(str,num,num,num)");

            CREATE_SLF(stru_89AFBC, 0x0089AFBC, "wait_prox(entity,num)");

            CREATE_SLF(stru_89AFC4, 0x0089AFC4, "wait_prox(vector3d,num)");

            CREATE_SLF(stru_89AFCC, 0x0089AFCC, "wait_prox(vector3d,num,vector3d,num)");

            CREATE_SLF(stru_89AFDC, 0x0089AFDC, "wait_prox_maxY(vector3d,num,num)");

            CREATE_SLF(stru_89AFD4, 0x0089AFD4, "wait_prox_minY(vector3d,num,num)");

            CREATE_SLF(stru_89AFF4, 0x0089AFF4, "wait_prox_sector(vector3d,num,str)");

            CREATE_SLF(stru_89ACAC, 0x0089ACAC, "wait_rotate(vector3d,num,num)");

            CREATE_SLF(stru_89ACBC, 0x0089ACBC, "wait_rotate_WCS(vector3d,vector3d,num,num)");

            CREATE_SLF(stru_89ACCC, 0x0089ACCC, "wait_rotate_WCS_cosmetic(vector3d,vector3d,num,num)");

            CREATE_SLF(stru_89ACC4, 0x0089ACC4, "wait_rotate_WCS_with_compute_sector(vector3d,vector3d,num,num)");

            CREATE_SLF(stru_89ACB4, 0x0089ACB4, "wait_rotate_cosmetic(vector3d,num,num)");

            CREATE_SLF(stru_89B27C, 0x0089B27C, "wait_set_scale(num,num)");

            CREATE_SLF(stru_89ACD4, 0x0089ACD4, "wait_translate(vector3d,num)");

            CREATE_SLF(stru_89ACEC, 0x0089ACEC, "wait_translate_WCS(vector3d,num)");

            CREATE_SLF(stru_89ACFC, 0x0089ACFC, "wait_translate_WCS_cosmetic(vector3d,num)");

            CREATE_SLF(stru_89ACF4, 0x0089ACF4, "wait_translate_WCS_with_compute_sector(vector3d,num)");

            CREATE_SLF(stru_89ACE4, 0x0089ACE4, "wait_translate_cosmetic(vector3d,num)");

            CREATE_SLF(stru_89ACDC, 0x0089ACDC, "wait_translate_with_compute_sector(vector3d,num)");

            CREATE_SLF(stru_89AE24, 0x0089AE24, "was_occluded_last_frame()");
#undef KLASS
#undef SLC_VAR

#define KLASS entity_list
#define SLC_VAR local_30
            CREATE_SLF(stru_89BFE4, 0x0089BFE4, "add(entity)");

            CREATE_SLF(stru_89BFFC, 0x0089BFFC, "begin()");

            CREATE_SLF(stru_89C004, 0x0089C004, "end()");

            CREATE_SLF(stru_89C00C, 0x0089C00C, "get_index(num)");

            CREATE_SLF(stru_89BFEC, 0x0089BFEC, "remove(entity)");

            CREATE_SLF(stru_89BFF4, 0x0089BFF4, "remove(entity_list_iterator)");

            CREATE_SLF(stru_89C014, 0x0089C014, "set_index(num,entity)");

            CREATE_SLF(stru_89BFDC, 0x0089BFDC, "size()");
#undef KLASS
#undef SLC_VAR

#define KLASS entity_list_iterator
#define SLC_VAR local_8c
            CREATE_SLF(stru_89C03C, 0x0089C03C, "get_entity()");

            CREATE_SLF(stru_89C034, 0x0089C034, "operator!=(entity_list_iterator)");

            CREATE_SLF(stru_89C01C, 0x0089C01C, "operator++()");

            CREATE_SLF(stru_89C024, 0x0089C024, "operator--()");

            CREATE_SLF(stru_89C02C, 0x0089C02C, "operator==(entity_list_iterator)");
#undef KLASS
#undef SLC_VAR

#define KLASS entity_tracker
#define SLC_VAR local_4c
            CREATE_SLF(stru_89C55C, 0x0089C55C, "get_entity()");

            CREATE_SLF(stru_89C56C, 0x0089C56C, "get_mini_map_active()");

            CREATE_SLF(stru_89C58C, 0x0089C58C, "get_poi_active()");

            CREATE_SLF(stru_89C554, 0x0089C554, "set_entity(entity)");

            CREATE_SLF(stru_89C584, 0x0089C584, "set_health_widget_active(num)");

            CREATE_SLF(stru_89C564, 0x0089C564, "set_mini_map_active(num)");

            CREATE_SLF(stru_89C57C, 0x0089C57C, "set_poi_active(num)");

            CREATE_SLF(stru_89C574, 0x0089C574, "set_poi_icon(num)");
#undef KLASS
#undef SLC_VAR

#define KLASS glamour_cam
#define SLC_VAR local_84
            CREATE_SLF(stru_89B788, 0x0089B788, "set_angle(num,num,num,num)");

            CREATE_SLF(stru_89B7A0, 0x0089B7A0, "set_look_at_bone(str)");

            CREATE_SLF(stru_89B798, 0x0089B798, "set_position_bone(str)");

            CREATE_SLF(stru_89B790, 0x0089B790, "set_target(entity)");
#undef KLASS
#undef SLC_VAR

#define KLASS gun
#define SLC_VAR local_28
            CREATE_SLF(stru_89B588, 0x0089B588, "get_blaster_beam()");

            CREATE_SLF(stru_89B590, 0x0089B590, "get_muzzle_pos()");

            CREATE_SLF(stru_89B598, 0x0089B598, "set_target_info(entity,vector3d,vector3d)");
#undef KLASS
#undef SLC_VAR

#define KLASS interactable_interface
#define SLC_VAR local_38
            CREATE_SLF(stru_89B61C, 0x0089B61C, "add_box_trigger(string_hash,num,vector3d,vector3d)");

            CREATE_SLF(stru_89B624, 0x0089B624, "add_named_box_trigger(string_hash,str)");

            CREATE_SLF(stru_89B614, 0x0089B614, "add_point_trigger(string_hash,num,vector3d,num)");

            CREATE_SLF(stru_89B5E4, 0x0089B5E4, "create_interaction(string_hash,num)");

            CREATE_SLF(stru_89B5EC, 0x0089B5EC, "create_interaction(string_hash,num,str)");

            CREATE_SLF(stru_89B5DC, 0x0089B5DC, "disable_interaction(string_hash)");

            CREATE_SLF(stru_89B5D4, 0x0089B5D4, "enable_interaction(string_hash)");

            CREATE_SLF(stru_89B604, 0x0089B604, "nondirectional(string_hash)");

            CREATE_SLF(stru_89B5FC, 0x0089B5FC, "one_shot(string_hash)");

            CREATE_SLF(stru_89B5F4, 0x0089B5F4, "set_activation_button(string_hash,num)");

            CREATE_SLF(stru_89B60C, 0x0089B60C, "set_approach(string_hash,num)");
#undef KLASS
#undef SLC_VAR

#define KLASS item
#define SLC_VAR local_7c
            CREATE_SLF(stru_89B6A4, 0x0089B6A4, "draw()");

            CREATE_SLF(stru_89B63C, 0x0089B63C, "get_count()");

            CREATE_SLF(stru_89B674, 0x0089B674, "get_last_grenade_armed()");

            CREATE_SLF(stru_89B67C, 0x0089B67C, "get_last_grenade_detonated()");

            CREATE_SLF(stru_89B66C, 0x0089B66C, "get_last_grenade_spawned()");

            CREATE_SLF(stru_89B64C, 0x0089B64C, "get_launch_force()");

            CREATE_SLF(stru_89B65C, 0x0089B65C, "get_launch_vec()");

            CREATE_SLF(stru_89B684, 0x0089B684, "get_owner()");

            CREATE_SLF(stru_89B664, 0x0089B664, "get_visual_item()");

            CREATE_SLF(stru_89B69C, 0x0089B69C, "holster()");

            CREATE_SLF(stru_89B6E4, 0x0089B6E4, "is_a_grenade()");

            CREATE_SLF(stru_89B6DC, 0x0089B6DC, "is_a_gun()");

            CREATE_SLF(stru_89B6F4, 0x0089B6F4, "is_a_melee()");

            CREATE_SLF(stru_89B6EC, 0x0089B6EC, "is_a_rocket()");

            CREATE_SLF(stru_89B634, 0x0089B634, "set_count(num)");

            CREATE_SLF(stru_89B6CC, 0x0089B6CC, "set_damage(num)");

            CREATE_SLF(stru_89B68C, 0x0089B68C, "set_drawn_limb(str)");

            CREATE_SLF(stru_89B694, 0x0089B694, "set_holster_limb(str)");

            CREATE_SLF(stru_89B644, 0x0089B644, "set_launch_force(num)");

            CREATE_SLF(stru_89B654, 0x0089B654, "set_launch_vec(vector3d)");

            CREATE_SLF(stru_89B6AC, 0x0089B6AC, "use()");

            CREATE_SLF(stru_89B6D4, 0x0089B6D4, "yank_remove(vector3d,num)");
#undef KLASS
#undef SLC_VAR

#define KLASS line_info
#define SLC_VAR local_44
            CREATE_SLF(stru_89B718, 0x0089B718, "check_collision(num,num)");

            CREATE_SLF(stru_89B720, 0x0089B720, "clear_collision()");

            CREATE_SLF(stru_89B768, 0x0089B768, "debug_render(num)");

            CREATE_SLF(stru_89B760, 0x0089B760, "did_collide()");

            CREATE_SLF(stru_89B740, 0x0089B740, "get_end_pos()");

            CREATE_SLF(stru_89B758, 0x0089B758, "get_hit_entity()");

            CREATE_SLF(stru_89B750, 0x0089B750, "get_hit_normal()");

            CREATE_SLF(stru_89B748, 0x0089B748, "get_hit_pos()");

            CREATE_SLF(stru_89B730, 0x0089B730, "get_start_pos()");

            CREATE_SLF(stru_89B738, 0x0089B738, "set_end_pos(vector3d)");

            CREATE_SLF(stru_89B728, 0x0089B728, "set_start_pos(vector3d)");
#undef KLASS
#undef SLC_VAR

#define KLASS mission_camera_marker
#define SLC_VAR local_74
            CREATE_SLF(stru_89C41C, 0x0089C41C, "get_base_position()");

            CREATE_SLF(stru_89C424, 0x0089C424, "get_camera_position()");
#undef KLASS
#undef SLC_VAR

#define KLASS mission_camera_transform_marker
#define SLC_VAR local_1c
            CREATE_SLF(stru_89C45C, 0x0089C45C, "get_base_position()");

            CREATE_SLF(stru_89C464, 0x0089C464, "get_camera_position()");

            CREATE_SLF(stru_89C46C, 0x0089C46C, "get_forward()");

            CREATE_SLF(stru_89C474, 0x0089C474, "get_up()");
#undef KLASS
#undef SLC_VAR

#define KLASS mission_transform_marker
#define SLC_VAR local_6c
            CREATE_SLF(stru_89C43C, 0x0089C43C, "get_base_position()");

            CREATE_SLF(stru_89C444, 0x0089C444, "get_forward()");

            CREATE_SLF(stru_89C44C, 0x0089C44C, "get_up()");
#undef KLASS
#undef SLC_VAR

#define KLASS num_list
#define SLC_VAR local_3c
            CREATE_SLF(stru_89BF6C, 0x0089BF6C, "add(num)");

            CREATE_SLF(stru_89BF84, 0x0089BF84, "begin()");

            CREATE_SLF(stru_89BF8C, 0x0089BF8C, "end()");

            CREATE_SLF(stru_89BF94, 0x0089BF94, "get_index(num)");

            CREATE_SLF(stru_89BF74, 0x0089BF74, "remove(num)");

            CREATE_SLF(stru_89BF7C, 0x0089BF7C, "remove(num_list_iterator)");

            CREATE_SLF(stru_89BF9C, 0x0089BF9C, "set_index(num,num)");

            CREATE_SLF(stru_89BF64, 0x0089BF64, "size()");
#undef KLASS
#undef SLC_VAR

#define KLASS num_list_iterator
#define SLC_VAR local_64
            CREATE_SLF(stru_89BFC4, 0x0089BFC4, "get_num()");

            CREATE_SLF(stru_89BFBC, 0x0089BFBC, "operator!=(num_list_iterator)");

            CREATE_SLF(stru_89BFA4, 0x0089BFA4, "operator++()");

            CREATE_SLF(stru_89BFAC, 0x0089BFAC, "operator--()");

            CREATE_SLF(stru_89BFB4, 0x0089BFB4, "operator==(num_list_iterator)");
#undef KLASS
#undef SLC_VAR

#define KLASS pfx
#define SLC_VAR local_5c
            CREATE_SLF(stru_89C8A4, 0x0089C8A4, "get_abs_position()");

            CREATE_SLF(stru_89C884, 0x0089C884, "get_parent()");

            CREATE_SLF(stru_89C894, 0x0089C894, "get_position()");

            CREATE_SLF(stru_89C8B4, 0x0089C8B4, "get_rel_position()");

            CREATE_SLF(stru_89C8C4, 0x0089C8C4, "get_rotation()");

            CREATE_SLF(stru_89C8D4, 0x0089C8D4, "get_scale()");

            CREATE_SLF(stru_89C8E4, 0x0089C8E4, "get_state(num)");

            CREATE_SLF(stru_89C8F4, 0x0089C8F4, "get_visible()");

            CREATE_SLF(stru_89C8AC, 0x0089C8AC, "set_abs_position(vector3d)");

            CREATE_SLF(stru_89C88C, 0x0089C88C, "set_parent(entity)");

            CREATE_SLF(stru_89C89C, 0x0089C89C, "set_position(vector3d)");

            CREATE_SLF(stru_89C8BC, 0x0089C8BC, "set_rel_position(vector3d)");

            CREATE_SLF(stru_89C8CC, 0x0089C8CC, "set_rotation(vector3d)");

            CREATE_SLF(stru_89C8DC, 0x0089C8DC, "set_scale(vector3d)");

            CREATE_SLF(stru_89C8EC, 0x0089C8EC, "set_state(num,num)");

            CREATE_SLF(stru_89C8FC, 0x0089C8FC, "set_visible(num)");
#undef KLASS
#undef SLC_VAR

#define KLASS polytube
#define SLC_VAR local_24
            CREATE_SLF(stru_89C108, 0x0089C108, "add_control_pt(vector3d)");

            CREATE_SLF(stru_89C140, 0x0089C140, "build(num,num)");

            CREATE_SLF(stru_89C0F8, 0x0089C0F8, "clear()");

            CREATE_SLF(stru_89C220, 0x0089C220, "clear_simulations()");

            CREATE_SLF(stru_89C240, 0x0089C240, "create_tentacle()");

            CREATE_SLF(stru_89C248, 0x0089C248, "destroy_tentacle()");

            CREATE_SLF(stru_89C118, 0x0089C118, "get_control_pt(num)");

            CREATE_SLF(stru_89C128, 0x0089C128, "get_curve_pt(num)");

            CREATE_SLF(stru_89C1A0, 0x0089C1A0, "get_ifl_frame()");

            CREATE_SLF(stru_89C1D8, 0x0089C1D8, "get_max_length()");

            CREATE_SLF(stru_89C130, 0x0089C130, "get_num_control_pts()");

            CREATE_SLF(stru_89C138, 0x0089C138, "get_num_curve_pts()");

            CREATE_SLF(stru_89C1B8, 0x0089C1B8, "get_num_sides()");

            CREATE_SLF(stru_89C1C8, 0x0089C1C8, "get_tiles_per_meter()");

            CREATE_SLF(stru_89C1A8, 0x0089C1A8, "get_tube_radius()");

            CREATE_SLF(stru_89C190, 0x0089C190, "ifl_lock(num)");

            CREATE_SLF(stru_89C198, 0x0089C198, "ifl_play()");

            CREATE_SLF(stru_89C208, 0x0089C208, "kill_pt_anim(num,num)");

            CREATE_SLF(stru_89C148, 0x0089C148, "rebuild()");

            CREATE_SLF(stru_89C100, 0x0089C100, "reserve_control_pts(num)");

            CREATE_SLF(stru_89C120, 0x0089C120, "set_additive(num)");

            CREATE_SLF(stru_89C168, 0x0089C168, "set_begin_material(str,num)");

            CREATE_SLF(stru_89C180, 0x0089C180, "set_begin_material_ifl(str,num)");

            CREATE_SLF(stru_89C188, 0x0089C188, "set_blend_mode(num)");

            CREATE_SLF(stru_89C110, 0x0089C110, "set_control_pt(num,vector3d)");

            CREATE_SLF(stru_89C160, 0x0089C160, "set_end_material(str,num)");

            CREATE_SLF(stru_89C178, 0x0089C178, "set_end_material_ifl(str,num)");

            CREATE_SLF(stru_89C150, 0x0089C150, "set_force_start(num)");

            CREATE_SLF(stru_89C158, 0x0089C158, "set_material(str)");

            CREATE_SLF(stru_89C170, 0x0089C170, "set_material_ifl(str)");

            CREATE_SLF(stru_89C1E0, 0x0089C1E0, "set_max_length(num)");

            CREATE_SLF(stru_89C1C0, 0x0089C1C0, "set_num_sides(num)");

            CREATE_SLF(stru_89C1F8, 0x0089C1F8, "set_pt_anim(num,vector3d,num,num)");

            CREATE_SLF(stru_89C200, 0x0089C200, "set_random_pt_anim(num,num,num,num)");

            CREATE_SLF(stru_89C1F0, 0x0089C1F0, "set_start_v(num)");

            CREATE_SLF(stru_89C1D0, 0x0089C1D0, "set_tiles_per_meter(num)");

            CREATE_SLF(stru_89C1B0, 0x0089C1B0, "set_tube_radius(num)");

            CREATE_SLF(stru_89C210, 0x0089C210, "simulate_slack(vector3d,vector3d,num)");

            CREATE_SLF(stru_89C218, 0x0089C218, "simulate_tether(entity,entity,num)");

            CREATE_SLF(stru_89C2A8, 0x0089C2A8, "tentacle_add_dangle_engine(num,num)");

            CREATE_SLF(stru_89C2B0, 0x0089C2B0, "tentacle_add_follow_engine(num,num,vector3d,num)");

            CREATE_SLF(stru_89C2B8, 0x0089C2B8, "tentacle_add_slack_engine(num,num)");

            CREATE_SLF(stru_89C298, 0x0089C298, "tentacle_add_strike_engine(vector3d,num,num)");

            CREATE_SLF(stru_89C2A0, 0x0089C2A0, "tentacle_add_swirl_strike_engine(vector3d,num,num,num,num)");

            CREATE_SLF(stru_89C280, 0x0089C280, "tentacle_create_line(vector3d,num)");

            CREATE_SLF(stru_89C290, 0x0089C290, "tentacle_engine_running(num)");

            CREATE_SLF(stru_89C260, 0x0089C260, "tentacle_get_end_position()");

            CREATE_SLF(stru_89C2F0, 0x0089C2F0, "tentacle_get_engine_drag(num)");

            CREATE_SLF(stru_89C300, 0x0089C300, "tentacle_get_engine_gravity(num)");

            CREATE_SLF(stru_89C2D0, 0x0089C2D0, "tentacle_get_engine_length(num)");

            CREATE_SLF(stru_89C2E0, 0x0089C2E0, "tentacle_get_engine_slack_percent(num)");

            CREATE_SLF(stru_89C268, 0x0089C268, "tentacle_get_num_positions()");

            CREATE_SLF(stru_89C278, 0x0089C278, "tentacle_get_position(num)");

            CREATE_SLF(stru_89C288, 0x0089C288, "tentacle_kill_engine(num)");

            CREATE_SLF(stru_89C250, 0x0089C250, "tentacle_set_collide(num)");

            CREATE_SLF(stru_89C258, 0x0089C258, "tentacle_set_end_position(vector3d)");

            CREATE_SLF(stru_89C2C0, 0x0089C2C0, "tentacle_set_engine_attach_ent(num,entity)");

            CREATE_SLF(stru_89C2F8, 0x0089C2F8, "tentacle_set_engine_drag(num,num)");

            CREATE_SLF(stru_89C308, 0x0089C308, "tentacle_set_engine_gravity(num,vector3d)");

            CREATE_SLF(stru_89C2D8, 0x0089C2D8, "tentacle_set_engine_length(num,num)");

            CREATE_SLF(stru_89C2E8, 0x0089C2E8, "tentacle_set_engine_slack_percent(num,num)");

            CREATE_SLF(stru_89C2C8, 0x0089C2C8, "tentacle_set_engine_target(num,vector3d)");

            CREATE_SLF(stru_89C270, 0x0089C270, "tentacle_set_position(num,vector3d)");

            CREATE_SLF(stru_89C1E8, 0x0089C1E8, "v_animate(num)");
#undef KLASS
#undef SLC_VAR

#define KLASS posfacing3d
#define SLC_VAR local_34
            CREATE_SLF(stru_89BA98, 0x0089BA98, "get_facing()");

            CREATE_SLF(stru_89BAA8, 0x0089BAA8, "get_position()");

            CREATE_SLF(stru_89BAA0, 0x0089BAA0, "get_rotation()");

            CREATE_SLF(stru_89BAB8, 0x0089BAB8, "operator!=(posfacing3d)");

            CREATE_SLF(stru_89BA88, 0x0089BA88, "operator+(posfacing3d)");

            CREATE_SLF(stru_89BA90, 0x0089BA90, "operator-(posfacing3d)");

            CREATE_SLF(stru_89BAB0, 0x0089BAB0, "operator==(posfacing3d)");

            CREATE_SLF(stru_89BA68, 0x0089BA68, "posfacing3d(num,num,num,num)");

            CREATE_SLF(stru_89BA78, 0x0089BA78, "posfacing3d(num,num,num,vector3d)");

            CREATE_SLF(stru_89BA70, 0x0089BA70, "posfacing3d(vector3d,num)");

            CREATE_SLF(stru_89BA80, 0x0089BA80, "posfacing3d(vector3d,vector3d)");
#undef KLASS
#undef SLC_VAR

#define KLASS position3d
#define SLC_VAR local_9c
            CREATE_SLF(stru_89BA60, 0x0089BA60, "operator=(vector3d)");

            CREATE_SLF(stru_89BA58, 0x0089BA58, "position3d(num,num,num)");
#undef KLASS
#undef SLC_VAR

#define KLASS script_controller
#define SLC_VAR local_54
            CREATE_SLF(stru_89BCD8, 0x0089BCD8, "is_button_pressed(num)");

            CREATE_SLF(stru_89BCE8, 0x0089BCE8, "is_down_pressed()");

            CREATE_SLF(stru_89BCF0, 0x0089BCF0, "is_left_pressed()");

            CREATE_SLF(stru_89BD28, 0x0089BD28, "is_lstick_down_pressed()");

            CREATE_SLF(stru_89BD30, 0x0089BD30, "is_lstick_left_pressed()");

            CREATE_SLF(stru_89BD38, 0x0089BD38, "is_lstick_right_pressed()");

            CREATE_SLF(stru_89BD20, 0x0089BD20, "is_lstick_up_pressed()");

            CREATE_SLF(stru_89BCF8, 0x0089BCF8, "is_right_pressed()");

            CREATE_SLF(stru_89BD08, 0x0089BD08, "is_rstick_down_pressed()");

            CREATE_SLF(stru_89BD10, 0x0089BD10, "is_rstick_left_pressed()");

            CREATE_SLF(stru_89BD18, 0x0089BD18, "is_rstick_right_pressed()");

            CREATE_SLF(stru_89BD00, 0x0089BD00, "is_rstick_up_pressed()");

            CREATE_SLF(stru_89BCE0, 0x0089BCE0, "is_up_pressed()");
#undef KLASS
#undef SLC_VAR

#define KLASS signaller
#define SLC_VAR local_98
            CREATE_SLF(stru_89B7F0, 0x0089B7F0, "clear_callback(str)");

            CREATE_SLF(stru_89B7E8, 0x0089B7E8, "clear_callbacks()");
#undef KLASS
#undef SLC_VAR

#define KLASS sound_inst
#define SLC_VAR local_90
            CREATE_SLF(stru_89B880, 0x0089B880, "dampen_guard()");

            CREATE_SLF(stru_89B898, 0x0089B898, "fade_in(num,num)");

            CREATE_SLF(stru_89B8A0, 0x0089B8A0, "fade_out(num)");

            CREATE_SLF(stru_89B890, 0x0089B890, "fade_to(num,num)");

            CREATE_SLF(stru_89B878, 0x0089B878, "get_doppler()");

            CREATE_SLF(stru_89B848, 0x0089B848, "get_entity()");

            CREATE_SLF(stru_89B870, 0x0089B870, "get_max_distance()");

            CREATE_SLF(stru_89B868, 0x0089B868, "get_min_distance()");

            CREATE_SLF(stru_89B860, 0x0089B860, "get_pitch()");

            CREATE_SLF(stru_89B828, 0x0089B828, "get_source()");

            CREATE_SLF(stru_89B888, 0x0089B888, "get_status()");

            CREATE_SLF(stru_89B858, 0x0089B858, "get_volume()");

            CREATE_SLF(stru_89B820, 0x0089B820, "is_valid()");

            CREATE_SLF(stru_89B8B0, 0x0089B8B0, "play(num)");

            CREATE_SLF(stru_89B8B8, 0x0089B8B8, "play_3d(vector3d,num)");

            CREATE_SLF(stru_89B8A8, 0x0089B8A8, "queue(num)");

            CREATE_SLF(stru_89B850, 0x0089B850, "set_entity(entity)");

            CREATE_SLF(stru_89B830, 0x0089B830, "set_preregistered_source(str)");

            CREATE_SLF(stru_89B840, 0x0089B840, "set_sound_group(str)");

            CREATE_SLF(stru_89B838, 0x0089B838, "set_source(str)");

            CREATE_SLF(stru_89B8C8, 0x0089B8C8, "stop(num)");

            CREATE_SLF(stru_89B8C0, 0x0089B8C0, "wait(num)");
#undef KLASS
#undef SLC_VAR

#define KLASS str_list
#define SLC_VAR local_88
            CREATE_SLF(stru_89C05C, 0x0089C05C, "add(str)");

            CREATE_SLF(stru_89C074, 0x0089C074, "begin()");

            CREATE_SLF(stru_89C07C, 0x0089C07C, "end()");

            CREATE_SLF(stru_89C084, 0x0089C084, "get_index(num)");

            CREATE_SLF(stru_89C064, 0x0089C064, "remove(str)");

            CREATE_SLF(stru_89C06C, 0x0089C06C, "remove(str_list_iterator)");

            CREATE_SLF(stru_89C08C, 0x0089C08C, "set_index(num,str)");

            CREATE_SLF(stru_89C054, 0x0089C054, "size()");
#undef KLASS
#undef SLC_VAR

#define KLASS str_list_iterator
#define SLC_VAR local_80
            CREATE_SLF(stru_89C0B4, 0x0089C0B4, "get_str()");

            CREATE_SLF(stru_89C0AC, 0x0089C0AC, "operator!=(str_list_iterator)");

            CREATE_SLF(stru_89C094, 0x0089C094, "operator++()");

            CREATE_SLF(stru_89C09C, 0x0089C09C, "operator--()");

            CREATE_SLF(stru_89C0A4, 0x0089C0A4, "operator==(str_list_iterator)");
#undef KLASS
#undef SLC_VAR

#define KLASS string_hash
#define SLC_VAR local_40
            CREATE_SLF(stru_89C7D4, 0x0089C7D4, "operator==(str)");

            CREATE_SLF(stru_89C7CC, 0x0089C7CC, "operator==(string_hash)");

            CREATE_SLF(stru_89C7C4, 0x0089C7C4, "set(str)");

            CREATE_SLF(stru_89C7B4, 0x0089C7B4, "string_hash(str)");

            CREATE_SLF(stru_89C7BC, 0x0089C7BC, "to_string()");
#undef KLASS
#undef SLC_VAR

#define KLASS switch_obj
#define SLC_VAR local_78
            CREATE_SLF(stru_89B8DC, 0x0089B8DC, "get_state()");

            CREATE_SLF(stru_89B904, 0x0089B904, "set_alarm(num)");

            CREATE_SLF(stru_89B90C, 0x0089B90C, "set_single_use(num)");

            CREATE_SLF(stru_89B8F4, 0x0089B8F4, "set_state(num)");

            CREATE_SLF(stru_89B8FC, 0x0089B8FC, "set_web_targetable(num)");

            CREATE_SLF(stru_89B8EC, 0x0089B8EC, "who_pressed_me()");
#undef KLASS
#undef SLC_VAR

#define KLASS tam
#define SLC_VAR local_70
            CREATE_SLF(stru_89C6DC, 0x0089C6DC, "set_entity(entity)");

            CREATE_SLF(stru_89C6E4, 0x0089C6E4, "set_pos(vector3d)");

            CREATE_SLF(stru_89C6EC, 0x0089C6EC, "set_state(num)");

            CREATE_SLF(stru_89C6F4, 0x0089C6F4, "set_type(num)");
#undef KLASS
#undef SLC_VAR

#define KLASS taunt_entry
#define SLC_VAR local_68
            CREATE_SLF(stru_89C62C, 0x0089C62C, "get_entity()");

            CREATE_SLF(stru_89C634, 0x0089C634, "get_flags()");

            CREATE_SLF(stru_89C624, 0x0089C624, "get_taunt_name()");
#undef KLASS
#undef SLC_VAR

#define KLASS taunt_exchange
#define SLC_VAR local_60
            CREATE_SLF(stru_89C654, 0x0089C654, "get_entity_to_do_hurting()");

            CREATE_SLF(stru_89C64C, 0x0089C64C, "get_entity_to_hurt()");

            CREATE_SLF(stru_89C664, 0x0089C664, "get_last_hit_pt_value()");

            CREATE_SLF(stru_89C684, 0x0089C684, "get_max_times_to_play()");

            CREATE_SLF(stru_89C65C, 0x0089C65C, "get_min_damage()");

            CREATE_SLF(stru_89C6A4, 0x0089C6A4, "get_normalized_weight()");

            CREATE_SLF(stru_89C694, 0x0089C694, "get_taunt_entry(num)");

            CREATE_SLF(stru_89C674, 0x0089C674, "get_times_played()");

            CREATE_SLF(stru_89C68C, 0x0089C68C, "get_total_taunts()");

            CREATE_SLF(stru_89C69C, 0x0089C69C, "get_weight()");

            CREATE_SLF(stru_89C67C, 0x0089C67C, "increment_times_played()");

            CREATE_SLF(stru_89C66C, 0x0089C66C, "set_last_hit_pt_value(num)");

            CREATE_SLF(stru_89C6AC, 0x0089C6AC, "set_normalized_weight(num)");
#undef KLASS
#undef SLC_VAR

#define KLASS taunt_exchange_list
#define SLC_VAR local_58
            CREATE_SLF(stru_89C0BC, 0x0089C0BC, "add(taunt_exchange)");

            CREATE_SLF(stru_89C0D4, 0x0089C0D4, "clear()");

            CREATE_SLF(stru_89C0C4, 0x0089C0C4, "get_index(num)");

            CREATE_SLF(stru_89C0CC, 0x0089C0CC, "size()");
#undef KLASS
#undef SLC_VAR

#define KLASS trigger
#define SLC_VAR local_50
            CREATE_SLF(stru_89B938, 0x0089B938, "contains(entity)");

            CREATE_SLF(stru_89B920, 0x0089B920, "get_abs_position()");

            CREATE_SLF(stru_89B9A0, 0x0089B9A0, "get_radius()");

            CREATE_SLF(stru_89B928, 0x0089B928, "get_triggered_ent()");

            CREATE_SLF(stru_89B930, 0x0089B930, "get_triggered_entity_list()");

            CREATE_SLF(stru_89B9B0, 0x0089B9B0, "is_point_radius_trigger()");

            CREATE_SLF(stru_89B940, 0x0089B940, "set_active(num)");

            CREATE_SLF(stru_89B988, 0x0089B988, "set_multiple_entrance(num)");

            CREATE_SLF(stru_89B9A8, 0x0089B9A8, "set_position(vector3d)");

            CREATE_SLF(stru_89B998, 0x0089B998, "set_radius(num)");

            CREATE_SLF(stru_89B990, 0x0089B990, "set_sees_dead_people(num)");

            CREATE_SLF(stru_89B980, 0x0089B980, "set_use_any_char(num)");
#undef KLASS
#undef SLC_VAR

#define KLASS vector3d
#define SLC_VAR local_48
            CREATE_SLF(stru_89B9F8, 0x0089B9F8, "length()");

            CREATE_SLF(stru_89BA00, 0x0089BA00, "length2()");

            CREATE_SLF(stru_89B9F0, 0x0089B9F0, "operator!=(vector3d)");

            CREATE_SLF(stru_89B9D8, 0x0089B9D8, "operator*(num)");

            CREATE_SLF(stru_89B9C8, 0x0089B9C8, "operator+(vector3d)");

            CREATE_SLF(stru_89B9D0, 0x0089B9D0, "operator-(vector3d)");

            CREATE_SLF(stru_89B9E0, 0x0089B9E0, "operator/(num)");

            CREATE_SLF(stru_89B9E8, 0x0089B9E8, "operator==(vector3d)");

            CREATE_SLF(stru_89B9C0, 0x0089B9C0, "vector3d(num,num,num)");

            CREATE_SLF(stru_89BA18, 0x0089BA18, "x()");

            CREATE_SLF(stru_89BA08, 0x0089BA08, "xy_norm()");

            CREATE_SLF(stru_89BA10, 0x0089BA10, "xz_norm()");

            CREATE_SLF(stru_89BA20, 0x0089BA20, "y()");

            CREATE_SLF(stru_89BA28, 0x0089BA28, "z()");
#undef KLASS
#undef SLC_VAR

#define KLASS vector3d_list
#define SLC_VAR local_14
            CREATE_SLF(stru_89BEEC, 0x0089BEEC, "add(vector3d)");

            CREATE_SLF(stru_89BF04, 0x0089BF04, "begin()");

            CREATE_SLF(stru_89BF1C, 0x0089BF1C, "clear()");

            CREATE_SLF(stru_89BF0C, 0x0089BF0C, "end()");

            CREATE_SLF(stru_89BF14, 0x0089BF14, "get_index(num)");

            CREATE_SLF(stru_89BEF4, 0x0089BEF4, "remove(vector3d)");

            CREATE_SLF(stru_89BEFC, 0x0089BEFC, "remove(vector3d_list_iterator)");

            CREATE_SLF(stru_89BF24, 0x0089BF24, "set_index(num,vector3d)");

            CREATE_SLF(stru_89BEE4, 0x0089BEE4, "size()");
#undef KLASS
#undef SLC_VAR

#define KLASS vector3d_list_iterator
#define SLC_VAR local_10
            CREATE_SLF(stru_89BF4C, 0x0089BF4C, "get_vector3d()");

            CREATE_SLF(stru_89BF44, 0x0089BF44, "operator!=(vector3d_list_iterator)");

            CREATE_SLF(stru_89BF2C, 0x0089BF2C, "operator++()");

            CREATE_SLF(stru_89BF34, 0x0089BF34, "operator--()");

            CREATE_SLF(stru_89BF3C, 0x0089BF3C, "operator==(vector3d_list_iterator)");
        }

        slc_global()->add_functions_complete();

        for (auto &slc : classes) {
            slc->add_functions_complete();
        }

#undef KLASS
#undef SLC_VAR 

#undef CREATE_SLF
#undef CREATE_SLC
    } else {
        CDECL_CALL(0x0064EB60);
    }
}

void slc_manager::init()
{
    TRACE("slc_manager::init");

    if constexpr (1) {
        if (slc_manager_classes == nullptr) {
            slc_manager_classes = new std::set<script_library_class *>{};
        }

        if (slc_manager_class_array() == nullptr) {
            using slc_manager_class_array_t = std::decay_t<decltype(*slc_manager_class_array())>;
            slc_manager_class_array() = new slc_manager_class_array_t {};
        }

        register_standard_script_libs();
        chuck_register_script_libs();
        construct_client_script_libs();
    }
    else
    {
        CDECL_CALL(0x005AD720);
    }
}

void slc_manager::add(script_library_class *slc)
{
    TRACE("slc_manager::add");

    assert(slc_manager_classes != nullptr);
    auto ret = slc_manager_classes->insert(slc);
    if ( !ret.second ) {
        auto name = slc->get_name();
        sp_log("slc already exists %s", name);
        assert(0);
    }

    assert(slc_manager_class_array() != nullptr);
    slc_manager_class_array()->push_back(slc);
}

void slc_manager::kill() {
    TRACE("slc_manager::kill");

    if constexpr (1) {
        destruct_client_script_libs();
        if ( slc_manager_class_array() != nullptr ) {
            for ( auto &slc : (*slc_manager_class_array()) ) {
                if ( slc != nullptr ) {
                    delete slc;
                }
            }

            if ( slc_manager_class_array() != nullptr ) {
                delete slc_manager_class_array();
            }

            slc_manager_class_array() = nullptr;
        }
    } else {
        CDECL_CALL(0x005A5200);
    }
}

script_library_class *slc_manager::get_class(int class_index)
{
    assert(slc_manager_class_array() != nullptr);

    assert(class_index >= 0);

    assert(class_index < slc_manager_class_array()->size());

    return slc_manager_class_array()->at(class_index);
}

script_library_class *slc_manager::get(const char *a1)
{
    assert(slc_manager_classes != nullptr);

    script_library_class v9{};
    v9.store_name(a1);
    auto it = slc_manager_classes->find(&v9);
    auto end = slc_manager_classes->end();
    if ( it != end ) {
        return (*it);
    }

    return nullptr;
}

void slc_manager::un_mash_all_funcs()
{
    TRACE("slc_manager::un_mash_all_funcs");

    assert(!script_manager::using_chuck_old_fashioned());
    assert(!g_is_the_packer());

    auto a1 = create_resource_key_from_path("all_slc_functions_mac", RESOURCE_KEY_TYPE_SLF);
    sp_log("%s", a1.get_platform_string(3).c_str());

    auto *image = bit_cast<char *>(resource_manager::get_resource(a1, nullptr, nullptr));
    assert(image != nullptr);

    assert(slc_manager_class_array() != nullptr);

    auto total_classes = bit_cast<int *>(image)[0];
    auto *buffer = image + 4;

    assert(total_classes == slc_manager_class_array()->size());
    
    for ( auto &slc : (*slc_manager_class_array()) ) {
        slc->total_funcs = bit_cast<int *>(buffer)[0];
        buffer += 4;
        assert(slc->funcs == nullptr);

        if ( slc->total_funcs > 0 ) {
            slc->funcs = CAST(slc->funcs, buffer);
            buffer += 4 * slc->total_funcs;
            slc->field_1C |= 1u;
        }
    }

    if constexpr (0) {
        uint32_t i {0};
        auto total_funcs = 0u;
        for (auto &slc : (*slc_manager_class_array())) {
            printf("slc: %u %s %u\n", i++, slc->get_name(), slc->total_funcs);
            total_funcs += slc->total_funcs;
        }

        printf("total_funcs: %d", total_funcs);

        assert(0);
    }
}

void slc_manager_patch()
{
    SET_JUMP(0x005AD720, slc_manager::init);

    SET_JUMP(0x005A5200, slc_manager::kill);

    SET_JUMP(0x005A5280, slc_manager::add);

    SET_JUMP(0x0059EC00, slc_manager::un_mash_all_funcs);

    REDIRECT(0x005AD778, chuck_register_script_libs);
}
