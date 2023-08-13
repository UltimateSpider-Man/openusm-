#include "conglom.h"

#include "app.h"
#include "als_res_data.h"
#include "animation_interface.h"
#include "base_ai_data.h"
#include "beam.h"
#include "camera.h"
#include "collision_geometry.h"
#include "common.h"
#include "custom_math.h"
#include "debug_render.h"
#include "decal_data_interface.h"
#include "entity_mash.h"
#include "femanager.h"
#include "func_wrapper.h"
#include "game.h"
#include "geometry_manager.h"
#include "light_manager.h"
#include "ngl.h"

#ifdef TARGET_XBOX
#include "mashable_interface.h"
#endif

#include "memory.h"
#include "ngl_mesh.h"
#include "oldmath_po.h"
#include "os_developer_options.h"
#include "potential_shadow.h"
#include "script_data_interface.h"
#include "render_text.h"
#include "skeleton_interface.h"
#include "tentacle_interface.h"
#include "trace.h"
#include "utility.h"
#include "variables.h"
#include "variant_interface.h"
#include "vector2di.h"
#include "vtbl.h"

#include <cmath>

VALIDATE_SIZE(conglomerate, 0x130);

conglomerate::conglomerate(const string_hash &a2, unsigned int a3) : actor(a2, a3) {}

void conglomerate::init_member_data() {
    this->skeleton_ifc = nullptr;
    this->field_11C = nullptr;
    this->script_data_ifc = nullptr;
    this->field_124 = nullptr;
    this->my_decal_data_interface = nullptr;
    this->field_12C = nullptr;
    this->field_FC = nullptr;
    this->field_100 = nullptr;
    this->field_104 = 0;
    this->field_108 = -1.0;
    this->field_10C = -1.0;
    this->field_4 |= 4;
    this->field_110 = 3;
}

constexpr auto _ENTM_TYPE_MAX = 28u;

void conglomerate::_un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4)
{
    TRACE("conglomerate::un_mash", this->field_10.to_string());
    
    if constexpr (1)
    {
        std::memcpy(&this->field_110, a4->field_4, 4);
        a4->field_4 += 4;
        if ( this != (conglomerate *)-248 )
        {
            this->field_F8 = nullptr;
        }


#ifndef TARGET_XBOX
        if ( (a2->field_E & 0x40) != 0 )
        {
            if ( auto v6 = 4 - ((int)a4->field_0 % 4u);
                    v6 < 4 )
            {
                a4->field_0 += v6;
            }

            this->skeleton_ifc = (skeleton_interface *)a4->field_0;
            a4->field_0 += sizeof(skeleton_interface);
            fix_ifc_v_table((char *) this->skeleton_ifc, (eEntityMashIFCTypeEnum) 6);

            this->skeleton_ifc->un_mash(
                a2,
                this,
                this->skeleton_ifc,
                a4);
        }
        else
        {
            this->skeleton_ifc = nullptr;
        }
#endif

        this->member_abs_po.custom_un_mash(a2, &this->member_abs_po, a4, nullptr);
        this->all_rel_po.custom_un_mash(a2, &this->all_rel_po, a4, nullptr);
        this->all_model_po.custom_un_mash(a2, &this->all_model_po, a4, nullptr);

        {
            auto *header = a2;
            assert(((int)header) % 4 == 0);
        }

#ifdef TARGET_XBOX
        mashable_interface<skeleton_interface> tmp_skeleton_ifc;
        tmp_skeleton_ifc.custom_un_mash(a2, &tmp_skeleton_ifc, a4);

        if ( tmp_skeleton_ifc.exists() )
        {
            auto *skel_ifc = tmp_skeleton_ifc.get_interface();
            skel_ifc->field_4 = this;
        }

        skeleton_ifc = tmp_skeleton_ifc.get_interface();
#endif

#ifndef TARGET_XBOX
        if ( (a2->field_E & 4) != 0 )
        {
            if ( auto v7 = 4 - ((int)a4->field_0 % 4u);
                    v7 < 4 )
            {
                a4->field_0 += v7;
            }

            this->field_11C = (animation_interface *) a4->field_0;
            a4->field_0 += sizeof(animation_interface);

            fix_ifc_v_table((char *)this->field_11C, (eEntityMashIFCTypeEnum) 0);

            this->field_11C->un_mash(a2, this,
                this->field_11C,
                a4);
        }
        else
        {
            this->field_11C = nullptr;
        }

        if ( (a2->field_E & 0x20) != 0 )
        {
            auto v8 = 4 - ((int)a4->field_0 % 4u);
            if ( v8 < 4 )
            {
                a4->field_0 += v8;
            }

            this->script_data_ifc = (script_data_interface *)a4->field_0;
            a4->field_0 += sizeof(script_data_interface);

            fix_ifc_v_table((char *)this->script_data_ifc, (eEntityMashIFCTypeEnum) 3);

            this->script_data_ifc->un_mash(
                a2,
                this,
                this->script_data_ifc,
                a4);
        }
        else
        {
            this->script_data_ifc = nullptr;
        }

        if ( (a2->field_E & 0x2000) != 0 )
        {
            auto v9 = 4 - ((int)a4->field_0 % 4);
            if ( v9 < 4 )
            {
                a4->field_0 += v9;
            }

            this->field_124 = (tentacle_interface *)a4->field_0;
            a4->field_0 += sizeof(tentacle_interface);

            fix_ifc_v_table((char *) this->field_124, (eEntityMashIFCTypeEnum) 8);
            this->field_124->un_mash(
                a2,
                this,
                this->field_124,
                a4);
        }
        else
        {
            this->field_124 = nullptr;
        }

        if ( (a2->field_E & 0x1000) != 0 )
        {
            auto v10 = 4 - ((int)a4->field_0 % 4);
            if ( v10 < 4 )
            {
                a4->field_0 += v10;
            }

            this->my_decal_data_interface = (decal_data_interface *)a4->field_0;
            a4->field_0 += sizeof(decal_data_interface);

            fix_ifc_v_table((char *) this->my_decal_data_interface, (eEntityMashIFCTypeEnum) 9);
            this->my_decal_data_interface->un_mash(
                a2,
                this,
                this->my_decal_data_interface,
                a4);

            assert(!my_decal_data_interface->is_dynamic());
        }
        else
        {
            this->my_decal_data_interface = nullptr;
        }

        assert(((int)a2) % 4 == 0);

        if ( (a2->field_E & 0x4000) != 0 )
        {
            auto v11 = 4 - ((int)a4->field_0 & 3);
            if ( v11 < 4 )
            {
                a4->field_0 += v11;
            }

            this->field_12C = (variant_interface *)a4->field_0;
            a4->field_0 += sizeof(variant_interface);

            fix_ifc_v_table((char *) this->field_12C, (eEntityMashIFCTypeEnum) 10);

            this->field_12C->un_mash(
                a2,
                this,
                this->field_12C,
                a4);
        }
        else
        {
            this->field_12C = nullptr;
        }
#endif

        assert(((int)a2) % 4 == 0);

        this->field_E8.custom_un_mash(a2, &this->field_E8, a4, nullptr);
        this->field_F0.custom_un_mash(a2, &this->field_F0, a4, nullptr);
        this->members.custom_un_mash(a2, &this->members, a4, nullptr);

        assert(members.size() == member_abs_po.size());

        auto *v87 = this->member_abs_po.m_data;
        this->field_110 &= 0xFFFFFFF3;
        this->field_FC = nullptr;
        this->field_100 = nullptr;
        this->field_4 = this->field_4 & 0xFFFFFFFC | 4;
        this->my_conglom_root = this;

        sp_log("members.size() = %d", this->members.size());
        for (auto it = this->members.begin(); it != this->members.end(); ++it, ++v87)
        {
            uint16_t __ENT_TYPE;
            std::memcpy(&__ENT_TYPE, a4->field_4, 2);
            a4->field_4 += 2;

            assert(__ENT_TYPE <= _ENTM_TYPE_MAX);

            actor *tmp_ptr = nullptr;

            if ( __ENT_TYPE != _ENTM_TYPE_MAX )
            {
                auto v19 = 4 - (bit_cast<uint32_t>(a4->field_4) % 4);
                if ( v19 < 4 )
                {
                    a4->field_4 += v19;
                }
                
                auto *header = bit_cast<generic_mash_header *>(a4->field_4);
                assert(((int)header) % 4 == 0);

                a4->field_4 += 16;

                assert(__ENT_TYPE == header->get_class_id());

                auto v22 = 16 - (bit_cast<uint32_t>(a4->field_0) % 16);
                if ( v22 < 16 )
                {
                    a4->field_0 += v22;
                }

                auto *a3 = a4->field_0;
                entity_base *__ENT_ptr = CAST(__ENT_ptr, a4->field_0);
                a4->field_0 += ent_size_lookup()[header->get_class_id()];

                {
                    eEntityMashTypeEnum v11 = (eEntityMashTypeEnum) header->get_class_id();
                    fix_entity_v_table((char *)__ENT_ptr, v11);
                }

                assert(__ENT_ptr->rel_po_idx != 0xFF);
                assert(__ENT_ptr->rel_po_idx < all_rel_po.size());

                __ENT_ptr->my_rel_po = &this->all_rel_po.m_data[__ENT_ptr->rel_po_idx];
                __ENT_ptr->my_conglom_root = this;
                __ENT_ptr->un_mash_start(header, a3, a4, nullptr);

                __ENT_ptr->field_8 |= 0x10u;
                __ENT_ptr->field_3E = 0;

                tmp_ptr = CAST(tmp_ptr, __ENT_ptr);
            }

            assert(tmp_ptr->is_conglom_member());

            assert(!tmp_ptr->manage_abs_po());

            tmp_ptr->my_abs_po = v87;
            if ( tmp_ptr->is_an_actor() )
            {
                if ( tmp_ptr->get_colgeom() != nullptr )
                {
                    this->field_110 |= 4u;
                    this->field_4 |= 2;
                    if ( tmp_ptr->possibly_collide() )
                    {
                        if ( this->field_FC == nullptr )
                        {
                            auto *v31 = mem_alloc(sizeof(*this->field_FC));
                            this->field_FC = new (v31) _std::list<actor *> {};
                        }

                        this->field_FC->push_back(tmp_ptr);
                    }
                }

                if ( tmp_ptr->get_ai_core() )
                {
                    this->field_110 |= 8u;
                    this->field_4 |= 1;
                }

                if ( this->is_material_switching() )
                {
                    auto *v37 = &tmp_ptr->field_9C;
                    auto v38 = 4;
                    do
                    {
                        *v37 = v37[(char *)this - (char *)tmp_ptr];
                        ++v37;
                        --v38;
                    }
                    while ( v38 );
                }
            }

            if ( tmp_ptr->is_a_light_source() )
            {
                if ( this->field_100 == nullptr )
                {
                    auto *v39 = mem_alloc(sizeof(*this->field_100));
                    this->field_100 = new (v39) _std::list<light_source *> {};
                }

                this->field_100->push_back(bit_cast<light_source *>(tmp_ptr));
            }

            *it = tmp_ptr;
        }

        this->skin_bones.custom_un_mash(a2, &this->skin_bones, a4, nullptr);

        sp_log("skin_bones_size = %d", this->skin_bones.size());

#ifdef TARGET_XBOX
        assert(skin_bones.empty() || tmp_skeleton_ifc.exists());
#endif

        for (auto it = this->skin_bones.begin(); it != this->skin_bones.end(); ++it)
        {
            uint16_t __ENT_TYPE;
            std::memcpy(&__ENT_TYPE, a4->field_4, 2);
            a4->field_4 += sizeof(2);

            assert(__ENT_TYPE <= _ENTM_TYPE_MAX);

            actor *tmp_ptr = nullptr;
            if ( __ENT_TYPE != _ENTM_TYPE_MAX )
            {
                auto v48 = 4 - ((uint32_t) a4->field_4 % 4u);
                if ( v48 < 4 )
                {
                    a4->field_4 += v48;
                }

                auto *header = (generic_mash_header *) a4->field_4;
                assert(((int)header) % 4 == 0);

                a4->field_4 += 16;

                assert(__ENT_TYPE == header->get_class_id());

                auto v50 = (uint32_t) a4->field_0;
                auto v51 = 16 - (v50 & 15);
                if ( v51 < 16 )
                {
                    a4->field_0 += v51;
                }
                
                auto *__ENT_ptr = (entity_base *) a4->field_0;
                auto *v78 = a4->field_0;
                a4->field_0 += ent_size_lookup()[header->get_class_id()];

                {
                    auto v26 = (eEntityMashTypeEnum) header->get_class_id();
                    fix_entity_v_table((char *) __ENT_ptr, v26);
                }

                assert(__ENT_ptr->rel_po_idx != 0xFF);
                assert(__ENT_ptr->rel_po_idx < all_rel_po.size());

                __ENT_ptr->my_rel_po = &this->all_rel_po.m_data[__ENT_ptr->rel_po_idx];
                __ENT_ptr->my_conglom_root = this;

                __ENT_ptr->un_mash_start(header, v78, a4, nullptr);

                __ENT_ptr->field_8 |= 0x10u;
                __ENT_ptr->field_3E = 0;

                tmp_ptr = (actor *) __ENT_ptr;
            }

            {
                auto *tmp_handle = tmp_ptr;
                assert(tmp_handle->is_conglom_member());
            }

            this->skeleton_ifc->connect_bone_abs_po(tmp_ptr->get_bone_idx(), tmp_ptr);

            tmp_ptr->field_8 |= 0x10000000u;
            *it = tmp_ptr;
        }

        int v59;
        std::memcpy(&v59, a4->field_0, 4u);
        a4->field_0 += 4;
        if ( v59 )
        {
            int v61 = 0;
            std::memcpy(&v61, a4->field_0, 4);

            a4->field_0 += 4;

            auto v63 = 16 - (bit_cast<int>(a4->field_0) % 16);
            if ( v63 < 16 )
            {
                a4->field_0 += v63;
            }

            auto v64 = 4 - ((int)a4->field_0 % 4u);
            if ( v64 < 4 )
            {
                a4->field_0 += v64;
            }

            auto *v65 = a4->field_0;
            global_transfer_variable_the_conglom() = this;

            a4->field_0 += v61;

#ifdef TARGET_XBOX
            mash_info_struct v92 {mash::UNMASH_MODE, v65, v61, true};
#else
            mash_info_struct v92 {v65, v61};
#endif

            this->field_114 = (als_res_data *) v92.read_from_buffer(
#ifdef TARGET_XBOX
                mash::NORMAL_BUFFER,
#endif
                    sizeof(als_res_data), 8);
            this->field_114->unmash(&v92, nullptr);
            mash_info_struct::construct_class(this->field_114);
        }

        actor::_un_mash(a2, a3, a4);

        {
            bool (__fastcall *func_12C)(void *) = CAST(func_12C, get_vfunc(this->m_vtbl, 0x12C));
            if ( func_12C(this) )
            {
                void (__fastcall *func_268)(void *, int, int) = CAST(func_268, get_vfunc(this->m_vtbl, 0x268));
                func_268(this, 0, 0);
            }
        }

        nglMesh **v70;
        if ( this->field_90.field_5 <= 1u )
            v70 = this->field_90.field_0;
        else
            v70 = (nglMesh **)this->field_90.field_0[this->field_90.field_4];

        if ( v70 != nullptr )
        {
            auto **v71 = this->field_90.field_5 <= 1u ? this->field_90.field_0 : (nglMesh **) this->field_90.field_0[this->field_90.field_4];
            if ( v71[4] != nullptr )
            {
                auto *v72 = mem_alloc(sizeof(light_manager));
                auto *v74 = new (v72) light_manager {0};

                auto *v75 = this->field_F8;
                if ( v75 != v74 )
                {
                    if ( v75 != nullptr )
                    {
                        auto v17 = v75->field_0-- == 1;
                        if ( v17 )
                        {
                            auto *v76 = this->field_F8;
                            if ( v76 != nullptr )
                            {
                                this->field_F8->remove_from_list();
                                mem_dealloc(v76, sizeof(*v76));
                            }
                        }
                    }

                    this->field_F8 = v74;

                    if ( v74 != nullptr )
                    {
                        ++v74->field_0;
                    }
                }

                this->field_F8->field_C = this->my_handle.field_0;
                this->field_4 |= 0x2000u;
            }
        }

        this->field_110 |= 3u;

        this->set_flag_recursive(entity_flag_t {2}, this->possibly_collide());

        this->field_108 = -1.0;
        this->field_10C = -1.0;
        if ( this->field_7C != nullptr )
        {
            this->field_7C->post_entity_mash();
        }

        if ( this->has_tentacle_ifc() )
        {
            auto *v81 = this->tentacle_ifc();
            v81->initialize_polytubes();
        }

        if ( this->has_variant_ifc() )
        {
            auto *v82 = this->variant_ifc();
            v82->field_28 = v82->field_4->get_mesh()->File;
            auto *v83 = v82->sub_4CAD00();
            v82->apply_variant(v83);
        }
    }
    else
    {
        THISCALL(0x004FC830, this, a2, a3, a4);
    }
}

void conglomerate::release_mem() {
    THISCALL(0x004F9F10, this);
}

void conglomerate::_render(Float a2)
{
    TRACE("conglomerate::render");

    THISCALL(0x004F9930, this, a2);
    return;

    debug_render_set_ival(SKELETONS, 1);

    if (debug_render_get_ival(SKELETONS) <= 0)
    {
        THISCALL(0x004F9930, this, a2);
    }
    else
    {
        this->debug_render();
    }
}

static Var<camera*> g_camera_link {0x0095C720};

void conglomerate::debug_render()
{
    TRACE("conglomerate::debug_render");

    auto &v1 = this->get_abs_po();
    auto &v138 = v1.get_z_facing();
    auto &v2 = this->get_abs_position();
    auto v139 = v2 + v138 + YVEC;
    auto v5 = this->get_abs_position() + YVEC;
    //render_beam(v5, v139, color32 {33, 134, 216, 128}, 0.1, false);

    auto &v6 = this->get_abs_po();
    auto &v140 = v6.get_z_facing();
    auto v8 = this->get_abs_position() + v140;
    auto v9 = v8 + YVEC;
    render_debug_hemisphere(v9, 0.12, color32 {242, 124, 6, 128});

    auto &v175 = this->get_abs_position();
    auto *v10 = g_camera_link();
    auto &v11 = v10->get_abs_position();
    auto v12 = v11 - v175;
    auto v189 = v12.length2();
    auto v176 = this->get_visual_radius();
    auto v188 = (sqr(v176) > v189 && debug_render_get_ival(SKELETONS) == 1);
    auto v245 = v188;
    if ( v188 )
    {
        auto v13 = this->get_id();
        auto *v177 = v13.to_string();
        auto v141 = color32(255, 0, 0, 255);
        auto &v14 = this->get_abs_position();
        sub_6A2635(v14, v141, 0.5, "%s", v177);
    }

    for ( auto i = 0; i < this->members.size(); ++i )
    {
        if ( this->field_E8.at(i) < 0
            || this->field_E8.at(i) >= this->skin_bones.size() + this->members.size() )
        {
            auto v165 = color32(33, 134, 216, 128);
            auto &v143 = this->get_abs_position();
            auto &v28 = this->members.at(i);
            auto &v29 = v28->get_abs_position();
            //render_beam(v29, v143, v165, 0.02, 0);
        }
        else
        {
            entity_base *v21;
            auto v18 = this->field_E8.at(i);
            if ( v18 >= this->members.size() )
            {
                auto v22 = this->field_E8.at(i);
                auto v23 = this->members.size();
                v21 = this->skin_bones.at(v22 - v23);
            }
            else
            {
                auto v19 = this->field_E8.at(i);
                v21 = this->members.at(v19);
            }

            auto &a2 = v21->get_abs_position();
            auto v164 = color32(33, 134, 216, 128);
            auto &v25 = this->members.at(i);
            auto &v26 = v25->get_abs_position();
            //render_beam(v26, a2, v164, 0.02, 0);
        }

        auto v178 = color32(242, 124, 6, 128);
        auto &v31 = this->members.at(i);
        auto &v32 = v31->get_abs_position();
        render_debug_hemisphere(v32, 0.02, v178);

        if ( v245 )
        {
            auto &v34 = this->members.at(i);
            auto v35 = v34->get_id();
            auto *v179 = v35.to_string();
            auto v144 = color32(255, 0, 0, 255);
            auto &v37 = this->members.at(i);
            auto &v38 = v37->get_abs_position();
            sub_6A2635(v38, v144, 0.5, "%s", v179);

            auto v166 = color32(255, 0, 0, 128);
            auto &v40 = this->members.at(i);
            auto &v41 = v40->get_rel_po();
            auto &v42 = v41.get_x_facing();
            auto v145 = v42 * 0.050000001;
            auto *v44 = this->members.at(i);
            auto &v45 = v44->get_abs_position();

            auto v146 = v45 + v145;
            auto &v47 = this->members.at(i);
            auto &v48 = v47->get_abs_position();
            //render_beam(v48, v146, v166, 0.0099999998, 0);

            auto v167 = color32(0, 255, 0, 128);
            auto &v50 = this->members.at(i);
            auto &v51 = v50->get_rel_po();
            auto &v52 = v51.get_y_facing();
            auto v147 = v52 * 0.050000001;
            auto &v54 = this->members.at(i);
            auto &v55 = v54->get_abs_position();
            auto v148 = v55 + v147;
            auto &v57 = this->members.at(i);
            auto &v58 = v57->get_abs_position();
            //render_beam(v58, v148, v167, 0.0099999998, 0);

            auto v168 = color32(0, 0, 255, 128);
            auto &v60 = this->members.at(i);
            auto &v61 = v60->get_rel_po();
            auto &v62 = v61.get_z_facing();
            auto v149 = v62 * 0.050000001;
            auto &v64 = this->members.at(i);
            auto &v65 = v64->get_abs_position();
            auto v150 = v65 + v149;

            auto &v67 = this->members.at(i);
            auto &v68 = v67->get_abs_position();
            //render_beam(v68, v150, v168, 0.0099999998, 0);
        }
    }

    for ( auto i = 0; i < this->skin_bones.size(); ++i )
    {
        int8_t v70;
        uint16_t v71;
        if ( this->field_F0.at(i) < 0
            || (v70 = this->field_F0.at(i),
            v71 = this->members.size(),
            v70 >= this->skin_bones.size() + v71) )
        {
            auto v170 = color32(33, 134, 216, 128);
            auto &v152 = this->get_abs_position();
            auto &v82 = this->skin_bones.at(i);
            auto &v83 = v82->get_abs_position();
            //render_beam(v83, v152, v170, 0.02, 0);
        }
        else
        {
            entity_base *v75 = nullptr;
            auto v72 = this->field_F0.at(i);
            if ( v72 >= this->members.size() )
            {
                auto v76 = this->field_F0.at(i);
                auto v77 = this->members.size();
                v75 = this->skin_bones.at(v76 - v77);
            }
            else
            {
                auto v73 = this->field_F0.at(i);
                v75 = this->members.at(v73);
            }

            auto &v214 = v75->get_abs_position();
            auto v169 = color32(33, 134, 216, 128);
            auto v151 = v214;
            auto &v79 = this->skin_bones.at(i);
            auto &v80 = v79->get_abs_position();
            //render_beam(v80, v151, v169, 0.02, 0);
        }

        auto v180 = color32(242, 124, 6, 128);
        auto &v85 = this->skin_bones.at(i);
        auto &v86 = v85->get_abs_position();
        render_debug_hemisphere(v86, 0.02, v180);

        if ( v245 )
        {
            auto &v88 = this->skin_bones.at(i);
            auto v89 = v88->get_id();
            auto *v181 = v89.to_string();
            auto v153 = color32(255, 0, 0, 255);

            auto &v91 = this->skin_bones.at(i);
            auto &v92 = v91->get_abs_position();
            sub_6A2635(v92, v153, 0.5, "%s", v181);

            auto v171 = color32(255, 0, 0, 128);
            auto &v94 = this->skin_bones.at(i);
            auto &v95 = v94->get_abs_po();
            auto &v96 = v95.get_x_facing();
            auto v154 = v96 * 0.050000001;

            auto &v98 = this->skin_bones.at(i);
            auto &v99 = v98->get_abs_position();
            auto v155 = v99 + v154;
            auto &v101 = this->skin_bones.at(i);
            auto &v102 = v101->get_abs_position();
            //render_beam(v102, v155, v171, 0.0099999998, 0);
            auto v172 = color32(0, 255, 0, 128);

            auto &v104 = this->skin_bones.at(i);
            auto &v105 = v104->get_abs_po();
            auto &v106 = v105.get_y_facing();
            auto v156 = v106 * 0.050000001;

            auto &v108 = this->skin_bones.at(i);
            auto &v109 = v108->get_abs_position();
            auto v157 = v109 + v156;

            auto &v111 = this->skin_bones.at(i);
            auto &v112 = v111->get_abs_position();
            //render_beam(v112, v157, v172, 0.0099999998, 0);

            auto v173 = color32(0, 0, 255, 128);
            auto &v114 = this->skin_bones.at(i);
            auto &v115 = v114->get_abs_po();
            auto &v116 = v115.get_z_facing();
            auto v158 = v116 * 0.050000001;

            auto &v118 = this->skin_bones.at(i);
            auto &v119 = v118->get_abs_position();
            auto v159 = v119 + v158;

            auto &v121 = this->skin_bones.at(i);
            auto &v122 = v121->get_abs_position();
            //render_beam(v122, v159, v173, 0.0099999998, 0);
        }
    }

    if ( debug_render_get_ival(SKELETONS) == 2 )
    {
        static string_hash stru_1564240 {"CAMERA_ROOT"};

        auto *v123 = this->get_member(stru_1564240, true);
        if ( v123 != nullptr )
        {
            auto *v244 = this->get_member(stru_1564240, true);
            auto v182 = color32(0, 255, 0, 255);
            auto &v125 = v244->get_abs_position();
            render_debug_hemisphere(v125, 0.1, v182);
            auto v126 = v244->get_id();
            auto *v183 = v126.to_string();
            
            auto v160 = color32(255, 0, 0, 255);
            auto &v127 = v244->get_abs_position();
            sub_6A2635(v127, v160, 0.5, "%s", v183);
        }
    }

    if ( debug_render_get_ival(SKELETONS) == 3 )
    {
        static string_hash stru_1564218 {"BIP01 PROP"};

        auto *v128 = this->get_member(stru_1564218, true);

        if ( v128 != nullptr )
        {
            auto *v243 = this->get_member(stru_1564218, true);
            auto v184 = color32(0, 255, 0, 255);
            auto &v130 = v243->get_abs_position();
            render_debug_hemisphere(v130, 0.1, v184);

            auto v131 = v243->get_id();
            auto *v185 = v131.to_string();
            auto v161 = color32(255, 0, 0, 255);
            auto &v132 = v243->get_abs_position();
            sub_6A2635(v132, v161, 0.5, "%s", v185);
        }

        static string_hash stru_156410C {"BIP01 PROP2"};

        auto *v133 = this->get_member(stru_156410C, true);
        if ( v133 != nullptr )
        {
            auto *v242 = this->get_member(stru_156410C, true);
            auto v186 = color32(0, 255, 0, 255);
            auto &v135 = v242->get_abs_position();
            render_debug_hemisphere(v135, 0.1, v186);

            auto v136 = v242->get_id();
            auto *v187 = v136.to_string();
            auto v162 = color32(255, 0, 0, 255);
            auto &v137 = v242->get_abs_position();
            sub_6A2635(v137, v162, 0.5, "%s", v187);
        }
    }
}

float conglomerate::get_colgeom_radius() {
    if constexpr (1) {
        if ((this->field_110 & 2) != 0) {
            float v1 = ((this->colgeom != nullptr) ? this->colgeom->get_bounding_sphere_radius()
                                                   : 0.0f);

            auto *v4 = this->field_FC;
            this->field_10C = v1;
            if (v4 != nullptr && v4->size()) {
                for (auto &act : (*v4)) {
                    vector3d v8 = this->get_colgeom_center();

                    vector3d v9 = act->get_colgeom_center();

                    auto tmp = v9 - v8;

                    auto v10 = act->get_colgeom_radius() + tmp.length();

                    if (v10 > this->field_10C) {
                        this->field_10C = v10;
                    }
                }

                this->field_10C *= 1.1f;
            }

            this->field_110 &= 0xFFFFFFFD;
        }

        return this->field_10C;

    } else {
        float __fastcall (*func)(void *) = CAST(func, 0x004D2670);

        return func(this);
    }
}

vector3d conglomerate::get_colgeom_center() {
    if (this->colgeom != nullptr) {
        auto &v3 = this->get_abs_po();
        auto v4 = this->colgeom->get_local_space_bounding_sphere_center();

        auto v7 = v3.m * v4;
        return v7;
    }

    return this->get_abs_position();
}

void conglomerate::radius_changed(bool a2) {
    if (a2) {
        this->field_110 |= 3u;
        this->field_8 |= 0x40u;
    }
}

void conglomerate::render_simple_shadow(Float arg0, Float arg4) {
    THISCALL(0x004E4D80, this, arg0, arg4);
}

bool sub_4C19C0(const string_hash &a1, entity_base **a2, int size, int *index) {
    bool v14 = false;
    int v13 = 0;
    auto v12 = size;
    while (v13 < v12) {
        auto v11 = (v12 + v13) >> 1;
        auto *v4 = a2[v11];
        auto v5 = v4->get_id();
        if (a1 < v5) {
            v12 = (v12 + v13) >> 1;
        } else {
            auto *v6 = a2[v11];
            auto v7 = v6->get_id();
            if (!(a1 > v7)) {
                v14 = true;
                if (index) {
                    *index = v11;
                }

                break;
            }

            v13 = v11 + 1;
        }
    }

    if (!v14 && index != nullptr) {
        if (v12 == size - 1) {
            auto *v8 = a2[v12];
            auto v9 = v8->get_id();
            if (a1 > v9) {
                ++v12;
            }
        }

        *index = v12;
    }

    return v14;
}

entity_base *conglomerate::get_member(const string_hash &a2, bool a3) {
    auto members_size = this->members.size();
    auto i = -1;
    if (members_size != 0) {
        auto **data = this->members.m_data;
        if (sub_4C19C0(a2, data, members_size, &i)) {
            return data[i];
        }
    }

    if (a3) {
        auto skin_bones_size = this->skin_bones.size();
        auto i = -1;
        if (skin_bones_size != 0) {
            auto **data = this->skin_bones.m_data;
            if (sub_4C19C0(a2, data, skin_bones_size, &i)) {
                return data[i];
            }
        }
    }

    return nullptr;
}

bool conglomerate::has_tentacle_ifc()
{
    bool (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x294));
    return func(this);
}

tentacle_interface *conglomerate::tentacle_ifc()
{
    tentacle_interface * (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x298));
    return func(this);
}

bool conglomerate::has_variant_ifc()
{
    bool (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x29C));
    return func(this);
}

variant_interface *conglomerate::variant_ifc()
{
    variant_interface* (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x2A0));
    return func(this);
}

entity_base *conglomerate::get_bone(const string_hash &a2, bool a3) {
    if constexpr (1) {
        auto skin_bones_size = this->skin_bones.size();
        auto i = -1;
        if (skin_bones_size != 0) {
            auto **data = this->skin_bones.m_data;
            if (sub_4C19C0(a2, data, skin_bones_size, &i)) {
                return data[i];
            }
        }

        if (a3) {
            return this->get_member(a2, 0);
        }

        return nullptr;
    } else {
        return (entity_base *) THISCALL(0x004CCC90, this, &a2, a3);
    }
}

void conglomerate_patch() {

    {
        FUNC_ADDRESS(address, &conglomerate::_un_mash);
        set_vfunc(0x00884834, address);
    }

    {
        FUNC_ADDRESS(address, &conglomerate::_render);
        set_vfunc(0x0088487C, address);
    }

    {
        FUNC_ADDRESS(address, &mashable_vector<entity_base *>::custom_un_mash);
        REDIRECT(0x004FCAC8, address);
        REDIRECT(0x004FCE5A, address);
    }

    {
        FUNC_ADDRESS(address, &mashable_vector<int8_t>::custom_un_mash);
        REDIRECT(0x004FCAA6, address);
        REDIRECT(0x004FCAB6, address);
    }

    {
        FUNC_ADDRESS(address, &mashable_vector<po>::custom_un_mash);
        REDIRECT(0x004FC8D4, address);
        REDIRECT(0x004FC8E3, address);
        REDIRECT(0x004FC8F2, address);
    }

    return;

    FUNC_ADDRESS(address, &conglomerate::get_colgeom_radius);
    set_vfunc(0x00884924, address);

    {
        FUNC_ADDRESS(address, &conglomerate::get_colgeom_center);
        //set_vfunc(0x00884928, address);
    }
}
