#pragma once

#include "entity.h"

#include "float.hpp"
#include "spline.h"

namespace ai {
struct ai_core;
}

struct traffic_light_interface;
struct string_hash;
struct physical_interface;
struct ai_player_controller;
struct generic_mash_header;
struct generic_mash_data_ptrs;
struct nglMesh;
struct resource_pack_slot;
struct item;
struct signaller;
struct advanced_entity_ptrs;
struct damage_interface;
struct interactable_interface;
struct facial_expression_interface;
struct generic_anim_controller;
struct base_ai_data;
struct nalBaseSkeleton;
struct lego_map_root_node;
struct movement_info;

struct actor : entity {
    using base_type = vhandle_type<entity>;

    struct mesh_buffers {
        nglMesh **field_0;
        uint8_t field_4;
        uint8_t field_5;
        uint16_t field_6;
        int field_8;
    };

    damage_interface *m_damage_interface;
    physical_interface *m_physical_interface;
    int field_70;
    generic_anim_controller *field_74;
    advanced_entity_ptrs *adv_ptrs;
    base_ai_data *field_7C;
    interactable_interface *m_interactable_ifc;
    facial_expression_interface *m_facial_expression_interface;
    int field_88;
    ai_player_controller *m_player_controller;
    mesh_buffers field_90;
    uint8_t *field_9C;
    traffic_light_interface *field_A0;
    int16_t field_A4;
    int16_t field_A6;
    int16_t field_A8[1];
    int16_t field_AA;
    vector3d field_AC;

    int field_B8;
    resource_pack_slot *field_BC;

    //0x004F92D0
    actor(const string_hash &a2, uint32_t a3);

    //0x0050A3F0
    actor(int);

    ~actor();

    int get_entity_size();

    void release_mem();

    vector3d get_velocity();

    bool has_traffic_light_ifc();

    traffic_light_interface *traffic_light_ifc();

    void allocate_anim_controller(unsigned int a2, nalBaseSkeleton *a3);

    void bind_to_scene_anim();

    void unbind_from_scene_anim(string_hash a3, string_hash a4);

    float get_floor_offset();

    bool anim_finished(int);

    //virtual
    void invalidate_frame_delta();

    inline ai_player_controller *get_player_controller() {
        return this->m_player_controller;
    }

    //0x004D6B60
    void set_frame_delta_no_update(const po &a2, Float a3);

    //0x004CC940
    bool get_allow_tunnelling_into_next_frame();

    //0x004D2100
    void *find_like_item(
        vhandle_type<
            item,
            vhandle_type<actor, vhandle_type<entity, vhandle_type<signaller, entity_base_vhandle>>>>
            a2);

    //0x004E2670
    void create_damage_ifc();

    //0x004F5720
    void common_destruct();

    //0x004E3970
    void cancel_animated_movement(const vector3d &a2, Float a3);

    //0x004E2EE0
    void get_velocity(vector3d *a2);

    //0x004FB960
    void process_extra_scene_flags(unsigned int a2);

    //0x004B8B40
    physical_interface *physical_ifc();

    //0x004C0E60
    bool has_camera_collision();

    //0x004C0E30
    bool has_entity_collision();

    //0x004CC740
    void kill_interact_anim();

    //0x004E26E0
    void create_physical_ifc();

    //0x004FBD40
    //virtual
    void _un_mash(generic_mash_header *a3, void *a4, generic_mash_data_ptrs *a5);

    //0x004C0CD0
    void create_player_controller(int a2);

    //0x004C0D40
    void destroy_player_controller();

    bool has_vertical_obb();

    vector3d *get_cached_visual_bounding_sphere_center();

    nglMesh **sub_4B8BCA();

    damage_interface *damage_ifc();

    lego_map_root_node *get_lego_map_root();

    movement_info *get_movement_info();

    //virtual
    double get_colgeom_radius();

    //0x0x004B8FC0
    //virtual
    bool is_frame_delta_valid();

    //0x004B9000
    //virtual
    po *get_frame_delta();

    //0x004E31F0
    vector3d _get_visual_center();

    //0x004B8BB0
    nglMesh *get_mesh();

    //0x004C0F80
    ai::ai_core *_get_ai_core();

    //virtual
    vector3d get_colgeom_center();

    //0x004E33B0
    void _render(Float a2);

    //0x004D2060
    static void swap_all_mesh_buffers();
};

namespace ai {

//0x0068A440
extern void setup_hero_capsule(actor *act);
} // namespace ai

extern void actor_patch();
