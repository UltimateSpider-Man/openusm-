#include "wds.h"

#include "aeps.h"
#include "ai_path.h"
#include "ai_player_controller.h"
#include "base_ai_core.h"
#include "beam.h"
#include "camera.h"
#include "collide_trajectories.h"
#include "collision_trajectory_filter.h"
#include "common.h"
#include "cut_scene_player.h"
#include "damage_interface.h"
#include "daynight.h"
#include "decal_data_interface.h"
#include "decal_morphs.h"
#include "dirty_sphere.h"
#include "facial_expression_interface.h"
#include "femanager.h"
#include "fixed_pool.h"
#include "force_generator.h"
#include "func_wrapper.h"
#include "fx_cache.h"
#include "game.h"
#include "grenade.h"
#include "interactable_interface.h"
#include "intersected_trajectory.h"
#include "intraframe_trajectory.h"
#include "item.h"
#include "line_info.h"
#include "manip_obj.h"
#include "mash_virtual_base.h"
#include "motion_effect_struct.h"
#include "moved_entities.h"
#include "nal_system.h"
#include "nearby_hero_regions.h"
#include "physical_interface.h"
#include "polytube.h"
#include "resource_key.h"
#include "resource_manager.h"
#include "scene_spline_path_brew.h"
#include "scratchpad_stack.h"
#include "script_manager.h"
#include "sound_interface.h"
#include "spawnable.h"
#include "spiderman_camera.h"
#include "stack_allocator.h"
#include "terrain.h"
#include "time_interface.h"
#include "trace.h"
#include "traffic_signal_mgr.h"
#include "trajectory_cluster.h"
#include "trigger_manager.h"
#include "utility.h"
#include "vtbl.h"
#include "wds.h"
#include "web_interface.h"

VALIDATE_SIZE(world_dynamics_system, 0x400u);
VALIDATE_SIZE((*world_dynamics_system::field_0), 0x3C);
VALIDATE_OFFSET(world_dynamics_system, ent_mgr, 0x74);
VALIDATE_OFFSET(world_dynamics_system, field_230, 0x230);
VALIDATE_OFFSET(world_dynamics_system, the_terrain, 0x1AC);

static constexpr auto ENTITIES_TAG = 0;
static constexpr auto BOX_TRIGGERS_TAG = 6;
static constexpr auto SPLINE_PATHS_TAG = 7;
static constexpr auto AUDIO_BOXES_TAG = 8;
static constexpr auto REGION_MESH_VOBBS_TAG = 13;

Var<world_dynamics_system *> g_world_ptr{0x0095C770};

int *sub_566A70() {
    return (int *) CDECL_CALL(0x00566A70);
}

world_dynamics_system::world_dynamics_system()
#if 0
    : field_4(), field_3E0() {
    this->field_18 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_28 = wds_camera_manager();
    this->field_74 = wds_entity_manager();
    this->field_A0 = wds_render_manager();
    this->field_140 = wds_script_manager();
    this->field_158 = wds_time_manager();
    this->field_178 = wds_patrol_def_manager();

    this->field_188.field_1C = sub_566A70();
    this->field_1A8 = 0;
    this->field_188.field_0 = 0;
    this->field_188.field_5 = 0;
    this->field_188.field_4 = 0;
    this->field_188.field_14 = 0;
    this->field_1B0 = cached_special_effect();
    this->field_1F0 = cached_special_effect();

    cdecl_call sub_504D60 = CAST(sub_504D60, 0x00504D60);
    this->field_240 = CAST(field_240, sub_504D60());
    this->field_244 = 0;
    this->field_24C = CAST(field_24C, sub_504D60());
    this->field_250 = 0;
    this->field_258 = CAST(field_258, sub_504D60());
    this->field_25C = 0;
    this->field_264 = 0;
    this->field_268 = 0;
    this->field_26C = 0;
    this->field_274 = 0;
    this->field_278 = 0;
    this->field_27C = 0;
    this->field_284 = 0;
    this->field_288 = 0;
    this->field_28C = 0;
    this->field_29C = mission_stack_manager();
    this->field_2A8 = mission_manager();
    this->field_3A8 = patrol_manager();

    this->field_0 = new slot_pool<nal_anim_control *, uint32_t>{500};

    this->field_4.reserve(20u);

    this->field_295 = 0;
    this->field_230[0] = nullptr;
    this->field_234[0] = nullptr;
    this->field_298 = -1;
    this->field_290 = 4;
    this->ter = nullptr;
    this->num_players = 0;
    mash_virtual_base::generate_vtable();
    physical_interface::clear_static_lists();
    this->field_3F0 = 1;
#else
{
    THISCALL(0x005554D0, this);
#endif
}

world_dynamics_system::~world_dynamics_system() {
    THISCALL(0x00555750, this);
}

void world_dynamics_system::malor_point(const vector3d &a2, int a3, bool a4)
{
    THISCALL(0x00530460, this, &a2, a3, a4);
}

void cleanup_actor_scene_anim_state_hash() {
    CDECL_CALL(0x004D00E0);
}

int world_dynamics_system::add_generator(force_generator *generator) {
    return THISCALL(0x005421B0, this, generator);
}

void world_dynamics_system::advance_entity_animations(Float a3) {
    THISCALL(0x00537170, this, a3);
}

void zero_xz_velocity_for_effectively_standing_physical_interfaces() {
    CDECL_CALL(0x004D1A30);
}

int sub_A4B0D0() {
    assert(intraframe_trajectory_t::pool().is_empty());

    assert(local_collision::closest_points_pair_t::pool().is_empty());

    assert(local_collision::primitive_list_t::pool().is_empty());

    assert(intersected_trajectory_t::pool().is_empty());

    assert(dirty_sphere_t::pool().is_empty());

    assert(trajectory_cluster_t::pool().is_empty());
    return 0;
}

void collide_all_moved_entities(Float a1) {
    if constexpr (1) {
        stack_allocator allocator;
        scratchpad_stack::save_state(&allocator);
        collision_trajectory_filter_t filter{};
        auto *trajectories = moved_entities::get_all_trajectories(a1, &filter);
        auto v2 = 0u;

        fixed_vector<intraframe_trajectory_t *, 300> v10{};

        for (auto *i = trajectories; i != nullptr; i = i->field_15C) {
            v10.push_back(i);
        }

        auto v4 = 0u;
        for (auto *v5 = trajectories; v5 != nullptr; v5 = v5->field_15C) {
            ++v4;
        }

        if (trajectories != nullptr) {
            resolve_rotations(trajectories, v4);
            resolve_collisions(&trajectories, a1);
            resolve_moving_pendulums(trajectories, a1);
        }

        for (auto j = 0u; j < v2; ++j) {
            auto *v7 = v10.at(j);
            if (!sub_512730(v7)) {
                intraframe_trajectory_t::pool().set(v7);
            }
        }

        scratchpad_stack::restore_state(allocator);

    } else {
        CDECL_CALL(0x00605470, a1);
    }
}

void manage_standing_for_all_physical_interfaces(Float a1) {
    CDECL_CALL(0x004F28B0, a1);
}

entity *world_dynamics_system::get_hero_ptr(int index) {
    static constexpr auto MAX_GAME_PLAYERS = 1;

    assert(index >= 0 && index <= MAX_GAME_PLAYERS);

    auto *result = this->field_230[index];
    return result;
}

void world_dynamics_system::frame_advance(Float a2) {
    if constexpr (0) {
        this->field_158.frame_advance(a2);
        this->field_28.frame_advance(a2);
        this->field_A0.frame_advance(a2);
        this->field_188.frame_advance(a2);
        daynight::frame_advance(a2);

        traffic_signal_mgr::frame_advance(a2);

        this->ent_mgr.frame_advance(a2);
        cleanup_actor_scene_anim_state_hash();
        this->update_ai_and_visibility_proximity_maps_for_moved_entities(a2);
        moved_entities::reset_all_moved();
        script_manager::run(a2, false);
        this->field_28.advance_controllers(a2);
        this->advance_entity_animations(a2);
        time_interface::frame_advance_all_time_interfaces(a2);
        spawnable::advance_traffic_and_peds(a2);
        if (this->field_3F0) {
            ai::ai_core::frame_advance_all_core_ais(a2);
        }

        ai_path::frame_advance_all_ai_paths(a2);
        interactable_interface::frame_advance_all(a2);
        facial_expression_interface::frame_advance_all_facial_expression_ifc(a2);
        this->field_3A8.frame_advance(a2);
        this->field_1B0.frame_advance(a2);
        this->field_1F0.frame_advance(a2);

        for (auto &generator : this->field_260) {
            struct Vtbl {
                int field_0;
                bool __thiscall (*is_active)(void *);
                int field_8;
                void __thiscall (*frame_advance)(void *, Float);
            };

            Vtbl *vtbl = CAST(vtbl, generator->m_vtbl);

            if (vtbl->is_active(generator)) {
                vtbl->frame_advance(generator, a2);
            }
        }

        physical_interface::frame_advance_all_phys_interfaces(a2);
        manage_standing_for_all_physical_interfaces(a2);
        zero_xz_velocity_for_effectively_standing_physical_interfaces();
        collide_all_moved_entities(a2);
        line_info::frame_advance(2);
        beam::frame_advance_all_beams(a2);
        item::frame_advance_all_items(a2);
        grenade::frame_advance_all_grenades(a2);
        manip_obj::frame_advance_all_manip_objs(a2);
        polytube::frame_advance_all_polytubes(a2);
        motion_effect_struct::record_all_motion_fx(a2);
        aeps::FrameAdvance(a2);
        sound_interface::frame_advance_all_sound_ifc(a2);
        damage_interface::frame_advance_all_damage_ifc(a2);
        decal_data_interface::frame_advance_all_decal_interfaces(a2);
        web_interface::frame_advance_all_web_interfaces(a2);
        this->update_collision_proximity_maps_for_moved_entities(a2);
        this->the_terrain->frame_advance(a2);
        trigger_manager::instance()->update();
        this->sub_54A3B0();
        decal_morphs::frame_advance(a2);

    } else {
        THISCALL(0x00558370, this, a2);
    }
}

void world_dynamics_system::sub_54A3B0() {
    THISCALL(0x0054A3B0, this);
}

void world_dynamics_system::sub_530460(const vector3d &a2, int visited_regions, bool a4) {
    THISCALL(0x00530460, this, &a2, visited_regions, a4);
}

bool world_dynamics_system::un_mash_scene_entities(const resource_key &a2, region *a3, worldly_pack_slot *a4, bool a5, scene_entity_brew *a6)
{
    TRACE("world_dynamics_system::un_mash_scene_entities");
    return (bool) THISCALL(0x0055A680, this, &a2, a3, a4, a5, a6);
}

bool world_dynamics_system::un_mash_scene_audio_boxes(const resource_key &key_id,
                                                      region *reg,
                                                      worldly_pack_slot *slot_ptr,
                                                      timed_progress &a4) {
    if constexpr (1) {
        if (a4.is_done()) {
            return false;
        }

        int mash_data_size = 0;
        int buffer_index = 0;
        uint8_t *buffer_ptr = nullptr;

        int parse_code;

        if (!resource_manager::get_resource_if_exists(key_id,
                                                      reg,
                                                      &buffer_ptr,
                                                      slot_ptr,
                                                      &mash_data_size) ||
            (g_femanager().RenderLoadMeter(false),
             parse_code = *(uint32_t *) &buffer_ptr[buffer_index],
             parse_code == 18)) {
        } else {
            assert(parse_code == AUDIO_BOXES_TAG);

            buffer_index += 4;

            assert(the_terrain != nullptr);

            if (reg == nullptr) {
                auto *str = key_id.m_hash.to_string();

                sp_log("Unknown region '%s'.  Make sure your sin file is correct.", str);

                assert(0);
            }

            int v9;
            this->the_terrain->un_mash_audio_boxes((char *) &buffer_ptr[buffer_index], &v9, reg);
            buffer_index += v9;
        }

        a4.done();

        return false;

    } else {
        return THISCALL(0x0053CB50, this, &key_id, reg, slot_ptr, &a4);
    }
}

bool world_dynamics_system::un_mash_scene_spline_paths(const resource_key &a2,
                                                       region *reg,
                                                       worldly_pack_slot *slot_ptr,
                                                       scene_spline_path_brew &brew) {
    if constexpr (1) {
        if (brew.field_0.is_done()) {
            return false;
        }

        if (!brew.field_0.is_started()) {
            brew.field_0.start();
            brew.field_8 = slot_ptr;
            brew.field_C = 0;
            brew.field_10 = nullptr;
            brew.field_14 = 0;
            if (!resource_manager::get_resource_if_exists(a2,
                                                          reg,
                                                          &brew.field_10,
                                                          brew.field_8,
                                                          &brew.field_C) ||
                (brew.parse_code = *(uint32_t *) &brew.field_10[brew.field_14],
                 brew.parse_code == 18)) {
                brew.field_0.done();
                return false;
            }

            assert(brew.parse_code == SPLINE_PATHS_TAG);

            brew.field_14 += 4;
        }

        for (uint32_t i = 0; i < nearby_hero_regions::regs().size(); ++i) {
            if (nearby_hero_regions::regs().at(i) == reg) {
                break;
            }
        }

        auto buffer_index = brew.field_14;
        auto v16 = brew.parse_code;
        auto *buffer_ptr = brew.field_10;
        auto a2a = brew.field_C;

        g_femanager().RenderLoadMeter(false);

        assert(the_terrain != nullptr);

        int v17;
        if (this->the_terrain->un_mash_traffic_paths((char *) &buffer_ptr[buffer_index],
                                                     &v17,
                                                     reg,
                                                     brew.field_1C)) {
            brew.field_10 = buffer_ptr;
            brew.field_8 = slot_ptr;
            brew.parse_code = v16;
            brew.field_C = a2a;
            brew.field_14 = buffer_index;
            return true;
        } else {
            buffer_index += v17;

            brew.field_0.done();
        }

        return false;

    } else {
        return (bool) THISCALL(0x0052FC90, this, &a2, reg, slot_ptr, &brew);
    }
}

bool world_dynamics_system::un_mash_scene_quad_paths(const resource_key &key_id,
                                                     region *reg,
                                                     worldly_pack_slot *slot_ptr,
                                                     timed_progress &a4) {
    if constexpr (1) {
        if (a4.is_done()) {
            return false;
        }

        int mash_data_size = 0;
        int buffer_index = 0;
        uint8_t *buffer_ptr = nullptr;

        int parse_code;

        if (!resource_manager::get_resource_if_exists(key_id,
                                                      reg,
                                                      &buffer_ptr,
                                                      slot_ptr,
                                                      &mash_data_size) ||
            (g_femanager().RenderLoadMeter(false),
             parse_code = *(uint32_t *) &buffer_ptr[buffer_index],
             parse_code == 18)) {
        } else {
            static constexpr auto QUAD_PATHS_TAG = 10;

            assert(parse_code == QUAD_PATHS_TAG);

            buffer_index += 4;

            assert(the_terrain != nullptr);

            if (reg == nullptr) {
                auto *str = key_id.m_hash.to_string();

                error("Unknown region '%s'.  Make sure your sin file is correct.", str);
            }

            int v9;
            this->the_terrain->un_mash_region_paths((char *) &buffer_ptr[buffer_index], &v9, reg);
            buffer_index += v9;
        }

        a4.done();

        return false;

    } else {
        return (bool) THISCALL(0x0053CAC0, this, &key_id, reg, slot_ptr, &a4);
    }
}

bool world_dynamics_system::load_scene(resource_key &a2,
                                       bool a3,
                                       const char *a4,
                                       region *a5,
                                       worldly_pack_slot *a6,
                                       limited_timer *a7)
{
    TRACE("world_dynamics_system::load_scene");

    if (a4 != nullptr) {
        sp_log("Load scene %s", a4);
    }

    return static_cast<bool>(THISCALL(0x0055B160, this, &a2, a3, a4, a5, a6, a7));
}

camera *world_dynamics_system::get_chase_cam_ptr(int a2) {
    auto v1 = this->field_234[a2];

    return bit_cast<camera *>(v1);
}

void world_dynamics_system::create_water_kill_trigger() {
    THISCALL(0x0054A430, this);
}

int world_dynamics_system::add_player(const mString &a2)
{
    TRACE("world_dynamics_system::add_player");

    return THISCALL(0x0055B400, this, &a2);
}

void world_dynamics_system::deactivate_corner_web_splats() {
    resource_key *v2 = &this->field_1F0.field_8;
    if (v2->sub_48AB80()) {
        v2->m_hash.source_hash_code = 0;
        v2->m_type = RESOURCE_KEY_TYPE_NONE;
        this->field_1F0.field_10[0] = 0.0;
        this->field_1F0.field_10[2] = 0.0;
        this->field_1F0.field_10[1] = 0.0;
        this->field_1F0.field_38 = 0;
        fx_cache *v3 = this->field_1F0.field_30;
        char v4 = v3->field_F;
        char *v5 = (char *) &v3->field_8;
        if (!v4) {
            if (*(uint32_t *) v5) {
                operator delete[](*(void **) v5);
            }
        }
        *(uint32_t *) v5 = 0;
        *(bit_cast<uint16_t *>(v5) + 4) = 0;
    }
}

terrain *world_dynamics_system::create_terrain(const mString &a2) {
    TRACE("world_dynamics_system::create_terrain");

    if constexpr (1)
    {
        this->the_terrain = new terrain{a2};
        return this->the_terrain;
    }
    else
    {
        return (terrain *) THISCALL(0x0055B100, this, &a2);
    }
}

void world_dynamics_system::activate_corner_web_splats() {
    //sp_log("activate_corner_web_splats:");

    auto *act = (actor *) this->get_hero_ptr(0);

    auto *__old_context = resource_manager::push_resource_context(act->field_BC);

    string_hash v3{"websplat_crnr"};

    resource_key a2;
    a2.set(v3, RESOURCE_KEY_TYPE_ENTITY);

    this->field_1F0.field_8 = a2;

    this->field_1F0.field_10[0] = 15.0;
    this->field_1F0.field_10[1] = 0.33000001;
    this->field_1F0.field_10[2] = 0.5;

    this->field_1F0.field_38 = 5;
    this->field_1F0.fill_cache();
    resource_manager::pop_resource_context();
    assert(resource_manager::get_resource_context() == __old_context);
}

entity *world_dynamics_system::get_hero_or_marky_cam_ptr() {
    if constexpr (1) {
        auto *result = this->get_hero_ptr(0);
        if (result == nullptr) {
            result = (entity *) this->field_28.field_44;
        }

        return result;
    } else {
        return (entity *) THISCALL(0x0050D310, this);
    }
}

void world_dynamics_system::activate_web_splats()
{
    TRACE("world_dynamics_system::activate_web_splats");
    
    if constexpr (0)
    {
        auto *act = bit_cast<actor *>(this->get_hero_ptr(0));

        auto *__old_context = resource_manager::push_resource_context(act->field_BC);
        string_hash v3{"spdywebsplatter"};

        resource_key a2;
        a2.set(v3, RESOURCE_KEY_TYPE_ENTITY);

        this->field_1B0.field_8 = a2;

        this->field_1B0.field_10[0] = 15.0;
        this->field_1B0.field_10[1] = 0.33000001;
        this->field_1B0.field_10[2] = 0.5;

        this->field_1B0.field_38 = 5;
        this->field_1B0.fill_cache();
        resource_manager::pop_resource_context();

        assert(resource_manager::get_resource_context() == __old_context);
    } else {
        THISCALL(0x0054ABE0, this);
    }
}

void world_dynamics_system::deactivate_web_splats() {
    resource_key *v2 = &this->field_1B0.field_8;
    if (v2->sub_48AB80()) {
        v2->m_hash.source_hash_code = 0;
        v2->m_type = RESOURCE_KEY_TYPE_NONE;
        this->field_1B0.field_10[0] = 0.0;
        this->field_1B0.field_10[1] = 0.0;
        this->field_1B0.field_10[2] = 0.0;

        this->field_1B0.field_38 = 0;
        fx_cache *v3 = this->field_1B0.field_30;
        char v4 = v3->field_F;
        char *v5 = (char *) &v3->field_8;
        if (!v4) {
            if (*(uint32_t *) v5) {
                operator delete[](*(void **) v5);
            }
        }
        *(uint32_t *) v5 = 0;
        *(bit_cast<uint16_t *>(v5) + 4) = 0;
    }
}

bool world_dynamics_system::is_loading_from_scn_file() {
    return this->field_295;
}

int world_dynamics_system::remove_player(int player_num) {
    assert(player_num == num_players - 1);

    struct Vtbl {
        int empty0[29];
        bool __thiscall (*is_a_game_camera)(void *);
        int empty1[135];
        int __thiscall (*sync)(void *, void *);
    };

    cut_scene_player *v3 = g_cut_scene_player();
    v3->stop(nullptr);
    bool v4 = this->num_players-- == 1;
    if (v4) {
        void *vtbl = get_vtbl(this->field_28.field_44);

        bit_cast<Vtbl *>(vtbl)->sync(this->field_28.field_44, this->field_234[0]);
    }

    g_world_ptr()->ent_mgr.destroy_entity(this->field_234[this->num_players]);
    this->field_234[this->num_players] = nullptr;
    bit_cast<actor *>(this->field_230[this->num_players])->destroy_player_controller();
    g_world_ptr()->ent_mgr.destroy_entity(this->field_230[this->num_players]);
    this->field_230[this->num_players] = nullptr;
    if (this->num_players == 0) {
        g_game_ptr()->unload_hero_packfile();
        this->field_234[0] = CAST(this->field_234[0], this->field_28.field_44);
        g_spiderman_camera_ptr() = nullptr;
    }

    auto *v6 = this->get_chase_cam_ptr(0);
    g_game_ptr()->set_current_camera(v6, true);
    this->deactivate_web_splats();
    this->deactivate_corner_web_splats();
    return this->num_players;
}

void world_dynamics_system::update_ai_and_visibility_proximity_maps_for_moved_entities(Float a1) {
    THISCALL(0x00530100, this, a1);
}

void world_dynamics_system::update_collision_proximity_maps_for_moved_entities(Float a1) {
    THISCALL(0x0054A610, this, a1);
}

void world_dynamics_system::update_light_proximity_maps_for_moved_entities(Float a1) {
    THISCALL(0x00529CC0, this, a1);
}

void world_dynamics_system::add_anim_ctrl(animation_controller *a2) {
    THISCALL(0x00542160, this, a2);
}

int get_hero_type_helper() {
    auto *hero_ptr = (actor *) g_world_ptr()->get_hero_ptr(0);
    if (hero_ptr != nullptr) {
        return hero_ptr->m_player_controller->field_420;
    }

    assert(0 && "no hero available right now");
    return 0;
}

void world_dynamics_system_patch() {

    {
        FUNC_ADDRESS(address, &world_dynamics_system::create_terrain);
        REDIRECT(0x0055BB5C, address);
    }

    {
        FUNC_ADDRESS(address, &world_dynamics_system::load_scene);
        REDIRECT(0x0055CC2F, address);
    }

    {
        FUNC_ADDRESS(address, &world_dynamics_system::un_mash_scene_entities);
        REDIRECT(0x0055B268, address);
    }

    if constexpr (0)
    {
        FUNC_ADDRESS(address, &world_dynamics_system::add_player);
        REDIRECT(0x0055CCA3, address);
        REDIRECT(0x005C5889, address);
        REDIRECT(0x00641C5C, address);
        REDIRECT(0x00641C97, address);
        REDIRECT(0x00676CFB, address);
    }

    return;
    {
        FUNC_ADDRESS(address, &world_dynamics_system::create_water_kill_trigger);
        REDIRECT(0x0055BF7B, address);
    }

    {
        FUNC_ADDRESS(address, &world_dynamics_system::activate_corner_web_splats);

        REDIRECT(0x0047DB5F, address);
    }

    {
        FUNC_ADDRESS(address, &world_dynamics_system::frame_advance);
        REDIRECT(0x0055A0F7, address);
    }

    {
        FUNC_ADDRESS(address, &world_dynamics_system::un_mash_scene_audio_boxes);
        REDIRECT(0x0055B328, address);
    }
}
