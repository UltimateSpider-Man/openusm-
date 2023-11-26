#include "wds_render_manager.h"

#include "GL/gl.h"

#include "beam.h"
#include "bitvector.h"
#include "camera.h"
#include "camera_teleport_update_visitor.h"
#include "city_lod.h"
#include "culling_params.h"
#include "cut_scene_player.h"
#include "debug_render.h"
#include "filespec.h"
#include "func_wrapper.h"
#include "game.h"
#include "geometry_manager.h"
#include "glass_house_manager.h"
#include "hierarchical_entity_proximity_map.h"
#include "line_info.h"
#include "loaded_regions_cache.h"
#include "ngl.h"
#include "ngl_mesh.h"
#include "render_text.h"
#include "occlusion.h"
#include "occlusion_visitor.h"
#include "oldmath_po.h"
#include "oriented_bounding_box_root_node.h"
#include "pcuv_shadermaterial.h"
#include "proximity_map.h"
#include "region.h"
#include "renderoptimizations.h"
#include "sector2d.h"
#include "subdivision_node_obb_base.h"
#include "trace.h"
#include "wds.h"
#include "terrain.h"
#include "vector2di.h"
#include "vector2d.h"
#include "utility.h"
#include "physical_interface.h"
#include "os_developer_options.h"

#include "common.h"

#include <cassert>
#include <cmath>

VALIDATE_SIZE(wds_render_manager, 156u);

struct traversed_entity {
    entity_base_vhandle m_handle;
    int field_4;
};
static Var<fixed_vector<traversed_entity, 750> *> traversed_entities_last_frame {0x0095C7B4};

wds_render_manager::wds_render_manager() {
    this->field_30.sub_56FCB0();

    this->field_0 = new RenderOptimizations();
    this->field_94 = nullptr;
    this->field_98 = 0;

    this->field_10[0] = 0.30000001f;
    this->field_10[1] = -1.0f;
    this->field_10[2] = 0.2f;
    this->field_10[3] = 0;

    this->field_20[0] = 0.80000001f;
    this->field_20[1] = 0.80000001f;
    this->field_20[2] = 0.85000002f;
    this->field_20[3] = 1.0f;

    this->field_60 = {0, 0, 0, 1};

    this->field_90 = 1.0f;
    this->field_5C = nullptr;
    this->field_8C = 0;
    this->field_84 = 175.0f;
    this->field_88 = 250.0f;
}


void show_terrain_info()
{
    if ( g_world_ptr() != nullptr )
    {
        auto *v0 = g_world_ptr()->get_hero_ptr(0);
        if ( v0 != nullptr )
        {
            auto *v8 = g_world_ptr()->get_hero_ptr(0);
            if ( v8->has_physical_ifc() )
            {
                auto *v3 = g_world_ptr()->get_hero_ptr(0);
                auto *v4 = v3->physical_ifc();

                string_hash v17;
                v4->get_parent_terrain_type(&v17);

                vector2d v5{512.0, 32.0};
                vector2di v14 {v5};

                auto *v6 = v17.to_string();
                mString v16 {v6};
                color32 v7{255, 255, 255, 255};
                render_text(v16, v14, v7, 1.0, 1.0);
            }
        }
    }
}

void wds_render_manager::debug_render()
{
    TRACE("wds_render_manager::debug_render");

    if constexpr (1) {

        if (os_developer_options::instance()->get_flag(mString{"SHOW_TERRAIN_INFO"}))
        {
            show_terrain_info();
        }

        if ( debug_render_get_ival((debug_render_items_e)20) || os_developer_options::instance()->get_flag(mString {"SHOW_GLASS_HOUSE"}))
        {
            //glass_house_manager::show_glass_houses();
        }

        //if ( debug_render_get_ival((debug_render_items_e)21) || SHOW_OBBS || SHOW_DISTRICTS )
        {
            auto *ter= g_world_ptr()->get_the_terrain();
            ter->show_obbs();
        }

        render_debug_spheres();

        debug_render_line_info();
    }
}

int wds_render_manager::add_far_away_entity(vhandle_type<entity> a2) {
    return THISCALL(0x0052A470, this, a2);
}

void wds_render_manager::init_level(const char *a2) {

    TRACE("wds_render_manager::init_level", a2);
    if constexpr (1) {
        if (this->field_5C == nullptr) {
            tlFixedString a1{"obb_shadow000"};
            this->field_5C = nglGetMesh(a1, true);
        }

        if (this->field_94 == nullptr) {
            filespec v7{mString{a2}};

            this->field_94 = new city_lod{v7.m_name.c_str()};
        }
    } else {
        THISCALL(0x00550930, this, a2);
    }
}

static constexpr auto g_projected_fov_multiplier = 0.80000001f;

void wds_render_manager::update_occluders(camera *a2) {
    occlusion::empty_quad_database();

    for (auto &i : this->field_30.field_0) {
        auto *reg = i.field_0;

        float v18 = reg->get_ground_level();

        auto &v5 = a2->get_abs_po();

        auto &v6 = a2->get_abs_position();

        occlusion_visitor visitor{v6, v5.get_z_facing(), v18, reg};

        ++subdivision_node_obb_base::visit_key();

        auto a4 = a2->compute_xz_projected_fov() * g_projected_fov_multiplier;

        auto &v11 = a2->get_abs_po();

        auto &v12 = a2->get_abs_po();

        vector3d a2a = a2->get_abs_position() - v12.get_z_facing() * 20.f;

        sector2d v26{a2a, v11.get_z_facing(), a4};
        ++region::visit_key2();
        auto *v16 = reg->field_98;
        if (v16 != nullptr) {
            v16->field_5C->traverse_sector_raster(v26, 100.0f, visitor);
        }
    }
}

void update_camera_teleport(camera &cam)
{
    TRACE("update_camera_teleport");

    if constexpr (1) {
        auto *v1 = g_cut_scene_player();
        auto v17 = ( v1->is_playing() ? 1.0 : 25.0 );

        static Var<vector3d> last_camera_position {0x00960B48};
        static Var<bool> last_camera_position_valid {0x00960B54};

        auto &abs_pos = cam.get_abs_position();
        if ( !last_camera_position_valid() )
        {
            last_camera_position() = abs_pos;
        }

        ++entity::visit_key();

        auto len2 = (last_camera_position() - abs_pos).length2();
        if ( len2 > v17 )
        {
            fixed_vector<region *, 15> a2 {};
            
            camera_teleport_update_visitor_t visitor {};
            loaded_regions_cache::get_regions_intersecting_sphere(abs_pos, culling_params::entity_traversal_distance, &a2);
            for (auto i = 0u; i < a2.size(); ++i) 
            {
                region *reg = a2.at(i);
                assert(reg != nullptr);

                reg->visibility_map->traverse_sphere(
                                                abs_pos,
                                                culling_params::entity_traversal_distance,
                                                &visitor);
                auto *bitvector_of_legos_rendered_last_frame = reg->bitvector_of_legos_rendered_last_frame;
                if ( bitvector_of_legos_rendered_last_frame != nullptr ) {
                    bitvector_of_legos_rendered_last_frame->clear();
                }

            }

            if ( traversed_entities_last_frame() != nullptr ) {
                traversed_entities_last_frame()->m_size = 0;
            }
        }

        last_camera_position() = cam.get_abs_position();
        last_camera_position_valid() = true;
    } else {
        CDECL_CALL(0x00530760, &cam);
    }
}

#include "debug_menu.h"

void wds_render_manager::render(camera &a2, int a3)
{
    TRACE("wds_render_manager::render");

    assert(this->field_94 != nullptr);

    THISCALL(0x0054B250, this, &a2, a3);

    //_populate_missions();

    if ( debug_render_get_bval(OCCLUSION) )
    {
        occlusion::debug_render_occluders();
    }

    this->debug_render();
}

void render_data::sub_56FCB0() {
    THISCALL(0x0056FCB0, this);
}

void wds_render_manager::frame_advance(Float a2) {
    TRACE("wds_render_manager::frame_advance");

    THISCALL(0x0054ADE0, this, a2);
}

void wds_render_manager::render_stencil_shadows(const camera &a2)
{
    TRACE("wds_render_manager::render_stencil_shadows");
    
    THISCALL(0x0053D5E0, this, &a2);
}

void wds_render_manager::build_render_data_regions(render_data *arg0, camera *arg4)
{
    TRACE("wds_render_manager::build_render_data_regions");

    THISCALL(0x00547000, this, arg0, arg4);
}

void wds_render_manager::build_render_data_ents(render_data *a2, camera *a3, int a4)
{
    TRACE("wds_render_manager::build_render_data_ents");

    THISCALL(0x00547250, this, a2, a3, a4);
}

void wds_render_manager::sub_53D560(const camera *a2)
{
    TRACE("wds_render_manager::sub_53D560");

    THISCALL(0x0053D560, this, a2);
}

void wds_render_manager_patch() {
    REDIRECT(0x0054B410, debug_render_get_bval);

    {
        FUNC_ADDRESS(address, &wds_render_manager::render);
        REDIRECT(0x0054E52D, address);
    }

    REDIRECT(0x0054B265, update_camera_teleport);

    {
        FUNC_ADDRESS(address, &wds_render_manager::init_level);
        REDIRECT(0x0055B355, address);
    }

    {
        FUNC_ADDRESS(address, &wds_render_manager::render_stencil_shadows);
        REDIRECT(0x0054E585, address);
    }

    {
        FUNC_ADDRESS(address, &wds_render_manager::build_render_data_regions);
        REDIRECT(0x0054B3FB, address);
    }

    {
        FUNC_ADDRESS(address, &wds_render_manager::build_render_data_ents);
        REDIRECT(0x0054B428, address);
    }

    {
        FUNC_ADDRESS(address, &wds_render_manager::sub_53D560);
        REDIRECT(0x0054B403, address);
    }
}
