#include "region.h"

#include "bitvector.h"
#include "common.h"
#include "fixed_pool.h"
#include "func_wrapper.h"
#include "lego_map.h"
#include "memory.h"
#include "region_mash_info.h"
#include "subdivision_node_obb_base.h"
#include "terrain.h"
#include "trace.h"
#include "wds.h"

#include <cassert>
#include <cmath>

VALIDATE_SIZE(region, 0x134u);
VALIDATE_OFFSET(region, field_C4, 0xC4);
VALIDATE_OFFSET(region, field_108, 0x108);

static Var<fixed_pool> lego_bitvector_pool {0x009222D4};

region::region(const mString &a2) {
    THISCALL(0x0053B4B0, this, &a2);
}

void region::constructor_common() {
    this->bitvector_of_legos_rendered_last_frame = nullptr;
    this->field_98 = nullptr;
    this->obb = nullptr;
    this->field_34 = nullptr;
    this->field_38 = 0;
    this->field_3C = 0;
    this->m_fade_groups_count= 0;
    this->field_44 = 0;
    this->field_48 = 0;
    this->meshes = nullptr;
    this->texture_to_frame_maps = nullptr;
    this->m_total_frame_maps = 0;
    this->flags = 0;
    this->field_D4 = -1;
    this->multiblock_number = 1;
    this->district_id = 0;
    this->strip_id = -1;
    this->field_100 = nullptr;
    this->field_104 = nullptr;
    this->current_proximity_map_stack = nullptr;
    this->collision_proximity_map = nullptr;
    this->ai_proximity_map = nullptr;
    this->visibility_map = nullptr;
    this->light_proximity_map = nullptr;
    this->parking_proximity_map = nullptr;
    this->field_20 = 0;
    this->field_24 = 0;
    this->region_entities = nullptr;
    this->lights = nullptr;
}

region::region_astar_search_record::region_astar_search_record() {
    this->m_vtbl = 0x0087F0EC;
    this->field_24 = {};
}

void region::region_astar_search_record::setup(void *search_start, void *search_end) {
    if constexpr (1) {
        auto *_search_start = static_cast<region *>(search_start);
        auto *_search_end = static_cast<region *>(search_end);

        assert(_search_start != nullptr);

        this->field_34 = _search_start->field_B0;

        if (_search_end != nullptr) {
            auto v3 = _search_end->field_B0 - this->field_34;

            this->field_40 = v3.length();
        } else {
            this->field_40 = 3.4028235e38;
        }

        astar_search_record::setup(_search_start, _search_end, &this->field_24, nullptr);

    } else {
        THISCALL(0x00519CB0, this, search_start, search_end);
    }
}

float region::get_ground_level() const {
    if (this->obb != nullptr) {
        return this->field_BC;
    }

    return 0.0;
}

void region::set_ambient(uint8_t a2, uint8_t a3, uint8_t a4) {
    assert(mash_info != nullptr);

    this->mash_info->field_20 = color{a2 / 255.f, a3 / 255.f, a4 / 255.f, 1.0};
}

void region::remove(entity *a3) {
    THISCALL(0x00545700, this, a3);
}

bool region::has_quad_paths() {
    return (this->flags & 0x800) != 0;
}

bool region::is_interior() {
    uint32_t v6 = this->flags;

    return ((v6 & 0x100) != 0) && ((v6 & 0x40000) != 0);
}

traffic_path_graph *region::get_traffic_path_graph() {
    auto *result = g_world_ptr()->the_terrain->traffic_ptr;
    if (result == nullptr) {
        result = this->field_100;
    }

    return result;
}

int region::get_district_id() {
    static constexpr auto REGION_UNINITIALIZED_DISTRICT_ID = 0;

    assert(district_id != REGION_UNINITIALIZED_DISTRICT_ID && "dsg and sin probably out of sync");

    return this->district_id;
}

bool region::is_loaded() {
    return (this->flags & 0x10) != 0;
}

ai_region_paths *region::get_region_path_graph() {
    if (this->is_loaded()) {
        return this->field_104;
    }

    return nullptr;
}

void region::sub_5452D0() {
    if (0) {
#if 0
        auto *v2 = mem_alloc(0x10);

        if (v2) {
            v2->m_first = 0;
            v2->m_last = 0;
            v2->m_end = 0;
        } else {
            v2 = 0;
        }

        auto *v3 = this->mash_info;
        this->meshes = v2;
        //std::vector::reserve(v2, v3->field_30);

        auto *v4 = mem_alloc(0x10);
        this->lights = new (v4) _std::vector<light_source *>{};
        this->field_30 = (_STL::hashtable__ptr_entity *) stru_95F938.m_head->_Prev->_Myval;
        auto *v5 = stru_95F938.m_head->_Prev;
        if (v5 != stru_95F938.m_head) {
            v5->_Prev->_Next = v5->_Next;
            v5->_Next->_Prev = v5->_Prev;
            operator delete(v5);
            --stru_95F938.m_size;
        }

        this->create_proximity_maps();
#endif

    } else {
        THISCALL(0x005452D0, this);
    }
}

bool region::is_inside_or_on(const vector3d &a2) {
    return this->obb->point_inside_or_on(a2);
}

void region::create_proximity_maps() {
    THISCALL(0x00544F60, this);
}

region *region::__nw(uint32_t) {
    if (region::all_regions() == nullptr) {
        region::all_regions() = static_cast<region *>(arch_memalign(4u, sizeof(region) * 256));
    }

    ++region::number_of_allocated_regions();
    return &region::all_regions()[region::number_of_allocated_regions() - 1];
}

mString *region::get_scene_id(bool a2) {
    return (mString *) THISCALL(0x00519E00, this, a2);
}

void region::set_district_variant(int a2) {
    auto *v3 = this->field_78.c_str();
    this->field_C4 = a2;
    mString a1{0, "%s_v%d", v3, a2};

    this->field_88 = a1;
}

fixedstring<8> &region::get_name() {
    return this->mash_info->field_0;
}

void region::un_mash_lego_map(char *a2, int *a3)
{
    TRACE("region::un_mash_lego_map");

    if constexpr (1) {
        this->field_9C = (lego_map_root_node *)a2;
        this->field_9C->un_mash(a2, a3, this);
        auto *mem = lego_bitvector_pool().allocate_new_block();
        this->bitvector_of_legos_rendered_last_frame = new (mem) fixed_bitvector<uint, 2048>{};

        assert(bitvector_of_legos_rendered_last_frame != nullptr);
        auto sub_663403 = [](auto *self) -> void
        {
            for ( auto i = 0u; i < 65u; ++i ) {
                self->field_4[i] = -1;
            }
        };

        sub_663403(this->bitvector_of_legos_rendered_last_frame);
    } else {
        THISCALL(0x0054FEC0, this, a2, a3);
    }
}

void region::add(entity *e)
{
    THISCALL(0x0054FF40, this, e);
}

void region::add(light_source *l)
{
    THISCALL(0x00545780, this, l);
}
