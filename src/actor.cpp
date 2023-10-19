#include "actor.h"

#include "advanced_entity_ptrs.h"
#include "ai_player_controller.h"
#include "als_animation_logic_system.h"
#include "als_res_data.h"
#include "base_ai_core.h"
#include "base_ai_data.h"
#include "colgeom_alter_sys.h"
#include "collision_capsule.h"
#include "color.h"
#include "common.h"
#include "conglom.h"
#include "custom_math.h"
#include "damage_interface.h"
#include "func_wrapper.h"
#include "generic_anim_controller.h"
#include "item.h"
#include "lego_map.h"
#include "ngl.h"
#include "ngl_mesh.h"
#include "ngl_support.h"
#include "oldmath_po.h"
#include "physical_interface.h"
#include "string_hash.h"
#include "utility.h"
#include "variables.h"
#include "vtbl.h"

#include <list.hpp>

VALIDATE_SIZE(actor, 0xC0u);

actor::actor(const string_hash &a2, uint32_t a3) : entity(a2, a3) {
    this->field_64 = 0;
    this->field_60 = 0;
    this->field_5C = 0;
    this->regions[0] = nullptr;
    this->regions[1] = nullptr;
    this->extended_regions = nullptr;
    this->field_58 = nullptr;
    this->field_7C = nullptr;

    this->colgeom = nullptr;

    this->m_damage_interface = nullptr;
    this->m_physical_interface = nullptr;

    this->field_A0 = nullptr;
    this->field_88 = 0;
    this->adv_ptrs = nullptr;
    this->anim_ctrl = nullptr;
    this->field_70 = 0;
    this->field_A4 = 0;
    this->field_BC = nullptr;
    this->field_A8[0] = 0;
    this->field_AC = {};
    this->field_B8 = 0;

    this->field_4 &= 0xFFFFFFFD;
}

actor::actor(int) : entity() {
    this->field_10 = {};

    this->field_90.field_4 = 1;
    this->field_90.field_5 = 1;
    this->field_90.field_0 = nullptr;
    this->field_90.field_6 = -1;
    this->field_90.field_8 = 0;
}

actor::~actor() {
    THISCALL(0x004F93A0, this);
}

int actor::get_entity_size() {
    return 192;
}

void actor::release_mem() {
    THISCALL(0x004F9410, this);
}

vector3d actor::get_velocity() {
    vector3d a2;
    this->get_velocity(&a2);

    return a2;
}

bool actor::has_traffic_light_ifc() {
    return this->field_A0 != nullptr;
}

traffic_light_interface *actor::traffic_light_ifc() {
    return this->field_A0;
}

void actor::allocate_anim_controller(unsigned int a2, nalBaseSkeleton *a3) {
    TRACE("actor::allocate_anim_controller");

    if constexpr (0) {
    } else {
        THISCALL(0x004CC630, this, a2, a3);
    }
}

#include "resource_pack_slot.h"
#include "resource_directory.h"
#include "tlresource_location.h"
#include "nal_system.h"

animation_controller::anim_ctrl_handle actor::play_anim(const string_hash &a3)
{
    TRACE("actor::play_anim");

    if ( this->anim_ctrl == nullptr ) {
        this->allocate_anim_controller(0u, nullptr);
    }

    assert(anim_ctrl != nullptr);
    this->anim_ctrl->play_base_layer_anim(a3, 0.0, 32u, true);

    {
        animation_controller::anim_ctrl_handle result{};
        result.field_0 = true;
        result.field_8 = this->anim_ctrl;
        return result;
    }
}

void actor::bind_to_scene_anim() {
    THISCALL(0x004EF400, this);
}

void actor::unbind_from_scene_anim(string_hash a3, string_hash a4) {
    THISCALL(0x004E2750, this, a3, a4);
}

float actor::get_floor_offset() {
    float __fastcall (*func)(void *) = bit_cast<decltype(func)>(0x004C0D90);

    return func(this);
}

bool actor::anim_finished(int) {
    return true;
}

void actor::invalidate_frame_delta() {
    THISCALL(0x004E3880, this);
}

void actor::set_frame_delta_no_update(const po &a2, Float a3) {
    THISCALL(0x004D6B60, this, &a2, a3);
}

bool actor::get_allow_tunnelling_into_next_frame() {
    return (bool) THISCALL(0x004CC940, this);
}

void *actor::find_like_item(vhandle_type<item> a2) {
    return (void *) THISCALL(0x004D2100, this, a2);
}

void actor::common_destruct() {
    THISCALL(0x004F5720, this);
}

void actor::cancel_animated_movement(const vector3d &a2, Float a3) {
    if constexpr (1) {
        if (this->is_frame_delta_valid()) {
            auto &v4 = this->adv_ptrs->field_C->field_0;

            vector3d pos = v4.get_position();

            if (a2 != ZEROVEC) {
                auto local_dot = dot(a2, pos);
                if (local_dot <= 0.0f) {
                    pos = a2 * (local_dot - a3);

                    if (pos.length2() > v4.get_position().length2()) {
                        pos = v4.get_position();
                    }
                }
            }

            vector3d v17 = this->get_abs_position() - pos;

            entity_set_abs_position(this, v17);

            auto tmp = v4.get_position() - pos;
            v4.set_position(tmp);
        } else {
            THISCALL(0x004E3970, this, &a2, a3);
        }
    }
}

void actor::get_velocity(vector3d *a2) {
    if constexpr (0) {
        vector3d *v5;

        auto *v3 = (actor *) this->m_parent;
        if (v3 != nullptr) {
            if (this->has_physical_ifc()) {
                auto *v4 = this->physical_ifc();
                v5 = a2;
                *a2 = v4->get_velocity();
                auto *v6 = this->adv_ptrs;
                if (v6 != nullptr) {
                    auto *v7 = v6->field_C;
                    if (v7 != nullptr) {
                        if (v7->field_54) {
                            auto *v8 = this->physical_ifc();
                            v8->field_84.get_volatile_ptr();
                            auto *v9 = this->physical_ifc();
                            if (v9->field_84.get_volatile_ptr() != nullptr) {
                                auto *v10 = this->physical_ifc();
                                if (v10->field_84.get_volatile_ptr() == (entity *) v3) {
                                    auto *v11 = (const vector3d *) this->adv_ptrs->field_C;
                                    auto v31 = 1.f / v11[5][1];
                                    auto v12 = v11[4] * v31;
                                    *a2 += v12;
                                }
                            }
                        }
                    }
                }
            } else {
                v5 = a2;
                *a2 = ZEROVEC;
            }

            po v35 = this->get_rel_po();
            for (; v3->m_parent != nullptr; v3 = (actor *) v3->m_parent) {
                v35 = v35.sub_4BAB00(v3->get_abs_po());
            }

            if (v3->is_an_actor()) {
                auto a3 = ZEROVEC;
                v3->get_velocity(&a3);

                vector3d v33 = ZEROVEC;

                if (v3->has_physical_ifc()) {
                    auto &v14 = v3->physical_ifc()->field_2C;

                    v33 = v14;
                }

                auto v18 = vector3d::cross(v35.get_position(), v33);

                *v5 += a3 + v18;
            }

        } else {
            if (this->has_physical_ifc()) {
                auto *v21 = this->physical_ifc();
                auto v22 = v21->get_velocity();

                *a2 = v22;

            } else {
                *a2 = ZEROVEC;
            }

            auto *v26 = this->adv_ptrs;
            if (v26 != nullptr) {
                auto *v27 = v26->field_C;
                if (v27 != nullptr) {
                    if (v27->field_54) {
                        auto *v28 = this->adv_ptrs->field_C;
                        auto v29 = 1.f / v28->field_40;

                        *a2 += v29 * v28->field_30;
                    }
                }
            }
        }

    } else {
        THISCALL(0x004E2EE0, this, a2);
    }
}

void actor::process_extra_scene_flags(unsigned int a2) {
    THISCALL(0x004FB960, this, a2);
}

bool actor::has_camera_collision() {
    auto *v1 = this->colgeom;
    return (v1 != nullptr) && (this->field_4 & 0x4000) != 0 && (v1->field_C & 0x10) != 0;
}

bool actor::has_entity_collision() {
    auto *v1 = this->colgeom;
    return v1 && (this->field_4 & 0x4000) != 0 && (v1->field_C & 2) != 0;
}

void actor::kill_interact_anim() {
    if constexpr (1) {
        auto *v2 = this->anim_ctrl;
        if (v2 != nullptr && (v2->field_10 & 1) != 0) {
            auto &finalize = get_vfunc(v2->m_vtbl, 0x0);
            finalize(v2, true);
            this->anim_ctrl = nullptr;
        }

        if (this->is_a_conglomerate()) {
            conglomerate *self = CAST(self, this);

            auto *v3 = self->field_114;
            if (v3 != nullptr) {
                auto *v4 = v3->field_8;
                if (v4 != nullptr) {
                    auto &suspend_logic_system = get_vfunc(v4->m_vtbl, 0x8);
                    suspend_logic_system(v4, 0);
                }
            }
        }

    } else {
        THISCALL(0x004CC740, this);
    }
}

physical_interface *actor::physical_ifc() {
    auto &func = get_vfunc(m_vtbl, 0x128);

    return (physical_interface *) func(this);
}

void actor::create_physical_ifc() {
    this->m_physical_interface = new physical_interface(this);
}

void actor::destroy_player_controller() {
    if constexpr (1) {
        auto *v2 = this->m_player_controller;
        if (v2 != nullptr) {
            auto &finalize = get_vfunc(v2->m_vtbl, 0x0);
            finalize(v2, true);
        }

        this->m_player_controller = nullptr;

    } else {
        THISCALL(0x004C0D40, this);
    }
}

void actor::_un_mash(generic_mash_header *a3, void *a4, generic_mash_data_ptrs *a5)
{
    TRACE("actor::un_mash");

    THISCALL(0x004FBD40, this, a3, a4, a5);
}

void actor::create_player_controller(int a2) {
    assert(this->m_player_controller == nullptr);

    this->m_player_controller = new ai_player_controller{this};

    this->m_player_controller->set_player_num(a2);
}

static Var<_std::list<actor::mesh_buffers *>> stru_95AAB4{0x0095AAB4};

void actor::swap_all_mesh_buffers() {
    for (auto &i : stru_95AAB4()) {
        actor::mesh_buffers *v2 = i;
        auto v3 = v2->field_5;
        if (v3 > 1u) {
            ++v2->field_4;

            v2->field_4 %= (int16_t) v3;
            nglCopyMesh(v2->field_0[v2->field_4], v2->field_0[v3]);
        }
    }
}

vector3d actor::get_colgeom_center() {
    auto &func = get_vfunc(m_vtbl, 0x258);

    vector3d result;
    func(this, &result);

    return result;
}

lego_map_root_node *actor::get_lego_map_root() {
    return (lego_map_root_node *) THISCALL(0x00502C70, this);
}

void actor::_render(Float a2)
{
    TRACE("actor::render");

    if constexpr (0)
    {
        auto *mesh = this->get_mesh();
        if (mesh != nullptr) {
            assert(mesh != nullptr && is_visible() && is_renderable());

            nglParamSet<nglShaderParamSet_Pool> ShaderParams{1};

            if (this->is_material_switching()) {
                auto *root_node = this->get_lego_map_root();
                if (root_node != nullptr) {
                    USMMaterialListParam list_param{root_node->field_4};
                    ShaderParams.SetParam(list_param);

                    USMMaterialIndicesParam indices_param{this->field_9C};
                    ShaderParams.SetParam(indices_param);
                }
            }

            if ((this->field_90.field_6 & 0x3FFF) != 0x3FFF) {
                auto v11 = (this->field_90.field_6 & 0x3FFF);

                nglTextureFrameParam frame_param{v11};
                ShaderParams.SetParam(frame_param);
            }

            auto v12 = this->field_90.field_6 >> 14;
            auto v13 = 3 - v12;
            if (v12 != 3) {
                USDamageFrameParam frame_param{v13};
                ShaderParams.SetParam(frame_param);
            }

            advanced_entity_ptrs *v15 = nullptr;
            if (a2 != 1.f || (v15 = this->adv_ptrs) != nullptr && v15->field_8 != nullptr) {
                auto *mem = nglListAlloc(16, 16);

                auto v17 = this->get_render_color();

                color *v18 = new (mem) color{v17.to_color()};

                v18->a = this->get_render_alpha_mod() * v18->a * a2;

                nglTintParam param{(vector4d *) v18};
                ShaderParams.SetParam(param);
            }

            math::MatClass<4, 3> *v21 = bit_cast<decltype(v21)>(&this->get_abs_po());

            static nglMeshParams g_MeshParams{0x80000040};

            FastListAddMesh(mesh, *v21, &g_MeshParams, &ShaderParams);
        }

    }
    else
    {
        THISCALL(0x004E33B0, this, a2);
    }
}

damage_interface *actor::damage_ifc() {
    //return this->my_damage_interface;

    auto &func = get_vfunc(m_vtbl, 0x118);
    return (damage_interface *) func(this);
}

void actor::create_damage_ifc() {
    this->m_damage_interface = new damage_interface{this};
}

double actor::get_colgeom_radius() {
    auto &func = get_vfunc(m_vtbl, 0x254);
    return (float) func(this);
};

bool actor::is_frame_delta_valid() {
    if constexpr (1) {
        auto *v1 = this->adv_ptrs;
        bool result = false;
        if (v1 != nullptr) {
            auto *v2 = v1->field_C;
            if (v2 != nullptr) {
                if (v2->field_54) {
                    result = true;
                }
            }
        }
        return result;
    } else {
        return (bool) THISCALL(0x004B8FC0, this);
    }
}

movement_info *actor::get_movement_info() {
    movement_info *result = nullptr;

    if (this->adv_ptrs) {
        result = this->adv_ptrs->field_C;
    }

    return result;
}

po *actor::get_frame_delta() {
    if constexpr (1) {
        po *result = nullptr;

        auto *v1 = this->adv_ptrs;
        if (v1 == nullptr || (result = &v1->field_C->field_0) == nullptr) {
            static po po_identity_matrix{};

            result = &po_identity_matrix;
        }

        return result;

    } else {
        return (po *) THISCALL(0x004B9000, this);
    }
}

vector4d __fastcall sub_503A90(void *a1, int, vector4d a2) {
    if constexpr (1) {
        struct {
            int field_0;
            int field_4;
            int16_t field_8[3];

        } *self = static_cast<decltype(self)>(a1);

        vector4d a3;

        a3[0] = self->field_8[0] * LARGE_EPSILON;

        a3[1] = self->field_8[1] * LARGE_EPSILON;

        a3[2] = self->field_8[2] * LARGE_EPSILON;

        a3[3] = 1.0;

        return sub_411750(a2, a3);

    } else {
        vector4d result;
        THISCALL(0x00503A90, a1, &result, a2);

        return result;
    }
}

vector3d sub_509170(entity_base *a2, unsigned int a3) {
    vector3d result;

    if ((a3 & 0x20) != 0) {
        auto &v3 = a2->get_abs_po().get_x_facing();

        result = 4.5f * YVEC + v3 * 3.0f;

    } else if ((a3 & 0x1000000) != 0) {
        auto &v8 = a2->get_abs_po().get_z_facing();

        result = -2.0f * YVEC + v8 * 3.2f;

    } else if ((a2->field_4 & 0x800) != 0) {
        auto &v12 = a2->get_abs_po().get_z_facing();

        result = v12 * 2.f;

    } else {
        result = ZEROVEC;
    }

    return result;
}

bool actor::has_vertical_obb() {
    return this->field_B8 != 0;
}

vector3d *actor::get_cached_visual_bounding_sphere_center() {
    assert(!has_vertical_obb());

    return &this->field_AC;
}

vector3d actor::_get_visual_center()
{
    TRACE("actor::get_visual_center");

    if constexpr (0)
    {
        vector3d v6;

        if (this->get_mesh() != nullptr) {
            if (this->has_vertical_obb()) {
                auto v17 = sub_503A90(this->field_A8, 0, this->get_abs_po().m[3]);

                auto v10 = sub_509170(this, this->field_8);
                v6 = v17 + v10;

            } else {
                if (this->is_ext_flagged(0x40u)) {
                    this->field_8 &= 0xFFFFFFBF;

                    auto *Mesh = this->get_mesh();

                    this->field_AC[0] = Mesh->field_20.field_0[0];
                    this->field_AC[1] = Mesh->field_20.field_0[1];
                    this->field_AC[2] = Mesh->field_20.field_0[2];

                    assert(get_cached_visual_bounding_sphere_center()->is_valid());

                    auto &abs_po = this->get_abs_po();

                    this->field_AC = abs_po.slow_xform(this->field_AC);

                    assert(get_cached_visual_bounding_sphere_center()->is_valid());
                }

                auto v10 = sub_509170(this, this->field_8);
                v6 = this->field_AC + v10;
            }

        } else {
            auto v4 = this->get_abs_position();

            vector3d v5 = sub_509170(this, this->field_8);
            v6 = v5 + v4;
        }

        return v6;

    }
    else
    {
        vector3d result;
        THISCALL(0x004E31F0, this, &result);
        return result;
    }
}

bool actor::add_item(int a4, bool a6)
{
    return (bool) THISCALL(0x004E3B80, this, a4, a6);
}

void actor::add_collision_ignorance(entity_base_vhandle a2)
{
    TRACE("actor::add_collision_ignorance");

    THISCALL(0x004E2C10, this, a2);
}

nglMesh **actor::sub_4B8BCA() {
    return this->field_90.field_0;
}

nglMesh *actor::get_mesh() {
    if constexpr (0) {
        nglMesh *result;

        if (this->field_90.field_5 <= 1u)
            result = (nglMesh *) this->sub_4B8BCA();
        else
            result = this->field_90.field_0[this->field_90.field_4];
        return result;
    } else {
        return (nglMesh *) THISCALL(0x004B8BB0, this);
    }
}

ai::ai_core *actor::_get_ai_core() {
    ai::ai_core *result = nullptr;

    auto *v1 = this->field_7C;
    if (v1 != nullptr) {
        result = v1->field_14;
    }

    return result;
}

void actor::get_animations(actor *a1, std::list<nalAnimClass<nalAnyPose> *> &a2)
{
    a2.clear();
    auto *v11 = a1->field_BC;
    if ( v11 != nullptr )
    {
        auto &res_dir = v11->get_resource_directory();
        auto tlresource_count = res_dir.get_tlresource_count(TLRESOURCE_TYPE_ANIM_FILE);
        for (auto idx = 0; idx < tlresource_count; ++idx)
        {
            auto *tlres_loc = res_dir.get_tlresource_location(idx, TLRESOURCE_TYPE_ANIM_FILE);
            auto *animFile = (nalAnimFile *) tlres_loc->field_8;
            if ( animFile->field_0 == 0x10101 )
            {
                for ( auto *anim = bit_cast<nalAnimClass<nalAnyPose> *>(animFile->field_34);
                        anim != nullptr;
                        anim = anim->field_4 ) {
                    a2.push_back(anim);
                }
            }
        }
    }
}

namespace ai {

void setup_hero_capsule(actor *act) {
    if constexpr (1) {
        auto *core = act->get_ai_core();

        core->create_capsule_alter();
        auto *capsule_alter = core->field_70;
        auto *ctrl = act->m_player_controller;
        conglomerate *cngl = CAST(cngl, act);

        if (ctrl != nullptr && ctrl->field_420 == 2) {
            capsule_alter->set_avoid_floor(false);
            capsule_alter->set_avg_radius(0.64999998);
            capsule_alter->set_mode(capsule_alter_sys::eAlterMode{3});

            auto *v4 = cngl->get_bone(bip01_l_calf(), true);
            capsule_alter->set_base_avg_node(0, v4, 0.5);
            auto *v5 = cngl->get_bone(bip01_r_calf(), true);
            capsule_alter->set_base_avg_node(1, v5, 0.5);
            auto *v6 = cngl->get_bone(bip01_pelvis(), true);
            capsule_alter->set_base_avg_node(2, v6, 1.0);
            capsule_alter->set_base_avg_node(3, nullptr, 0.0);
            auto *v7 = cngl->get_bone(bip01_head(), true);
            capsule_alter->set_end_avg_node(0, v7, 3.0);
            auto *v8 = cngl->get_bone(bip01_spine(), true);
            capsule_alter->set_end_avg_node(1, v8, 1.0);
            capsule_alter->set_end_avg_node(2, nullptr, 0.0);
        } else {
            set_to_default_capsule_alter(capsule_alter, cngl);
            capsule_alter->set_avoid_floor(false);
        }

    } else {
        CDECL_CALL(0x0068A440, act);
    }
}
} // namespace ai

void actor_patch()
{
    {
        FUNC_ADDRESS(address, &actor::_un_mash);
        set_vfunc(0x00884304, address);
    }

    {
        FUNC_ADDRESS(address, &actor::_render);
        set_vfunc(0x0088434C, address);
    }
    return;

    {
        FUNC_ADDRESS(address, &actor::_get_visual_center);
        set_vfunc(0x008841CC, address);
    }

    if constexpr (0) {
        REDIRECT(0x006A799C, &ai::setup_hero_capsule);

        {
            FUNC_ADDRESS(address, &actor::has_entity_collision);
            REDIRECT(0x00563817, address);
        }

        {
            FUNC_ADDRESS(address, &actor::kill_interact_anim);
            SET_JUMP(0x004CC740, address);
        }
        {
            FUNC_ADDRESS(address, &actor::cancel_animated_movement);
            SET_JUMP(0x004E3970, address);
        }
    }
}
