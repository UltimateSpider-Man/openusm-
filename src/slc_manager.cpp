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

#define DECLARE_GLOBAL_SLF(TYPE, vtbl)                                              \
    struct BUILD_GLOBAL_SLF_NAME(TYPE) : script_library_class::function { \
        BUILD_GLOBAL_SLF_NAME(TYPE) (                                   \
            const char *a3) : function(a3)  {                      \
            m_vtbl = vtbl;                                              \
        }                                                               \
    };

#define DECLARE_SLF(TYPE, vtbl)                                              \
    struct BUILD_SLF_NAME(KLASS, TYPE) : script_library_class::function { \
        BUILD_SLF_NAME(KLASS, TYPE) (                                   \
            script_library_class *slc,                                  \
            const char *a3) : function(slc, a3)  {                      \
            m_vtbl = vtbl;                                              \
        }                                                               \
    };                                                                  \

#undef DECLARE_SLF
#undef DECLARE_GLOBAL_SLF

struct slf__abs_delay__num__t : script_library_class::function {
    slf__abs_delay__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A724;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__acos__num__t : script_library_class::function {
    slf__acos__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A91C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_2d_debug_str__vector3d__vector3d__num__str__t : script_library_class::function {
    slf__add_2d_debug_str__vector3d__vector3d__num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A860;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_2d_debug_str__vector3d__vector3d__num__str__num__t : script_library_class::function {
    slf__add_2d_debug_str__vector3d__vector3d__num__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A858;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_3d_debug_str__vector3d__vector3d__num__str__t : script_library_class::function {
    slf__add_3d_debug_str__vector3d__vector3d__num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A850;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_civilian_info__vector3d__num__num__num__t : script_library_class::function {
    slf__add_civilian_info__vector3d__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_civilian_info_entity__entity__num__num__num__t : script_library_class::function {
    slf__add_civilian_info_entity__entity__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_debug_cyl__vector3d__vector3d__num__t : script_library_class::function {
    slf__add_debug_cyl__vector3d__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A774;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_debug_cyl__vector3d__vector3d__num__vector3d__num__t : script_library_class::function {
    slf__add_debug_cyl__vector3d__vector3d__num__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A77C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_debug_line__vector3d__vector3d__t : script_library_class::function {
    slf__add_debug_line__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A764;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_debug_line__vector3d__vector3d__vector3d__num__t : script_library_class::function {
    slf__add_debug_line__vector3d__vector3d__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A76C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_debug_sphere__vector3d__num__t : script_library_class::function {
    slf__add_debug_sphere__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A754;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_debug_sphere__vector3d__num__vector3d__num__t : script_library_class::function {
    slf__add_debug_sphere__vector3d__num__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A75C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_glass_house__str__t : script_library_class::function {
    slf__add_glass_house__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A548;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_glass_house__str__num__t : script_library_class::function {
    slf__add_glass_house__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A550;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_glass_house__str__num__vector3d__t : script_library_class::function {
    slf__add_glass_house__str__num__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A560;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_glass_house__str__vector3d__t : script_library_class::function {
    slf__add_glass_house__str__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A558;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_to_console__str__t : script_library_class::function {
    slf__add_to_console__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A834;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__add_traffic_model__num__str__t : script_library_class::function {
    slf__add_traffic_model__num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__allow_suspend_thread__num__t : script_library_class::function {
    slf__allow_suspend_thread__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A594;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__angle_between__vector3d__vector3d__t : script_library_class::function {
    slf__angle_between__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BA50;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__apply_donut_damage__vector3d__num__num__num__num__num__t : script_library_class::function {
    slf__apply_donut_damage__vector3d__num__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A804;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__apply_radius_damage__vector3d__num__num__num__num__t : script_library_class::function {
    slf__apply_radius_damage__vector3d__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__apply_radius_subdue__vector3d__num__num__num__num__t : script_library_class::function {
    slf__apply_radius_subdue__vector3d__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A80C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__assert__num__str__t : script_library_class::function {
    slf__assert__num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A518;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__attach_decal__str__vector3d__num__vector3d__entity__t : script_library_class::function {
    slf__attach_decal__str__vector3d__num__vector3d__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A9FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__begin_screen_recording__str__num__t : script_library_class::function {
    slf__begin_screen_recording__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B7B0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__blackscreen_off__num__t : script_library_class::function {
    slf__blackscreen_off__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BCAC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__blackscreen_on__num__t : script_library_class::function {
    slf__blackscreen_on__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BCA0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__bring_up_dialog_box__num__num__t : script_library_class::function {
    slf__bring_up_dialog_box__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC28;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__bring_up_dialog_box_debug__str__num__str__t : script_library_class::function {
    slf__bring_up_dialog_box_debug__str__num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC38;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__bring_up_dialog_box_title__num__num__num__t : script_library_class::function {
    slf__bring_up_dialog_box_title__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC30;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__bring_up_medal_award_box__num__t : script_library_class::function {
    slf__bring_up_medal_award_box__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB10;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__bring_up_race_announcer__t : script_library_class::function {
    slf__bring_up_race_announcer__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB08;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__calc_launch_vector__vector3d__vector3d__num__entity__t : script_library_class::function {
    slf__calc_launch_vector__vector3d__vector3d__num__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A98C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__can_load_pack__str__t : script_library_class::function {
    slf__can_load_pack__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__chase_cam__t : script_library_class::function {
    slf__chase_cam__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AF04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_all_grenades__t : script_library_class::function {
    slf__clear_all_grenades__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A95C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_civilians_within_radius__vector3d__num__t : script_library_class::function {
    slf__clear_civilians_within_radius__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_controls__t : script_library_class::function {
    slf__clear_controls__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BD48;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_debug_all__t : script_library_class::function {
    slf__clear_debug_all__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A79C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_debug_cyls__t : script_library_class::function {
    slf__clear_debug_cyls__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A794;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_debug_lines__t : script_library_class::function {
    slf__clear_debug_lines__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A78C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_debug_spheres__t : script_library_class::function {
    slf__clear_debug_spheres__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A784;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_screen__t : script_library_class::function {
    slf__clear_screen__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A944;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__clear_traffic_within_radius__vector3d__num__t : script_library_class::function {
    slf__clear_traffic_within_radius__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__col_check__vector3d__vector3d__num__t : script_library_class::function {
    slf__col_check__vector3d__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A868;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__console_exec__str__t : script_library_class::function {
    slf__console_exec__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A83C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__copy_vector3d_list__vector3d_list__vector3d_list__t : script_library_class::function {
    slf__copy_vector3d_list__vector3d_list__vector3d_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BED4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__cos__num__t : script_library_class::function {
    slf__cos__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A90C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_beam__t : script_library_class::function {
    slf__create_beam__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089ABB4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_credits__t : script_library_class::function {
    slf__create_credits__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BAE8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_cut_scene__str__t : script_library_class::function {
    slf__create_cut_scene__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B7C0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_debug_menu_entry__str__t : script_library_class::function {
    slf__create_debug_menu_entry__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C704;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_debug_menu_entry__str__str__t : script_library_class::function {
    slf__create_debug_menu_entry__str__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C70C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_decal__str__vector3d__num__vector3d__t : script_library_class::function {
    slf__create_decal__str__vector3d__num__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A9F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_entity__str__t : script_library_class::function {
    slf__create_entity__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AF0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_entity__str__str__t : script_library_class::function {
    slf__create_entity__str__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AF14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_entity_in_hero_region__str__t : script_library_class::function {
    slf__create_entity_in_hero_region__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AF2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_entity_list__t : script_library_class::function {
    slf__create_entity_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BFCC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_entity_tracker__entity__t : script_library_class::function {
    slf__create_entity_tracker__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C594;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_item__str__t : script_library_class::function {
    slf__create_item__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B6B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_line_info__vector3d__vector3d__t : script_library_class::function {
    slf__create_line_info__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B708;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_lofi_stereo_sound_inst__str__t : script_library_class::function {
    slf__create_lofi_stereo_sound_inst__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B818;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_num_list__t : script_library_class::function {
    slf__create_num_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BF54;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_pfx__str__t : script_library_class::function {
    slf__create_pfx__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C904;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_pfx__str__vector3d__t : script_library_class::function {
    slf__create_pfx__str__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C90C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_polytube__t : script_library_class::function {
    slf__create_polytube__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C228;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_polytube__str__t : script_library_class::function {
    slf__create_polytube__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C230;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_progression_menu_entry__str__str__t : script_library_class::function {
    slf__create_progression_menu_entry__str__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C714;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_sound_inst__t : script_library_class::function {
    slf__create_sound_inst__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B7F8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_sound_inst__str__t : script_library_class::function {
    slf__create_sound_inst__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B800;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_stompable_music_sound_inst__str__t : script_library_class::function {
    slf__create_stompable_music_sound_inst__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B808;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_str_list__t : script_library_class::function {
    slf__create_str_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C044;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_taunt_entry__entity__str__num__t : script_library_class::function {
    slf__create_taunt_entry__entity__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C63C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_taunt_exchange__entity__entity__num__num__num__num__t : script_library_class::function {
    slf__create_taunt_exchange__entity__entity__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C6B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_taunt_exchange_list__t : script_library_class::function {
    slf__create_taunt_exchange_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C0DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_threat_assessment_meter__t : script_library_class::function {
    slf__create_threat_assessment_meter__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C6CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_time_limited_entity__str__num__t : script_library_class::function {
    slf__create_time_limited_entity__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AF3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_trigger__entity__num__t : script_library_class::function {
    slf__create_trigger__entity__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B970;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_trigger__str__vector3d__num__t : script_library_class::function {
    slf__create_trigger__str__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B968;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_trigger__vector3d__num__t : script_library_class::function {
    slf__create_trigger__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B960;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_unstompable_script_cutscene_sound_inst__str__t : script_library_class::function {
    slf__create_unstompable_script_cutscene_sound_inst__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B810;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__create_vector3d_list__t : script_library_class::function {
    slf__create_vector3d_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BECC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__cross__vector3d__vector3d__t : script_library_class::function {
    slf__cross__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BA38;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_breakpoint__t : script_library_class::function {
    slf__debug_breakpoint__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A510;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_print__num__str__t : script_library_class::function {
    slf__debug_print__num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A528;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_print__num__vector3d__str__t : script_library_class::function {
    slf__debug_print__num__vector3d__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A530;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_print__str__t : script_library_class::function {
    slf__debug_print__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A520;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_print_set_background_color__vector3d__t : script_library_class::function {
    slf__debug_print_set_background_color__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A538;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__delay__num__t : script_library_class::function {
    slf__delay__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A71C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_credits__t : script_library_class::function {
    slf__destroy_credits__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BAF0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_debug_menu_entry__debug_menu_entry__t : script_library_class::function {
    slf__destroy_debug_menu_entry__debug_menu_entry__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C71C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_entity__entity__t : script_library_class::function {
    slf__destroy_entity__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AF34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_entity_list__entity_list__t : script_library_class::function {
    slf__destroy_entity_list__entity_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BFD4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_entity_tracker__entity_tracker__t : script_library_class::function {
    slf__destroy_entity_tracker__entity_tracker__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C59C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_line_info__line_info__t : script_library_class::function {
    slf__destroy_line_info__line_info__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B710;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_num_list__num_list__t : script_library_class::function {
    slf__destroy_num_list__num_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BF5C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_pfx__pfx__t : script_library_class::function {
    slf__destroy_pfx__pfx__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C914;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_str_list__str_list__t : script_library_class::function {
    slf__destroy_str_list__str_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C04C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_taunt_entry__taunt_entry__t : script_library_class::function {
    slf__destroy_taunt_entry__taunt_entry__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C644;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_taunt_exchange__taunt_exchange__t : script_library_class::function {
    slf__destroy_taunt_exchange__taunt_exchange__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C6BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_taunt_exchange_list__taunt_exchange_list__t : script_library_class::function {
    slf__destroy_taunt_exchange_list__taunt_exchange_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C0E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_threat_assessment_meter__tam__t : script_library_class::function {
    slf__destroy_threat_assessment_meter__tam__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C6D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_trigger__trigger__t : script_library_class::function {
    slf__destroy_trigger__trigger__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B978;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__destroy_vector3d_list__vector3d_list__t : script_library_class::function {
    slf__destroy_vector3d_list__vector3d_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BEDC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__dilated_delay__num__t : script_library_class::function {
    slf__dilated_delay__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A72C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__disable_marky_cam__num__t : script_library_class::function {
    slf__disable_marky_cam__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__disable_nearby_occlusion_only_obb__vector3d__t : script_library_class::function {
    slf__disable_nearby_occlusion_only_obb__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__disable_player_shadows__t : script_library_class::function {
    slf__disable_player_shadows__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A614;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__disable_subtitles__t : script_library_class::function {
    slf__disable_subtitles__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A93C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__disable_vibrator__t : script_library_class::function {
    slf__disable_vibrator__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__disable_zoom_map__num__t : script_library_class::function {
    slf__disable_zoom_map__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBF0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance3d__vector3d__vector3d__t : script_library_class::function {
    slf__distance3d__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BA48;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance_chase_widget_set_pos__num__t : script_library_class::function {
    slf__distance_chase_widget_set_pos__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB88;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance_chase_widget_turn_off__t : script_library_class::function {
    slf__distance_chase_widget_turn_off__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB80;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance_chase_widget_turn_on__num__num__t : script_library_class::function {
    slf__distance_chase_widget_turn_on__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB78;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance_race_widget_set_boss_pos__num__t : script_library_class::function {
    slf__distance_race_widget_set_boss_pos__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBA8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance_race_widget_set_hero_pos__num__t : script_library_class::function {
    slf__distance_race_widget_set_hero_pos__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBA0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance_race_widget_set_types__num__num__t : script_library_class::function {
    slf__distance_race_widget_set_types__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBB0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance_race_widget_turn_off__t : script_library_class::function {
    slf__distance_race_widget_turn_off__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB98;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__distance_race_widget_turn_on__t : script_library_class::function {
    slf__distance_race_widget_turn_on__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB90;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district_id__str__t : script_library_class::function {
    slf__district_id__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C47C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district_name__num__t : script_library_class::function {
    slf__district_name__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C484;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__dot__vector3d__vector3d__t : script_library_class::function {
    slf__dot__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BA30;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__dump_searchable_region_list__str__t : script_library_class::function {
    slf__dump_searchable_region_list__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A994;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_ai__num__t : script_library_class::function {
    slf__enable_ai__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_civilians__num__t : script_library_class::function {
    slf__enable_civilians__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_controls__num__t : script_library_class::function {
    slf__enable_controls__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BD40;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_entity_fading__num__t : script_library_class::function {
    slf__enable_entity_fading__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B05C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_interface__num__t : script_library_class::function {
    slf__enable_interface__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_marky_cam__num__t : script_library_class::function {
    slf__enable_marky_cam__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_mini_map__num__t : script_library_class::function {
    slf__enable_mini_map__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBE8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_nearby_occlusion_only_obb__vector3d__t : script_library_class::function {
    slf__enable_nearby_occlusion_only_obb__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_obb__vector3d__num__t : script_library_class::function {
    slf__enable_obb__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A588;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_pause__num__t : script_library_class::function {
    slf__enable_pause__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_physics__num__t : script_library_class::function {
    slf__enable_physics__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_player_shadows__t : script_library_class::function {
    slf__enable_player_shadows__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A61C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_pois__num__t : script_library_class::function {
    slf__enable_pois__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_quad_path_connector__district__num__district__num__num__t : script_library_class::function {
    slf__enable_quad_path_connector__district__num__district__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A578;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_subtitles__t : script_library_class::function {
    slf__enable_subtitles__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A934;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_tokens_of_type__num__num__t : script_library_class::function {
    slf__enable_tokens_of_type__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B54C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_traffic__num__t : script_library_class::function {
    slf__enable_traffic__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_user_camera__num__t : script_library_class::function {
    slf__enable_user_camera__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__enable_vibrator__t : script_library_class::function {
    slf__enable_vibrator__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__end_current_patrol__t : script_library_class::function {
    slf__end_current_patrol__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__end_cut_scenes__t : script_library_class::function {
    slf__end_cut_scenes__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B7C8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__end_screen_recording__t : script_library_class::function {
    slf__end_screen_recording__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B7B8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_col_check__entity__entity__t : script_library_class::function {
    slf__entity_col_check__entity__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A88C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_exists__str__t : script_library_class::function {
    slf__entity_exists__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AF24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_get_entity_tracker__entity__t : script_library_class::function {
    slf__entity_get_entity_tracker__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B034;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_has_entity_tracker__entity__t : script_library_class::function {
    slf__entity_has_entity_tracker__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B02C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__exit_water__entity__t : script_library_class::function {
    slf__exit_water__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A604;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_closest_point_on_a_path_to_point__vector3d__t : script_library_class::function {
    slf__find_closest_point_on_a_path_to_point__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A570;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_district_for_point__vector3d__t : script_library_class::function {
    slf__find_district_for_point__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A81C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_entities_in_radius__entity_list__vector3d__num__num__t : script_library_class::function {
    slf__find_entities_in_radius__entity_list__vector3d__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B46C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_entity__str__t : script_library_class::function {
    slf__find_entity__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AF1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_innermost_district__vector3d__t : script_library_class::function {
    slf__find_innermost_district__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A824;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_outermost_district__vector3d__t : script_library_class::function {
    slf__find_outermost_district__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A82C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_trigger__entity__t : script_library_class::function {
    slf__find_trigger__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B950;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_trigger__str__t : script_library_class::function {
    slf__find_trigger__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B948;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__find_trigger_in_district__district__str__t : script_library_class::function {
    slf__find_trigger_in_district__district__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B958;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__float_random__num__t : script_library_class::function {
    slf__float_random__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A74C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__force_mission__district__str__num__t : script_library_class::function {
    slf__force_mission__district__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__force_streamer_refresh__t : script_library_class::function {
    slf__force_streamer_refresh__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__format_time_string__num__t : script_library_class::function {
    slf__format_time_string__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC74;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__freeze_hero__num__t : script_library_class::function {
    slf__freeze_hero__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__game_ini_get_flag__str__t : script_library_class::function {
    slf__game_ini_get_flag__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A97C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__game_time_advance__num__num__t : script_library_class::function {
    slf__game_time_advance__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_all_execs_thread_count__str__t : script_library_class::function {
    slf__get_all_execs_thread_count__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A9EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_all_instances_thread_count__str__t : script_library_class::function {
    slf__get_all_instances_thread_count__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A9E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_attacker_entity__t : script_library_class::function {
    slf__get_attacker_entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_attacker_member__t : script_library_class::function {
    slf__get_attacker_member__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_available_stack_size__t : script_library_class::function {
    slf__get_available_stack_size__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_character_packname_list__t : script_library_class::function {
    slf__get_character_packname_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C354;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_closest_point_on_lane_with_facing__num__vector3d__vector3d_list__t : script_library_class::function {
    slf__get_closest_point_on_lane_with_facing__num__vector3d__vector3d_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C61C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_col_hit_ent__t : script_library_class::function {
    slf__get_col_hit_ent__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A884;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_col_hit_norm__t : script_library_class::function {
    slf__get_col_hit_norm__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A87C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_col_hit_pos__t : script_library_class::function {
    slf__get_col_hit_pos__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A874;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_control_state__num__t : script_library_class::function {
    slf__get_control_state__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_control_trigger__num__t : script_library_class::function {
    slf__get_control_trigger__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_current_instance_thread_count__str__t : script_library_class::function {
    slf__get_current_instance_thread_count__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A9DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_current_view_cam_pos__t : script_library_class::function {
    slf__get_current_view_cam_pos__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_current_view_cam_x_facing__t : script_library_class::function {
    slf__get_current_view_cam_x_facing__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A59C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_current_view_cam_y_facing__t : script_library_class::function {
    slf__get_current_view_cam_y_facing__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_current_view_cam_z_facing__t : script_library_class::function {
    slf__get_current_view_cam_z_facing__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_fog_color__t : script_library_class::function {
    slf__get_fog_color__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_fog_distance__t : script_library_class::function {
    slf__get_fog_distance__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_game_info_num__str__t : script_library_class::function {
    slf__get_game_info_num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_game_info_str__str__t : script_library_class::function {
    slf__get_game_info_str__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_glam_cam__num__t : script_library_class::function {
    slf__get_glam_cam__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B780;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_global_time_dilation__t : script_library_class::function {
    slf__get_global_time_dilation__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A894;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_ini_flag__str__t : script_library_class::function {
    slf__get_ini_flag__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A94C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_ini_num__str__t : script_library_class::function {
    slf__get_ini_num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A954;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_int_num__num__t : script_library_class::function {
    slf__get_int_num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A92C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_camera_marker__num__t : script_library_class::function {
    slf__get_mission_camera_marker__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C414;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_camera_transform_marker__num__t : script_library_class::function {
    slf__get_mission_camera_transform_marker__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C454;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_entity__t : script_library_class::function {
    slf__get_mission_entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C38C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_key_posfacing3d__t : script_library_class::function {
    slf__get_mission_key_posfacing3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C36C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_key_position__t : script_library_class::function {
    slf__get_mission_key_position__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C364;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_marker__num__t : script_library_class::function {
    slf__get_mission_marker__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C40C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_nums__t : script_library_class::function {
    slf__get_mission_nums__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_patrol_waypoint__t : script_library_class::function {
    slf__get_mission_patrol_waypoint__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C384;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_positions__t : script_library_class::function {
    slf__get_mission_positions__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C39C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_strings__t : script_library_class::function {
    slf__get_mission_strings__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_transform_marker__num__t : script_library_class::function {
    slf__get_mission_transform_marker__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C42C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_mission_trigger__t : script_library_class::function {
    slf__get_mission_trigger__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C394;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_missions_key_position_by_index__district__str__num__t : script_library_class::function {
    slf__get_missions_key_position_by_index__district__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_missions_nums_by_index__district__str__num__num_list__t : script_library_class::function {
    slf__get_missions_nums_by_index__district__str__num__num_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_missions_patrol_waypoint_by_index__district__str__num__t : script_library_class::function {
    slf__get_missions_patrol_waypoint_by_index__district__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_neighborhood_name__num__t : script_library_class::function {
    slf__get_neighborhood_name__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C54C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_num_free_slots__str__t : script_library_class::function {
    slf__get_num_free_slots__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_num_mission_transform_marker__t : script_library_class::function {
    slf__get_num_mission_transform_marker__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C434;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_pack_group__str__t : script_library_class::function {
    slf__get_pack_group__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_pack_size__str__t : script_library_class::function {
    slf__get_pack_size__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_patrol_difficulty__str__t : script_library_class::function {
    slf__get_patrol_difficulty__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C534;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_patrol_node_position_by_index__str__num__t : script_library_class::function {
    slf__get_patrol_node_position_by_index__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C52C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_patrol_start_position__str__t : script_library_class::function {
    slf__get_patrol_start_position__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C524;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_patrol_unlock_threshold__str__t : script_library_class::function {
    slf__get_patrol_unlock_threshold__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C53C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_platform__t : script_library_class::function {
    slf__get_platform__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A508;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_render_opt_num__str__t : script_library_class::function {
    slf__get_render_opt_num__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_spider_reflexes_spiderman_time_dilation__t : script_library_class::function {
    slf__get_spider_reflexes_spiderman_time_dilation__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAC4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_spider_reflexes_world_time_dilation__t : script_library_class::function {
    slf__get_spider_reflexes_world_time_dilation__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAD4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_time_inc__t : script_library_class::function {
    slf__get_time_inc__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_time_of_day__t : script_library_class::function {
    slf__get_time_of_day__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A974;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_time_of_day_rate__t : script_library_class::function {
    slf__get_time_of_day_rate__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A96C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_token_index_from_id__num__num__t : script_library_class::function {
    slf__get_token_index_from_id__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B554;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__get_traffic_spawn_point_near_camera__vector3d_list__t : script_library_class::function {
    slf__get_traffic_spawn_point_near_camera__vector3d_list__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA98;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__greater_than_or_equal_rounded__num__num__t : script_library_class::function {
    slf__greater_than_or_equal_rounded__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC90;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__hard_break__t : script_library_class::function {
    slf__hard_break__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__has_substring__str__str__t : script_library_class::function {
    slf__has_substring__str__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A580;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__hero__t : script_library_class::function {
    slf__hero__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AED4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__hero_exists__t : script_library_class::function {
    slf__hero_exists__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AEDC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__hero_type__t : script_library_class::function {
    slf__hero_type__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AEE4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__hide_controller_gauge__t : script_library_class::function {
    slf__hide_controller_gauge__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB20;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__initialize_encounter_object__t : script_library_class::function {
    slf__initialize_encounter_object__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__initialize_encounter_objects__t : script_library_class::function {
    slf__initialize_encounter_objects__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__insert_pack__str__t : script_library_class::function {
    slf__insert_pack__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__invoke_pause_menu_unlockables__t : script_library_class::function {
    slf__invoke_pause_menu_unlockables__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC98;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_ai_enabled__t : script_library_class::function {
    slf__is_ai_enabled__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_cut_scene_playing__t : script_library_class::function {
    slf__is_cut_scene_playing__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B7D0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_district_loaded__num__t : script_library_class::function {
    slf__is_district_loaded__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C49C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_hero_frozen__t : script_library_class::function {
    slf__is_hero_frozen__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A60C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_hero_peter_parker__t : script_library_class::function {
    slf__is_hero_peter_parker__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AEFC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_hero_spidey__t : script_library_class::function {
    slf__is_hero_spidey__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AEEC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_hero_venom__t : script_library_class::function {
    slf__is_hero_venom__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AEF4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_marky_cam_enabled__t : script_library_class::function {
    slf__is_marky_cam_enabled__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_mission_active__t : script_library_class::function {
    slf__is_mission_active__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C50C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_mission_loading__t : script_library_class::function {
    slf__is_mission_loading__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C514;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_pack_available__str__t : script_library_class::function {
    slf__is_pack_available__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C404;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_pack_loaded__str__t : script_library_class::function {
    slf__is_pack_loaded__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_pack_pushed__str__t : script_library_class::function {
    slf__is_pack_pushed__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C34C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_path_graph_inside_glass_house__str__t : script_library_class::function {
    slf__is_path_graph_inside_glass_house__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AAA0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_patrol_active__t : script_library_class::function {
    slf__is_patrol_active__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C504;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_patrol_node_empty__num__t : script_library_class::function {
    slf__is_patrol_node_empty__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C544;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_paused__t : script_library_class::function {
    slf__is_paused__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_physics_enabled__t : script_library_class::function {
    slf__is_physics_enabled__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_point_inside_glass_house__vector3d__t : script_library_class::function {
    slf__is_point_inside_glass_house__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A540;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_point_under_water__vector3d__t : script_library_class::function {
    slf__is_point_under_water__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__is_user_camera_enabled__t : script_library_class::function {
    slf__is_user_camera_enabled__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__load_anim__str__t : script_library_class::function {
    slf__load_anim__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AAF0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__load_level__str__vector3d__t : script_library_class::function {
    slf__load_level__str__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__lock_all_districts__t : script_library_class::function {
    slf__lock_all_districts__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__lock_district__num__t : script_library_class::function {
    slf__lock_district__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C494;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__lock_mission_manager__num__t : script_library_class::function {
    slf__lock_mission_manager__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C51C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__los_check__vector3d__vector3d__t : script_library_class::function {
    slf__los_check__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A814;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__lower_hotpursuit_indicator_level__t : script_library_class::function {
    slf__lower_hotpursuit_indicator_level__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BAE0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__malor__vector3d__num__t : script_library_class::function {
    slf__malor__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A984;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__normal__vector3d__t : script_library_class::function {
    slf__normal__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BA40;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pause_game__num__t : script_library_class::function {
    slf__pause_game__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__play_credits__t : script_library_class::function {
    slf__play_credits__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BAF8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__play_prerender__str__t : script_library_class::function {
    slf__play_prerender__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pop_pack__str__t : script_library_class::function {
    slf__pop_pack__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C344;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__post_message__str__num__t : script_library_class::function {
    slf__post_message__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A73C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pre_roll_all_pfx__num__t : script_library_class::function {
    slf__pre_roll_all_pfx__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__press_controller_gauge__num__t : script_library_class::function {
    slf__press_controller_gauge__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB28;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__press_controller_gauge__num__num__num__t : script_library_class::function {
    slf__press_controller_gauge__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB30;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__purge_district__num__t : script_library_class::function {
    slf__purge_district__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__push_pack__str__t : script_library_class::function {
    slf__push_pack__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C334;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__push_pack_into_district_slot__str__t : script_library_class::function {
    slf__push_pack_into_district_slot__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C33C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__raise_hotpursuit_indicator_level__t : script_library_class::function {
    slf__raise_hotpursuit_indicator_level__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BAD8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__random__num__t : script_library_class::function {
    slf__random__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A744;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__remove_civilian_info__num__t : script_library_class::function {
    slf__remove_civilian_info__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__remove_civilian_info_entity__entity__num__t : script_library_class::function {
    slf__remove_civilian_info_entity__entity__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__remove_glass_house__str__t : script_library_class::function {
    slf__remove_glass_house__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A568;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__remove_item_entity_from_world__entity__t : script_library_class::function {
    slf__remove_item_entity_from_world__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AFFC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__remove_pack__str__t : script_library_class::function {
    slf__remove_pack__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C3DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__remove_traffic_model__num__t : script_library_class::function {
    slf__remove_traffic_model__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__reset_externed_alses__t : script_library_class::function {
    slf__reset_externed_alses__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B064;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_all_anchors_activated__num__t : script_library_class::function {
    slf__set_all_anchors_activated__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAEC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_blur__num__t : script_library_class::function {
    slf__set_blur__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A63C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_blur_blend_mode__num__t : script_library_class::function {
    slf__set_blur_blend_mode__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A664;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_blur_color__vector3d__t : script_library_class::function {
    slf__set_blur_color__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A644;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_blur_offset__num__num__t : script_library_class::function {
    slf__set_blur_offset__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A654;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_blur_rot__num__t : script_library_class::function {
    slf__set_blur_rot__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A65C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_blur_scale__num__num__t : script_library_class::function {
    slf__set_blur_scale__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A64C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_clear_color__vector3d__t : script_library_class::function {
    slf__set_clear_color__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_current_mission_objective_caption__num__t : script_library_class::function {
    slf__set_current_mission_objective_caption__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CADC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_default_traffic_hitpoints__num__t : script_library_class::function {
    slf__set_default_traffic_hitpoints__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C614;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_dialog_box_flavor__num__t : script_library_class::function {
    slf__set_dialog_box_flavor__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC5C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_dialog_box_lockout_time__num__t : script_library_class::function {
    slf__set_dialog_box_lockout_time__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC6C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_engine_property__str__num__t : script_library_class::function {
    slf__set_engine_property__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A99C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_fov__num__t : script_library_class::function {
    slf__set_fov__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A62C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_game_info_num__str__num__t : script_library_class::function {
    slf__set_game_info_num__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_game_info_str__str__str__t : script_library_class::function {
    slf__set_game_info_str__str__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_global_time_dilation__num__t : script_library_class::function {
    slf__set_global_time_dilation__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A89C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_marky_cam_lookat__vector3d__t : script_library_class::function {
    slf__set_marky_cam_lookat__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A5EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_max_streaming_distance__num__t : script_library_class::function {
    slf__set_max_streaming_distance__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_mission_key_pos_facing__vector3d__vector3d__t : script_library_class::function {
    slf__set_mission_key_pos_facing__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C37C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_mission_key_position__vector3d__t : script_library_class::function {
    slf__set_mission_key_position__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C374;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_mission_text__num__t : script_library_class::function {
    slf__set_mission_text__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBF8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_mission_text_box_flavor__num__t : script_library_class::function {
    slf__set_mission_text_box_flavor__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC64;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_mission_text_debug__str__t : script_library_class::function {
    slf__set_mission_text_debug__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC00;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_parking_density__num__t : script_library_class::function {
    slf__set_parking_density__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C60C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_pedestrian_density__num__t : script_library_class::function {
    slf__set_pedestrian_density__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_render_opt_num__str__num__t : script_library_class::function {
    slf__set_render_opt_num__str__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_score_widget_score__num__t : script_library_class::function {
    slf__set_score_widget_score__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BAC8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_sound_category_volume__num__num__num__t : script_library_class::function {
    slf__set_sound_category_volume__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A9D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_blur__num__t : script_library_class::function {
    slf__set_spider_reflexes_blur__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A674;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_blur_blend_mode__num__t : script_library_class::function {
    slf__set_spider_reflexes_blur_blend_mode__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A69C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_blur_color__vector3d__t : script_library_class::function {
    slf__set_spider_reflexes_blur_color__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A67C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_blur_offset__num__num__t : script_library_class::function {
    slf__set_spider_reflexes_blur_offset__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A68C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_blur_rot__num__t : script_library_class::function {
    slf__set_spider_reflexes_blur_rot__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A694;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_blur_scale__num__num__t : script_library_class::function {
    slf__set_spider_reflexes_blur_scale__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A684;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_hero_meter_depletion_rate__num__t : script_library_class::function {
    slf__set_spider_reflexes_hero_meter_depletion_rate__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAB4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_spiderman_time_dilation__num__t : script_library_class::function {
    slf__set_spider_reflexes_spiderman_time_dilation__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CABC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_spider_reflexes_world_time_dilation__num__t : script_library_class::function {
    slf__set_spider_reflexes_world_time_dilation__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CACC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_state_of_the_story_caption__num__t : script_library_class::function {
    slf__set_state_of_the_story_caption__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAE4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_target_info__entity__vector3d__vector3d__t : script_library_class::function {
    slf__set_target_info__entity__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B6C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_time_of_day__num__t : script_library_class::function {
    slf__set_time_of_day__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A964;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_traffic_density__num__t : script_library_class::function {
    slf__set_traffic_density__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C604;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_traffic_model_usage__num__num__t : script_library_class::function {
    slf__set_traffic_model_usage__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C5B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_vibration_resume__num__t : script_library_class::function {
    slf__set_vibration_resume__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_whoosh_interp_rate__num__t : script_library_class::function {
    slf__set_whoosh_interp_rate__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B504;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_whoosh_pitch_range__num__num__t : script_library_class::function {
    slf__set_whoosh_pitch_range__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B4FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_whoosh_speed_range__num__num__t : script_library_class::function {
    slf__set_whoosh_speed_range__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B4EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_whoosh_volume_range__num__num__t : script_library_class::function {
    slf__set_whoosh_volume_range__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B4F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__set_zoom__num__t : script_library_class::function {
    slf__set_zoom__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A624;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__show_controller_gauge__t : script_library_class::function {
    slf__show_controller_gauge__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB18;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__show_hotpursuit_indicator__num__t : script_library_class::function {
    slf__show_hotpursuit_indicator__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BAD0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__show_score_widget__num__t : script_library_class::function {
    slf__show_score_widget__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BAC0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__shut_up_all_ai_voice_boxes__t : script_library_class::function {
    slf__shut_up_all_ai_voice_boxes__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B50C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sin__num__t : script_library_class::function {
    slf__sin__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A904;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sin_cos__num__t : script_library_class::function {
    slf__sin_cos__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A924;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__soft_load__num__t : script_library_class::function {
    slf__soft_load__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BCBC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__soft_save__num__t : script_library_class::function {
    slf__soft_save__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BCB4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_add_hero_points__num__t : script_library_class::function {
    slf__spiderman_add_hero_points__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAA4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_bank_stylepoints__t : script_library_class::function {
    slf__spiderman_bank_stylepoints__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C91C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_break_web__t : script_library_class::function {
    slf__spiderman_break_web__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_add_shake__num__num__num__t : script_library_class::function {
    slf__spiderman_camera_add_shake__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_autocorrect__num__t : script_library_class::function {
    slf__spiderman_camera_autocorrect__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C924;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_clear_fixedstatic__t : script_library_class::function {
    slf__spiderman_camera_clear_fixedstatic__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAFC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_enable_combat__num__t : script_library_class::function {
    slf__spiderman_camera_enable_combat__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_enable_lookaround__num__t : script_library_class::function {
    slf__spiderman_camera_enable_lookaround__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_set_fixedstatic__vector3d__vector3d__t : script_library_class::function {
    slf__spiderman_camera_set_fixedstatic__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAF4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_set_follow__entity__t : script_library_class::function {
    slf__spiderman_camera_set_follow__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_set_hero_underwater__num__t : script_library_class::function {
    slf__spiderman_camera_set_hero_underwater__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_set_interpolation_time__num__t : script_library_class::function {
    slf__spiderman_camera_set_interpolation_time__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_set_lockon_min_distance__num__t : script_library_class::function {
    slf__spiderman_camera_set_lockon_min_distance__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_camera_set_lockon_y_offset__num__t : script_library_class::function {
    slf__spiderman_camera_set_lockon_y_offset__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_charged_jump__t : script_library_class::function {
    slf__spiderman_charged_jump__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C98C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_enable_control_button__num__num__t : script_library_class::function {
    slf__spiderman_enable_control_button__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA94;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_enable_lockon__num__t : script_library_class::function {
    slf__spiderman_enable_lockon__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_engage_lockon__num__t : script_library_class::function {
    slf__spiderman_engage_lockon__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_engage_lockon__num__entity__t : script_library_class::function {
    slf__spiderman_engage_lockon__num__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_get_hero_points__t : script_library_class::function {
    slf__spiderman_get_hero_points__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA9C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_get_max_zip_length__t : script_library_class::function {
    slf__spiderman_get_max_zip_length__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_get_spidey_sense_level__t : script_library_class::function {
    slf__spiderman_get_spidey_sense_level__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C99C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_crawling__t : script_library_class::function {
    slf__spiderman_is_crawling__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C934;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_falling__t : script_library_class::function {
    slf__spiderman_is_falling__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C964;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_jumping__t : script_library_class::function {
    slf__spiderman_is_jumping__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C96C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_on_ceiling__t : script_library_class::function {
    slf__spiderman_is_on_ceiling__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C944;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_on_ground__t : script_library_class::function {
    slf__spiderman_is_on_ground__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C94C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_on_wall__t : script_library_class::function {
    slf__spiderman_is_on_wall__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C93C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_running__t : script_library_class::function {
    slf__spiderman_is_running__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C95C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_sprint_crawling__t : script_library_class::function {
    slf__spiderman_is_sprint_crawling__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C984;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_sprinting__t : script_library_class::function {
    slf__spiderman_is_sprinting__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C974;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_swinging__t : script_library_class::function {
    slf__spiderman_is_swinging__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C954;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_is_wallsprinting__t : script_library_class::function {
    slf__spiderman_is_wallsprinting__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C97C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_lock_spider_reflexes_off__t : script_library_class::function {
    slf__spiderman_lock_spider_reflexes_off__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_lock_spider_reflexes_on__t : script_library_class::function {
    slf__spiderman_lock_spider_reflexes_on__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_lockon_camera_engaged__t : script_library_class::function {
    slf__spiderman_lockon_camera_engaged__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_lockon_mode_engaged__t : script_library_class::function {
    slf__spiderman_lockon_mode_engaged__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_camera_target__entity__t : script_library_class::function {
    slf__spiderman_set_camera_target__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_desired_mode__num__vector3d__vector3d__t : script_library_class::function {
    slf__spiderman_set_desired_mode__num__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_health_beep_min_max_cooldown_time__num__num__t : script_library_class::function {
    slf__spiderman_set_health_beep_min_max_cooldown_time__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_health_beep_threshold__num__t : script_library_class::function {
    slf__spiderman_set_health_beep_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_hero_meter_empty_rate__num__t : script_library_class::function {
    slf__spiderman_set_hero_meter_empty_rate__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB44;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_max_height__num__t : script_library_class::function {
    slf__spiderman_set_max_height__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_max_zip_length__num__t : script_library_class::function {
    slf__spiderman_set_max_zip_length__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_min_height__num__t : script_library_class::function {
    slf__spiderman_set_min_height__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_spidey_sense_level__num__t : script_library_class::function {
    slf__spiderman_set_spidey_sense_level__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C994;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_set_swing_anchor_max_sticky_time__num__t : script_library_class::function {
    slf__spiderman_set_swing_anchor_max_sticky_time__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C9A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_subtract_hero_points__num__t : script_library_class::function {
    slf__spiderman_subtract_hero_points__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CAAC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_alternating_wall_run_occurrence_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_alternating_wall_run_occurrence_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA74;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_alternating_wall_run_time_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_alternating_wall_run_time_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA6C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_big_air_height_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_big_air_height_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_continuous_air_swings_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_continuous_air_swings_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA4C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_gain_altitude_height_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_gain_altitude_height_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA54;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_near_miss_trigger_radius__num__t : script_library_class::function {
    slf__spiderman_td_set_near_miss_trigger_radius__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA84;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_near_miss_velocity_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_near_miss_velocity_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA8C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_orbit_min_radius_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_orbit_min_radius_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_soft_landing_velocity_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_soft_landing_velocity_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA5C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_super_speed_speed_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_super_speed_speed_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA7C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_swinging_wall_run_time_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_swinging_wall_run_time_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA64;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_td_set_wall_sprint_time_threshold__num__t : script_library_class::function {
    slf__spiderman_td_set_wall_sprint_time_threshold__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA44;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_unlock_spider_reflexes__t : script_library_class::function {
    slf__spiderman_unlock_spider_reflexes__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CA2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spiderman_wait_add_threat__entity__str__num__num__t : script_library_class::function {
    slf__spiderman_wait_add_threat__entity__str__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089CB4C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__spidey_can_see__vector3d__t : script_library_class::function {
    slf__spidey_can_see__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C92C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sqrt__num__t : script_library_class::function {
    slf__sqrt__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A914;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__start_patrol__str__t : script_library_class::function {
    slf__start_patrol__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__stop_all_sounds__t : script_library_class::function {
    slf__stop_all_sounds__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B514;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__stop_credits__t : script_library_class::function {
    slf__stop_credits__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB00;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__stop_vibration__t : script_library_class::function {
    slf__stop_vibration__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__subtitle__num__num__num__num__num__num__t : script_library_class::function {
    slf__subtitle__num__num__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BCC4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__swap_hero_costume__str__t : script_library_class::function {
    slf__swap_hero_costume__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__text_width__str__t : script_library_class::function {
    slf__text_width__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__timer_widget_get_count_up__t : script_library_class::function {
    slf__timer_widget_get_count_up__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB70;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__timer_widget_get_time__t : script_library_class::function {
    slf__timer_widget_get_time__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB60;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__timer_widget_set_count_up__num__t : script_library_class::function {
    slf__timer_widget_set_count_up__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB68;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__timer_widget_set_time__num__t : script_library_class::function {
    slf__timer_widget_set_time__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB58;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__timer_widget_start__t : script_library_class::function {
    slf__timer_widget_start__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB48;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__timer_widget_stop__t : script_library_class::function {
    slf__timer_widget_stop__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB50;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__timer_widget_turn_off__t : script_library_class::function {
    slf__timer_widget_turn_off__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB40;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__timer_widget_turn_on__t : script_library_class::function {
    slf__timer_widget_turn_on__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BB38;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__to_beam__entity__t : script_library_class::function {
    slf__to_beam__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089ABBC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__to_gun__entity__t : script_library_class::function {
    slf__to_gun__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B5A0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__to_item__entity__t : script_library_class::function {
    slf__to_item__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B6BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__to_polytube__entity__t : script_library_class::function {
    slf__to_polytube__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C238;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__to_switch__entity__t : script_library_class::function {
    slf__to_switch__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B8E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trace__str__t : script_library_class::function {
    slf__trace__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089AA14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger_is_valid__trigger__t : script_library_class::function {
    slf__trigger_is_valid__trigger__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089B9B8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__turn_off_boss_health__t : script_library_class::function {
    slf__turn_off_boss_health__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBD0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__turn_off_hero_health__t : script_library_class::function {
    slf__turn_off_hero_health__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBD8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__turn_off_mission_text__t : script_library_class::function {
    slf__turn_off_mission_text__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BC20;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__turn_off_third_party_health__t : script_library_class::function {
    slf__turn_off_third_party_health__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBE0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__turn_on_boss_health__num__entity__t : script_library_class::function {
    slf__turn_on_boss_health__num__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBB8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__turn_on_hero_health__num__entity__t : script_library_class::function {
    slf__turn_on_hero_health__num__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBC0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__turn_on_third_party_health__num__entity__t : script_library_class::function {
    slf__turn_on_third_party_health__num__entity__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089BBC8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__unload_script__t : script_library_class::function {
    slf__unload_script__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C35C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__unlock_all_exterior_districts__t : script_library_class::function {
    slf__unlock_all_exterior_districts__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__unlock_district__num__t : script_library_class::function {
    slf__unlock_district__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C48C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vibrate_controller__num__t : script_library_class::function {
    slf__vibrate_controller__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vibrate_controller__num__num__t : script_library_class::function {
    slf__vibrate_controller__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vibrate_controller__num__num__num__num__num__num__t : script_library_class::function {
    slf__vibrate_controller__num__num__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A7B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vo_delay__num__num__num__num__t : script_library_class::function {
    slf__vo_delay__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A734;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_animate_fog_color__vector3d__num__t : script_library_class::function {
    slf__wait_animate_fog_color__vector3d__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_animate_fog_distance__num__num__t : script_library_class::function {
    slf__wait_animate_fog_distance__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A704;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_animate_fog_distances__num__num__num__t : script_library_class::function {
    slf__wait_animate_fog_distances__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A70C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_change_blur__num__vector3d__num__num__num__num__num__num__t : script_library_class::function {
    slf__wait_change_blur__num__vector3d__num__num__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A66C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_change_spider_reflexes_blur__num__vector3d__num__num__num__num__num__num__t : script_library_class::function {
    slf__wait_change_spider_reflexes_blur__num__vector3d__num__num__num__num__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A6A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_for_streamer_to_reach_equilibrium__t : script_library_class::function {
    slf__wait_for_streamer_to_reach_equilibrium__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089C4A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_fps_test__num__num__vector3d__vector3d__t : script_library_class::function {
    slf__wait_fps_test__num__num__vector3d__vector3d__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_frame__t : script_library_class::function {
    slf__wait_frame__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A714;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_set_global_time_dilation__num__num__t : script_library_class::function {
    slf__wait_set_global_time_dilation__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A8A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__wait_set_zoom__num__num__t : script_library_class::function {
    slf__wait_set_zoom__num__num__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A634;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__write_to_file__str__str__t : script_library_class::function {
    slf__write_to_file__str__str__t (const char *a3) : function(a3)  {
        m_vtbl = 0x0089A844;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

// non global slf
struct slf__anim__kill_anim__t : script_library_class::function {
    slf__anim__kill_anim__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AAE8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__anim__pause__t : script_library_class::function {
    slf__anim__pause__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AAB8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__anim__play__t : script_library_class::function {
    slf__anim__play__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AAD8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__anim__set_fade_time__num__t : script_library_class::function {
    slf__anim__set_fade_time__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AAC8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__anim__set_time__num__t : script_library_class::function {
    slf__anim__set_time__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AAD0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__anim__set_timescale__num__t : script_library_class::function {
    slf__anim__set_timescale__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AAC0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__anim__wait_finished__t : script_library_class::function {
    slf__anim__wait_finished__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AAE0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__add_alpha_effect__num__num__num__num__num__num__t : script_library_class::function {
    slf__beam__add_alpha_effect__num__num__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB9C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__add_color_effect__num__num__num__num__num__num__num__num__num__num__t : script_library_class::function {
    slf__beam__add_color_effect__num__num__num__num__num__num__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB8C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__add_width_effect__num__num__num__num__num__num__t : script_library_class::function {
    slf__beam__add_width_effect__num__num__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB94;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__get_impact_normal__t : script_library_class::function {
    slf__beam__get_impact_normal__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__get_impact_point__t : script_library_class::function {
    slf__beam__get_impact_point__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__hit_hero__t : script_library_class::function {
    slf__beam__hit_hero__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__hit_world__t : script_library_class::function {
    slf__beam__hit_world__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__kill_all_effects__num__t : script_library_class::function {
    slf__beam__kill_all_effects__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABAC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__kill_effect__num__num__t : script_library_class::function {
    slf__beam__kill_effect__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABA4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_additive__num__t : script_library_class::function {
    slf__beam__set_additive__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB64;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_collide_beamable__num__t : script_library_class::function {
    slf__beam__set_collide_beamable__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB54;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_collide_hero__num__t : script_library_class::function {
    slf__beam__set_collide_hero__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB44;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_collide_world__num__t : script_library_class::function {
    slf__beam__set_collide_world__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB4C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_color__num__num__num__num__t : script_library_class::function {
    slf__beam__set_color__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_detect_stealth__num__t : script_library_class::function {
    slf__beam__set_detect_stealth__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_material__str__t : script_library_class::function {
    slf__beam__set_material__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB84;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_max_length__num__t : script_library_class::function {
    slf__beam__set_max_length__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_no_collision__t : script_library_class::function {
    slf__beam__set_no_collision__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB5C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_point_to_point__vector3d__vector3d__t : script_library_class::function {
    slf__beam__set_point_to_point__vector3d__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB6C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_thickness__num__t : script_library_class::function {
    slf__beam__set_thickness__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_tiles_per_meter__num__t : script_library_class::function {
    slf__beam__set_tiles_per_meter__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB7C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__beam__set_uv_anim__num__num__t : script_library_class::function {
    slf__beam__set_uv_anim__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AB74;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__critical_section__critical_section__num__t : script_library_class::function {
    slf__critical_section__critical_section__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7E8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__cut_scene__wait_play__t : script_library_class::function {
    slf__cut_scene__wait_play__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B7D8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__cut_scene__wait_play__entity_list__t : script_library_class::function {
    slf__cut_scene__wait_play__entity_list__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B7E0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_handler__t : script_library_class::function {
    slf__debug_menu_entry__get_handler__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C744;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_id__t : script_library_class::function {
    slf__debug_menu_entry__get_id__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C734;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_max_value__t : script_library_class::function {
    slf__debug_menu_entry__get_max_value__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C784;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_min_value__t : script_library_class::function {
    slf__debug_menu_entry__get_min_value__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C774;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_name__t : script_library_class::function {
    slf__debug_menu_entry__get_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C724;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_step_scale__t : script_library_class::function {
    slf__debug_menu_entry__get_step_scale__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_step_size__t : script_library_class::function {
    slf__debug_menu_entry__get_step_size__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C794;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_value__t : script_library_class::function {
    slf__debug_menu_entry__get_value__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C754;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__get_value_type__t : script_library_class::function {
    slf__debug_menu_entry__get_value_type__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C764;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_handler__str__t : script_library_class::function {
    slf__debug_menu_entry__set_handler__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C74C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_id__num__t : script_library_class::function {
    slf__debug_menu_entry__set_id__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C73C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_max_value__num__t : script_library_class::function {
    slf__debug_menu_entry__set_max_value__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C78C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_min_value__num__t : script_library_class::function {
    slf__debug_menu_entry__set_min_value__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C77C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_name__str__t : script_library_class::function {
    slf__debug_menu_entry__set_name__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C72C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_step_scale__num__t : script_library_class::function {
    slf__debug_menu_entry__set_step_scale__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_step_size__num__t : script_library_class::function {
    slf__debug_menu_entry__set_step_size__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C79C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_value__num__t : script_library_class::function {
    slf__debug_menu_entry__set_value__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C75C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__debug_menu_entry__set_value_type__num__t : script_library_class::function {
    slf__debug_menu_entry__set_value_type__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C76C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__contains_point__vector3d__t : script_library_class::function {
    slf__district__contains_point__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C838;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__district__num__t : script_library_class::function {
    slf__district__district__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7F0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__district__str__t : script_library_class::function {
    slf__district__district__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7F8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__get_id__t : script_library_class::function {
    slf__district__get_id__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C818;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__get_name__t : script_library_class::function {
    slf__district__get_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C850;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__get_neighborhood__t : script_library_class::function {
    slf__district__get_neighborhood__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C868;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__get_num_missions__str__t : script_library_class::function {
    slf__district__get_num_missions__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C860;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__get_variant__t : script_library_class::function {
    slf__district__get_variant__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C840;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__get_variant_count__t : script_library_class::function {
    slf__district__get_variant_count__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C848;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__is_in_neighborhood__num__t : script_library_class::function {
    slf__district__is_in_neighborhood__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C870;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__is_loaded__t : script_library_class::function {
    slf__district__is_loaded__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C820;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__is_locked__t : script_library_class::function {
    slf__district__is_locked__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C828;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__lock__t : script_library_class::function {
    slf__district__lock__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C800;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__purge__t : script_library_class::function {
    slf__district__purge__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C810;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__set_variant__num__t : script_library_class::function {
    slf__district__set_variant__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C858;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__unlock__t : script_library_class::function {
    slf__district__unlock__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C808;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__district__wait_for_load__t : script_library_class::function {
    slf__district__wait_for_load__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C830;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__abs_snap_to__entity__t : script_library_class::function {
    slf__entity__abs_snap_to__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__add_collision_ignorance__entity__t : script_library_class::function {
    slf__entity__add_collision_ignorance__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF94;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__add_exclusive_interactor__string_hash__interactable_interface__t : script_library_class::function {
    slf__entity__add_exclusive_interactor__string_hash__interactable_interface__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__add_item__entity__t : script_library_class::function {
    slf__entity__add_item__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF44;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__add_selectable_target__entity__t : script_library_class::function {
    slf__entity__add_selectable_target__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B17C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__add_vehicle_to_traffic_system__num__t : script_library_class::function {
    slf__entity__add_vehicle_to_traffic_system__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B474;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_get_viseme_morph_set__str__str__t : script_library_class::function {
    slf__entity__ai_get_viseme_morph_set__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_get_viseme_stream__str__t : script_library_class::function {
    slf__entity__ai_get_viseme_stream__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_is_speaking__t : script_library_class::function {
    slf__entity__ai_is_speaking__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B40C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_run_lip_sync__str__t : script_library_class::function {
    slf__entity__ai_run_lip_sync__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_say_file__str__num__num__t : script_library_class::function {
    slf__entity__ai_say_file__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_say_gab__str__num__num__t : script_library_class::function {
    slf__entity__ai_say_gab__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B424;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_say_sound_group__str__num__num__t : script_library_class::function {
    slf__entity__ai_say_sound_group__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B414;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_shut_up__t : script_library_class::function {
    slf__entity__ai_shut_up__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B404;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_come_on_camera__vector3d__num__t : script_library_class::function {
    slf__entity__ai_traffic_come_on_camera__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_come_on_camera__vector3d__vector3d__num__t : script_library_class::function {
    slf__entity__ai_traffic_come_on_camera__vector3d__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_follow_entity__entity__num__t : script_library_class::function {
    slf__entity__ai_traffic_follow_entity__entity__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_follow_vehicle__entity__t : script_library_class::function {
    slf__entity__ai_traffic_follow_vehicle__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B304;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_get_value__num__t : script_library_class::function {
    slf__entity__ai_traffic_get_value__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_get_value__num__num__t : script_library_class::function {
    slf__entity__ai_traffic_get_value__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_goto__vector3d__num__num__num__t : script_library_class::function {
    slf__entity__ai_traffic_goto__vector3d__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_set_value__num__num__t : script_library_class::function {
    slf__entity__ai_traffic_set_value__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_spawn_away_from__vector3d__num__t : script_library_class::function {
    slf__entity__ai_traffic_spawn_away_from__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_spawn_behind__entity__t : script_library_class::function {
    slf__entity__ai_traffic_spawn_behind__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_traffic_spawn_near__vector3d__t : script_library_class::function {
    slf__entity__ai_traffic_spawn_near__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_voice_box_set_team_respect__string_hash__num__t : script_library_class::function {
    slf__entity__ai_voice_box_set_team_respect__string_hash__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_wait_say_file__str__num__num__t : script_library_class::function {
    slf__entity__ai_wait_say_file__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_wait_say_gab__str__num__num__t : script_library_class::function {
    slf__entity__ai_wait_say_gab__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B42C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_wait_say_preregistered_file__str__num__num__t : script_library_class::function {
    slf__entity__ai_wait_say_preregistered_file__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ai_wait_say_sound_group__str__num__num__t : script_library_class::function {
    slf__entity__ai_wait_say_sound_group__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B41C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__anim_finished__t : script_library_class::function {
    slf__entity__anim_finished__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AEC4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__anim_finished__num__t : script_library_class::function {
    slf__entity__anim_finished__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AECC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__apply_continuous_rotation__vector3d__num__num__t : script_library_class::function {
    slf__entity__apply_continuous_rotation__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACA4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__apply_damage__num__t : script_library_class::function {
    slf__entity__apply_damage__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADBC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__apply_directed_damage__num__vector3d__t : script_library_class::function {
    slf__entity__apply_directed_damage__num__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADD4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__apply_directed_damage_cat__num__vector3d__str__num__t : script_library_class::function {
    slf__entity__apply_directed_damage_cat__num__vector3d__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADDC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__apply_explosive_damage__num__vector3d__t : script_library_class::function {
    slf__entity__apply_explosive_damage__num__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADE4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__apply_explosive_damage__num__vector3d__vector3d__t : script_library_class::function {
    slf__entity__apply_explosive_damage__num__vector3d__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADEC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__apply_subdue__num__t : script_library_class::function {
    slf__entity__apply_subdue__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADC4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__camera_get_target__t : script_library_class::function {
    slf__entity__camera_get_target__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE44;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__camera_orbit__vector3d__num__num__num__t : script_library_class::function {
    slf__entity__camera_orbit__vector3d__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE74;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__camera_set_collide_with_world__num__t : script_library_class::function {
    slf__entity__camera_set_collide_with_world__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE5C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__camera_set_roll__num__t : script_library_class::function {
    slf__entity__camera_set_roll__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE4C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__camera_set_target__vector3d__t : script_library_class::function {
    slf__entity__camera_set_target__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__camera_slide_to__vector3d__vector3d__num__num__t : script_library_class::function {
    slf__entity__camera_slide_to__vector3d__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE64;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__camera_slide_to_orbit__vector3d__num__num__num__num__t : script_library_class::function {
    slf__entity__camera_slide_to_orbit__vector3d__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE6C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__cancel_tether__t : script_library_class::function {
    slf__entity__cancel_tether__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__car_random_body_and_color__t : script_library_class::function {
    slf__entity__car_random_body_and_color__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__change_ai_base_machine__str__t : script_library_class::function {
    slf__entity__change_ai_base_machine__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B144;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__collisions_enabled__t : script_library_class::function {
    slf__entity__collisions_enabled__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B43C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__compute_sector__t : script_library_class::function {
    slf__entity__compute_sector__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABE4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__create_damage_interface__t : script_library_class::function {
    slf__entity__create_damage_interface__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B34C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__create_interactable_ifc__t : script_library_class::function {
    slf__entity__create_interactable_ifc__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__create_physical_interface__t : script_library_class::function {
    slf__entity__create_physical_interface__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B344;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__create_script_data_interface__t : script_library_class::function {
    slf__entity__create_script_data_interface__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B334;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__create_web_ifc__str__num__num__t : script_library_class::function {
    slf__entity__create_web_ifc__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B534;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__disable_as_target__t : script_library_class::function {
    slf__entity__disable_as_target__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B14C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__disable_collisions__t : script_library_class::function {
    slf__entity__disable_collisions__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF84;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__disable_fading__t : script_library_class::function {
    slf__entity__disable_fading__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADB4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__disgorge_items__t : script_library_class::function {
    slf__entity__disgorge_items__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF74;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__enable_as_target__t : script_library_class::function {
    slf__entity__enable_as_target__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B154;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__enable_collisions__t : script_library_class::function {
    slf__entity__enable_collisions__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF8C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__enable_collisions__num__t : script_library_class::function {
    slf__entity__enable_collisions__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B434;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__eye_check_ent__entity__t : script_library_class::function {
    slf__entity__eye_check_ent__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B054;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__eye_check_pos__vector3d__t : script_library_class::function {
    slf__entity__eye_check_pos__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B04C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__force_activate_interaction__string_hash__interactable_interface__t : script_library_class::function {
    slf__entity__force_activate_interaction__string_hash__interactable_interface__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B62C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__force_current_region__t : script_library_class::function {
    slf__entity__force_current_region__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__force_region__entity__t : script_library_class::function {
    slf__entity__force_region__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_abs_position__t : script_library_class::function {
    slf__entity__get_abs_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABCC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ai_base_machine_name__t : script_library_class::function {
    slf__entity__get_ai_base_machine_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B16C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ai_param_float__str__t : script_library_class::function {
    slf__entity__get_ai_param_float__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B074;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ai_param_hash__str__t : script_library_class::function {
    slf__entity__get_ai_param_hash__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B08C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ai_param_int__str__t : script_library_class::function {
    slf__entity__get_ai_param_int__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B07C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ai_param_str__str__t : script_library_class::function {
    slf__entity__get_ai_param_str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B084;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ai_param_vector3d__str__t : script_library_class::function {
    slf__entity__get_ai_param_vector3d__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B094;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ai_signaller__t : script_library_class::function {
    slf__entity__get_ai_signaller__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF6C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_anchor_point__t : script_library_class::function {
    slf__entity__get_anchor_point__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_carry_slave__t : script_library_class::function {
    slf__entity__get_carry_slave__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B19C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_current_animation_name__t : script_library_class::function {
    slf__entity__get_current_animation_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B044;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_damage_force__t : script_library_class::function {
    slf__entity__get_damage_force__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABD4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_debug_name__t : script_library_class::function {
    slf__entity__get_debug_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B444;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_detonate_position__t : script_library_class::function {
    slf__entity__get_detonate_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABDC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_district__t : script_library_class::function {
    slf__entity__get_district__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B024;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_facing__t : script_library_class::function {
    slf__entity__get_facing__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABEC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_fade_timer__t : script_library_class::function {
    slf__entity__get_fade_timer__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_first_child__t : script_library_class::function {
    slf__entity__get_first_child__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC4C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_hash_name__t : script_library_class::function {
    slf__entity__get_hash_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B44C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_hidey_pos__vector3d__num__t : script_library_class::function {
    slf__entity__get_hidey_pos__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ifc_num__str__t : script_library_class::function {
    slf__entity__get_ifc_num__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B284;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ifc_str__str__t : script_library_class::function {
    slf__entity__get_ifc_str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ifc_vec__str__t : script_library_class::function {
    slf__entity__get_ifc_vec__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B294;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_ifl_frame__t : script_library_class::function {
    slf__entity__get_ifl_frame__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B03C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_inode_param_float__str__str__t : script_library_class::function {
    slf__entity__get_inode_param_float__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_inode_param_hash__str__str__t : script_library_class::function {
    slf__entity__get_inode_param_hash__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_inode_param_int__str__str__t : script_library_class::function {
    slf__entity__get_inode_param_int__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_inode_param_str__str__str__t : script_library_class::function {
    slf__entity__get_inode_param_str__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_inode_param_vector3d__str__str__t : script_library_class::function {
    slf__entity__get_inode_param_vector3d__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_interactable_ifc__t : script_library_class::function {
    slf__entity__get_interactable_ifc__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_item__num__t : script_library_class::function {
    slf__entity__get_item__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF54;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_item_by_name__str__t : script_library_class::function {
    slf__entity__get_item_by_name__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF5C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_item_quantity__num__t : script_library_class::function {
    slf__entity__get_item_quantity__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF64;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_last_anchor__t : script_library_class::function {
    slf__entity__get_last_anchor__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_last_attacker__t : script_library_class::function {
    slf__entity__get_last_attacker__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_last_item_used__t : script_library_class::function {
    slf__entity__get_last_item_used__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B20C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_member__str__t : script_library_class::function {
    slf__entity__get_member__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE8C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_next_sibling__t : script_library_class::function {
    slf__entity__get_next_sibling__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC54;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_num_items__t : script_library_class::function {
    slf__entity__get_num_items__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF4C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_parent__t : script_library_class::function {
    slf__entity__get_parent__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC44;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_pendulum_length__t : script_library_class::function {
    slf__entity__get_pendulum_length__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_rel_position__t : script_library_class::function {
    slf__entity__get_rel_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_rel_velocity__entity__t : script_library_class::function {
    slf__entity__get_rel_velocity__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_render_alpha__t : script_library_class::function {
    slf__entity__get_render_alpha__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B254;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_render_color__t : script_library_class::function {
    slf__entity__get_render_color__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B24C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_scripted_target__t : script_library_class::function {
    slf__entity__get_scripted_target__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B194;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_sector_name__t : script_library_class::function {
    slf__entity__get_sector_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_state__num__t : script_library_class::function {
    slf__entity__get_state__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B56C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_time_dilation__t : script_library_class::function {
    slf__entity__get_time_dilation__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B314;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_time_mode__t : script_library_class::function {
    slf__entity__get_time_mode__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B324;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_x_facing__t : script_library_class::function {
    slf__entity__get_x_facing__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABF4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_y_facing__t : script_library_class::function {
    slf__entity__get_y_facing__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ABFC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__get_z_facing__t : script_library_class::function {
    slf__entity__get_z_facing__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__has_carry_slave__t : script_library_class::function {
    slf__entity__has_carry_slave__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__has_member__str__t : script_library_class::function {
    slf__entity__has_member__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE94;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__has_script_data_interface__t : script_library_class::function {
    slf__entity__has_script_data_interface__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B33C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__hates__entity__t : script_library_class::function {
    slf__entity__hates__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B51C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ifl_damage_lock__num__t : script_library_class::function {
    slf__entity__ifl_damage_lock__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B004;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ifl_lock__num__t : script_library_class::function {
    slf__entity__ifl_lock__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B00C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ifl_pause__t : script_library_class::function {
    slf__entity__ifl_pause__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B014;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__ifl_play__t : script_library_class::function {
    slf__entity__ifl_play__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B01C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__in_sector__vector3d__vector3d__num__t : script_library_class::function {
    slf__entity__in_sector__vector3d__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__inhibit_universal_soldier_ability__str__num__t : script_library_class::function {
    slf__entity__inhibit_universal_soldier_ability__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B174;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__invoke_facial_expression__num__num__num__num__t : script_library_class::function {
    slf__entity__invoke_facial_expression__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__is_a_car__t : script_library_class::function {
    slf__entity__is_a_car__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD5C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__is_picked_up__t : script_library_class::function {
    slf__entity__is_picked_up__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__is_suspended__t : script_library_class::function {
    slf__entity__is_suspended__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B45C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__is_throwable__t : script_library_class::function {
    slf__entity__is_throwable__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD64;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__is_valid__t : script_library_class::function {
    slf__entity__is_valid__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B464;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__is_visible__t : script_library_class::function {
    slf__entity__is_visible__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD74;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__kill_anim_in_slot__num__t : script_library_class::function {
    slf__entity__kill_anim_in_slot__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AEBC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__likes__entity__t : script_library_class::function {
    slf__entity__likes__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B524;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__look_at__vector3d__t : script_library_class::function {
    slf__entity__look_at__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC7C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__motion_blur_off__t : script_library_class::function {
    slf__entity__motion_blur_off__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADFC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__motion_blur_on__num__num__num__t : script_library_class::function {
    slf__entity__motion_blur_on__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADF4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__motion_trail_off__t : script_library_class::function {
    slf__entity__motion_trail_off__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__motion_trail_on__entity__entity__vector3d__num__num__num__num__t : script_library_class::function {
    slf__entity__motion_trail_on__entity__entity__vector3d__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__motion_trail_on__entity__str__num__num__vector3d__num__num__num__num__t : script_library_class::function {
    slf__entity__motion_trail_on__entity__str__num__num__vector3d__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__neutral__entity__t : script_library_class::function {
    slf__entity__neutral__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B52C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__operator_not_equals__entity__t : script_library_class::function {
    slf__entity__operator_not_equals__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__operator_equals_equals__entity__t : script_library_class::function {
    slf__entity__operator_equals_equals__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_add_particle__str__t : script_library_class::function {
    slf__entity__physical_ifc_add_particle__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_apply_force__vector3d__num__t : script_library_class::function {
    slf__entity__physical_ifc_apply_force__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B354;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_cancel_all_velocity__t : script_library_class::function {
    slf__entity__physical_ifc_cancel_all_velocity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B36C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_clear_pendulum__t : script_library_class::function {
    slf__entity__physical_ifc_clear_pendulum__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_get_attached_particle_name__t : script_library_class::function {
    slf__entity__physical_ifc_get_attached_particle_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_get_bounce_particle_name__t : script_library_class::function {
    slf__entity__physical_ifc_get_bounce_particle_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_is_biped_physics_running__t : script_library_class::function {
    slf__entity__physical_ifc_is_biped_physics_running__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B374;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_is_effectively_standing__t : script_library_class::function {
    slf__entity__physical_ifc_is_effectively_standing__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B35C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_is_prop_physics_at_rest__t : script_library_class::function {
    slf__entity__physical_ifc_is_prop_physics_at_rest__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_is_prop_physics_running__t : script_library_class::function {
    slf__entity__physical_ifc_is_prop_physics_running__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_manage_standing__num__t : script_library_class::function {
    slf__entity__physical_ifc_manage_standing__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B364;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_set_allow_biped_physics__num__t : script_library_class::function {
    slf__entity__physical_ifc_set_allow_biped_physics__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B38C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_set_attached_particle_name__str__t : script_library_class::function {
    slf__entity__physical_ifc_set_attached_particle_name__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_set_bounce_particle_name__str__t : script_library_class::function {
    slf__entity__physical_ifc_set_bounce_particle_name__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_set_pendulum__entity__num__t : script_library_class::function {
    slf__entity__physical_ifc_set_pendulum__entity__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B39C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_set_pendulum__vector3d__num__t : script_library_class::function {
    slf__entity__physical_ifc_set_pendulum__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B394;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_start_biped_physics__t : script_library_class::function {
    slf__entity__physical_ifc_start_biped_physics__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B37C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_start_prop_physics__vector3d__num__t : script_library_class::function {
    slf__entity__physical_ifc_start_prop_physics__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B494;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_stop_biped_physics__t : script_library_class::function {
    slf__entity__physical_ifc_stop_biped_physics__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B384;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__physical_ifc_stop_prop_physics__t : script_library_class::function {
    slf__entity__physical_ifc_stop_prop_physics__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B49C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__play_anim__str__t : script_library_class::function {
    slf__entity__play_anim__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AEA4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__play_anim__str__num__num__t : script_library_class::function {
    slf__entity__play_anim__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AEAC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__poison__num__num__t : script_library_class::function {
    slf__entity__poison__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__pop_ai_base_machine__t : script_library_class::function {
    slf__entity__pop_ai_base_machine__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B164;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__pre_roll__num__t : script_library_class::function {
    slf__entity__pre_roll__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B55C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__push_ai_base_machine__str__t : script_library_class::function {
    slf__entity__push_ai_base_machine__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B15C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__randomize_position__vector3d__num__num__num__t : script_library_class::function {
    slf__entity__randomize_position__vector3d__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__regenerate__num__num__t : script_library_class::function {
    slf__entity__regenerate__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__rel_angle__vector3d__t : script_library_class::function {
    slf__entity__rel_angle__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__remove_collision_ignorance__entity__t : script_library_class::function {
    slf__entity__remove_collision_ignorance__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF9C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__remove_exclusive_interactor__string_hash__interactable_interface__t : script_library_class::function {
    slf__entity__remove_exclusive_interactor__string_hash__interactable_interface__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__remove_selectable_target__entity__t : script_library_class::function {
    slf__entity__remove_selectable_target__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B184;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__remove_vehicle_from_traffic_system__t : script_library_class::function {
    slf__entity__remove_vehicle_from_traffic_system__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B47C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__reset_ai__t : script_library_class::function {
    slf__entity__reset_ai__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B06C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__restart__t : script_library_class::function {
    slf__entity__restart__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B564;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__seriously_kill__t : script_library_class::function {
    slf__entity__seriously_kill__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADCC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_abs_xz_facing__vector3d__t : script_library_class::function {
    slf__entity__set_abs_xz_facing__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC94;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_active__num__t : script_library_class::function {
    slf__entity__set_active__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD9C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ai_param_float__str__num__t : script_library_class::function {
    slf__entity__set_ai_param_float__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B09C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ai_param_float_variance__str__num__num__t : script_library_class::function {
    slf__entity__set_ai_param_float_variance__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ai_param_hash__str__num__t : script_library_class::function {
    slf__entity__set_ai_param_hash__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ai_param_hash__str__str__t : script_library_class::function {
    slf__entity__set_ai_param_hash__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ai_param_hash__str__string_hash__t : script_library_class::function {
    slf__entity__set_ai_param_hash__str__string_hash__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ai_param_int__str__num__t : script_library_class::function {
    slf__entity__set_ai_param_int__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ai_param_str__str__str__t : script_library_class::function {
    slf__entity__set_ai_param_str__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ai_param_vector3d__str__vector3d__t : script_library_class::function {
    slf__entity__set_ai_param_vector3d__str__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B0D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ambient_factor__vector3d__t : script_library_class::function {
    slf__entity__set_ambient_factor__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B32C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_anchor_activated__num__t : script_library_class::function {
    slf__entity__set_anchor_activated__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFA4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_car_combat_info__num__num__num__num__num__num__num__num__t : script_library_class::function {
    slf__entity__set_car_combat_info__num__num__num__num__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_crawlable__num__t : script_library_class::function {
    slf__entity__set_crawlable__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD84;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_default_variant__t : script_library_class::function {
    slf__entity__set_default_variant__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B544;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_distance_clip__num__t : script_library_class::function {
    slf__entity__set_distance_clip__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADAC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_entity_blur__num__t : script_library_class::function {
    slf__entity__set_entity_blur__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B224;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_facing__vector3d__vector3d__t : script_library_class::function {
    slf__entity__set_facing__vector3d__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC8C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_fade_timer__num__t : script_library_class::function {
    slf__entity__set_fade_timer__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_hires_shadow__num__t : script_library_class::function {
    slf__entity__set_hires_shadow__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD4C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ifc_num__str__num__t : script_library_class::function {
    slf__entity__set_ifc_num__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B28C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ifc_str__str__str__t : script_library_class::function {
    slf__entity__set_ifc_str__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B2AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ifc_vec__str__vector3d__t : script_library_class::function {
    slf__entity__set_ifc_vec__str__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B29C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_ignore_limbo__num__t : script_library_class::function {
    slf__entity__set_ignore_limbo__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B4E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_immobile__num__t : script_library_class::function {
    slf__entity__set_immobile__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B484;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_inode_param_entity__str__str__entity__t : script_library_class::function {
    slf__entity__set_inode_param_entity__str__str__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B11C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_inode_param_float__str__str__num__t : script_library_class::function {
    slf__entity__set_inode_param_float__str__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B104;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_inode_param_float_variance__str__str__num__num__t : script_library_class::function {
    slf__entity__set_inode_param_float_variance__str__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B10C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_inode_param_hash__str__str__num__t : script_library_class::function {
    slf__entity__set_inode_param_hash__str__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B134;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_inode_param_hash__str__str__str__t : script_library_class::function {
    slf__entity__set_inode_param_hash__str__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B12C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_inode_param_int__str__str__num__t : script_library_class::function {
    slf__entity__set_inode_param_int__str__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B114;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_inode_param_str__str__str__str__t : script_library_class::function {
    slf__entity__set_inode_param_str__str__str__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B124;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_inode_param_vector3d__str__str__vector3d__t : script_library_class::function {
    slf__entity__set_inode_param_vector3d__str__str__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B13C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_invulnerable__num__t : script_library_class::function {
    slf__entity__set_invulnerable__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD44;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_kill_ent_on_destroy__num__t : script_library_class::function {
    slf__entity__set_kill_ent_on_destroy__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B48C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_member_hidden__num__t : script_library_class::function {
    slf__entity__set_member_hidden__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE9C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_parent__entity__t : script_library_class::function {
    slf__entity__set_parent__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_parent_rel__entity__t : script_library_class::function {
    slf__entity__set_parent_rel__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC5C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_path_graph__str__t : script_library_class::function {
    slf__entity__set_path_graph__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B214;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_path_graph_start_node__num__t : script_library_class::function {
    slf__entity__set_path_graph_start_node__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B21C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_pendulum_attach_limb__num__t : script_library_class::function {
    slf__entity__set_pendulum_attach_limb__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_pendulum_length__num__t : script_library_class::function {
    slf__entity__set_pendulum_length__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B3AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_physical__num__t : script_library_class::function {
    slf__entity__set_physical__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ADA4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_po_facing__vector3d__t : script_library_class::function {
    slf__entity__set_po_facing__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC9C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_rel_position__vector3d__t : script_library_class::function {
    slf__entity__set_rel_position__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC64;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_render_alpha__num__t : script_library_class::function {
    slf__entity__set_render_alpha__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B244;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_render_color__vector3d__t : script_library_class::function {
    slf__entity__set_render_color__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B23C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_render_scale__vector3d__t : script_library_class::function {
    slf__entity__set_render_scale__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B22C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_scale__num__t : script_library_class::function {
    slf__entity__set_scale__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B274;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_scripted_target__entity__t : script_library_class::function {
    slf__entity__set_scripted_target__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B18C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_see_thru__num__t : script_library_class::function {
    slf__entity__set_see_thru__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD94;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_special_target__num__t : script_library_class::function {
    slf__entity__set_special_target__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B454;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_state__num__num__t : script_library_class::function {
    slf__entity__set_state__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B574;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_targetting__num__t : script_library_class::function {
    slf__entity__set_targetting__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD54;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_throwable__num__t : script_library_class::function {
    slf__entity__set_throwable__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD6C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_time_dilation__num__t : script_library_class::function {
    slf__entity__set_time_dilation__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B30C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_time_mode__num__t : script_library_class::function {
    slf__entity__set_time_mode__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B31C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_variant__string_hash__t : script_library_class::function {
    slf__entity__set_variant__string_hash__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B53C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_velocity__vector3d__t : script_library_class::function {
    slf__entity__set_velocity__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC74;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_visible__num__t : script_library_class::function {
    slf__entity__set_visible__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD7C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_visible_and_disable_fading__num__t : script_library_class::function {
    slf__entity__set_visible_and_disable_fading__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD8C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__set_xz_facing__vector3d__t : script_library_class::function {
    slf__entity__set_xz_facing__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC84;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__setup_tether__vector3d__num__t : script_library_class::function {
    slf__entity__setup_tether__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__snap_to__entity__t : script_library_class::function {
    slf__entity__snap_to__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__suspend__t : script_library_class::function {
    slf__entity__suspend__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AF7C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__teleport_to_point__vector3d__t : script_library_class::function {
    slf__entity__teleport_to_point__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AC6C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__unforce_regions__t : script_library_class::function {
    slf__entity__unforce_regions__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AD2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__unsuspend__t : script_library_class::function {
    slf__entity__unsuspend__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFAC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__use_item__str__t : script_library_class::function {
    slf__entity__use_item__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__use_item_by_id__str__t : script_library_class::function {
    slf__entity__use_item_by_id__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B204;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_camera_set_roll__num__num__t : script_library_class::function {
    slf__entity__wait_camera_set_roll__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE54;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_change_color__vector3d__vector3d__num__t : script_library_class::function {
    slf__entity__wait_change_color__vector3d__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE7C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_change_range__num__num__num__t : script_library_class::function {
    slf__entity__wait_change_range__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE84;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_change_render_color__vector3d__num__num__t : script_library_class::function {
    slf__entity__wait_change_render_color__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B25C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_change_render_scale__vector3d__num__t : script_library_class::function {
    slf__entity__wait_change_render_scale__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B234;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_for_not_sector__str__t : script_library_class::function {
    slf__entity__wait_for_not_sector__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFEC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_for_pickup__t : script_library_class::function {
    slf__entity__wait_for_pickup__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFB4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_for_sector__str__t : script_library_class::function {
    slf__entity__wait_for_sector__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFE4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_lookat__vector3d__num__t : script_library_class::function {
    slf__entity__wait_lookat__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B26C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_lookat2__entity__entity__vector3d__num__t : script_library_class::function {
    slf__entity__wait_lookat2__entity__entity__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B264;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_looping_anim__str__num__num__t : script_library_class::function {
    slf__entity__wait_looping_anim__str__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B1F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_play_anim__str__num__num__num__t : script_library_class::function {
    slf__entity__wait_play_anim__str__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AEB4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_prox__entity__num__t : script_library_class::function {
    slf__entity__wait_prox__entity__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFBC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_prox__vector3d__num__t : script_library_class::function {
    slf__entity__wait_prox__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFC4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_prox__vector3d__num__vector3d__num__t : script_library_class::function {
    slf__entity__wait_prox__vector3d__num__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFCC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_prox_maxY__vector3d__num__num__t : script_library_class::function {
    slf__entity__wait_prox_maxY__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFDC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_prox_minY__vector3d__num__num__t : script_library_class::function {
    slf__entity__wait_prox_minY__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFD4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_prox_sector__vector3d__num__str__t : script_library_class::function {
    slf__entity__wait_prox_sector__vector3d__num__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AFF4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_rotate__vector3d__num__num__t : script_library_class::function {
    slf__entity__wait_rotate__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACAC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_rotate_WCS__vector3d__vector3d__num__num__t : script_library_class::function {
    slf__entity__wait_rotate_WCS__vector3d__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACBC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_rotate_WCS_cosmetic__vector3d__vector3d__num__num__t : script_library_class::function {
    slf__entity__wait_rotate_WCS_cosmetic__vector3d__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACCC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_rotate_WCS_with_compute_sector__vector3d__vector3d__num__num__t : script_library_class::function {
    slf__entity__wait_rotate_WCS_with_compute_sector__vector3d__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACC4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_rotate_cosmetic__vector3d__num__num__t : script_library_class::function {
    slf__entity__wait_rotate_cosmetic__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACB4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_set_scale__num__num__t : script_library_class::function {
    slf__entity__wait_set_scale__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B27C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_translate__vector3d__num__t : script_library_class::function {
    slf__entity__wait_translate__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACD4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_translate_WCS__vector3d__num__t : script_library_class::function {
    slf__entity__wait_translate_WCS__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACEC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_translate_WCS_cosmetic__vector3d__num__t : script_library_class::function {
    slf__entity__wait_translate_WCS_cosmetic__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACFC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_translate_WCS_with_compute_sector__vector3d__num__t : script_library_class::function {
    slf__entity__wait_translate_WCS_with_compute_sector__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACF4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_translate_cosmetic__vector3d__num__t : script_library_class::function {
    slf__entity__wait_translate_cosmetic__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACE4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__wait_translate_with_compute_sector__vector3d__num__t : script_library_class::function {
    slf__entity__wait_translate_with_compute_sector__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089ACDC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity__was_occluded_last_frame__t : script_library_class::function {
    slf__entity__was_occluded_last_frame__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089AE24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list__add__entity__t : script_library_class::function {
    slf__entity_list__add__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFE4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list__begin__t : script_library_class::function {
    slf__entity_list__begin__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFFC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list__end__t : script_library_class::function {
    slf__entity_list__end__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C004;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list__get_index__num__t : script_library_class::function {
    slf__entity_list__get_index__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C00C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list__remove__entity__t : script_library_class::function {
    slf__entity_list__remove__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFEC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list__remove__entity_list_iterator__t : script_library_class::function {
    slf__entity_list__remove__entity_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFF4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list__set_index__num__entity__t : script_library_class::function {
    slf__entity_list__set_index__num__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C014;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list__size__t : script_library_class::function {
    slf__entity_list__size__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFDC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list_iterator__get_entity__t : script_library_class::function {
    slf__entity_list_iterator__get_entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C03C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list_iterator__operator_not_equals__entity_list_iterator__t : script_library_class::function {
    slf__entity_list_iterator__operator_not_equals__entity_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C034;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list_iterator__operator_plus_plus__t : script_library_class::function {
    slf__entity_list_iterator__operator_plus_plus__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C01C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list_iterator__operator_minus_munus__t : script_library_class::function {
    slf__entity_list_iterator__operator_minus_munus__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C024;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_list_iterator__operator_equals_equals__entity_list_iterator__t : script_library_class::function {
    slf__entity_list_iterator__operator_equals_equals__entity_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C02C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_tracker__get_entity__t : script_library_class::function {
    slf__entity_tracker__get_entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C55C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_tracker__get_mini_map_active__t : script_library_class::function {
    slf__entity_tracker__get_mini_map_active__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C56C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_tracker__get_poi_active__t : script_library_class::function {
    slf__entity_tracker__get_poi_active__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C58C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_tracker__set_entity__entity__t : script_library_class::function {
    slf__entity_tracker__set_entity__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C554;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_tracker__set_health_widget_active__num__t : script_library_class::function {
    slf__entity_tracker__set_health_widget_active__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C584;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_tracker__set_mini_map_active__num__t : script_library_class::function {
    slf__entity_tracker__set_mini_map_active__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C564;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_tracker__set_poi_active__num__t : script_library_class::function {
    slf__entity_tracker__set_poi_active__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C57C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__entity_tracker__set_poi_icon__num__t : script_library_class::function {
    slf__entity_tracker__set_poi_icon__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C574;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__glamour_cam__set_angle__num__num__num__num__t : script_library_class::function {
    slf__glamour_cam__set_angle__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B788;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__glamour_cam__set_look_at_bone__str__t : script_library_class::function {
    slf__glamour_cam__set_look_at_bone__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B7A0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__glamour_cam__set_position_bone__str__t : script_library_class::function {
    slf__glamour_cam__set_position_bone__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B798;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__glamour_cam__set_target__entity__t : script_library_class::function {
    slf__glamour_cam__set_target__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B790;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__gun__get_blaster_beam__t : script_library_class::function {
    slf__gun__get_blaster_beam__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B588;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__gun__get_muzzle_pos__t : script_library_class::function {
    slf__gun__get_muzzle_pos__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B590;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__gun__set_target_info__entity__vector3d__vector3d__t : script_library_class::function {
    slf__gun__set_target_info__entity__vector3d__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B598;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__add_box_trigger__string_hash__num__vector3d__vector3d__t : script_library_class::function {
    slf__interactable_interface__add_box_trigger__string_hash__num__vector3d__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B61C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__add_named_box_trigger__string_hash__str__t : script_library_class::function {
    slf__interactable_interface__add_named_box_trigger__string_hash__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B624;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__add_point_trigger__string_hash__num__vector3d__num__t : script_library_class::function {
    slf__interactable_interface__add_point_trigger__string_hash__num__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B614;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__create_interaction__string_hash__num__t : script_library_class::function {
    slf__interactable_interface__create_interaction__string_hash__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__create_interaction__string_hash__num__str__t : script_library_class::function {
    slf__interactable_interface__create_interaction__string_hash__num__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__disable_interaction__string_hash__t : script_library_class::function {
    slf__interactable_interface__disable_interaction__string_hash__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__enable_interaction__string_hash__t : script_library_class::function {
    slf__interactable_interface__enable_interaction__string_hash__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__nondirectional__string_hash__t : script_library_class::function {
    slf__interactable_interface__nondirectional__string_hash__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B604;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__one_shot__string_hash__t : script_library_class::function {
    slf__interactable_interface__one_shot__string_hash__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__set_activation_button__string_hash__num__t : script_library_class::function {
    slf__interactable_interface__set_activation_button__string_hash__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B5F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__interactable_interface__set_approach__string_hash__num__t : script_library_class::function {
    slf__interactable_interface__set_approach__string_hash__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B60C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__draw__t : script_library_class::function {
    slf__item__draw__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B6A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__get_count__t : script_library_class::function {
    slf__item__get_count__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B63C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__get_last_grenade_armed__t : script_library_class::function {
    slf__item__get_last_grenade_armed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B674;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__get_last_grenade_detonated__t : script_library_class::function {
    slf__item__get_last_grenade_detonated__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B67C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__get_last_grenade_spawned__t : script_library_class::function {
    slf__item__get_last_grenade_spawned__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B66C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__get_launch_force__t : script_library_class::function {
    slf__item__get_launch_force__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B64C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__get_launch_vec__t : script_library_class::function {
    slf__item__get_launch_vec__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B65C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__get_owner__t : script_library_class::function {
    slf__item__get_owner__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B684;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__get_visual_item__t : script_library_class::function {
    slf__item__get_visual_item__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B664;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__holster__t : script_library_class::function {
    slf__item__holster__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B69C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__is_a_grenade__t : script_library_class::function {
    slf__item__is_a_grenade__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B6E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__is_a_gun__t : script_library_class::function {
    slf__item__is_a_gun__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B6DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__is_a_melee__t : script_library_class::function {
    slf__item__is_a_melee__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B6F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__is_a_rocket__t : script_library_class::function {
    slf__item__is_a_rocket__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B6EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__set_count__num__t : script_library_class::function {
    slf__item__set_count__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B634;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__set_damage__num__t : script_library_class::function {
    slf__item__set_damage__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B6CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__set_drawn_limb__str__t : script_library_class::function {
    slf__item__set_drawn_limb__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B68C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__set_holster_limb__str__t : script_library_class::function {
    slf__item__set_holster_limb__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B694;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__set_launch_force__num__t : script_library_class::function {
    slf__item__set_launch_force__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B644;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__set_launch_vec__vector3d__t : script_library_class::function {
    slf__item__set_launch_vec__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B654;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__use__t : script_library_class::function {
    slf__item__use__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B6AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__item__yank_remove__vector3d__num__t : script_library_class::function {
    slf__item__yank_remove__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B6D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__check_collision__num__num__t : script_library_class::function {
    slf__line_info__check_collision__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B718;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__clear_collision__t : script_library_class::function {
    slf__line_info__clear_collision__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B720;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__debug_render__num__t : script_library_class::function {
    slf__line_info__debug_render__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B768;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__did_collide__t : script_library_class::function {
    slf__line_info__did_collide__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B760;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__get_end_pos__t : script_library_class::function {
    slf__line_info__get_end_pos__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B740;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__get_hit_entity__t : script_library_class::function {
    slf__line_info__get_hit_entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B758;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__get_hit_normal__t : script_library_class::function {
    slf__line_info__get_hit_normal__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B750;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__get_hit_pos__t : script_library_class::function {
    slf__line_info__get_hit_pos__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B748;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__get_start_pos__t : script_library_class::function {
    slf__line_info__get_start_pos__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B730;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__set_end_pos__vector3d__t : script_library_class::function {
    slf__line_info__set_end_pos__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B738;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__line_info__set_start_pos__vector3d__t : script_library_class::function {
    slf__line_info__set_start_pos__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B728;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_camera_marker__get_base_position__t : script_library_class::function {
    slf__mission_camera_marker__get_base_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C41C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_camera_marker__get_camera_position__t : script_library_class::function {
    slf__mission_camera_marker__get_camera_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C424;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_camera_transform_marker__get_base_position__t : script_library_class::function {
    slf__mission_camera_transform_marker__get_base_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C45C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_camera_transform_marker__get_camera_position__t : script_library_class::function {
    slf__mission_camera_transform_marker__get_camera_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C464;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_camera_transform_marker__get_forward__t : script_library_class::function {
    slf__mission_camera_transform_marker__get_forward__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C46C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_camera_transform_marker__get_up__t : script_library_class::function {
    slf__mission_camera_transform_marker__get_up__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C474;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_transform_marker__get_base_position__t : script_library_class::function {
    slf__mission_transform_marker__get_base_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C43C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_transform_marker__get_forward__t : script_library_class::function {
    slf__mission_transform_marker__get_forward__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C444;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__mission_transform_marker__get_up__t : script_library_class::function {
    slf__mission_transform_marker__get_up__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C44C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list__add__num__t : script_library_class::function {
    slf__num_list__add__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF6C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list__begin__t : script_library_class::function {
    slf__num_list__begin__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF84;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list__end__t : script_library_class::function {
    slf__num_list__end__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF8C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list__get_index__num__t : script_library_class::function {
    slf__num_list__get_index__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF94;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list__remove__num__t : script_library_class::function {
    slf__num_list__remove__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF74;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list__remove__num_list_iterator__t : script_library_class::function {
    slf__num_list__remove__num_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF7C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list__set_index__num__num__t : script_library_class::function {
    slf__num_list__set_index__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF9C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list__size__t : script_library_class::function {
    slf__num_list__size__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF64;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list_iterator__get_num__t : script_library_class::function {
    slf__num_list_iterator__get_num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFC4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list_iterator__operator_not_equals__num_list_iterator__t : script_library_class::function {
    slf__num_list_iterator__operator_not_equals__num_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFBC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list_iterator__operator_plus_plus__t : script_library_class::function {
    slf__num_list_iterator__operator_plus_plus__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFA4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list_iterator__operator_minus_munus__t : script_library_class::function {
    slf__num_list_iterator__operator_minus_munus__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFAC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__num_list_iterator__operator_equals_equals__num_list_iterator__t : script_library_class::function {
    slf__num_list_iterator__operator_equals_equals__num_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BFB4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__get_abs_position__t : script_library_class::function {
    slf__pfx__get_abs_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__get_parent__t : script_library_class::function {
    slf__pfx__get_parent__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C884;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__get_position__t : script_library_class::function {
    slf__pfx__get_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C894;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__get_rel_position__t : script_library_class::function {
    slf__pfx__get_rel_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__get_rotation__t : script_library_class::function {
    slf__pfx__get_rotation__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__get_scale__t : script_library_class::function {
    slf__pfx__get_scale__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__get_state__num__t : script_library_class::function {
    slf__pfx__get_state__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__get_visible__t : script_library_class::function {
    slf__pfx__get_visible__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__set_abs_position__vector3d__t : script_library_class::function {
    slf__pfx__set_abs_position__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__set_parent__entity__t : script_library_class::function {
    slf__pfx__set_parent__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C88C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__set_position__vector3d__t : script_library_class::function {
    slf__pfx__set_position__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C89C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__set_rel_position__vector3d__t : script_library_class::function {
    slf__pfx__set_rel_position__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__set_rotation__vector3d__t : script_library_class::function {
    slf__pfx__set_rotation__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__set_scale__vector3d__t : script_library_class::function {
    slf__pfx__set_scale__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__set_state__num__num__t : script_library_class::function {
    slf__pfx__set_state__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__pfx__set_visible__num__t : script_library_class::function {
    slf__pfx__set_visible__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C8FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__add_control_pt__vector3d__t : script_library_class::function {
    slf__polytube__add_control_pt__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C108;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__build__num__num__t : script_library_class::function {
    slf__polytube__build__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C140;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__clear__t : script_library_class::function {
    slf__polytube__clear__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C0F8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__clear_simulations__t : script_library_class::function {
    slf__polytube__clear_simulations__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C220;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__create_tentacle__t : script_library_class::function {
    slf__polytube__create_tentacle__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C240;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__destroy_tentacle__t : script_library_class::function {
    slf__polytube__destroy_tentacle__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C248;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_control_pt__num__t : script_library_class::function {
    slf__polytube__get_control_pt__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C118;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_curve_pt__num__t : script_library_class::function {
    slf__polytube__get_curve_pt__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C128;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_ifl_frame__t : script_library_class::function {
    slf__polytube__get_ifl_frame__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1A0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_max_length__t : script_library_class::function {
    slf__polytube__get_max_length__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1D8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_num_control_pts__t : script_library_class::function {
    slf__polytube__get_num_control_pts__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C130;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_num_curve_pts__t : script_library_class::function {
    slf__polytube__get_num_curve_pts__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C138;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_num_sides__t : script_library_class::function {
    slf__polytube__get_num_sides__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1B8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_tiles_per_meter__t : script_library_class::function {
    slf__polytube__get_tiles_per_meter__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1C8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__get_tube_radius__t : script_library_class::function {
    slf__polytube__get_tube_radius__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1A8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__ifl_lock__num__t : script_library_class::function {
    slf__polytube__ifl_lock__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C190;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__ifl_play__t : script_library_class::function {
    slf__polytube__ifl_play__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C198;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__kill_pt_anim__num__num__t : script_library_class::function {
    slf__polytube__kill_pt_anim__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C208;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__rebuild__t : script_library_class::function {
    slf__polytube__rebuild__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C148;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__reserve_control_pts__num__t : script_library_class::function {
    slf__polytube__reserve_control_pts__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C100;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_additive__num__t : script_library_class::function {
    slf__polytube__set_additive__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C120;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_begin_material__str__num__t : script_library_class::function {
    slf__polytube__set_begin_material__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C168;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_begin_material_ifl__str__num__t : script_library_class::function {
    slf__polytube__set_begin_material_ifl__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C180;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_blend_mode__num__t : script_library_class::function {
    slf__polytube__set_blend_mode__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C188;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_control_pt__num__vector3d__t : script_library_class::function {
    slf__polytube__set_control_pt__num__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C110;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_end_material__str__num__t : script_library_class::function {
    slf__polytube__set_end_material__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C160;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_end_material_ifl__str__num__t : script_library_class::function {
    slf__polytube__set_end_material_ifl__str__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C178;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_force_start__num__t : script_library_class::function {
    slf__polytube__set_force_start__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C150;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_material__str__t : script_library_class::function {
    slf__polytube__set_material__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C158;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_material_ifl__str__t : script_library_class::function {
    slf__polytube__set_material_ifl__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C170;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_max_length__num__t : script_library_class::function {
    slf__polytube__set_max_length__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1E0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_num_sides__num__t : script_library_class::function {
    slf__polytube__set_num_sides__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1C0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_pt_anim__num__vector3d__num__num__t : script_library_class::function {
    slf__polytube__set_pt_anim__num__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1F8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_random_pt_anim__num__num__num__num__t : script_library_class::function {
    slf__polytube__set_random_pt_anim__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C200;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_start_v__num__t : script_library_class::function {
    slf__polytube__set_start_v__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1F0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_tiles_per_meter__num__t : script_library_class::function {
    slf__polytube__set_tiles_per_meter__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1D0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__set_tube_radius__num__t : script_library_class::function {
    slf__polytube__set_tube_radius__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1B0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__simulate_slack__vector3d__vector3d__num__t : script_library_class::function {
    slf__polytube__simulate_slack__vector3d__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C210;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__simulate_tether__entity__entity__num__t : script_library_class::function {
    slf__polytube__simulate_tether__entity__entity__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C218;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_add_dangle_engine__num__num__t : script_library_class::function {
    slf__polytube__tentacle_add_dangle_engine__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2A8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_add_follow_engine__num__num__vector3d__num__t : script_library_class::function {
    slf__polytube__tentacle_add_follow_engine__num__num__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2B0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_add_slack_engine__num__num__t : script_library_class::function {
    slf__polytube__tentacle_add_slack_engine__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2B8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_add_strike_engine__vector3d__num__num__t : script_library_class::function {
    slf__polytube__tentacle_add_strike_engine__vector3d__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C298;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_add_swirl_strike_engine__vector3d__num__num__num__num__t : script_library_class::function {
    slf__polytube__tentacle_add_swirl_strike_engine__vector3d__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2A0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_create_line__vector3d__num__t : script_library_class::function {
    slf__polytube__tentacle_create_line__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C280;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_engine_running__num__t : script_library_class::function {
    slf__polytube__tentacle_engine_running__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C290;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_get_end_position__t : script_library_class::function {
    slf__polytube__tentacle_get_end_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C260;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_get_engine_drag__num__t : script_library_class::function {
    slf__polytube__tentacle_get_engine_drag__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2F0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_get_engine_gravity__num__t : script_library_class::function {
    slf__polytube__tentacle_get_engine_gravity__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C300;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_get_engine_length__num__t : script_library_class::function {
    slf__polytube__tentacle_get_engine_length__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2D0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_get_engine_slack_percent__num__t : script_library_class::function {
    slf__polytube__tentacle_get_engine_slack_percent__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2E0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_get_num_positions__t : script_library_class::function {
    slf__polytube__tentacle_get_num_positions__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C268;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_get_position__num__t : script_library_class::function {
    slf__polytube__tentacle_get_position__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C278;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_kill_engine__num__t : script_library_class::function {
    slf__polytube__tentacle_kill_engine__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C288;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_collide__num__t : script_library_class::function {
    slf__polytube__tentacle_set_collide__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C250;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_end_position__vector3d__t : script_library_class::function {
    slf__polytube__tentacle_set_end_position__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C258;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_engine_attach_ent__num__entity__t : script_library_class::function {
    slf__polytube__tentacle_set_engine_attach_ent__num__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2C0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_engine_drag__num__num__t : script_library_class::function {
    slf__polytube__tentacle_set_engine_drag__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2F8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_engine_gravity__num__vector3d__t : script_library_class::function {
    slf__polytube__tentacle_set_engine_gravity__num__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C308;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_engine_length__num__num__t : script_library_class::function {
    slf__polytube__tentacle_set_engine_length__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2D8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_engine_slack_percent__num__num__t : script_library_class::function {
    slf__polytube__tentacle_set_engine_slack_percent__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2E8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_engine_target__num__vector3d__t : script_library_class::function {
    slf__polytube__tentacle_set_engine_target__num__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C2C8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__tentacle_set_position__num__vector3d__t : script_library_class::function {
    slf__polytube__tentacle_set_position__num__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C270;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__polytube__v_animate__num__t : script_library_class::function {
    slf__polytube__v_animate__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C1E8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__get_facing__t : script_library_class::function {
    slf__posfacing3d__get_facing__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA98;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__get_position__t : script_library_class::function {
    slf__posfacing3d__get_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BAA8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__get_rotation__t : script_library_class::function {
    slf__posfacing3d__get_rotation__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BAA0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__operator_not_equals__posfacing3d__t : script_library_class::function {
    slf__posfacing3d__operator_not_equals__posfacing3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BAB8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__operator_plus__posfacing3d__t : script_library_class::function {
    slf__posfacing3d__operator_plus__posfacing3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA88;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__operator_multiply__posfacing3d__t : script_library_class::function {
    slf__posfacing3d__operator_multiply__posfacing3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA90;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__operator_equals_equals__posfacing3d__t : script_library_class::function {
    slf__posfacing3d__operator_equals_equals__posfacing3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BAB0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__posfacing3d__num__num__num__num__t : script_library_class::function {
    slf__posfacing3d__posfacing3d__num__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA68;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__posfacing3d__num__num__num__vector3d__t : script_library_class::function {
    slf__posfacing3d__posfacing3d__num__num__num__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA78;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__posfacing3d__vector3d__num__t : script_library_class::function {
    slf__posfacing3d__posfacing3d__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA70;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__posfacing3d__posfacing3d__vector3d__vector3d__t : script_library_class::function {
    slf__posfacing3d__posfacing3d__vector3d__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA80;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__position3d__operator_assign__vector3d__t : script_library_class::function {
    slf__position3d__operator_assign__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA60;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__position3d__position3d__num__num__num__t : script_library_class::function {
    slf__position3d__position3d__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA58;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_button_pressed__num__t : script_library_class::function {
    slf__script_controller__is_button_pressed__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BCD8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_down_pressed__t : script_library_class::function {
    slf__script_controller__is_down_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BCE8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_left_pressed__t : script_library_class::function {
    slf__script_controller__is_left_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BCF0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_lstick_down_pressed__t : script_library_class::function {
    slf__script_controller__is_lstick_down_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BD28;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_lstick_left_pressed__t : script_library_class::function {
    slf__script_controller__is_lstick_left_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BD30;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_lstick_right_pressed__t : script_library_class::function {
    slf__script_controller__is_lstick_right_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BD38;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_lstick_up_pressed__t : script_library_class::function {
    slf__script_controller__is_lstick_up_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BD20;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_right_pressed__t : script_library_class::function {
    slf__script_controller__is_right_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BCF8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_rstick_down_pressed__t : script_library_class::function {
    slf__script_controller__is_rstick_down_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BD08;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_rstick_left_pressed__t : script_library_class::function {
    slf__script_controller__is_rstick_left_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BD10;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_rstick_right_pressed__t : script_library_class::function {
    slf__script_controller__is_rstick_right_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BD18;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_rstick_up_pressed__t : script_library_class::function {
    slf__script_controller__is_rstick_up_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BD00;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__script_controller__is_up_pressed__t : script_library_class::function {
    slf__script_controller__is_up_pressed__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BCE0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__signaller__clear_callback__str__t : script_library_class::function {
    slf__signaller__clear_callback__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B7F0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__signaller__clear_callbacks__t : script_library_class::function {
    slf__signaller__clear_callbacks__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B7E8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__dampen_guard__t : script_library_class::function {
    slf__sound_inst__dampen_guard__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B880;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__fade_in__num__num__t : script_library_class::function {
    slf__sound_inst__fade_in__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B898;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__fade_out__num__t : script_library_class::function {
    slf__sound_inst__fade_out__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8A0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__fade_to__num__num__t : script_library_class::function {
    slf__sound_inst__fade_to__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B890;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__get_doppler__t : script_library_class::function {
    slf__sound_inst__get_doppler__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B878;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__get_entity__t : script_library_class::function {
    slf__sound_inst__get_entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B848;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__get_max_distance__t : script_library_class::function {
    slf__sound_inst__get_max_distance__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B870;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__get_min_distance__t : script_library_class::function {
    slf__sound_inst__get_min_distance__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B868;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__get_pitch__t : script_library_class::function {
    slf__sound_inst__get_pitch__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B860;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__get_source__t : script_library_class::function {
    slf__sound_inst__get_source__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B828;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__get_status__t : script_library_class::function {
    slf__sound_inst__get_status__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B888;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__get_volume__t : script_library_class::function {
    slf__sound_inst__get_volume__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B858;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__is_valid__t : script_library_class::function {
    slf__sound_inst__is_valid__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B820;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__play__num__t : script_library_class::function {
    slf__sound_inst__play__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8B0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__play_3d__vector3d__num__t : script_library_class::function {
    slf__sound_inst__play_3d__vector3d__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8B8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__queue__num__t : script_library_class::function {
    slf__sound_inst__queue__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8A8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__set_entity__entity__t : script_library_class::function {
    slf__sound_inst__set_entity__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B850;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__set_preregistered_source__str__t : script_library_class::function {
    slf__sound_inst__set_preregistered_source__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B830;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__set_sound_group__str__t : script_library_class::function {
    slf__sound_inst__set_sound_group__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B840;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__set_source__str__t : script_library_class::function {
    slf__sound_inst__set_source__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B838;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__stop__num__t : script_library_class::function {
    slf__sound_inst__stop__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8C8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__sound_inst__wait__num__t : script_library_class::function {
    slf__sound_inst__wait__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8C0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list__add__str__t : script_library_class::function {
    slf__str_list__add__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C05C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list__begin__t : script_library_class::function {
    slf__str_list__begin__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C074;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list__end__t : script_library_class::function {
    slf__str_list__end__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C07C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list__get_index__num__t : script_library_class::function {
    slf__str_list__get_index__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C084;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list__remove__str__t : script_library_class::function {
    slf__str_list__remove__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C064;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list__remove__str_list_iterator__t : script_library_class::function {
    slf__str_list__remove__str_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C06C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list__set_index__num__str__t : script_library_class::function {
    slf__str_list__set_index__num__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C08C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list__size__t : script_library_class::function {
    slf__str_list__size__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C054;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list_iterator__get_str__t : script_library_class::function {
    slf__str_list_iterator__get_str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C0B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list_iterator__operator_not_equals__str_list_iterator__t : script_library_class::function {
    slf__str_list_iterator__operator_not_equals__str_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C0AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list_iterator__operator_plus_plus__t : script_library_class::function {
    slf__str_list_iterator__operator_plus_plus__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C094;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list_iterator__operator_minus_munus__t : script_library_class::function {
    slf__str_list_iterator__operator_minus_munus__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C09C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__str_list_iterator__operator_equals_equals__str_list_iterator__t : script_library_class::function {
    slf__str_list_iterator__operator_equals_equals__str_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C0A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__string_hash__operator_equals_equals__str__t : script_library_class::function {
    slf__string_hash__operator_equals_equals__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__string_hash__operator_equals_equals__string_hash__t : script_library_class::function {
    slf__string_hash__operator_equals_equals__string_hash__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__string_hash__set__str__t : script_library_class::function {
    slf__string_hash__set__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__string_hash__string_hash__str__t : script_library_class::function {
    slf__string_hash__string_hash__str__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7B4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__string_hash__to_string__t : script_library_class::function {
    slf__string_hash__to_string__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C7BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__switch_obj__get_state__t : script_library_class::function {
    slf__switch_obj__get_state__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__switch_obj__set_alarm__num__t : script_library_class::function {
    slf__switch_obj__set_alarm__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B904;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__switch_obj__set_single_use__num__t : script_library_class::function {
    slf__switch_obj__set_single_use__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B90C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__switch_obj__set_state__num__t : script_library_class::function {
    slf__switch_obj__set_state__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__switch_obj__set_web_targetable__num__t : script_library_class::function {
    slf__switch_obj__set_web_targetable__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8FC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__switch_obj__who_pressed_me__t : script_library_class::function {
    slf__switch_obj__who_pressed_me__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B8EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__tam__set_entity__entity__t : script_library_class::function {
    slf__tam__set_entity__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C6DC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__tam__set_pos__vector3d__t : script_library_class::function {
    slf__tam__set_pos__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C6E4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__tam__set_state__num__t : script_library_class::function {
    slf__tam__set_state__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C6EC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__tam__set_type__num__t : script_library_class::function {
    slf__tam__set_type__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C6F4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_entry__get_entity__t : script_library_class::function {
    slf__taunt_entry__get_entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C62C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_entry__get_flags__t : script_library_class::function {
    slf__taunt_entry__get_flags__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C634;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_entry__get_taunt_name__t : script_library_class::function {
    slf__taunt_entry__get_taunt_name__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C624;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_entity_to_do_hurting__t : script_library_class::function {
    slf__taunt_exchange__get_entity_to_do_hurting__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C654;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_entity_to_hurt__t : script_library_class::function {
    slf__taunt_exchange__get_entity_to_hurt__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C64C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_last_hit_pt_value__t : script_library_class::function {
    slf__taunt_exchange__get_last_hit_pt_value__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C664;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_max_times_to_play__t : script_library_class::function {
    slf__taunt_exchange__get_max_times_to_play__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C684;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_min_damage__t : script_library_class::function {
    slf__taunt_exchange__get_min_damage__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C65C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_normalized_weight__t : script_library_class::function {
    slf__taunt_exchange__get_normalized_weight__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C6A4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_taunt_entry__num__t : script_library_class::function {
    slf__taunt_exchange__get_taunt_entry__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C694;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_times_played__t : script_library_class::function {
    slf__taunt_exchange__get_times_played__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C674;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_total_taunts__t : script_library_class::function {
    slf__taunt_exchange__get_total_taunts__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C68C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__get_weight__t : script_library_class::function {
    slf__taunt_exchange__get_weight__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C69C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__increment_times_played__t : script_library_class::function {
    slf__taunt_exchange__increment_times_played__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C67C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__set_last_hit_pt_value__num__t : script_library_class::function {
    slf__taunt_exchange__set_last_hit_pt_value__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C66C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange__set_normalized_weight__num__t : script_library_class::function {
    slf__taunt_exchange__set_normalized_weight__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C6AC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange_list__add__taunt_exchange__t : script_library_class::function {
    slf__taunt_exchange_list__add__taunt_exchange__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C0BC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange_list__clear__t : script_library_class::function {
    slf__taunt_exchange_list__clear__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C0D4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange_list__get_index__num__t : script_library_class::function {
    slf__taunt_exchange_list__get_index__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C0C4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__taunt_exchange_list__size__t : script_library_class::function {
    slf__taunt_exchange_list__size__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089C0CC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__contains__entity__t : script_library_class::function {
    slf__trigger__contains__entity__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B938;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__get_abs_position__t : script_library_class::function {
    slf__trigger__get_abs_position__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B920;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__get_radius__t : script_library_class::function {
    slf__trigger__get_radius__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9A0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__get_triggered_ent__t : script_library_class::function {
    slf__trigger__get_triggered_ent__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B928;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__get_triggered_entity_list__t : script_library_class::function {
    slf__trigger__get_triggered_entity_list__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B930;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__is_point_radius_trigger__t : script_library_class::function {
    slf__trigger__is_point_radius_trigger__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9B0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__set_active__num__t : script_library_class::function {
    slf__trigger__set_active__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B940;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__set_multiple_entrance__num__t : script_library_class::function {
    slf__trigger__set_multiple_entrance__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B988;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__set_position__vector3d__t : script_library_class::function {
    slf__trigger__set_position__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9A8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__set_radius__num__t : script_library_class::function {
    slf__trigger__set_radius__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B998;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__set_sees_dead_people__num__t : script_library_class::function {
    slf__trigger__set_sees_dead_people__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B990;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__trigger__set_use_any_char__num__t : script_library_class::function {
    slf__trigger__set_use_any_char__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B980;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__length__t : script_library_class::function {
    slf__vector3d__length__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9F8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__length2__t : script_library_class::function {
    slf__vector3d__length2__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA00;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__operator_not_equals__vector3d__t : script_library_class::function {
    slf__vector3d__operator_not_equals__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9F0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__operator_multiply__num__t : script_library_class::function {
    slf__vector3d__operator_multiply__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9D8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__operator_plus__vector3d__t : script_library_class::function {
    slf__vector3d__operator_plus__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9C8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__operator_multiply__vector3d__t : script_library_class::function {
    slf__vector3d__operator_multiply__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9D0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__operator_divide__num__t : script_library_class::function {
    slf__vector3d__operator_divide__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9E0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__operator_equals_equals__vector3d__t : script_library_class::function {
    slf__vector3d__operator_equals_equals__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9E8;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__vector3d__num__num__num__t : script_library_class::function {
    slf__vector3d__vector3d__num__num__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089B9C0;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__x__t : script_library_class::function {
    slf__vector3d__x__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA18;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__xy_norm__t : script_library_class::function {
    slf__vector3d__xy_norm__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA08;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__xz_norm__t : script_library_class::function {
    slf__vector3d__xz_norm__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA10;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__y__t : script_library_class::function {
    slf__vector3d__y__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA20;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d__z__t : script_library_class::function {
    slf__vector3d__z__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BA28;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__add__vector3d__t : script_library_class::function {
    slf__vector3d_list__add__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BEEC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__begin__t : script_library_class::function {
    slf__vector3d_list__begin__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF04;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__clear__t : script_library_class::function {
    slf__vector3d_list__clear__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF1C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__end__t : script_library_class::function {
    slf__vector3d_list__end__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF0C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__get_index__num__t : script_library_class::function {
    slf__vector3d_list__get_index__num__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF14;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__remove__vector3d__t : script_library_class::function {
    slf__vector3d_list__remove__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BEF4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__remove__vector3d_list_iterator__t : script_library_class::function {
    slf__vector3d_list__remove__vector3d_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BEFC;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__set_index__num__vector3d__t : script_library_class::function {
    slf__vector3d_list__set_index__num__vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF24;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list__size__t : script_library_class::function {
    slf__vector3d_list__size__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BEE4;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list_iterator__get_vector3d__t : script_library_class::function {
    slf__vector3d_list_iterator__get_vector3d__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF4C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list_iterator__operator_not_equals__vector3d_list_iterator__t : script_library_class::function {
    slf__vector3d_list_iterator__operator_not_equals__vector3d_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF44;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list_iterator__operator_plus_plus__t : script_library_class::function {
    slf__vector3d_list_iterator__operator_plus_plus__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF2C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list_iterator__operator_minus_munus__t : script_library_class::function {
    slf__vector3d_list_iterator__operator_minus_munus__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF34;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};

struct slf__vector3d_list_iterator__operator_equals_equals__vector3d_list_iterator__t : script_library_class::function {
    slf__vector3d_list_iterator__operator_equals_equals__vector3d_list_iterator__t (script_library_class *slc, const char *a3) : function(slc, a3)  {
        m_vtbl = 0x0089BF3C;
    }

    bool operator()(vm_stack &, script_library_class::function::entry_t) const {}
};


void chuck_register_script_libs()
{
    TRACE("chuck_register_script_libs");

    if constexpr (1) {
        std::vector<script_library_class *> classes(39u);
        auto class_idx = 0u;

#define CREATE_SLC(TYPE) \
    classes[class_idx++] = new (mem_alloc(sizeof(TYPE))) TYPE {}

        CREATE_SLC(slc_pfx_t);
        CREATE_SLC(slc_interactable_interface_t);
        CREATE_SLC(slc_anim_t);
        CREATE_SLC(slc_beam_t);
        CREATE_SLC(slc_entity_t);
        CREATE_SLC(slc_cut_scene_t);
        CREATE_SLC(slc_debug_menu_entry_t);
        CREATE_SLC(slc_entity_list_t);
        CREATE_SLC(slc_entity_list_iterator_t);
        CREATE_SLC(slc_entity_tracker_t);
        CREATE_SLC(slc_glamour_cam_t);
        CREATE_SLC(slc_gun_t);
        CREATE_SLC(slc_item_t);
        CREATE_SLC(slc_line_info_t);
        CREATE_SLC(slc_mission_camera_marker_t);
        CREATE_SLC(slc_mission_camera_transform_marker_t);
        CREATE_SLC(slc_mission_transform_marker_t);
        CREATE_SLC(slc_num_list_t);
        CREATE_SLC(slc_num_list_iterator_t);
        CREATE_SLC(slc_panel_t);
        CREATE_SLC(slc_polytube_t);
        CREATE_SLC(slc_script_controller_t);
        CREATE_SLC(slc_signaller_t);
        CREATE_SLC(slc_sound_inst_t);
        CREATE_SLC(slc_str_list_t);
        CREATE_SLC(slc_str_list_iterator_t);
        CREATE_SLC(slc_switch_obj_t);
        CREATE_SLC(slc_tam_t);
        CREATE_SLC(slc_taunt_entry_t);
        CREATE_SLC(slc_taunt_exchange_t);
        CREATE_SLC(slc_taunt_exchange_list_t);
        CREATE_SLC(slc_trigger_t);
        CREATE_SLC(slc_vector3d_t);
        CREATE_SLC(slc_position3d_t);
        CREATE_SLC(slc_posfacing3d_t);
        CREATE_SLC(slc_vector3d_list_t);
        CREATE_SLC(slc_vector3d_list_iterator_t);
        CREATE_SLC(slc_string_hash_t);
        CREATE_SLC(slc_critical_section_t);
        CREATE_SLC(slc_district_t);

        if (!g_is_the_packer() && !script_manager::using_chuck_old_fashioned()) {
            slc_manager::un_mash_all_funcs();
        }

#undef CREATE_SLC

#define CREATE_GLOBAL_SLF(TYPE, NAME)              \
    new (mem_alloc(sizeof(TYPE))) TYPE {NAME}

        {
            CREATE_GLOBAL_SLF(slf__abs_delay__num__t, "abs_delay(num)");
            CREATE_GLOBAL_SLF(slf__acos__num__t, "acos(num)");
            CREATE_GLOBAL_SLF(slf__add_2d_debug_str__vector3d__vector3d__num__str__t, "add_2d_debug_str(vector3d,vector3d,num,str)");
            CREATE_GLOBAL_SLF(slf__add_2d_debug_str__vector3d__vector3d__num__str__num__t, "add_2d_debug_str(vector3d,vector3d,num,str,num)");
            CREATE_GLOBAL_SLF(slf__add_3d_debug_str__vector3d__vector3d__num__str__t, "add_3d_debug_str(vector3d,vector3d,num,str)");
            CREATE_GLOBAL_SLF(slf__add_civilian_info__vector3d__num__num__num__t, "add_civilian_info(vector3d,num,num,num)");
            CREATE_GLOBAL_SLF(slf__add_civilian_info_entity__entity__num__num__num__t, "add_civilian_info_entity(entity,num,num,num)");
            CREATE_GLOBAL_SLF(slf__add_debug_cyl__vector3d__vector3d__num__t, "add_debug_cyl(vector3d,vector3d,num)");
            CREATE_GLOBAL_SLF(slf__add_debug_cyl__vector3d__vector3d__num__vector3d__num__t, "add_debug_cyl(vector3d,vector3d,num,vector3d,num)");
            CREATE_GLOBAL_SLF(slf__add_debug_line__vector3d__vector3d__t, "add_debug_line(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__add_debug_line__vector3d__vector3d__vector3d__num__t, "add_debug_line(vector3d,vector3d,vector3d,num)");
            CREATE_GLOBAL_SLF(slf__add_debug_sphere__vector3d__num__t, "add_debug_sphere(vector3d,num)");
            CREATE_GLOBAL_SLF(slf__add_debug_sphere__vector3d__num__vector3d__num__t, "add_debug_sphere(vector3d,num,vector3d,num)");
            CREATE_GLOBAL_SLF(slf__add_glass_house__str__t, "add_glass_house(str)");
            CREATE_GLOBAL_SLF(slf__add_glass_house__str__num__t, "add_glass_house(str,num)");
            CREATE_GLOBAL_SLF(slf__add_glass_house__str__num__vector3d__t, "add_glass_house(str,num,vector3d)");
            CREATE_GLOBAL_SLF(slf__add_glass_house__str__vector3d__t, "add_glass_house(str,vector3d)");
            CREATE_GLOBAL_SLF(slf__add_to_console__str__t, "add_to_console(str)");
            CREATE_GLOBAL_SLF(slf__add_traffic_model__num__str__t, "add_traffic_model(num,str)");
            CREATE_GLOBAL_SLF(slf__allow_suspend_thread__num__t, "allow_suspend_thread(num)");
            CREATE_GLOBAL_SLF(slf__angle_between__vector3d__vector3d__t, "angle_between(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__apply_donut_damage__vector3d__num__num__num__num__num__t, "apply_donut_damage(vector3d,num,num,num,num,num)");
            CREATE_GLOBAL_SLF(slf__apply_radius_damage__vector3d__num__num__num__num__t, "apply_radius_damage(vector3d,num,num,num,num)");
            CREATE_GLOBAL_SLF(slf__apply_radius_subdue__vector3d__num__num__num__num__t, "apply_radius_subdue(vector3d,num,num,num,num)");
            CREATE_GLOBAL_SLF(slf__assert__num__str__t, "assert(num,str)");
            CREATE_GLOBAL_SLF(slf__attach_decal__str__vector3d__num__vector3d__entity__t, "attach_decal(str,vector3d,num,vector3d,entity)");
            CREATE_GLOBAL_SLF(slf__begin_screen_recording__str__num__t, "begin_screen_recording(str,num)");
            CREATE_GLOBAL_SLF(slf__blackscreen_off__num__t, "blackscreen_off(num)");
            CREATE_GLOBAL_SLF(slf__blackscreen_on__num__t, "blackscreen_on(num)");
            CREATE_GLOBAL_SLF(slf__bring_up_dialog_box__num__num__t, "bring_up_dialog_box(num,num,...)");
            CREATE_GLOBAL_SLF(slf__bring_up_dialog_box_debug__str__num__str__t, "bring_up_dialog_box_debug(str,num,str)");
            CREATE_GLOBAL_SLF(slf__bring_up_dialog_box_title__num__num__num__t, "bring_up_dialog_box_title(num,num,num,...)");
            CREATE_GLOBAL_SLF(slf__bring_up_medal_award_box__num__t, "bring_up_medal_award_box(num)");
            CREATE_GLOBAL_SLF(slf__bring_up_race_announcer__t, "bring_up_race_announcer()");
            CREATE_GLOBAL_SLF(slf__calc_launch_vector__vector3d__vector3d__num__entity__t, "calc_launch_vector(vector3d,vector3d,num,entity)");
            CREATE_GLOBAL_SLF(slf__can_load_pack__str__t, "can_load_pack(str)");
            CREATE_GLOBAL_SLF(slf__chase_cam__t, "chase_cam()");
            CREATE_GLOBAL_SLF(slf__clear_all_grenades__t, "clear_all_grenades()");
            CREATE_GLOBAL_SLF(slf__clear_civilians_within_radius__vector3d__num__t, "clear_civilians_within_radius(vector3d,num)");
            CREATE_GLOBAL_SLF(slf__clear_controls__t, "clear_controls()");
            CREATE_GLOBAL_SLF(slf__clear_debug_all__t, "clear_debug_all()");
            CREATE_GLOBAL_SLF(slf__clear_debug_cyls__t, "clear_debug_cyls()");
            CREATE_GLOBAL_SLF(slf__clear_debug_lines__t, "clear_debug_lines()");
            CREATE_GLOBAL_SLF(slf__clear_debug_spheres__t, "clear_debug_spheres()");
            CREATE_GLOBAL_SLF(slf__clear_screen__t, "clear_screen()");
            CREATE_GLOBAL_SLF(slf__clear_traffic_within_radius__vector3d__num__t, "clear_traffic_within_radius(vector3d,num)");
            CREATE_GLOBAL_SLF(slf__col_check__vector3d__vector3d__num__t, "col_check(vector3d,vector3d,num)");
            CREATE_GLOBAL_SLF(slf__console_exec__str__t, "console_exec(str)");
            CREATE_GLOBAL_SLF(slf__copy_vector3d_list__vector3d_list__vector3d_list__t, "copy_vector3d_list(vector3d_list,vector3d_list)");
            CREATE_GLOBAL_SLF(slf__cos__num__t, "cos(num)");
            CREATE_GLOBAL_SLF(slf__create_beam__t, "create_beam()");
            CREATE_GLOBAL_SLF(slf__create_credits__t, "create_credits()");
            CREATE_GLOBAL_SLF(slf__create_cut_scene__str__t, "create_cut_scene(str)");
            CREATE_GLOBAL_SLF(slf__create_debug_menu_entry__str__t, "create_debug_menu_entry(str)");
            CREATE_GLOBAL_SLF(slf__create_debug_menu_entry__str__str__t, "create_debug_menu_entry(str,str)");
            CREATE_GLOBAL_SLF(slf__create_decal__str__vector3d__num__vector3d__t, "create_decal(str,vector3d,num,vector3d)");
            CREATE_GLOBAL_SLF(slf__create_entity__str__t, "create_entity(str)");
            CREATE_GLOBAL_SLF(slf__create_entity__str__str__t, "create_entity(str,str)");
            CREATE_GLOBAL_SLF(slf__create_entity_in_hero_region__str__t, "create_entity_in_hero_region(str)");
            CREATE_GLOBAL_SLF(slf__create_entity_list__t, "create_entity_list()");
            CREATE_GLOBAL_SLF(slf__create_entity_tracker__entity__t, "create_entity_tracker(entity)");
            CREATE_GLOBAL_SLF(slf__create_item__str__t, "create_item(str)");
            CREATE_GLOBAL_SLF(slf__create_line_info__vector3d__vector3d__t, "create_line_info(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__create_lofi_stereo_sound_inst__str__t, "create_lofi_stereo_sound_inst(str)");
            CREATE_GLOBAL_SLF(slf__create_num_list__t, "create_num_list()");
            CREATE_GLOBAL_SLF(slf__create_pfx__str__t, "create_pfx(str)");
            CREATE_GLOBAL_SLF(slf__create_pfx__str__vector3d__t, "create_pfx(str,vector3d)");
            CREATE_GLOBAL_SLF(slf__create_polytube__t, "create_polytube()");
            CREATE_GLOBAL_SLF(slf__create_polytube__str__t, "create_polytube(str)");
            CREATE_GLOBAL_SLF(slf__create_progression_menu_entry__str__str__t, "create_progression_menu_entry(str,str)");
            CREATE_GLOBAL_SLF(slf__create_sound_inst__t, "create_sound_inst()");
            CREATE_GLOBAL_SLF(slf__create_sound_inst__str__t, "create_sound_inst(str)");
            CREATE_GLOBAL_SLF(slf__create_stompable_music_sound_inst__str__t, "create_stompable_music_sound_inst(str)");
            CREATE_GLOBAL_SLF(slf__create_str_list__t, "create_str_list()");
            CREATE_GLOBAL_SLF(slf__create_taunt_entry__entity__str__num__t, "create_taunt_entry(entity,str,num)");
            CREATE_GLOBAL_SLF(slf__create_taunt_exchange__entity__entity__num__num__num__num__t, "create_taunt_exchange(entity,entity,num,num,num,num,...)");
            CREATE_GLOBAL_SLF(slf__create_taunt_exchange_list__t, "create_taunt_exchange_list()");
            CREATE_GLOBAL_SLF(slf__create_threat_assessment_meter__t, "create_threat_assessment_meter()");
            CREATE_GLOBAL_SLF(slf__create_time_limited_entity__str__num__t, "create_time_limited_entity(str,num)");
            CREATE_GLOBAL_SLF(slf__create_trigger__entity__num__t, "create_trigger(entity,num)");
            CREATE_GLOBAL_SLF(slf__create_trigger__str__vector3d__num__t, "create_trigger(str,vector3d,num)");
            CREATE_GLOBAL_SLF(slf__create_trigger__vector3d__num__t, "create_trigger(vector3d,num)");
            CREATE_GLOBAL_SLF(slf__create_unstompable_script_cutscene_sound_inst__str__t, "create_unstompable_script_cutscene_sound_inst(str)");
            CREATE_GLOBAL_SLF(slf__create_vector3d_list__t, "create_vector3d_list()");
            CREATE_GLOBAL_SLF(slf__cross__vector3d__vector3d__t, "cross(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__debug_breakpoint__t, "debug_breakpoint()");
            CREATE_GLOBAL_SLF(slf__debug_print__num__str__t, "debug_print(num,str)");
            CREATE_GLOBAL_SLF(slf__debug_print__num__vector3d__str__t, "debug_print(num,vector3d,str)");
            CREATE_GLOBAL_SLF(slf__debug_print__str__t, "debug_print(str)");
            CREATE_GLOBAL_SLF(slf__debug_print_set_background_color__vector3d__t, "debug_print_set_background_color(vector3d)");
            CREATE_GLOBAL_SLF(slf__delay__num__t, "delay(num)");
            CREATE_GLOBAL_SLF(slf__destroy_credits__t, "destroy_credits()");
            CREATE_GLOBAL_SLF(slf__destroy_debug_menu_entry__debug_menu_entry__t, "destroy_debug_menu_entry(debug_menu_entry)");
            CREATE_GLOBAL_SLF(slf__destroy_entity__entity__t, "destroy_entity(entity)");
            CREATE_GLOBAL_SLF(slf__destroy_entity_list__entity_list__t, "destroy_entity_list(entity_list)");
            CREATE_GLOBAL_SLF(slf__destroy_entity_tracker__entity_tracker__t, "destroy_entity_tracker(entity_tracker)");
            CREATE_GLOBAL_SLF(slf__destroy_line_info__line_info__t, "destroy_line_info(line_info)");
            CREATE_GLOBAL_SLF(slf__destroy_num_list__num_list__t, "destroy_num_list(num_list)");
            CREATE_GLOBAL_SLF(slf__destroy_pfx__pfx__t, "destroy_pfx(pfx)");
            CREATE_GLOBAL_SLF(slf__destroy_str_list__str_list__t, "destroy_str_list(str_list)");
            CREATE_GLOBAL_SLF(slf__destroy_taunt_entry__taunt_entry__t, "destroy_taunt_entry(taunt_entry)");
            CREATE_GLOBAL_SLF(slf__destroy_taunt_exchange__taunt_exchange__t, "destroy_taunt_exchange(taunt_exchange)");
            CREATE_GLOBAL_SLF(slf__destroy_taunt_exchange_list__taunt_exchange_list__t, "destroy_taunt_exchange_list(taunt_exchange_list)");
            CREATE_GLOBAL_SLF(slf__destroy_threat_assessment_meter__tam__t, "destroy_threat_assessment_meter(tam)");
            CREATE_GLOBAL_SLF(slf__destroy_trigger__trigger__t, "destroy_trigger(trigger)");
            CREATE_GLOBAL_SLF(slf__destroy_vector3d_list__vector3d_list__t, "destroy_vector3d_list(vector3d_list)");
            CREATE_GLOBAL_SLF(slf__dilated_delay__num__t, "dilated_delay(num)");
            CREATE_GLOBAL_SLF(slf__disable_marky_cam__num__t, "disable_marky_cam(num)");
            CREATE_GLOBAL_SLF(slf__disable_nearby_occlusion_only_obb__vector3d__t, "disable_nearby_occlusion_only_obb(vector3d)");
            CREATE_GLOBAL_SLF(slf__disable_player_shadows__t, "disable_player_shadows()");
            CREATE_GLOBAL_SLF(slf__disable_subtitles__t, "disable_subtitles()");
            CREATE_GLOBAL_SLF(slf__disable_vibrator__t, "disable_vibrator()");
            CREATE_GLOBAL_SLF(slf__disable_zoom_map__num__t, "disable_zoom_map(num)");
            CREATE_GLOBAL_SLF(slf__distance3d__vector3d__vector3d__t, "distance3d(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__distance_chase_widget_set_pos__num__t, "distance_chase_widget_set_pos(num)");
            CREATE_GLOBAL_SLF(slf__distance_chase_widget_turn_off__t, "distance_chase_widget_turn_off()");
            CREATE_GLOBAL_SLF(slf__distance_chase_widget_turn_on__num__num__t, "distance_chase_widget_turn_on(num,num)");
            CREATE_GLOBAL_SLF(slf__distance_race_widget_set_boss_pos__num__t, "distance_race_widget_set_boss_pos(num)");
            CREATE_GLOBAL_SLF(slf__distance_race_widget_set_hero_pos__num__t, "distance_race_widget_set_hero_pos(num)");
            CREATE_GLOBAL_SLF(slf__distance_race_widget_set_types__num__num__t, "distance_race_widget_set_types(num,num)");
            CREATE_GLOBAL_SLF(slf__distance_race_widget_turn_off__t, "distance_race_widget_turn_off()");
            CREATE_GLOBAL_SLF(slf__distance_race_widget_turn_on__t, "distance_race_widget_turn_on()");
            CREATE_GLOBAL_SLF(slf__district_id__str__t, "district_id(str)");
            CREATE_GLOBAL_SLF(slf__district_name__num__t, "district_name(num)");
            CREATE_GLOBAL_SLF(slf__dot__vector3d__vector3d__t, "dot(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__dump_searchable_region_list__str__t, "dump_searchable_region_list(str)");
            CREATE_GLOBAL_SLF(slf__enable_ai__num__t, "enable_ai(num)");
            CREATE_GLOBAL_SLF(slf__enable_civilians__num__t, "enable_civilians(num)");
            CREATE_GLOBAL_SLF(slf__enable_controls__num__t, "enable_controls(num)");
            CREATE_GLOBAL_SLF(slf__enable_entity_fading__num__t, "enable_entity_fading(num)");
            CREATE_GLOBAL_SLF(slf__enable_interface__num__t, "enable_interface(num)");
            CREATE_GLOBAL_SLF(slf__enable_marky_cam__num__t, "enable_marky_cam(num)");
            CREATE_GLOBAL_SLF(slf__enable_mini_map__num__t, "enable_mini_map(num)");
            CREATE_GLOBAL_SLF(slf__enable_nearby_occlusion_only_obb__vector3d__t, "enable_nearby_occlusion_only_obb(vector3d)");
            CREATE_GLOBAL_SLF(slf__enable_obb__vector3d__num__t, "enable_obb(vector3d,num)");
            CREATE_GLOBAL_SLF(slf__enable_pause__num__t, "enable_pause(num)");
            CREATE_GLOBAL_SLF(slf__enable_physics__num__t, "enable_physics(num)");
            CREATE_GLOBAL_SLF(slf__enable_player_shadows__t, "enable_player_shadows()");
            CREATE_GLOBAL_SLF(slf__enable_pois__num__t, "enable_pois(num)");
            CREATE_GLOBAL_SLF(slf__enable_quad_path_connector__district__num__district__num__num__t, "enable_quad_path_connector(district,num,district,num,num)");
            CREATE_GLOBAL_SLF(slf__enable_subtitles__t, "enable_subtitles()");
            CREATE_GLOBAL_SLF(slf__enable_tokens_of_type__num__num__t, "enable_tokens_of_type(num,num)");
            CREATE_GLOBAL_SLF(slf__enable_traffic__num__t, "enable_traffic(num)");
            CREATE_GLOBAL_SLF(slf__enable_user_camera__num__t, "enable_user_camera(num)");
            CREATE_GLOBAL_SLF(slf__enable_vibrator__t, "enable_vibrator()");
            CREATE_GLOBAL_SLF(slf__end_current_patrol__t, "end_current_patrol()");
            CREATE_GLOBAL_SLF(slf__end_cut_scenes__t, "end_cut_scenes()");
            CREATE_GLOBAL_SLF(slf__end_screen_recording__t, "end_screen_recording()");
            CREATE_GLOBAL_SLF(slf__entity_col_check__entity__entity__t, "entity_col_check(entity,entity)");
            CREATE_GLOBAL_SLF(slf__entity_exists__str__t, "entity_exists(str)");
            CREATE_GLOBAL_SLF(slf__entity_get_entity_tracker__entity__t, "entity_get_entity_tracker(entity)");
            CREATE_GLOBAL_SLF(slf__entity_has_entity_tracker__entity__t, "entity_has_entity_tracker(entity)");
            CREATE_GLOBAL_SLF(slf__exit_water__entity__t, "exit_water(entity)");
            CREATE_GLOBAL_SLF(slf__find_closest_point_on_a_path_to_point__vector3d__t, "find_closest_point_on_a_path_to_point(vector3d)");
            CREATE_GLOBAL_SLF(slf__find_district_for_point__vector3d__t, "find_district_for_point(vector3d)");
            CREATE_GLOBAL_SLF(slf__find_entities_in_radius__entity_list__vector3d__num__num__t, "find_entities_in_radius(entity_list,vector3d,num,num)");
            CREATE_GLOBAL_SLF(slf__find_entity__str__t, "find_entity(str)");
            CREATE_GLOBAL_SLF(slf__find_innermost_district__vector3d__t, "find_innermost_district(vector3d)");
            CREATE_GLOBAL_SLF(slf__find_outermost_district__vector3d__t, "find_outermost_district(vector3d)");
            CREATE_GLOBAL_SLF(slf__find_trigger__entity__t, "find_trigger(entity)");
            CREATE_GLOBAL_SLF(slf__find_trigger__str__t, "find_trigger(str)");
            CREATE_GLOBAL_SLF(slf__find_trigger_in_district__district__str__t, "find_trigger_in_district(district,str)");
            CREATE_GLOBAL_SLF(slf__float_random__num__t, "float_random(num)");
            CREATE_GLOBAL_SLF(slf__force_mission__district__str__num__t, "force_mission(district,str,num)");
            CREATE_GLOBAL_SLF(slf__force_streamer_refresh__t, "force_streamer_refresh()");
            CREATE_GLOBAL_SLF(slf__format_time_string__num__t, "format_time_string(num)");
            CREATE_GLOBAL_SLF(slf__freeze_hero__num__t, "freeze_hero(num)");
            CREATE_GLOBAL_SLF(slf__game_ini_get_flag__str__t, "game_ini_get_flag(str)");
            CREATE_GLOBAL_SLF(slf__game_time_advance__num__num__t, "game_time_advance(num,num)");
            CREATE_GLOBAL_SLF(slf__get_all_execs_thread_count__str__t, "get_all_execs_thread_count(str)");
            CREATE_GLOBAL_SLF(slf__get_all_instances_thread_count__str__t, "get_all_instances_thread_count(str)");
            CREATE_GLOBAL_SLF(slf__get_attacker_entity__t, "get_attacker_entity()");
            CREATE_GLOBAL_SLF(slf__get_attacker_member__t, "get_attacker_member()");
            CREATE_GLOBAL_SLF(slf__get_available_stack_size__t, "get_available_stack_size()");
            CREATE_GLOBAL_SLF(slf__get_character_packname_list__t, "get_character_packname_list()");
            CREATE_GLOBAL_SLF(slf__get_closest_point_on_lane_with_facing__num__vector3d__vector3d_list__t, "get_closest_point_on_lane_with_facing(num,vector3d,vector3d_list)");
            CREATE_GLOBAL_SLF(slf__get_col_hit_ent__t, "get_col_hit_ent()");
            CREATE_GLOBAL_SLF(slf__get_col_hit_norm__t, "get_col_hit_norm()");
            CREATE_GLOBAL_SLF(slf__get_col_hit_pos__t, "get_col_hit_pos()");
            CREATE_GLOBAL_SLF(slf__get_control_state__num__t, "get_control_state(num)");
            CREATE_GLOBAL_SLF(slf__get_control_trigger__num__t, "get_control_trigger(num)");
            CREATE_GLOBAL_SLF(slf__get_current_instance_thread_count__str__t, "get_current_instance_thread_count(str)");
            CREATE_GLOBAL_SLF(slf__get_current_view_cam_pos__t, "get_current_view_cam_pos()");
            CREATE_GLOBAL_SLF(slf__get_current_view_cam_x_facing__t, "get_current_view_cam_x_facing()");
            CREATE_GLOBAL_SLF(slf__get_current_view_cam_y_facing__t, "get_current_view_cam_y_facing()");
            CREATE_GLOBAL_SLF(slf__get_current_view_cam_z_facing__t, "get_current_view_cam_z_facing()");
            CREATE_GLOBAL_SLF(slf__get_fog_color__t, "get_fog_color()");
            CREATE_GLOBAL_SLF(slf__get_fog_distance__t, "get_fog_distance()");
            CREATE_GLOBAL_SLF(slf__get_game_info_num__str__t, "get_game_info_num(str)");
            CREATE_GLOBAL_SLF(slf__get_game_info_str__str__t, "get_game_info_str(str)");
            CREATE_GLOBAL_SLF(slf__get_glam_cam__num__t, "get_glam_cam(num)");
            CREATE_GLOBAL_SLF(slf__get_global_time_dilation__t, "get_global_time_dilation()");
            CREATE_GLOBAL_SLF(slf__get_ini_flag__str__t, "get_ini_flag(str)");
            CREATE_GLOBAL_SLF(slf__get_ini_num__str__t, "get_ini_num(str)");
            CREATE_GLOBAL_SLF(slf__get_int_num__num__t, "get_int_num(num)");
            CREATE_GLOBAL_SLF(slf__get_mission_camera_marker__num__t, "get_mission_camera_marker(num)");
            CREATE_GLOBAL_SLF(slf__get_mission_camera_transform_marker__num__t, "get_mission_camera_transform_marker(num)");
            CREATE_GLOBAL_SLF(slf__get_mission_entity__t, "get_mission_entity()");
            CREATE_GLOBAL_SLF(slf__get_mission_key_posfacing3d__t, "get_mission_key_posfacing3d()");
            CREATE_GLOBAL_SLF(slf__get_mission_key_position__t, "get_mission_key_position()");
            CREATE_GLOBAL_SLF(slf__get_mission_marker__num__t, "get_mission_marker(num)");
            CREATE_GLOBAL_SLF(slf__get_mission_nums__t, "get_mission_nums()");
            CREATE_GLOBAL_SLF(slf__get_mission_patrol_waypoint__t, "get_mission_patrol_waypoint()");
            CREATE_GLOBAL_SLF(slf__get_mission_positions__t, "get_mission_positions()");
            CREATE_GLOBAL_SLF(slf__get_mission_strings__t, "get_mission_strings()");
            CREATE_GLOBAL_SLF(slf__get_mission_transform_marker__num__t, "get_mission_transform_marker(num)");
            CREATE_GLOBAL_SLF(slf__get_mission_trigger__t, "get_mission_trigger()");
            CREATE_GLOBAL_SLF(slf__get_missions_key_position_by_index__district__str__num__t, "get_missions_key_position_by_index(district,str,num)");
            CREATE_GLOBAL_SLF(slf__get_missions_nums_by_index__district__str__num__num_list__t, "get_missions_nums_by_index(district,str,num,num_list)");
            CREATE_GLOBAL_SLF(slf__get_missions_patrol_waypoint_by_index__district__str__num__t, "get_missions_patrol_waypoint_by_index(district,str,num)");
            CREATE_GLOBAL_SLF(slf__get_neighborhood_name__num__t, "get_neighborhood_name(num)");
            CREATE_GLOBAL_SLF(slf__get_num_free_slots__str__t, "get_num_free_slots(str)");
            CREATE_GLOBAL_SLF(slf__get_num_mission_transform_marker__t, "get_num_mission_transform_marker()");
            CREATE_GLOBAL_SLF(slf__get_pack_group__str__t, "get_pack_group(str)");
            CREATE_GLOBAL_SLF(slf__get_pack_size__str__t, "get_pack_size(str)");
            CREATE_GLOBAL_SLF(slf__get_patrol_difficulty__str__t, "get_patrol_difficulty(str)");
            CREATE_GLOBAL_SLF(slf__get_patrol_node_position_by_index__str__num__t, "get_patrol_node_position_by_index(str,num)");
            CREATE_GLOBAL_SLF(slf__get_patrol_start_position__str__t, "get_patrol_start_position(str)");
            CREATE_GLOBAL_SLF(slf__get_patrol_unlock_threshold__str__t, "get_patrol_unlock_threshold(str)");
            CREATE_GLOBAL_SLF(slf__get_platform__t, "get_platform()");
            CREATE_GLOBAL_SLF(slf__get_render_opt_num__str__t, "get_render_opt_num(str)");
            CREATE_GLOBAL_SLF(slf__get_spider_reflexes_spiderman_time_dilation__t, "get_spider_reflexes_spiderman_time_dilation()");
            CREATE_GLOBAL_SLF(slf__get_spider_reflexes_world_time_dilation__t, "get_spider_reflexes_world_time_dilation()");
            CREATE_GLOBAL_SLF(slf__get_time_inc__t, "get_time_inc()");
            CREATE_GLOBAL_SLF(slf__get_time_of_day__t, "get_time_of_day()");
            CREATE_GLOBAL_SLF(slf__get_time_of_day_rate__t, "get_time_of_day_rate()");
            CREATE_GLOBAL_SLF(slf__get_token_index_from_id__num__num__t, "get_token_index_from_id(num,num)");
            CREATE_GLOBAL_SLF(slf__get_traffic_spawn_point_near_camera__vector3d_list__t, "get_traffic_spawn_point_near_camera(vector3d_list)");
            CREATE_GLOBAL_SLF(slf__greater_than_or_equal_rounded__num__num__t, "greater_than_or_equal_rounded(num,num)");
            CREATE_GLOBAL_SLF(slf__hard_break__t, "hard_break()");
            CREATE_GLOBAL_SLF(slf__has_substring__str__str__t, "has_substring(str,str)");
            CREATE_GLOBAL_SLF(slf__hero__t, "hero()");
            CREATE_GLOBAL_SLF(slf__hero_exists__t, "hero_exists()");
            CREATE_GLOBAL_SLF(slf__hero_type__t, "hero_type()");
            CREATE_GLOBAL_SLF(slf__hide_controller_gauge__t, "hide_controller_gauge()");
            CREATE_GLOBAL_SLF(slf__initialize_encounter_object__t, "initialize_encounter_object()");
            CREATE_GLOBAL_SLF(slf__initialize_encounter_objects__t, "initialize_encounter_objects()");
            CREATE_GLOBAL_SLF(slf__insert_pack__str__t, "insert_pack(str)");
            CREATE_GLOBAL_SLF(slf__invoke_pause_menu_unlockables__t, "invoke_pause_menu_unlockables()");
            CREATE_GLOBAL_SLF(slf__is_ai_enabled__t, "is_ai_enabled()");
            CREATE_GLOBAL_SLF(slf__is_cut_scene_playing__t, "is_cut_scene_playing()");
            CREATE_GLOBAL_SLF(slf__is_district_loaded__num__t, "is_district_loaded(num)");
            CREATE_GLOBAL_SLF(slf__is_hero_frozen__t, "is_hero_frozen()");
            CREATE_GLOBAL_SLF(slf__is_hero_peter_parker__t, "is_hero_peter_parker()");
            CREATE_GLOBAL_SLF(slf__is_hero_spidey__t, "is_hero_spidey()");
            CREATE_GLOBAL_SLF(slf__is_hero_venom__t, "is_hero_venom()");
            CREATE_GLOBAL_SLF(slf__is_marky_cam_enabled__t, "is_marky_cam_enabled()");
            CREATE_GLOBAL_SLF(slf__is_mission_active__t, "is_mission_active()");
            CREATE_GLOBAL_SLF(slf__is_mission_loading__t, "is_mission_loading()");
            CREATE_GLOBAL_SLF(slf__is_pack_available__str__t, "is_pack_available(str)");
            CREATE_GLOBAL_SLF(slf__is_pack_loaded__str__t, "is_pack_loaded(str)");
            CREATE_GLOBAL_SLF(slf__is_pack_pushed__str__t, "is_pack_pushed(str)");
            CREATE_GLOBAL_SLF(slf__is_path_graph_inside_glass_house__str__t, "is_path_graph_inside_glass_house(str)");
            CREATE_GLOBAL_SLF(slf__is_patrol_active__t, "is_patrol_active()");
            CREATE_GLOBAL_SLF(slf__is_patrol_node_empty__num__t, "is_patrol_node_empty(num)");
            CREATE_GLOBAL_SLF(slf__is_paused__t, "is_paused()");
            CREATE_GLOBAL_SLF(slf__is_physics_enabled__t, "is_physics_enabled()");
            CREATE_GLOBAL_SLF(slf__is_point_inside_glass_house__vector3d__t, "is_point_inside_glass_house(vector3d)");
            CREATE_GLOBAL_SLF(slf__is_point_under_water__vector3d__t, "is_point_under_water(vector3d)");
            CREATE_GLOBAL_SLF(slf__is_user_camera_enabled__t, "is_user_camera_enabled()");
            CREATE_GLOBAL_SLF(slf__load_anim__str__t, "load_anim(str)");
            CREATE_GLOBAL_SLF(slf__load_level__str__vector3d__t, "load_level(str,vector3d)");
            CREATE_GLOBAL_SLF(slf__lock_all_districts__t, "lock_all_districts()");
            CREATE_GLOBAL_SLF(slf__lock_district__num__t, "lock_district(num)");
            CREATE_GLOBAL_SLF(slf__lock_mission_manager__num__t, "lock_mission_manager(num)");
            CREATE_GLOBAL_SLF(slf__los_check__vector3d__vector3d__t, "los_check(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__lower_hotpursuit_indicator_level__t, "lower_hotpursuit_indicator_level()");
            CREATE_GLOBAL_SLF(slf__malor__vector3d__num__t, "malor(vector3d,num)");
            CREATE_GLOBAL_SLF(slf__normal__vector3d__t, "normal(vector3d)");
            CREATE_GLOBAL_SLF(slf__pause_game__num__t, "pause_game(num)");
            CREATE_GLOBAL_SLF(slf__play_credits__t, "play_credits()");
            CREATE_GLOBAL_SLF(slf__play_prerender__str__t, "play_prerender(str)");
            CREATE_GLOBAL_SLF(slf__pop_pack__str__t, "pop_pack(str)");
            CREATE_GLOBAL_SLF(slf__post_message__str__num__t, "post_message(str,num)");
            CREATE_GLOBAL_SLF(slf__pre_roll_all_pfx__num__t, "pre_roll_all_pfx(num)");
            CREATE_GLOBAL_SLF(slf__press_controller_gauge__num__t, "press_controller_gauge(num)");
            CREATE_GLOBAL_SLF(slf__press_controller_gauge__num__num__num__t, "press_controller_gauge(num,num,num)");
            CREATE_GLOBAL_SLF(slf__purge_district__num__t, "purge_district(num)");
            CREATE_GLOBAL_SLF(slf__push_pack__str__t, "push_pack(str)");
            CREATE_GLOBAL_SLF(slf__push_pack_into_district_slot__str__t, "push_pack_into_district_slot(str)");
            CREATE_GLOBAL_SLF(slf__raise_hotpursuit_indicator_level__t, "raise_hotpursuit_indicator_level()");
            CREATE_GLOBAL_SLF(slf__random__num__t, "random(num)");
            CREATE_GLOBAL_SLF(slf__remove_civilian_info__num__t, "remove_civilian_info(num)");
            CREATE_GLOBAL_SLF(slf__remove_civilian_info_entity__entity__num__t, "remove_civilian_info_entity(entity,num)");
            CREATE_GLOBAL_SLF(slf__remove_glass_house__str__t, "remove_glass_house(str)");
            CREATE_GLOBAL_SLF(slf__remove_item_entity_from_world__entity__t, "remove_item_entity_from_world(entity)");
            CREATE_GLOBAL_SLF(slf__remove_pack__str__t, "remove_pack(str)");
            CREATE_GLOBAL_SLF(slf__remove_traffic_model__num__t, "remove_traffic_model(num)");
            CREATE_GLOBAL_SLF(slf__reset_externed_alses__t, "reset_externed_alses()");
            CREATE_GLOBAL_SLF(slf__set_all_anchors_activated__num__t, "set_all_anchors_activated(num)");
            CREATE_GLOBAL_SLF(slf__set_blur__num__t, "set_blur(num)");
            CREATE_GLOBAL_SLF(slf__set_blur_blend_mode__num__t, "set_blur_blend_mode(num)");
            CREATE_GLOBAL_SLF(slf__set_blur_color__vector3d__t, "set_blur_color(vector3d)");
            CREATE_GLOBAL_SLF(slf__set_blur_offset__num__num__t, "set_blur_offset(num,num)");
            CREATE_GLOBAL_SLF(slf__set_blur_rot__num__t, "set_blur_rot(num)");
            CREATE_GLOBAL_SLF(slf__set_blur_scale__num__num__t, "set_blur_scale(num,num)");
            CREATE_GLOBAL_SLF(slf__set_clear_color__vector3d__t, "set_clear_color(vector3d)");
            CREATE_GLOBAL_SLF(slf__set_current_mission_objective_caption__num__t, "set_current_mission_objective_caption(num)");
            CREATE_GLOBAL_SLF(slf__set_default_traffic_hitpoints__num__t, "set_default_traffic_hitpoints(num)");
            CREATE_GLOBAL_SLF(slf__set_dialog_box_flavor__num__t, "set_dialog_box_flavor(num)");
            CREATE_GLOBAL_SLF(slf__set_dialog_box_lockout_time__num__t, "set_dialog_box_lockout_time(num)");
            CREATE_GLOBAL_SLF(slf__set_engine_property__str__num__t, "set_engine_property(str,num)");
            CREATE_GLOBAL_SLF(slf__set_fov__num__t, "set_fov(num)");
            CREATE_GLOBAL_SLF(slf__set_game_info_num__str__num__t, "set_game_info_num(str,num)");
            CREATE_GLOBAL_SLF(slf__set_game_info_str__str__str__t, "set_game_info_str(str,str)");
            CREATE_GLOBAL_SLF(slf__set_global_time_dilation__num__t, "set_global_time_dilation(num)");
            CREATE_GLOBAL_SLF(slf__set_marky_cam_lookat__vector3d__t, "set_marky_cam_lookat(vector3d)");
            CREATE_GLOBAL_SLF(slf__set_max_streaming_distance__num__t, "set_max_streaming_distance(num)");
            CREATE_GLOBAL_SLF(slf__set_mission_key_pos_facing__vector3d__vector3d__t, "set_mission_key_pos_facing(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__set_mission_key_position__vector3d__t, "set_mission_key_position(vector3d)");
            CREATE_GLOBAL_SLF(slf__set_mission_text__num__t, "set_mission_text(num,...)");
            CREATE_GLOBAL_SLF(slf__set_mission_text_box_flavor__num__t, "set_mission_text_box_flavor(num)");
            CREATE_GLOBAL_SLF(slf__set_mission_text_debug__str__t, "set_mission_text_debug(str)");
            CREATE_GLOBAL_SLF(slf__set_parking_density__num__t, "set_parking_density(num)");
            CREATE_GLOBAL_SLF(slf__set_pedestrian_density__num__t, "set_pedestrian_density(num)");
            CREATE_GLOBAL_SLF(slf__set_render_opt_num__str__num__t, "set_render_opt_num(str,num)");
            CREATE_GLOBAL_SLF(slf__set_score_widget_score__num__t, "set_score_widget_score(num)");
            CREATE_GLOBAL_SLF(slf__set_sound_category_volume__num__num__num__t, "set_sound_category_volume(num,num,num)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_blur__num__t, "set_spider_reflexes_blur(num)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_blur_blend_mode__num__t, "set_spider_reflexes_blur_blend_mode(num)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_blur_color__vector3d__t, "set_spider_reflexes_blur_color(vector3d)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_blur_offset__num__num__t, "set_spider_reflexes_blur_offset(num,num)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_blur_rot__num__t, "set_spider_reflexes_blur_rot(num)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_blur_scale__num__num__t, "set_spider_reflexes_blur_scale(num,num)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_hero_meter_depletion_rate__num__t, "set_spider_reflexes_hero_meter_depletion_rate(num)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_spiderman_time_dilation__num__t, "set_spider_reflexes_spiderman_time_dilation(num)");
            CREATE_GLOBAL_SLF(slf__set_spider_reflexes_world_time_dilation__num__t, "set_spider_reflexes_world_time_dilation(num)");
            CREATE_GLOBAL_SLF(slf__set_state_of_the_story_caption__num__t, "set_state_of_the_story_caption(num)");
            CREATE_GLOBAL_SLF(slf__set_target_info__entity__vector3d__vector3d__t, "set_target_info(entity,vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__set_time_of_day__num__t, "set_time_of_day(num)");
            CREATE_GLOBAL_SLF(slf__set_traffic_density__num__t, "set_traffic_density(num)");
            CREATE_GLOBAL_SLF(slf__set_traffic_model_usage__num__num__t, "set_traffic_model_usage(num,num)");
            CREATE_GLOBAL_SLF(slf__set_vibration_resume__num__t, "set_vibration_resume(num)");
            CREATE_GLOBAL_SLF(slf__set_whoosh_interp_rate__num__t, "set_whoosh_interp_rate(num)");
            CREATE_GLOBAL_SLF(slf__set_whoosh_pitch_range__num__num__t, "set_whoosh_pitch_range(num,num)");
            CREATE_GLOBAL_SLF(slf__set_whoosh_speed_range__num__num__t, "set_whoosh_speed_range(num,num)");
            CREATE_GLOBAL_SLF(slf__set_whoosh_volume_range__num__num__t, "set_whoosh_volume_range(num,num)");
            CREATE_GLOBAL_SLF(slf__set_zoom__num__t, "set_zoom(num)");
            CREATE_GLOBAL_SLF(slf__show_controller_gauge__t, "show_controller_gauge()");
            CREATE_GLOBAL_SLF(slf__show_hotpursuit_indicator__num__t, "show_hotpursuit_indicator(num)");
            CREATE_GLOBAL_SLF(slf__show_score_widget__num__t, "show_score_widget(num)");
            CREATE_GLOBAL_SLF(slf__shut_up_all_ai_voice_boxes__t, "shut_up_all_ai_voice_boxes()");
            CREATE_GLOBAL_SLF(slf__sin__num__t, "sin(num)");
            CREATE_GLOBAL_SLF(slf__sin_cos__num__t, "sin_cos(num)");
            CREATE_GLOBAL_SLF(slf__soft_load__num__t, "soft_load(num)");
            CREATE_GLOBAL_SLF(slf__soft_save__num__t, "soft_save(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_add_hero_points__num__t, "spiderman_add_hero_points(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_bank_stylepoints__t, "spiderman_bank_stylepoints()");
            CREATE_GLOBAL_SLF(slf__spiderman_break_web__t, "spiderman_break_web()");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_add_shake__num__num__num__t, "spiderman_camera_add_shake(num,num,num)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_autocorrect__num__t, "spiderman_camera_autocorrect(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_clear_fixedstatic__t, "spiderman_camera_clear_fixedstatic()");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_enable_combat__num__t, "spiderman_camera_enable_combat(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_enable_lookaround__num__t, "spiderman_camera_enable_lookaround(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_set_fixedstatic__vector3d__vector3d__t, "spiderman_camera_set_fixedstatic(vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_set_follow__entity__t, "spiderman_camera_set_follow(entity)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_set_hero_underwater__num__t, "spiderman_camera_set_hero_underwater(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_set_interpolation_time__num__t, "spiderman_camera_set_interpolation_time(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_set_lockon_min_distance__num__t, "spiderman_camera_set_lockon_min_distance(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_camera_set_lockon_y_offset__num__t, "spiderman_camera_set_lockon_y_offset(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_charged_jump__t, "spiderman_charged_jump()");
            CREATE_GLOBAL_SLF(slf__spiderman_enable_control_button__num__num__t, "spiderman_enable_control_button(num,num)");
            CREATE_GLOBAL_SLF(slf__spiderman_enable_lockon__num__t, "spiderman_enable_lockon(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_engage_lockon__num__t, "spiderman_engage_lockon(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_engage_lockon__num__entity__t, "spiderman_engage_lockon(num,entity)");
            CREATE_GLOBAL_SLF(slf__spiderman_get_hero_points__t, "spiderman_get_hero_points()");
            CREATE_GLOBAL_SLF(slf__spiderman_get_max_zip_length__t, "spiderman_get_max_zip_length()");
            CREATE_GLOBAL_SLF(slf__spiderman_get_spidey_sense_level__t, "spiderman_get_spidey_sense_level()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_crawling__t, "spiderman_is_crawling()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_falling__t, "spiderman_is_falling()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_jumping__t, "spiderman_is_jumping()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_on_ceiling__t, "spiderman_is_on_ceiling()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_on_ground__t, "spiderman_is_on_ground()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_on_wall__t, "spiderman_is_on_wall()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_running__t, "spiderman_is_running()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_sprint_crawling__t, "spiderman_is_sprint_crawling()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_sprinting__t, "spiderman_is_sprinting()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_swinging__t, "spiderman_is_swinging()");
            CREATE_GLOBAL_SLF(slf__spiderman_is_wallsprinting__t, "spiderman_is_wallsprinting()");
            CREATE_GLOBAL_SLF(slf__spiderman_lock_spider_reflexes_off__t, "spiderman_lock_spider_reflexes_off()");
            CREATE_GLOBAL_SLF(slf__spiderman_lock_spider_reflexes_on__t, "spiderman_lock_spider_reflexes_on()");
            CREATE_GLOBAL_SLF(slf__spiderman_lockon_camera_engaged__t, "spiderman_lockon_camera_engaged()");
            CREATE_GLOBAL_SLF(slf__spiderman_lockon_mode_engaged__t, "spiderman_lockon_mode_engaged()");
            CREATE_GLOBAL_SLF(slf__spiderman_set_camera_target__entity__t, "spiderman_set_camera_target(entity)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_desired_mode__num__vector3d__vector3d__t, "spiderman_set_desired_mode(num,vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_health_beep_min_max_cooldown_time__num__num__t, "spiderman_set_health_beep_min_max_cooldown_time(num,num)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_health_beep_threshold__num__t, "spiderman_set_health_beep_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_hero_meter_empty_rate__num__t, "spiderman_set_hero_meter_empty_rate(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_max_height__num__t, "spiderman_set_max_height(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_max_zip_length__num__t, "spiderman_set_max_zip_length(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_min_height__num__t, "spiderman_set_min_height(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_spidey_sense_level__num__t, "spiderman_set_spidey_sense_level(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_set_swing_anchor_max_sticky_time__num__t, "spiderman_set_swing_anchor_max_sticky_time(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_subtract_hero_points__num__t, "spiderman_subtract_hero_points(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_alternating_wall_run_occurrence_threshold__num__t, "spiderman_td_set_alternating_wall_run_occurrence_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_alternating_wall_run_time_threshold__num__t, "spiderman_td_set_alternating_wall_run_time_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_big_air_height_threshold__num__t, "spiderman_td_set_big_air_height_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_continuous_air_swings_threshold__num__t, "spiderman_td_set_continuous_air_swings_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_gain_altitude_height_threshold__num__t, "spiderman_td_set_gain_altitude_height_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_near_miss_trigger_radius__num__t, "spiderman_td_set_near_miss_trigger_radius(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_near_miss_velocity_threshold__num__t, "spiderman_td_set_near_miss_velocity_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_orbit_min_radius_threshold__num__t, "spiderman_td_set_orbit_min_radius_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_soft_landing_velocity_threshold__num__t, "spiderman_td_set_soft_landing_velocity_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_super_speed_speed_threshold__num__t, "spiderman_td_set_super_speed_speed_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_swinging_wall_run_time_threshold__num__t, "spiderman_td_set_swinging_wall_run_time_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_td_set_wall_sprint_time_threshold__num__t, "spiderman_td_set_wall_sprint_time_threshold(num)");
            CREATE_GLOBAL_SLF(slf__spiderman_unlock_spider_reflexes__t, "spiderman_unlock_spider_reflexes()");
            CREATE_GLOBAL_SLF(slf__spiderman_wait_add_threat__entity__str__num__num__t, "spiderman_wait_add_threat(entity,str,num,num)");
            CREATE_GLOBAL_SLF(slf__spidey_can_see__vector3d__t, "spidey_can_see(vector3d)");
            CREATE_GLOBAL_SLF(slf__sqrt__num__t, "sqrt(num)");
            CREATE_GLOBAL_SLF(slf__start_patrol__str__t, "start_patrol(str)");
            CREATE_GLOBAL_SLF(slf__stop_all_sounds__t, "stop_all_sounds()");
            CREATE_GLOBAL_SLF(slf__stop_credits__t, "stop_credits()");
            CREATE_GLOBAL_SLF(slf__stop_vibration__t, "stop_vibration()");
            CREATE_GLOBAL_SLF(slf__subtitle__num__num__num__num__num__num__t, "subtitle(num,num,num,num,num,num)");
            CREATE_GLOBAL_SLF(slf__swap_hero_costume__str__t, "swap_hero_costume(str)");
            CREATE_GLOBAL_SLF(slf__text_width__str__t, "text_width(str)");
            CREATE_GLOBAL_SLF(slf__timer_widget_get_count_up__t, "timer_widget_get_count_up()");
            CREATE_GLOBAL_SLF(slf__timer_widget_get_time__t, "timer_widget_get_time()");
            CREATE_GLOBAL_SLF(slf__timer_widget_set_count_up__num__t, "timer_widget_set_count_up(num)");
            CREATE_GLOBAL_SLF(slf__timer_widget_set_time__num__t, "timer_widget_set_time(num)");
            CREATE_GLOBAL_SLF(slf__timer_widget_start__t, "timer_widget_start()");
            CREATE_GLOBAL_SLF(slf__timer_widget_stop__t, "timer_widget_stop()");
            CREATE_GLOBAL_SLF(slf__timer_widget_turn_off__t, "timer_widget_turn_off()");
            CREATE_GLOBAL_SLF(slf__timer_widget_turn_on__t, "timer_widget_turn_on()");
            CREATE_GLOBAL_SLF(slf__to_beam__entity__t, "to_beam(entity)");
            CREATE_GLOBAL_SLF(slf__to_gun__entity__t, "to_gun(entity)");
            CREATE_GLOBAL_SLF(slf__to_item__entity__t, "to_item(entity)");
            CREATE_GLOBAL_SLF(slf__to_polytube__entity__t, "to_polytube(entity)");
            CREATE_GLOBAL_SLF(slf__to_switch__entity__t, "to_switch(entity)");
            CREATE_GLOBAL_SLF(slf__trace__str__t, "trace(str)");
            CREATE_GLOBAL_SLF(slf__trigger_is_valid__trigger__t, "trigger_is_valid(trigger)");
            CREATE_GLOBAL_SLF(slf__turn_off_boss_health__t, "turn_off_boss_health()");
            CREATE_GLOBAL_SLF(slf__turn_off_hero_health__t, "turn_off_hero_health()");
            CREATE_GLOBAL_SLF(slf__turn_off_mission_text__t, "turn_off_mission_text()");
            CREATE_GLOBAL_SLF(slf__turn_off_third_party_health__t, "turn_off_third_party_health()");
            CREATE_GLOBAL_SLF(slf__turn_on_boss_health__num__entity__t, "turn_on_boss_health(num,entity)");
            CREATE_GLOBAL_SLF(slf__turn_on_hero_health__num__entity__t, "turn_on_hero_health(num,entity)");
            CREATE_GLOBAL_SLF(slf__turn_on_third_party_health__num__entity__t, "turn_on_third_party_health(num,entity)");
            CREATE_GLOBAL_SLF(slf__unload_script__t, "unload_script()");
            CREATE_GLOBAL_SLF(slf__unlock_all_exterior_districts__t, "unlock_all_exterior_districts()");
            CREATE_GLOBAL_SLF(slf__unlock_district__num__t, "unlock_district(num)");
            CREATE_GLOBAL_SLF(slf__vibrate_controller__num__t, "vibrate_controller(num)");
            CREATE_GLOBAL_SLF(slf__vibrate_controller__num__num__t, "vibrate_controller(num,num)");
            CREATE_GLOBAL_SLF(slf__vibrate_controller__num__num__num__num__num__num__t, "vibrate_controller(num,num,num,num,num,num)");
            CREATE_GLOBAL_SLF(slf__vo_delay__num__num__num__num__t, "vo_delay(num,num,num,num)");
            CREATE_GLOBAL_SLF(slf__wait_animate_fog_color__vector3d__num__t, "wait_animate_fog_color(vector3d,num)");
            CREATE_GLOBAL_SLF(slf__wait_animate_fog_distance__num__num__t, "wait_animate_fog_distance(num,num)");
            CREATE_GLOBAL_SLF(slf__wait_animate_fog_distances__num__num__num__t, "wait_animate_fog_distances(num,num,num)");
            CREATE_GLOBAL_SLF(slf__wait_change_blur__num__vector3d__num__num__num__num__num__num__t, "wait_change_blur(num,vector3d,num,num,num,num,num,num)");
            CREATE_GLOBAL_SLF(slf__wait_change_spider_reflexes_blur__num__vector3d__num__num__num__num__num__num__t, "wait_change_spider_reflexes_blur(num,vector3d,num,num,num,num,num,num)");
            CREATE_GLOBAL_SLF(slf__wait_for_streamer_to_reach_equilibrium__t, "wait_for_streamer_to_reach_equilibrium()");
            CREATE_GLOBAL_SLF(slf__wait_fps_test__num__num__vector3d__vector3d__t, "wait_fps_test(num,num,vector3d,vector3d)");
            CREATE_GLOBAL_SLF(slf__wait_frame__t, "wait_frame()");
            CREATE_GLOBAL_SLF(slf__wait_set_global_time_dilation__num__num__t, "wait_set_global_time_dilation(num,num)");
            CREATE_GLOBAL_SLF(slf__wait_set_zoom__num__num__t, "wait_set_zoom(num,num)");
            CREATE_GLOBAL_SLF(slf__write_to_file__str__str__t, "write_to_file(str,str)");
        }

#undef CREATE_GLOBAL_SLF

#define CREATE_SLF(KLASS, TYPE, NAME)                                              \
    new (mem_alloc(sizeof(BUILD_SLF_NAME(KLASS, TYPE)))) BUILD_SLF_NAME(KLASS, TYPE) {slc, NAME}
        {
            auto *slc = classes[2];
            CREATE_SLF(anim, kill_anim, "kill_anim()");
            CREATE_SLF(anim, pause, "pause()");
            CREATE_SLF(anim, play, "play()");
            CREATE_SLF(anim, set_fade_time__num, "set_fade_time(num)");
            CREATE_SLF(anim, set_time__num, "set_time(num)");
            CREATE_SLF(anim, set_timescale__num, "set_timescale(num)");
            CREATE_SLF(anim, wait_finished, "wait_finished()");

            slc = classes[3];
            CREATE_SLF(beam, add_alpha_effect__num__num__num__num__num__num, "add_alpha_effect(num,num,num,num,num,num)");
            CREATE_SLF(beam, add_color_effect__num__num__num__num__num__num__num__num__num__num, "add_color_effect(num,num,num,num,num,num,num,num,num,num)");
            CREATE_SLF(beam, add_width_effect__num__num__num__num__num__num, "add_width_effect(num,num,num,num,num,num)");
            CREATE_SLF(beam, get_impact_normal, "get_impact_normal()");
            CREATE_SLF(beam, get_impact_point, "get_impact_point()");
            CREATE_SLF(beam, hit_hero, "hit_hero()");
            CREATE_SLF(beam, hit_world, "hit_world()");
            CREATE_SLF(beam, kill_all_effects__num, "kill_all_effects(num)");
            CREATE_SLF(beam, kill_effect__num__num, "kill_effect(num,num)");
            CREATE_SLF(beam, set_additive__num, "set_additive(num)");
            CREATE_SLF(beam, set_collide_beamable__num, "set_collide_beamable(num)");
            CREATE_SLF(beam, set_collide_hero__num, "set_collide_hero(num)");
            CREATE_SLF(beam, set_collide_world__num, "set_collide_world(num)");
            CREATE_SLF(beam, set_color__num__num__num__num, "set_color(num,num,num,num)");
            CREATE_SLF(beam, set_detect_stealth__num, "set_detect_stealth(num)");
            CREATE_SLF(beam, set_material__str, "set_material(str)");
            CREATE_SLF(beam, set_max_length__num, "set_max_length(num)");
            CREATE_SLF(beam, set_no_collision, "set_no_collision()");
            CREATE_SLF(beam, set_point_to_point__vector3d__vector3d, "set_point_to_point(vector3d,vector3d)");
            CREATE_SLF(beam, set_thickness__num, "set_thickness(num)");
            CREATE_SLF(beam, set_tiles_per_meter__num, "set_tiles_per_meter(num)");
            CREATE_SLF(beam, set_uv_anim__num__num, "set_uv_anim(num,num)");

            slc = classes[38];
            CREATE_SLF(critical_section, critical_section__num, "critical_section(num)");

            slc = classes[5];
            CREATE_SLF(cut_scene, wait_play, "wait_play()");
            CREATE_SLF(cut_scene, wait_play__entity_list, "wait_play(entity_list)");

            slc = classes[6];
            CREATE_SLF(debug_menu_entry, get_handler, "get_handler()");
            CREATE_SLF(debug_menu_entry, get_id, "get_id()");
            CREATE_SLF(debug_menu_entry, get_max_value, "get_max_value()");
            CREATE_SLF(debug_menu_entry, get_min_value, "get_min_value()");
            CREATE_SLF(debug_menu_entry, get_name, "get_name()");
            CREATE_SLF(debug_menu_entry, get_step_scale, "get_step_scale()");
            CREATE_SLF(debug_menu_entry, get_step_size, "get_step_size()");
            CREATE_SLF(debug_menu_entry, get_value, "get_value()");
            CREATE_SLF(debug_menu_entry, get_value_type, "get_value_type()");
            CREATE_SLF(debug_menu_entry, set_handler__str, "set_handler(str)");
            CREATE_SLF(debug_menu_entry, set_id__num, "set_id(num)");
            CREATE_SLF(debug_menu_entry, set_max_value__num, "set_max_value(num)");
            CREATE_SLF(debug_menu_entry, set_min_value__num, "set_min_value(num)");
            CREATE_SLF(debug_menu_entry, set_name__str, "set_name(str)");
            CREATE_SLF(debug_menu_entry, set_step_scale__num, "set_step_scale(num)");
            CREATE_SLF(debug_menu_entry, set_step_size__num, "set_step_size(num)");
            CREATE_SLF(debug_menu_entry, set_value__num, "set_value(num)");
            CREATE_SLF(debug_menu_entry, set_value_type__num, "set_value_type(num)");

            slc = classes[39];
            CREATE_SLF(district, contains_point__vector3d, "contains_point(vector3d)");
            CREATE_SLF(district, district__num, "district(num)");
            CREATE_SLF(district, district__str, "district(str)");
            CREATE_SLF(district, get_id, "get_id()");
            CREATE_SLF(district, get_name, "get_name()");
            CREATE_SLF(district, get_neighborhood, "get_neighborhood()");
            CREATE_SLF(district, get_num_missions__str, "get_num_missions(str)");
            CREATE_SLF(district, get_variant, "get_variant()");
            CREATE_SLF(district, get_variant_count, "get_variant_count()");
            CREATE_SLF(district, is_in_neighborhood__num, "is_in_neighborhood(num)");
            CREATE_SLF(district, is_loaded, "is_loaded()");
            CREATE_SLF(district, is_locked, "is_locked()");
            CREATE_SLF(district, lock, "lock()");
            CREATE_SLF(district, purge, "purge()");
            CREATE_SLF(district, set_variant__num, "set_variant(num)");
            CREATE_SLF(district, unlock, "unlock()");
            CREATE_SLF(district, wait_for_load, "wait_for_load()");

            slc = classes[4];
            CREATE_SLF(entity, abs_snap_to__entity, "abs_snap_to(entity)");
            CREATE_SLF(entity, add_collision_ignorance__entity, "add_collision_ignorance(entity)");
            CREATE_SLF(entity, add_exclusive_interactor__string_hash__interactable_interface, "add_exclusive_interactor(string_hash,interactable_interface)");
            CREATE_SLF(entity, add_item__entity, "add_item(entity)");
            CREATE_SLF(entity, add_selectable_target__entity, "add_selectable_target(entity)");
            CREATE_SLF(entity, add_vehicle_to_traffic_system__num, "add_vehicle_to_traffic_system(num)");
            CREATE_SLF(entity, ai_get_viseme_morph_set__str__str, "ai_get_viseme_morph_set(str,str)");
            CREATE_SLF(entity, ai_get_viseme_stream__str, "ai_get_viseme_stream(str)");
            CREATE_SLF(entity, ai_is_speaking, "ai_is_speaking()");
            CREATE_SLF(entity, ai_run_lip_sync__str, "ai_run_lip_sync(str)");
            CREATE_SLF(entity, ai_say_file__str__num__num, "ai_say_file(str,num,num)");
            CREATE_SLF(entity, ai_say_gab__str__num__num, "ai_say_gab(str,num,num)");
            CREATE_SLF(entity, ai_say_sound_group__str__num__num, "ai_say_sound_group(str,num,num)");
            CREATE_SLF(entity, ai_shut_up, "ai_shut_up()");
            CREATE_SLF(entity, ai_traffic_come_on_camera__vector3d__num, "ai_traffic_come_on_camera(vector3d,num)");
            CREATE_SLF(entity, ai_traffic_come_on_camera__vector3d__vector3d__num, "ai_traffic_come_on_camera(vector3d,vector3d,num)");
            CREATE_SLF(entity, ai_traffic_follow_entity__entity__num, "ai_traffic_follow_entity(entity,num)");
            CREATE_SLF(entity, ai_traffic_follow_vehicle__entity, "ai_traffic_follow_vehicle(entity)");
            CREATE_SLF(entity, ai_traffic_get_value__num, "ai_traffic_get_value(num)");
            CREATE_SLF(entity, ai_traffic_get_value__num__num, "ai_traffic_get_value(num,num)");
            CREATE_SLF(entity, ai_traffic_goto__vector3d__num__num__num, "ai_traffic_goto(vector3d,num,num,num)");
            CREATE_SLF(entity, ai_traffic_set_value__num__num, "ai_traffic_set_value(num,num)");
            CREATE_SLF(entity, ai_traffic_spawn_away_from__vector3d__num, "ai_traffic_spawn_away_from(vector3d,num)");
            CREATE_SLF(entity, ai_traffic_spawn_behind__entity, "ai_traffic_spawn_behind(entity)");
            CREATE_SLF(entity, ai_traffic_spawn_near__vector3d, "ai_traffic_spawn_near(vector3d)");
            CREATE_SLF(entity, ai_voice_box_set_team_respect__string_hash__num, "ai_voice_box_set_team_respect(string_hash,num)");
            CREATE_SLF(entity, ai_wait_say_file__str__num__num, "ai_wait_say_file(str,num,num)");
            CREATE_SLF(entity, ai_wait_say_gab__str__num__num, "ai_wait_say_gab(str,num,num)");
            CREATE_SLF(entity, ai_wait_say_preregistered_file__str__num__num, "ai_wait_say_preregistered_file(str,num,num)");
            CREATE_SLF(entity, ai_wait_say_sound_group__str__num__num, "ai_wait_say_sound_group(str,num,num)");
            CREATE_SLF(entity, anim_finished, "anim_finished()");
            CREATE_SLF(entity, anim_finished__num, "anim_finished(num)");
            CREATE_SLF(entity, apply_continuous_rotation__vector3d__num__num, "apply_continuous_rotation(vector3d,num,num)");
            CREATE_SLF(entity, apply_damage__num, "apply_damage(num)");
            CREATE_SLF(entity, apply_directed_damage__num__vector3d, "apply_directed_damage(num,vector3d)");
            CREATE_SLF(entity, apply_directed_damage_cat__num__vector3d__str__num, "apply_directed_damage_cat(num,vector3d,str,num)");
            CREATE_SLF(entity, apply_explosive_damage__num__vector3d, "apply_explosive_damage(num,vector3d)");
            CREATE_SLF(entity, apply_explosive_damage__num__vector3d__vector3d, "apply_explosive_damage(num,vector3d,vector3d)");
            CREATE_SLF(entity, apply_subdue__num, "apply_subdue(num)");
            CREATE_SLF(entity, camera_get_target, "camera_get_target()");
            CREATE_SLF(entity, camera_orbit__vector3d__num__num__num, "camera_orbit(vector3d,num,num,num)");
            CREATE_SLF(entity, camera_set_collide_with_world__num, "camera_set_collide_with_world(num)");
            CREATE_SLF(entity, camera_set_roll__num, "camera_set_roll(num)");
            CREATE_SLF(entity, camera_set_target__vector3d, "camera_set_target(vector3d)");
            CREATE_SLF(entity, camera_slide_to__vector3d__vector3d__num__num, "camera_slide_to(vector3d,vector3d,num,num)");
            CREATE_SLF(entity, camera_slide_to_orbit__vector3d__num__num__num__num, "camera_slide_to_orbit(vector3d,num,num,num,num)");
            CREATE_SLF(entity, cancel_tether, "cancel_tether()");
            CREATE_SLF(entity, car_random_body_and_color, "car_random_body_and_color()");
            CREATE_SLF(entity, change_ai_base_machine__str, "change_ai_base_machine(str)");
            CREATE_SLF(entity, collisions_enabled, "collisions_enabled()");
            CREATE_SLF(entity, compute_sector, "compute_sector()");
            CREATE_SLF(entity, create_damage_interface, "create_damage_interface()");
            CREATE_SLF(entity, create_interactable_ifc, "create_interactable_ifc()");
            CREATE_SLF(entity, create_physical_interface, "create_physical_interface()");
            CREATE_SLF(entity, create_script_data_interface, "create_script_data_interface()");
            CREATE_SLF(entity, create_web_ifc__str__num__num, "create_web_ifc(str,num,num)");
            CREATE_SLF(entity, disable_as_target, "disable_as_target()");
            CREATE_SLF(entity, disable_collisions, "disable_collisions()");
            CREATE_SLF(entity, disable_fading, "disable_fading()");
            CREATE_SLF(entity, disgorge_items, "disgorge_items()");
            CREATE_SLF(entity, enable_as_target, "enable_as_target()");
            CREATE_SLF(entity, enable_collisions, "enable_collisions()");
            CREATE_SLF(entity, enable_collisions__num, "enable_collisions(num)");
            CREATE_SLF(entity, eye_check_ent__entity, "eye_check_ent(entity)");
            CREATE_SLF(entity, eye_check_pos__vector3d, "eye_check_pos(vector3d)");
            CREATE_SLF(entity, force_activate_interaction__string_hash__interactable_interface, "force_activate_interaction(string_hash,interactable_interface)");
            CREATE_SLF(entity, force_current_region, "force_current_region()");
            CREATE_SLF(entity, force_region__entity, "force_region(entity)");
            CREATE_SLF(entity, get_abs_position, "get_abs_position()");
            CREATE_SLF(entity, get_ai_base_machine_name, "get_ai_base_machine_name()");
            CREATE_SLF(entity, get_ai_param_float__str, "get_ai_param_float(str)");
            CREATE_SLF(entity, get_ai_param_hash__str, "get_ai_param_hash(str)");
            CREATE_SLF(entity, get_ai_param_int__str, "get_ai_param_int(str)");
            CREATE_SLF(entity, get_ai_param_str__str, "get_ai_param_str(str)");
            CREATE_SLF(entity, get_ai_param_vector3d__str, "get_ai_param_vector3d(str)");
            CREATE_SLF(entity, get_ai_signaller, "get_ai_signaller()");
            CREATE_SLF(entity, get_anchor_point, "get_anchor_point()");
            CREATE_SLF(entity, get_carry_slave, "get_carry_slave()");
            CREATE_SLF(entity, get_current_animation_name, "get_current_animation_name()");
            CREATE_SLF(entity, get_damage_force, "get_damage_force()");
            CREATE_SLF(entity, get_debug_name, "get_debug_name()");
            CREATE_SLF(entity, get_detonate_position, "get_detonate_position()");
            CREATE_SLF(entity, get_district, "get_district()");
            CREATE_SLF(entity, get_facing, "get_facing()");
            CREATE_SLF(entity, get_fade_timer, "get_fade_timer()");
            CREATE_SLF(entity, get_first_child, "get_first_child()");
            CREATE_SLF(entity, get_hash_name, "get_hash_name()");
            CREATE_SLF(entity, get_hidey_pos__vector3d__num, "get_hidey_pos(vector3d,num)");
            CREATE_SLF(entity, get_ifc_num__str, "get_ifc_num(str)");
            CREATE_SLF(entity, get_ifc_str__str, "get_ifc_str(str)");
            CREATE_SLF(entity, get_ifc_vec__str, "get_ifc_vec(str)");
            CREATE_SLF(entity, get_ifl_frame, "get_ifl_frame()");
            CREATE_SLF(entity, get_inode_param_float__str__str, "get_inode_param_float(str,str)");
            CREATE_SLF(entity, get_inode_param_hash__str__str, "get_inode_param_hash(str,str)");
            CREATE_SLF(entity, get_inode_param_int__str__str, "get_inode_param_int(str,str)");
            CREATE_SLF(entity, get_inode_param_str__str__str, "get_inode_param_str(str,str)");
            CREATE_SLF(entity, get_inode_param_vector3d__str__str, "get_inode_param_vector3d(str,str)");
            CREATE_SLF(entity, get_interactable_ifc, "get_interactable_ifc()");
            CREATE_SLF(entity, get_item__num, "get_item(num)");
            CREATE_SLF(entity, get_item_by_name__str, "get_item_by_name(str)");
            CREATE_SLF(entity, get_item_quantity__num, "get_item_quantity(num)");
            CREATE_SLF(entity, get_last_anchor, "get_last_anchor()");
            CREATE_SLF(entity, get_last_attacker, "get_last_attacker()");
            CREATE_SLF(entity, get_last_item_used, "get_last_item_used()");
            CREATE_SLF(entity, get_member__str, "get_member(str)");
            CREATE_SLF(entity, get_next_sibling, "get_next_sibling()");
            CREATE_SLF(entity, get_num_items, "get_num_items()");
            CREATE_SLF(entity, get_parent, "get_parent()");
            CREATE_SLF(entity, get_pendulum_length, "get_pendulum_length()");
            CREATE_SLF(entity, get_rel_position, "get_rel_position()");
            CREATE_SLF(entity, get_rel_velocity__entity, "get_rel_velocity(entity)");
            CREATE_SLF(entity, get_render_alpha, "get_render_alpha()");
            CREATE_SLF(entity, get_render_color, "get_render_color()");
            CREATE_SLF(entity, get_scripted_target, "get_scripted_target()");
            CREATE_SLF(entity, get_sector_name, "get_sector_name()");
            CREATE_SLF(entity, get_state__num, "get_state(num)");
            CREATE_SLF(entity, get_time_dilation, "get_time_dilation()");
            CREATE_SLF(entity, get_time_mode, "get_time_mode()");
            CREATE_SLF(entity, get_x_facing, "get_x_facing()");
            CREATE_SLF(entity, get_y_facing, "get_y_facing()");
            CREATE_SLF(entity, get_z_facing, "get_z_facing()");
            CREATE_SLF(entity, has_carry_slave, "has_carry_slave()");
            CREATE_SLF(entity, has_member__str, "has_member(str)");
            CREATE_SLF(entity, has_script_data_interface, "has_script_data_interface()");
            CREATE_SLF(entity, hates__entity, "hates(entity)");
            CREATE_SLF(entity, ifl_damage_lock__num, "ifl_damage_lock(num)");
            CREATE_SLF(entity, ifl_lock__num, "ifl_lock(num)");
            CREATE_SLF(entity, ifl_pause, "ifl_pause()");
            CREATE_SLF(entity, ifl_play, "ifl_play()");
            CREATE_SLF(entity, in_sector__vector3d__vector3d__num, "in_sector(vector3d,vector3d,num)");
            CREATE_SLF(entity, inhibit_universal_soldier_ability__str__num, "inhibit_universal_soldier_ability(str,num)");
            CREATE_SLF(entity, invoke_facial_expression__num__num__num__num, "invoke_facial_expression(num,num,num,num)");
            CREATE_SLF(entity, is_a_car, "is_a_car()");
            CREATE_SLF(entity, is_picked_up, "is_picked_up()");
            CREATE_SLF(entity, is_suspended, "is_suspended()");
            CREATE_SLF(entity, is_throwable, "is_throwable()");
            CREATE_SLF(entity, is_valid, "is_valid()");
            CREATE_SLF(entity, is_visible, "is_visible()");
            CREATE_SLF(entity, kill_anim_in_slot__num, "kill_anim_in_slot(num)");
            CREATE_SLF(entity, likes__entity, "likes(entity)");
            CREATE_SLF(entity, look_at__vector3d, "look_at(vector3d)");
            CREATE_SLF(entity, motion_blur_off, "motion_blur_off()");
            CREATE_SLF(entity, motion_blur_on__num__num__num, "motion_blur_on(num,num,num)");
            CREATE_SLF(entity, motion_trail_off, "motion_trail_off()");
            CREATE_SLF(entity, motion_trail_on__entity__entity__vector3d__num__num__num__num, "motion_trail_on(entity,entity,vector3d,num,num,num,num)");
            CREATE_SLF(entity, motion_trail_on__entity__str__num__num__vector3d__num__num__num__num, "motion_trail_on(entity,str,num,num,vector3d,num,num,num,num)");
            CREATE_SLF(entity, neutral__entity, "neutral(entity)");
            CREATE_SLF(entity, operator_not_equals__entity, "operator!=(entity)");
            CREATE_SLF(entity, operator_equals_equals__entity, "operator==(entity)");
            CREATE_SLF(entity, physical_ifc_add_particle__str, "physical_ifc_add_particle(str)");
            CREATE_SLF(entity, physical_ifc_apply_force__vector3d__num, "physical_ifc_apply_force(vector3d,num)");
            CREATE_SLF(entity, physical_ifc_cancel_all_velocity, "physical_ifc_cancel_all_velocity()");
            CREATE_SLF(entity, physical_ifc_clear_pendulum, "physical_ifc_clear_pendulum()");
            CREATE_SLF(entity, physical_ifc_get_attached_particle_name, "physical_ifc_get_attached_particle_name()");
            CREATE_SLF(entity, physical_ifc_get_bounce_particle_name, "physical_ifc_get_bounce_particle_name()");
            CREATE_SLF(entity, physical_ifc_is_biped_physics_running, "physical_ifc_is_biped_physics_running()");
            CREATE_SLF(entity, physical_ifc_is_effectively_standing, "physical_ifc_is_effectively_standing()");
            CREATE_SLF(entity, physical_ifc_is_prop_physics_at_rest, "physical_ifc_is_prop_physics_at_rest()");
            CREATE_SLF(entity, physical_ifc_is_prop_physics_running, "physical_ifc_is_prop_physics_running()");
            CREATE_SLF(entity, physical_ifc_manage_standing__num, "physical_ifc_manage_standing(num)");
            CREATE_SLF(entity, physical_ifc_set_allow_biped_physics__num, "physical_ifc_set_allow_biped_physics(num)");
            CREATE_SLF(entity, physical_ifc_set_attached_particle_name__str, "physical_ifc_set_attached_particle_name(str)");
            CREATE_SLF(entity, physical_ifc_set_bounce_particle_name__str, "physical_ifc_set_bounce_particle_name(str)");
            CREATE_SLF(entity, physical_ifc_set_pendulum__entity__num, "physical_ifc_set_pendulum(entity,num)");
            CREATE_SLF(entity, physical_ifc_set_pendulum__vector3d__num, "physical_ifc_set_pendulum(vector3d,num)");
            CREATE_SLF(entity, physical_ifc_start_biped_physics, "physical_ifc_start_biped_physics()");
            CREATE_SLF(entity, physical_ifc_start_prop_physics__vector3d__num, "physical_ifc_start_prop_physics(vector3d,num)");
            CREATE_SLF(entity, physical_ifc_stop_biped_physics, "physical_ifc_stop_biped_physics()");
            CREATE_SLF(entity, physical_ifc_stop_prop_physics, "physical_ifc_stop_prop_physics()");
            CREATE_SLF(entity, play_anim__str, "play_anim(str)");
            CREATE_SLF(entity, play_anim__str__num__num, "play_anim(str,num,num)");
            CREATE_SLF(entity, poison__num__num, "poison(num,num)");
            CREATE_SLF(entity, pop_ai_base_machine, "pop_ai_base_machine()");
            CREATE_SLF(entity, pre_roll__num, "pre_roll(num)");
            CREATE_SLF(entity, push_ai_base_machine__str, "push_ai_base_machine(str)");
            CREATE_SLF(entity, randomize_position__vector3d__num__num__num, "randomize_position(vector3d,num,num,num)");
            CREATE_SLF(entity, regenerate__num__num, "regenerate(num,num)");
            CREATE_SLF(entity, rel_angle__vector3d, "rel_angle(vector3d)");
            CREATE_SLF(entity, remove_collision_ignorance__entity, "remove_collision_ignorance(entity)");
            CREATE_SLF(entity, remove_exclusive_interactor__string_hash__interactable_interface, "remove_exclusive_interactor(string_hash,interactable_interface)");
            CREATE_SLF(entity, remove_selectable_target__entity, "remove_selectable_target(entity)");
            CREATE_SLF(entity, remove_vehicle_from_traffic_system, "remove_vehicle_from_traffic_system()");
            CREATE_SLF(entity, reset_ai, "reset_ai()");
            CREATE_SLF(entity, restart, "restart()");
            CREATE_SLF(entity, seriously_kill, "seriously_kill()");
            CREATE_SLF(entity, set_abs_xz_facing__vector3d, "set_abs_xz_facing(vector3d)");
            CREATE_SLF(entity, set_active__num, "set_active(num)");
            CREATE_SLF(entity, set_ai_param_float__str__num, "set_ai_param_float(str,num)");
            CREATE_SLF(entity, set_ai_param_float_variance__str__num__num, "set_ai_param_float_variance(str,num,num)");
            CREATE_SLF(entity, set_ai_param_hash__str__num, "set_ai_param_hash(str,num)");
            CREATE_SLF(entity, set_ai_param_hash__str__str, "set_ai_param_hash(str,str)");
            CREATE_SLF(entity, set_ai_param_hash__str__string_hash, "set_ai_param_hash(str,string_hash)");
            CREATE_SLF(entity, set_ai_param_int__str__num, "set_ai_param_int(str,num)");
            CREATE_SLF(entity, set_ai_param_str__str__str, "set_ai_param_str(str,str)");
            CREATE_SLF(entity, set_ai_param_vector3d__str__vector3d, "set_ai_param_vector3d(str,vector3d)");
            CREATE_SLF(entity, set_ambient_factor__vector3d, "set_ambient_factor(vector3d)");
            CREATE_SLF(entity, set_anchor_activated__num, "set_anchor_activated(num)");
            CREATE_SLF(entity, set_car_combat_info__num__num__num__num__num__num__num__num, "set_car_combat_info(num,num,num,num,num,num,num,num)");
            CREATE_SLF(entity, set_crawlable__num, "set_crawlable(num)");
            CREATE_SLF(entity, set_default_variant, "set_default_variant()");
            CREATE_SLF(entity, set_distance_clip__num, "set_distance_clip(num)");
            CREATE_SLF(entity, set_entity_blur__num, "set_entity_blur(num)");
            CREATE_SLF(entity, set_facing__vector3d__vector3d, "set_facing(vector3d,vector3d)");
            CREATE_SLF(entity, set_fade_timer__num, "set_fade_timer(num)");
            CREATE_SLF(entity, set_hires_shadow__num, "set_hires_shadow(num)");
            CREATE_SLF(entity, set_ifc_num__str__num, "set_ifc_num(str,num)");
            CREATE_SLF(entity, set_ifc_str__str__str, "set_ifc_str(str,str)");
            CREATE_SLF(entity, set_ifc_vec__str__vector3d, "set_ifc_vec(str,vector3d)");
            CREATE_SLF(entity, set_ignore_limbo__num, "set_ignore_limbo(num)");
            CREATE_SLF(entity, set_immobile__num, "set_immobile(num)");
            CREATE_SLF(entity, set_inode_param_entity__str__str__entity, "set_inode_param_entity(str,str,entity)");
            CREATE_SLF(entity, set_inode_param_float__str__str__num, "set_inode_param_float(str,str,num)");
            CREATE_SLF(entity, set_inode_param_float_variance__str__str__num__num, "set_inode_param_float_variance(str,str,num,num)");
            CREATE_SLF(entity, set_inode_param_hash__str__str__num, "set_inode_param_hash(str,str,num)");
            CREATE_SLF(entity, set_inode_param_hash__str__str__str, "set_inode_param_hash(str,str,str)");
            CREATE_SLF(entity, set_inode_param_int__str__str__num, "set_inode_param_int(str,str,num)");
            CREATE_SLF(entity, set_inode_param_str__str__str__str, "set_inode_param_str(str,str,str)");
            CREATE_SLF(entity, set_inode_param_vector3d__str__str__vector3d, "set_inode_param_vector3d(str,str,vector3d)");
            CREATE_SLF(entity, set_invulnerable__num, "set_invulnerable(num)");
            CREATE_SLF(entity, set_kill_ent_on_destroy__num, "set_kill_ent_on_destroy(num)");
            CREATE_SLF(entity, set_member_hidden__num, "set_member_hidden(num)");
            CREATE_SLF(entity, set_parent__entity, "set_parent(entity)");
            CREATE_SLF(entity, set_parent_rel__entity, "set_parent_rel(entity)");
            CREATE_SLF(entity, set_path_graph__str, "set_path_graph(str)");
            CREATE_SLF(entity, set_path_graph_start_node__num, "set_path_graph_start_node(num)");
            CREATE_SLF(entity, set_pendulum_attach_limb__num, "set_pendulum_attach_limb(num)");
            CREATE_SLF(entity, set_pendulum_length__num, "set_pendulum_length(num)");
            CREATE_SLF(entity, set_physical__num, "set_physical(num)");
            CREATE_SLF(entity, set_po_facing__vector3d, "set_po_facing(vector3d)");
            CREATE_SLF(entity, set_rel_position__vector3d, "set_rel_position(vector3d)");
            CREATE_SLF(entity, set_render_alpha__num, "set_render_alpha(num)");
            CREATE_SLF(entity, set_render_color__vector3d, "set_render_color(vector3d)");
            CREATE_SLF(entity, set_render_scale__vector3d, "set_render_scale(vector3d)");
            CREATE_SLF(entity, set_scale__num, "set_scale(num)");
            CREATE_SLF(entity, set_scripted_target__entity, "set_scripted_target(entity)");
            CREATE_SLF(entity, set_see_thru__num, "set_see_thru(num)");
            CREATE_SLF(entity, set_special_target__num, "set_special_target(num)");
            CREATE_SLF(entity, set_state__num__num, "set_state(num,num)");
            CREATE_SLF(entity, set_targetting__num, "set_targetting(num)");
            CREATE_SLF(entity, set_throwable__num, "set_throwable(num)");
            CREATE_SLF(entity, set_time_dilation__num, "set_time_dilation(num)");
            CREATE_SLF(entity, set_time_mode__num, "set_time_mode(num)");
            CREATE_SLF(entity, set_variant__string_hash, "set_variant(string_hash)");
            CREATE_SLF(entity, set_velocity__vector3d, "set_velocity(vector3d)");
            CREATE_SLF(entity, set_visible__num, "set_visible(num)");
            CREATE_SLF(entity, set_visible_and_disable_fading__num, "set_visible_and_disable_fading(num)");
            CREATE_SLF(entity, set_xz_facing__vector3d, "set_xz_facing(vector3d)");
            CREATE_SLF(entity, setup_tether__vector3d__num, "setup_tether(vector3d,num)");
            CREATE_SLF(entity, snap_to__entity, "snap_to(entity)");
            CREATE_SLF(entity, suspend, "suspend()");
            CREATE_SLF(entity, teleport_to_point__vector3d, "teleport_to_point(vector3d)");
            CREATE_SLF(entity, unforce_regions, "unforce_regions()");
            CREATE_SLF(entity, unsuspend, "unsuspend()");
            CREATE_SLF(entity, use_item__str, "use_item(str)");
            CREATE_SLF(entity, use_item_by_id__str, "use_item_by_id(str)");
            CREATE_SLF(entity, wait_camera_set_roll__num__num, "wait_camera_set_roll(num,num)");
            CREATE_SLF(entity, wait_change_color__vector3d__vector3d__num, "wait_change_color(vector3d,vector3d,num)");
            CREATE_SLF(entity, wait_change_range__num__num__num, "wait_change_range(num,num,num)");
            CREATE_SLF(entity, wait_change_render_color__vector3d__num__num, "wait_change_render_color(vector3d,num,num)");
            CREATE_SLF(entity, wait_change_render_scale__vector3d__num, "wait_change_render_scale(vector3d,num)");
            CREATE_SLF(entity, wait_for_not_sector__str, "wait_for_not_sector(str)");
            CREATE_SLF(entity, wait_for_pickup, "wait_for_pickup()");
            CREATE_SLF(entity, wait_for_sector__str, "wait_for_sector(str)");
            CREATE_SLF(entity, wait_lookat__vector3d__num, "wait_lookat(vector3d,num)");
            CREATE_SLF(entity, wait_lookat2__entity__entity__vector3d__num, "wait_lookat2(entity,entity,vector3d,num)");
            CREATE_SLF(entity, wait_looping_anim__str__num__num, "wait_looping_anim(str,num,num)");
            CREATE_SLF(entity, wait_play_anim__str__num__num__num, "wait_play_anim(str,num,num,num)");
            CREATE_SLF(entity, wait_prox__entity__num, "wait_prox(entity,num)");
            CREATE_SLF(entity, wait_prox__vector3d__num, "wait_prox(vector3d,num)");
            CREATE_SLF(entity, wait_prox__vector3d__num__vector3d__num, "wait_prox(vector3d,num,vector3d,num)");
            CREATE_SLF(entity, wait_prox_maxY__vector3d__num__num, "wait_prox_maxY(vector3d,num,num)");
            CREATE_SLF(entity, wait_prox_minY__vector3d__num__num, "wait_prox_minY(vector3d,num,num)");
            CREATE_SLF(entity, wait_prox_sector__vector3d__num__str, "wait_prox_sector(vector3d,num,str)");
            CREATE_SLF(entity, wait_rotate__vector3d__num__num, "wait_rotate(vector3d,num,num)");
            CREATE_SLF(entity, wait_rotate_WCS__vector3d__vector3d__num__num, "wait_rotate_WCS(vector3d,vector3d,num,num)");
            CREATE_SLF(entity, wait_rotate_WCS_cosmetic__vector3d__vector3d__num__num, "wait_rotate_WCS_cosmetic(vector3d,vector3d,num,num)");
            CREATE_SLF(entity, wait_rotate_WCS_with_compute_sector__vector3d__vector3d__num__num, "wait_rotate_WCS_with_compute_sector(vector3d,vector3d,num,num)");
            CREATE_SLF(entity, wait_rotate_cosmetic__vector3d__num__num, "wait_rotate_cosmetic(vector3d,num,num)");
            CREATE_SLF(entity, wait_set_scale__num__num, "wait_set_scale(num,num)");
            CREATE_SLF(entity, wait_translate__vector3d__num, "wait_translate(vector3d,num)");
            CREATE_SLF(entity, wait_translate_WCS__vector3d__num, "wait_translate_WCS(vector3d,num)");
            CREATE_SLF(entity, wait_translate_WCS_cosmetic__vector3d__num, "wait_translate_WCS_cosmetic(vector3d,num)");
            CREATE_SLF(entity, wait_translate_WCS_with_compute_sector__vector3d__num, "wait_translate_WCS_with_compute_sector(vector3d,num)");
            CREATE_SLF(entity, wait_translate_cosmetic__vector3d__num, "wait_translate_cosmetic(vector3d,num)");
            CREATE_SLF(entity, wait_translate_with_compute_sector__vector3d__num, "wait_translate_with_compute_sector(vector3d,num)");
            CREATE_SLF(entity, was_occluded_last_frame, "was_occluded_last_frame()");

            slc = classes[7];
            CREATE_SLF(entity_list, add__entity, "add(entity)");
            CREATE_SLF(entity_list, begin, "begin()");
            CREATE_SLF(entity_list, end, "end()");
            CREATE_SLF(entity_list, get_index__num, "get_index(num)");
            CREATE_SLF(entity_list, remove__entity, "remove(entity)");
            CREATE_SLF(entity_list, remove__entity_list_iterator, "remove(entity_list_iterator)");
            CREATE_SLF(entity_list, set_index__num__entity, "set_index(num,entity)");
            CREATE_SLF(entity_list, size, "size()");

            slc = classes[8];
            CREATE_SLF(entity_list_iterator, get_entity, "get_entity()");
            CREATE_SLF(entity_list_iterator, operator_not_equals__entity_list_iterator, "operator!=(entity_list_iterator)");
            CREATE_SLF(entity_list_iterator, operator_plus_plus, "operator++()");
            CREATE_SLF(entity_list_iterator, operator_minus_munus, "operator--()");
            CREATE_SLF(entity_list_iterator, operator_equals_equals__entity_list_iterator, "operator==(entity_list_iterator)");

            slc = classes[9];
            CREATE_SLF(entity_tracker, get_entity, "get_entity()");
            CREATE_SLF(entity_tracker, get_mini_map_active, "get_mini_map_active()");
            CREATE_SLF(entity_tracker, get_poi_active, "get_poi_active()");
            CREATE_SLF(entity_tracker, set_entity__entity, "set_entity(entity)");
            CREATE_SLF(entity_tracker, set_health_widget_active__num, "set_health_widget_active(num)");
            CREATE_SLF(entity_tracker, set_mini_map_active__num, "set_mini_map_active(num)");
            CREATE_SLF(entity_tracker, set_poi_active__num, "set_poi_active(num)");
            CREATE_SLF(entity_tracker, set_poi_icon__num, "set_poi_icon(num)");

            slc = classes[10];
            CREATE_SLF(glamour_cam, set_angle__num__num__num__num, "set_angle(num,num,num,num)");
            CREATE_SLF(glamour_cam, set_look_at_bone__str, "set_look_at_bone(str)");
            CREATE_SLF(glamour_cam, set_position_bone__str, "set_position_bone(str)");
            CREATE_SLF(glamour_cam, set_target__entity, "set_target(entity)");

            slc = classes[11];
            CREATE_SLF(gun, get_blaster_beam, "get_blaster_beam()");
            CREATE_SLF(gun, get_muzzle_pos, "get_muzzle_pos()");
            CREATE_SLF(gun, set_target_info__entity__vector3d__vector3d, "set_target_info(entity,vector3d,vector3d)");

            slc = classes[1];
            CREATE_SLF(interactable_interface, add_box_trigger__string_hash__num__vector3d__vector3d, "add_box_trigger(string_hash,num,vector3d,vector3d)");
            CREATE_SLF(interactable_interface, add_named_box_trigger__string_hash__str, "add_named_box_trigger(string_hash,str)");
            CREATE_SLF(interactable_interface, add_point_trigger__string_hash__num__vector3d__num, "add_point_trigger(string_hash,num,vector3d,num)");
            CREATE_SLF(interactable_interface, create_interaction__string_hash__num, "create_interaction(string_hash,num)");
            CREATE_SLF(interactable_interface, create_interaction__string_hash__num__str, "create_interaction(string_hash,num,str)");
            CREATE_SLF(interactable_interface, disable_interaction__string_hash, "disable_interaction(string_hash)");
            CREATE_SLF(interactable_interface, enable_interaction__string_hash, "enable_interaction(string_hash)");
            CREATE_SLF(interactable_interface, nondirectional__string_hash, "nondirectional(string_hash)");
            CREATE_SLF(interactable_interface, one_shot__string_hash, "one_shot(string_hash)");
            CREATE_SLF(interactable_interface, set_activation_button__string_hash__num, "set_activation_button(string_hash,num)");
            CREATE_SLF(interactable_interface, set_approach__string_hash__num, "set_approach(string_hash,num)");

            slc = classes[12];
            CREATE_SLF(item, draw, "draw()");
            CREATE_SLF(item, get_count, "get_count()");
            CREATE_SLF(item, get_last_grenade_armed, "get_last_grenade_armed()");
            CREATE_SLF(item, get_last_grenade_detonated, "get_last_grenade_detonated()");
            CREATE_SLF(item, get_last_grenade_spawned, "get_last_grenade_spawned()");
            CREATE_SLF(item, get_launch_force, "get_launch_force()");
            CREATE_SLF(item, get_launch_vec, "get_launch_vec()");
            CREATE_SLF(item, get_owner, "get_owner()");
            CREATE_SLF(item, get_visual_item, "get_visual_item()");
            CREATE_SLF(item, holster, "holster()");
            CREATE_SLF(item, is_a_grenade, "is_a_grenade()");
            CREATE_SLF(item, is_a_gun, "is_a_gun()");
            CREATE_SLF(item, is_a_melee, "is_a_melee()");
            CREATE_SLF(item, is_a_rocket, "is_a_rocket()");
            CREATE_SLF(item, set_count__num, "set_count(num)");
            CREATE_SLF(item, set_damage__num, "set_damage(num)");
            CREATE_SLF(item, set_drawn_limb__str, "set_drawn_limb(str)");
            CREATE_SLF(item, set_holster_limb__str, "set_holster_limb(str)");
            CREATE_SLF(item, set_launch_force__num, "set_launch_force(num)");
            CREATE_SLF(item, set_launch_vec__vector3d, "set_launch_vec(vector3d)");
            CREATE_SLF(item, use, "use()");
            CREATE_SLF(item, yank_remove__vector3d__num, "yank_remove(vector3d,num)");

            slc = classes[13];
            CREATE_SLF(line_info, check_collision__num__num, "check_collision(num,num)");
            CREATE_SLF(line_info, clear_collision, "clear_collision()");
            CREATE_SLF(line_info, debug_render__num, "debug_render(num)");
            CREATE_SLF(line_info, did_collide, "did_collide()");
            CREATE_SLF(line_info, get_end_pos, "get_end_pos()");
            CREATE_SLF(line_info, get_hit_entity, "get_hit_entity()");
            CREATE_SLF(line_info, get_hit_normal, "get_hit_normal()");
            CREATE_SLF(line_info, get_hit_pos, "get_hit_pos()");
            CREATE_SLF(line_info, get_start_pos, "get_start_pos()");
            CREATE_SLF(line_info, set_end_pos__vector3d, "set_end_pos(vector3d)");
            CREATE_SLF(line_info, set_start_pos__vector3d, "set_start_pos(vector3d)");

            slc = classes[14];
            CREATE_SLF(mission_camera_marker, get_base_position, "get_base_position()");
            CREATE_SLF(mission_camera_marker, get_camera_position, "get_camera_position()");

            slc = classes[15];
            CREATE_SLF(mission_camera_transform_marker, get_base_position, "get_base_position()");
            CREATE_SLF(mission_camera_transform_marker, get_camera_position, "get_camera_position()");
            CREATE_SLF(mission_camera_transform_marker, get_forward, "get_forward()");
            CREATE_SLF(mission_camera_transform_marker, get_up, "get_up()");

            slc = classes[16];
            CREATE_SLF(mission_transform_marker, get_base_position, "get_base_position()");
            CREATE_SLF(mission_transform_marker, get_forward, "get_forward()");
            CREATE_SLF(mission_transform_marker, get_up, "get_up()");

            slc = classes[17];
            CREATE_SLF(num_list, add__num, "add(num)");
            CREATE_SLF(num_list, begin, "begin()");
            CREATE_SLF(num_list, end, "end()");
            CREATE_SLF(num_list, get_index__num, "get_index(num)");
            CREATE_SLF(num_list, remove__num, "remove(num)");
            CREATE_SLF(num_list, remove__num_list_iterator, "remove(num_list_iterator)");
            CREATE_SLF(num_list, set_index__num__num, "set_index(num,num)");
            CREATE_SLF(num_list, size, "size()");

            slc = classes[18];
            CREATE_SLF(num_list_iterator, get_num, "get_num()");
            CREATE_SLF(num_list_iterator, operator_not_equals__num_list_iterator, "operator!=(num_list_iterator)");
            CREATE_SLF(num_list_iterator, operator_plus_plus, "operator++()");
            CREATE_SLF(num_list_iterator, operator_minus_munus, "operator--()");
            CREATE_SLF(num_list_iterator, operator_equals_equals__num_list_iterator, "operator==(num_list_iterator)");

            slc = classes[0];
            CREATE_SLF(pfx, get_abs_position, "get_abs_position()");
            CREATE_SLF(pfx, get_parent, "get_parent()");
            CREATE_SLF(pfx, get_position, "get_position()");
            CREATE_SLF(pfx, get_rel_position, "get_rel_position()");
            CREATE_SLF(pfx, get_rotation, "get_rotation()");
            CREATE_SLF(pfx, get_scale, "get_scale()");
            CREATE_SLF(pfx, get_state__num, "get_state(num)");
            CREATE_SLF(pfx, get_visible, "get_visible()");
            CREATE_SLF(pfx, set_abs_position__vector3d, "set_abs_position(vector3d)");
            CREATE_SLF(pfx, set_parent__entity, "set_parent(entity)");
            CREATE_SLF(pfx, set_position__vector3d, "set_position(vector3d)");
            CREATE_SLF(pfx, set_rel_position__vector3d, "set_rel_position(vector3d)");
            CREATE_SLF(pfx, set_rotation__vector3d, "set_rotation(vector3d)");
            CREATE_SLF(pfx, set_scale__vector3d, "set_scale(vector3d)");
            CREATE_SLF(pfx, set_state__num__num, "set_state(num,num)");
            CREATE_SLF(pfx, set_visible__num, "set_visible(num)");

            slc = classes[20];
            CREATE_SLF(polytube, add_control_pt__vector3d, "add_control_pt(vector3d)");
            CREATE_SLF(polytube, build__num__num, "build(num,num)");
            CREATE_SLF(polytube, clear, "clear()");
            CREATE_SLF(polytube, clear_simulations, "clear_simulations()");
            CREATE_SLF(polytube, create_tentacle, "create_tentacle()");
            CREATE_SLF(polytube, destroy_tentacle, "destroy_tentacle()");
            CREATE_SLF(polytube, get_control_pt__num, "get_control_pt(num)");
            CREATE_SLF(polytube, get_curve_pt__num, "get_curve_pt(num)");
            CREATE_SLF(polytube, get_ifl_frame, "get_ifl_frame()");
            CREATE_SLF(polytube, get_max_length, "get_max_length()");
            CREATE_SLF(polytube, get_num_control_pts, "get_num_control_pts()");
            CREATE_SLF(polytube, get_num_curve_pts, "get_num_curve_pts()");
            CREATE_SLF(polytube, get_num_sides, "get_num_sides()");
            CREATE_SLF(polytube, get_tiles_per_meter, "get_tiles_per_meter()");
            CREATE_SLF(polytube, get_tube_radius, "get_tube_radius()");
            CREATE_SLF(polytube, ifl_lock__num, "ifl_lock(num)");
            CREATE_SLF(polytube, ifl_play, "ifl_play()");
            CREATE_SLF(polytube, kill_pt_anim__num__num, "kill_pt_anim(num,num)");
            CREATE_SLF(polytube, rebuild, "rebuild()");
            CREATE_SLF(polytube, reserve_control_pts__num, "reserve_control_pts(num)");
            CREATE_SLF(polytube, set_additive__num, "set_additive(num)");
            CREATE_SLF(polytube, set_begin_material__str__num, "set_begin_material(str,num)");
            CREATE_SLF(polytube, set_begin_material_ifl__str__num, "set_begin_material_ifl(str,num)");
            CREATE_SLF(polytube, set_blend_mode__num, "set_blend_mode(num)");
            CREATE_SLF(polytube, set_control_pt__num__vector3d, "set_control_pt(num,vector3d)");
            CREATE_SLF(polytube, set_end_material__str__num, "set_end_material(str,num)");
            CREATE_SLF(polytube, set_end_material_ifl__str__num, "set_end_material_ifl(str,num)");
            CREATE_SLF(polytube, set_force_start__num, "set_force_start(num)");
            CREATE_SLF(polytube, set_material__str, "set_material(str)");
            CREATE_SLF(polytube, set_material_ifl__str, "set_material_ifl(str)");
            CREATE_SLF(polytube, set_max_length__num, "set_max_length(num)");
            CREATE_SLF(polytube, set_num_sides__num, "set_num_sides(num)");
            CREATE_SLF(polytube, set_pt_anim__num__vector3d__num__num, "set_pt_anim(num,vector3d,num,num)");
            CREATE_SLF(polytube, set_random_pt_anim__num__num__num__num, "set_random_pt_anim(num,num,num,num)");
            CREATE_SLF(polytube, set_start_v__num, "set_start_v(num)");
            CREATE_SLF(polytube, set_tiles_per_meter__num, "set_tiles_per_meter(num)");
            CREATE_SLF(polytube, set_tube_radius__num, "set_tube_radius(num)");
            CREATE_SLF(polytube, simulate_slack__vector3d__vector3d__num, "simulate_slack(vector3d,vector3d,num)");
            CREATE_SLF(polytube, simulate_tether__entity__entity__num, "simulate_tether(entity,entity,num)");
            CREATE_SLF(polytube, tentacle_add_dangle_engine__num__num, "tentacle_add_dangle_engine(num,num)");
            CREATE_SLF(polytube, tentacle_add_follow_engine__num__num__vector3d__num, "tentacle_add_follow_engine(num,num,vector3d,num)");
            CREATE_SLF(polytube, tentacle_add_slack_engine__num__num, "tentacle_add_slack_engine(num,num)");
            CREATE_SLF(polytube, tentacle_add_strike_engine__vector3d__num__num, "tentacle_add_strike_engine(vector3d,num,num)");
            CREATE_SLF(polytube, tentacle_add_swirl_strike_engine__vector3d__num__num__num__num, "tentacle_add_swirl_strike_engine(vector3d,num,num,num,num)");
            CREATE_SLF(polytube, tentacle_create_line__vector3d__num, "tentacle_create_line(vector3d,num)");
            CREATE_SLF(polytube, tentacle_engine_running__num, "tentacle_engine_running(num)");
            CREATE_SLF(polytube, tentacle_get_end_position, "tentacle_get_end_position()");
            CREATE_SLF(polytube, tentacle_get_engine_drag__num, "tentacle_get_engine_drag(num)");
            CREATE_SLF(polytube, tentacle_get_engine_gravity__num, "tentacle_get_engine_gravity(num)");
            CREATE_SLF(polytube, tentacle_get_engine_length__num, "tentacle_get_engine_length(num)");
            CREATE_SLF(polytube, tentacle_get_engine_slack_percent__num, "tentacle_get_engine_slack_percent(num)");
            CREATE_SLF(polytube, tentacle_get_num_positions, "tentacle_get_num_positions()");
            CREATE_SLF(polytube, tentacle_get_position__num, "tentacle_get_position(num)");
            CREATE_SLF(polytube, tentacle_kill_engine__num, "tentacle_kill_engine(num)");
            CREATE_SLF(polytube, tentacle_set_collide__num, "tentacle_set_collide(num)");
            CREATE_SLF(polytube, tentacle_set_end_position__vector3d, "tentacle_set_end_position(vector3d)");
            CREATE_SLF(polytube, tentacle_set_engine_attach_ent__num__entity, "tentacle_set_engine_attach_ent(num,entity)");
            CREATE_SLF(polytube, tentacle_set_engine_drag__num__num, "tentacle_set_engine_drag(num,num)");
            CREATE_SLF(polytube, tentacle_set_engine_gravity__num__vector3d, "tentacle_set_engine_gravity(num,vector3d)");
            CREATE_SLF(polytube, tentacle_set_engine_length__num__num, "tentacle_set_engine_length(num,num)");
            CREATE_SLF(polytube, tentacle_set_engine_slack_percent__num__num, "tentacle_set_engine_slack_percent(num,num)");
            CREATE_SLF(polytube, tentacle_set_engine_target__num__vector3d, "tentacle_set_engine_target(num,vector3d)");
            CREATE_SLF(polytube, tentacle_set_position__num__vector3d, "tentacle_set_position(num,vector3d)");
            CREATE_SLF(polytube, v_animate__num, "v_animate(num)");

            slc = classes[34];
            CREATE_SLF(posfacing3d, get_facing, "get_facing()");
            CREATE_SLF(posfacing3d, get_position, "get_position()");
            CREATE_SLF(posfacing3d, get_rotation, "get_rotation()");
            CREATE_SLF(posfacing3d, operator_not_equals__posfacing3d, "operator!=(posfacing3d)");
            CREATE_SLF(posfacing3d, operator_plus__posfacing3d, "operator+(posfacing3d)");
            CREATE_SLF(posfacing3d, operator_multiply__posfacing3d, "operator-(posfacing3d)");
            CREATE_SLF(posfacing3d, operator_equals_equals__posfacing3d, "operator==(posfacing3d)");
            CREATE_SLF(posfacing3d, posfacing3d__num__num__num__num, "posfacing3d(num,num,num,num)");
            CREATE_SLF(posfacing3d, posfacing3d__num__num__num__vector3d, "posfacing3d(num,num,num,vector3d)");
            CREATE_SLF(posfacing3d, posfacing3d__vector3d__num, "posfacing3d(vector3d,num)");
            CREATE_SLF(posfacing3d, posfacing3d__vector3d__vector3d, "posfacing3d(vector3d,vector3d)");

            slc = classes[33];
            CREATE_SLF(position3d, operator_assign__vector3d, "operator=(vector3d)");
            CREATE_SLF(position3d, position3d__num__num__num, "position3d(num,num,num)");

            slc = classes[21];
            CREATE_SLF(script_controller, is_button_pressed__num, "is_button_pressed(num)");
            CREATE_SLF(script_controller, is_down_pressed, "is_down_pressed()");
            CREATE_SLF(script_controller, is_left_pressed, "is_left_pressed()");
            CREATE_SLF(script_controller, is_lstick_down_pressed, "is_lstick_down_pressed()");
            CREATE_SLF(script_controller, is_lstick_left_pressed, "is_lstick_left_pressed()");
            CREATE_SLF(script_controller, is_lstick_right_pressed, "is_lstick_right_pressed()");
            CREATE_SLF(script_controller, is_lstick_up_pressed, "is_lstick_up_pressed()");
            CREATE_SLF(script_controller, is_right_pressed, "is_right_pressed()");
            CREATE_SLF(script_controller, is_rstick_down_pressed, "is_rstick_down_pressed()");
            CREATE_SLF(script_controller, is_rstick_left_pressed, "is_rstick_left_pressed()");
            CREATE_SLF(script_controller, is_rstick_right_pressed, "is_rstick_right_pressed()");
            CREATE_SLF(script_controller, is_rstick_up_pressed, "is_rstick_up_pressed()");
            CREATE_SLF(script_controller, is_up_pressed, "is_up_pressed()");

            slc = classes[22];
            CREATE_SLF(signaller, clear_callback__str, "clear_callback(str)");
            CREATE_SLF(signaller, clear_callbacks, "clear_callbacks()");

            slc = classes[23];
            CREATE_SLF(sound_inst, dampen_guard, "dampen_guard()");
            CREATE_SLF(sound_inst, fade_in__num__num, "fade_in(num,num)");
            CREATE_SLF(sound_inst, fade_out__num, "fade_out(num)");
            CREATE_SLF(sound_inst, fade_to__num__num, "fade_to(num,num)");
            CREATE_SLF(sound_inst, get_doppler, "get_doppler()");
            CREATE_SLF(sound_inst, get_entity, "get_entity()");
            CREATE_SLF(sound_inst, get_max_distance, "get_max_distance()");
            CREATE_SLF(sound_inst, get_min_distance, "get_min_distance()");
            CREATE_SLF(sound_inst, get_pitch, "get_pitch()");
            CREATE_SLF(sound_inst, get_source, "get_source()");
            CREATE_SLF(sound_inst, get_status, "get_status()");
            CREATE_SLF(sound_inst, get_volume, "get_volume()");
            CREATE_SLF(sound_inst, is_valid, "is_valid()");
            CREATE_SLF(sound_inst, play__num, "play(num)");
            CREATE_SLF(sound_inst, play_3d__vector3d__num, "play_3d(vector3d,num)");
            CREATE_SLF(sound_inst, queue__num, "queue(num)");
            CREATE_SLF(sound_inst, set_entity__entity, "set_entity(entity)");
            CREATE_SLF(sound_inst, set_preregistered_source__str, "set_preregistered_source(str)");
            CREATE_SLF(sound_inst, set_sound_group__str, "set_sound_group(str)");
            CREATE_SLF(sound_inst, set_source__str, "set_source(str)");
            CREATE_SLF(sound_inst, stop__num, "stop(num)");
            CREATE_SLF(sound_inst, wait__num, "wait(num)");

            slc = classes[24];
            CREATE_SLF(str_list, add__str, "add(str)");
            CREATE_SLF(str_list, begin, "begin()");
            CREATE_SLF(str_list, end, "end()");
            CREATE_SLF(str_list, get_index__num, "get_index(num)");
            CREATE_SLF(str_list, remove__str, "remove(str)");
            CREATE_SLF(str_list, remove__str_list_iterator, "remove(str_list_iterator)");
            CREATE_SLF(str_list, set_index__num__str, "set_index(num,str)");
            CREATE_SLF(str_list, size, "size()");

            slc = classes[25];
            CREATE_SLF(str_list_iterator, get_str, "get_str()");
            CREATE_SLF(str_list_iterator, operator_not_equals__str_list_iterator, "operator!=(str_list_iterator)");
            CREATE_SLF(str_list_iterator, operator_plus_plus, "operator++()");
            CREATE_SLF(str_list_iterator, operator_minus_munus, "operator--()");
            CREATE_SLF(str_list_iterator, operator_equals_equals__str_list_iterator, "operator==(str_list_iterator)");

            slc = classes[37];
            CREATE_SLF(string_hash, operator_equals_equals__str, "operator==(str)");
            CREATE_SLF(string_hash, operator_equals_equals__string_hash, "operator==(string_hash)");
            CREATE_SLF(string_hash, set__str, "set(str)");
            CREATE_SLF(string_hash, string_hash__str, "string_hash(str)");
            CREATE_SLF(string_hash, to_string, "to_string()");

            slc = classes[26];
            CREATE_SLF(switch_obj, get_state, "get_state()");
            CREATE_SLF(switch_obj, set_alarm__num, "set_alarm(num)");
            CREATE_SLF(switch_obj, set_single_use__num, "set_single_use(num)");
            CREATE_SLF(switch_obj, set_state__num, "set_state(num)");
            CREATE_SLF(switch_obj, set_web_targetable__num, "set_web_targetable(num)");
            CREATE_SLF(switch_obj, who_pressed_me, "who_pressed_me()");

            slc = classes[27];
            CREATE_SLF(tam, set_entity__entity, "set_entity(entity)");
            CREATE_SLF(tam, set_pos__vector3d, "set_pos(vector3d)");
            CREATE_SLF(tam, set_state__num, "set_state(num)");
            CREATE_SLF(tam, set_type__num, "set_type(num)");

            slc = classes[28];
            CREATE_SLF(taunt_entry, get_entity, "get_entity()");
            CREATE_SLF(taunt_entry, get_flags, "get_flags()");
            CREATE_SLF(taunt_entry, get_taunt_name, "get_taunt_name()");

            slc = classes[29];
            CREATE_SLF(taunt_exchange, get_entity_to_do_hurting, "get_entity_to_do_hurting()");
            CREATE_SLF(taunt_exchange, get_entity_to_hurt, "get_entity_to_hurt()");
            CREATE_SLF(taunt_exchange, get_last_hit_pt_value, "get_last_hit_pt_value()");
            CREATE_SLF(taunt_exchange, get_max_times_to_play, "get_max_times_to_play()");
            CREATE_SLF(taunt_exchange, get_min_damage, "get_min_damage()");
            CREATE_SLF(taunt_exchange, get_normalized_weight, "get_normalized_weight()");
            CREATE_SLF(taunt_exchange, get_taunt_entry__num, "get_taunt_entry(num)");
            CREATE_SLF(taunt_exchange, get_times_played, "get_times_played()");
            CREATE_SLF(taunt_exchange, get_total_taunts, "get_total_taunts()");
            CREATE_SLF(taunt_exchange, get_weight, "get_weight()");
            CREATE_SLF(taunt_exchange, increment_times_played, "increment_times_played()");
            CREATE_SLF(taunt_exchange, set_last_hit_pt_value__num, "set_last_hit_pt_value(num)");
            CREATE_SLF(taunt_exchange, set_normalized_weight__num, "set_normalized_weight(num)");

            slc = classes[30];
            CREATE_SLF(taunt_exchange_list, add__taunt_exchange, "add(taunt_exchange)");
            CREATE_SLF(taunt_exchange_list, clear, "clear()");
            CREATE_SLF(taunt_exchange_list, get_index__num, "get_index(num)");
            CREATE_SLF(taunt_exchange_list, size, "size()");

            slc = classes[31];
            CREATE_SLF(trigger, contains__entity, "contains(entity)");
            CREATE_SLF(trigger, get_abs_position, "get_abs_position()");
            CREATE_SLF(trigger, get_radius, "get_radius()");
            CREATE_SLF(trigger, get_triggered_ent, "get_triggered_ent()");
            CREATE_SLF(trigger, get_triggered_entity_list, "get_triggered_entity_list()");
            CREATE_SLF(trigger, is_point_radius_trigger, "is_point_radius_trigger()");
            CREATE_SLF(trigger, set_active__num, "set_active(num)");
            CREATE_SLF(trigger, set_multiple_entrance__num, "set_multiple_entrance(num)");
            CREATE_SLF(trigger, set_position__vector3d, "set_position(vector3d)");
            CREATE_SLF(trigger, set_radius__num, "set_radius(num)");
            CREATE_SLF(trigger, set_sees_dead_people__num, "set_sees_dead_people(num)");
            CREATE_SLF(trigger, set_use_any_char__num, "set_use_any_char(num)");

            slc = classes[32];
            CREATE_SLF(vector3d, length, "length()");
            CREATE_SLF(vector3d, length2, "length2()");
            CREATE_SLF(vector3d, operator_not_equals__vector3d, "operator!=(vector3d)");
            CREATE_SLF(vector3d, operator_multiply__num, "operator*(num)");
            CREATE_SLF(vector3d, operator_plus__vector3d, "operator+(vector3d)");
            CREATE_SLF(vector3d, operator_multiply__vector3d, "operator-(vector3d)");
            CREATE_SLF(vector3d, operator_divide__num, "operator/(num)");
            CREATE_SLF(vector3d, operator_equals_equals__vector3d, "operator==(vector3d)");
            CREATE_SLF(vector3d, vector3d__num__num__num, "vector3d(num,num,num)");
            CREATE_SLF(vector3d, x, "x()");
            CREATE_SLF(vector3d, xy_norm, "xy_norm()");
            CREATE_SLF(vector3d, xz_norm, "xz_norm()");
            CREATE_SLF(vector3d, y, "y()");
            CREATE_SLF(vector3d, z, "z()");

            slc = classes[35];
            CREATE_SLF(vector3d_list, add__vector3d, "add(vector3d)");
            CREATE_SLF(vector3d_list, begin, "begin()");
            CREATE_SLF(vector3d_list, clear, "clear()");
            CREATE_SLF(vector3d_list, end, "end()");
            CREATE_SLF(vector3d_list, get_index__num, "get_index(num)");
            CREATE_SLF(vector3d_list, remove__vector3d, "remove(vector3d)");
            CREATE_SLF(vector3d_list, remove__vector3d_list_iterator, "remove(vector3d_list_iterator)");
            CREATE_SLF(vector3d_list, set_index__num__vector3d, "set_index(num,vector3d)");
            CREATE_SLF(vector3d_list, size, "size()");

            slc = classes[36];
            CREATE_SLF(vector3d_list_iterator, get_vector3d, "get_vector3d()");
            CREATE_SLF(vector3d_list_iterator, operator_not_equals__vector3d_list_iterator, "operator!=(vector3d_list_iterator)");
            CREATE_SLF(vector3d_list_iterator, operator_plus_plus, "operator++()");
            CREATE_SLF(vector3d_list_iterator, operator_minus_munus, "operator--()");
            CREATE_SLF(vector3d_list_iterator, operator_equals_equals__vector3d_list_iterator, "operator==(vector3d_list_iterator)");
        }

#undef CREATE_SLF

        slc_global()->add_functions_complete();

        for (auto &slc : classes) {
            slc->add_functions_complete();
        }
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
