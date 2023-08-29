#include "entity.h"

#include "collision_geometry.h"
#include "common.h"
#include "func_wrapper.h"
#include "memory.h"
#include "moved_entities.h"
#include "region.h"
#include "time_interface.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

#include <cassert>

VALIDATE_SIZE(entity, 0x68u);

Var<int> entity::visit_key3{0x0095A6EC};

entity::entity(const string_hash &a2, uint32_t a3) : signaller(a2, a3, false) {
    this->field_64 = 0;
    this->field_60 = 0;
    this->field_5C = 0;
    this->regions[0] = nullptr;
    this->regions[1] = nullptr;
    this->extended_regions = nullptr;
    this->field_58 = nullptr;
    this->colgeom = nullptr;
}

void entity::destroy_static_entity_pointers() {
    CDECL_CALL(0x004D6940);
}

entity::~entity() {
    THISCALL(0x004F91C0, this);
}

float entity::get_visual_radius() {
    if constexpr (0) {
        if ((this->field_4 & 0x8004) == 0) {
            return 0.0f;
        }

        auto *parent = this->get_conglom_owner();
        if (parent == nullptr) {
            return 0.0f;
        }

        assert(parent->is_a_conglomerate());

        return parent->get_visual_radius();
    } else {
        float __thiscall (*func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x28));
        return func(this);
    }
}

vector3d entity::get_visual_center() {
    vector3d result;
    if ((this->field_4 & 0x8004) != 0) {
        auto *parent = this->get_conglom_owner();

        if (parent != nullptr) {
            assert(parent->is_a_conglomerate());

            result = parent->get_visual_center();

        } else {
            result = this->get_abs_position();
        }

    } else {
        assert(!is_a_conglomerate() && !is_an_actor() && !is_conglom_member());

        result = this->get_abs_position();
    }

    return result;
}

void entity::un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4)
{
    TRACE("entity::un_mash");

    for (auto i = 0; i < 2; ++i)
    {
        this->regions[i] = nullptr;
    }

    this->extended_regions = nullptr;
    this->field_58 = nullptr;
    this->colgeom = nullptr;
    entity_base::un_mash(a2, a3, a4);
}

void entity::clear_region(region *r, int i_know_what_i_am_doing) {
    THISCALL(0x004F54A0, this, r, i_know_what_i_am_doing);
}

entity *entity::compute_sector(terrain *, bool, entity *) {
    entity *result;

    if ((this->field_4 & 0x10000000) == 0) {
        moved_entities::add_moved({this->get_my_handle()});
    }

    return result;
}

void entity::force_region_hack(region *a2) {
    assert(regions[0] == nullptr);

    this->regions[0] = a2;
}

void entity::force_region(region *r) {
    if ((this->field_4 & 0x10000000) == 0) {
        this->remove_from_regions();
    }

    this->field_4 |= 0x10000000u;
    if (r != nullptr) {
        if (!this->is_in_region(r)) {
            this->add_me_to_region(r);
        }
    }
}

void entity::force_current_region() {
    this->field_4 |= 0x10000000u;
}

void entity::unforce_regions() {
    if ((this->field_4 & 0x10000000) != 0) {
        this->remove_from_regions();
        this->field_4 &= 0xEFFFFFFF;
    }
}

void entity::force_regions(entity *ent) {
    THISCALL(0x004F56A0, this, ent);
}

void entity::update_ai_proximity_map_recursive() {
    ;
}

void entity::set_family_visible(bool a2) {
    if constexpr (1) {
        if (!a2 || this->is_renderable()) {
            this->set_visible(a2, false);
        }

        for (auto *ent = this->m_child; ent != nullptr; ent = ent->field_28) {
            if (ent->is_an_entity()) {
                bit_cast<entity *>(ent)->set_family_visible(a2);
            }
        }

    } else {
        THISCALL(0x004C07B0, this, a2);
    }
}

bool entity::is_renderable() {
    return (this->field_4 >> 8) & 1;
}

bool entity::possibly_collide()
{
    if constexpr (1)
    {
        bool (__fastcall *func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x190));
        return func(this);
    }
    else
    {
        return this->get_colgeom() != nullptr && this->are_collisions_active();
    }
}

bool entity::possibly_camera_collide() {
    auto *v1 = this->colgeom;

    return v1 && (this->field_4 & 0x4000) != 0 && (v1->field_C & 0x10) != 0;
}

bool entity::possibly_walkable() {
    bool result = false;
    if (this->colgeom != nullptr) {
        auto v1 = this->field_4;
        if ((v1 & 0x4000) != 0 && (v1 & 0x80) != 0) {
            result = true;
        }
    }

    return result;
}

bool entity::sub_4C08E0() {
    return this->colgeom != nullptr && (this->field_4 & 0x4000) != 0 &&
        (this->field_8 & 0x8000) == 0;
}

void entity::region_update_poss_collide() {
    THISCALL(0x004C0810, this);
}

void entity::frame_advance(Float) {
    ;
}

bool entity::is_still_visible() {
    return (this->field_4 & 0x200) != 0;
}

void entity::render(Float a2) {
    auto &func = get_vfunc(m_vtbl, 0x1AC);

    func(this, a2);
}

nglMesh *entity::get_mesh() {
    return nullptr;
}

bool entity::has_mesh() {
    return false;
}

void entity::suspend(bool) {
    ;
}

void entity::unsuspend(bool) {
    ;
}

void entity::set_render_color() {
    ;
}

color32 entity::get_render_color() {
    if constexpr (1)
    {
        auto &func = get_vfunc(m_vtbl, 0x1C4);

        auto result = func(this);
        color32 col;
        std::memcpy(&col, &result, sizeof(result));
        return col;

    } else {
        color32 result;
        result.field_0[0] = -1;
        result.field_0[1] = -1;
        result.field_0[2] = -1;
        result.field_0[3] = -1;
        return result;
    }
}

void entity::set_render_alpha_mod(Float) {
    ;
}

float entity::get_render_alpha_mod() {
    if constexpr (1) {
        float __thiscall (*func)(void *) = CAST(func, get_vfunc(m_vtbl, 0x1CC));

        return func(this);

    } else {
        return 0.0;
    }
}

void entity::set_render_scale(const vector3d &) {
    ;
}

vector3d entity::get_render_scale() {
    vector3d result;
    result[0] = 1.0;
    result[1] = 1.0;
    result[2] = 1.0;

    return result;
}

void entity::set_render_zbias(Float) {
    ;
}

float entity::get_render_zbias() {
    return 0.0;
}

int entity::get_light_set() {
    return 0;
}

bool entity::can_be_a_lego() {
    return false;
}

bool entity::can_be_a_conglom_clone() {
    return false;
}

bool entity::is_a_dynamic_conglomerate_clone() {
    return false;
}

void entity::set_collisions_active(bool a1, bool a2) {
    auto &func = get_vfunc(m_vtbl, 0x1F0);

    func(this, a1, a2);
}

bool entity::are_character_collisions_active() {
    return false;
}

void entity::set_character_collisions_active(bool a2) {
    if (a2) {
        this->field_4 |= 0x10;
    } else {
        this->field_4 &= 0xFFFFFFEF;
    }
}

void entity::set_terrain_collisions_active(bool a2) {
    if (a2) {
        this->field_4 |= 0x20;
    } else {
        this->field_4 &= 0xFFFFFFDF;
    }
}

float entity::get_age() {
    return 0.0;
}

void entity::set_age(Float) {
    ;
}

void entity::set_recursive_age(Float a2) {
    this->set_age(a2);
}

bool entity::is_in_region(const region *a2) {
    return (bool) THISCALL(0x004CB5C0, this, a2);
}

void entity::add_me_to_region(region *r) {
    THISCALL(0x004F52C0, this, r);
}

collision_geometry *entity::get_colgeom() const {
    return this->colgeom;
}

float entity::get_colgeom_radius() const {
    float (*func)(const void *) = CAST(func, get_vfunc(m_vtbl, 0x254));

    return func(this);
}

void entity::remove_me_from_region(region *r) {
    assert(r != nullptr);

    THISCALL(0x004F5390, this, r);
}

void entity::create_time_ifc() {
    if constexpr (1) {
        auto *mem = mem_alloc(sizeof(time_interface));

        this->field_58 = new (mem) time_interface{this};
    } else {
        THISCALL(0x004DBA10, this);
    }
}

bool entity::is_indoors() {
    return (bool) THISCALL(0x004CB670, this);
}

region *entity::update_regions(region **a2, int a3) {
    return (region *) THISCALL(0x004F5510, this, a2, a3);
}

void entity::remove_from_regions() {
    THISCALL(0x004CB750, this);
}

region *entity::get_primary_region()
{
    TRACE("entity::get_primary_region");

    uint32_t v1 = this->field_4;
    if ((v1 & 0x8000) == 0) {
        return this->regions[0];
    }

    while (1) {
        entity *v2 = CAST(v2, this->get_conglom_owner());
        if (v2 == nullptr) {
            break;
        }

        uint32_t v3 = v2->field_4;
        if ((v3 & 0x8000) == 0) {
            return v2->regions[0];
        }
    }
    
    return nullptr;
}

int entity::find_entities(int a1)
{
    return CDECL_CALL(0x004D67D0, a1);
}

void entity_patch() {

    {
        FUNC_ADDRESS(address, &entity::get_primary_region);
        SET_JUMP(0x004C0760, address);
    }

    {
        FUNC_ADDRESS(address, &entity::force_regions);
        //set_vfunc(0x0088F440, address);
    }
}
