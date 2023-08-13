#include "terrain.h"

#include "actor.h"
#include "ai_region_paths.h"
#include "camera.h"
#include "comic_panels.h"
#include "common.h"
#include "debug_render.h"
#include "district_graph_container.h"
#include "eligible_pack.h"
#include "eligible_pack_category.h"
#include "eligible_pack_token.h"
#include "femanager.h"
#include "filespec.h"
#include "func_wrapper.h"
#include "game.h"
#include "igofrontend.h"
#include "igozoomoutmap.h"
#include "mstring.h"
#include "oldmath_po.h"
#include "oriented_bounding_box_root_node.h"
#include "os_developer_options.h"
#include "parse_generic_mash.h"
#include "proximity_map.h"
#include "region.h"
#include "region_lookup_cache.h"
#include "region_mash_info.h"
#include "resource_key.h"
#include "resource_manager.h"
#include "rstr.h"
#include "scratchpad_stack.h"
#include "simple_region_visitor.h"
#include "stack_allocator.h"
#include "static_region_list_methods.h"
#include "subdivision_node_obb_base.h"
#include "subdivision_visitor.h"
#include "trace.h"
#include "traffic_path_graph.h"
#include "utility.h"
#include "vector3d.h"
#include "wds.h"

VALIDATE_SIZE(terrain, 0x8C);
VALIDATE_OFFSET(terrain, field_18, 0x18);
VALIDATE_OFFSET(terrain, field_24, 0x24);
VALIDATE_OFFSET(terrain, field_5C, 0x5C);

void terrain_packs_modified_callback(_std::vector<resource_key> &a1)
{
    CDECL_CALL(0x00559870, &a1);
}

terrain::terrain(const mString &a2)
{
    TRACE("terrain::terrain");

    if constexpr (1)
    {
        this->field_24.eligible_packs = {};
        this->field_24.field_14 = {};
        this->field_24.field_28 = {};

        this->field_24.field_0 = {};
        this->field_24.get_ideal_pack_info_callback = nullptr;

        this->field_5C = {};

        this->field_68 = 0;

        this->field_70 = {};

        this->field_80 = {};

        this->regions = nullptr;
        this->region_map = nullptr;
        this->total_regions = 0;
        this->strips = nullptr;
        this->total_strips = 0;
        this->region_proximity_map_allocator = nullptr;

        this->field_5C.field_8 = true;

        this->traffic_ptr = nullptr;
        this->field_68 = 0;

        filespec v30{a2};
        v30.m_ext = {".dsg"};

        mString v29 = v30.sub_55DBF0();

        resource_key a1 = create_resource_key_from_path(v29.c_str(), RESOURCE_KEY_TYPE_DISTRICT_GRAPH);
        auto *res = resource_manager::get_resource(a1, nullptr, nullptr);
        if (res == nullptr)
        {
            auto *v3 = a1.m_hash.to_string();
            sp_log("Couldn't get terrain resource %s", v3);
            assert(0);
        }

        {
            district_graph_container *dsg;

            auto allocated_mem =
#if 1 
                parse_generic_object_mash(dsg, res,
                    nullptr, nullptr, nullptr, 0u, 0u, nullptr);
#else
                CDECL_CALL(0x, dsg, res, nullptr, nullptr, nullptr, 0, 0, nullptr);
#endif
            assert(!allocated_mem);
            assert(dsg != nullptr && "we have no dsg!!!");

            dsg->setup_terrain(this);
        }

        for (int idx = 0; idx < this->total_regions; ++idx)
        {
            auto *v20 = this->get_region(idx);
            int v19 = 1;
            while ( 1 )
            {
                auto v9 = v19;
                auto *v4 = v20->get_scene_id(false);
                auto *v5 = v4->c_str();
                mString a1a {{0}, "%s_v%d", v5, v9};
                auto *v6 = a1a.c_str();
                auto v12 = create_resource_key_from_path(v6, RESOURCE_KEY_TYPE_PACK);
                auto v15 = !resource_manager::get_pack_file_stats(v12, nullptr, nullptr, nullptr);
                if ( v15 )
                    break;

                ++v19;
            }

            v20->field_C8 = v19;
        }

        resource_manager::add_resource_pack_modified_callback(terrain_packs_modified_callback);

        this->field_18 = vector3d {3.4028235e38, 3.4028235e38, 3.4028235e38};

    }
    else
    {
        THISCALL(0x00559920, this, a2);
    }

    
}

terrain::~terrain() {
    THISCALL(0x0054E990, this);
}

void terrain::update_region_pack_info()
{
    TRACE("terrain::update_region_pack_info");

    for ( auto i = 0; i < this->get_num_regions(); ++i )
    {
        auto *v12 = this->regions[i];
        auto &v2 = v12->get_name();
        auto *v3 = v2.to_string();
        string_hash v6 {v3};
        resource_key v11 {v6, RESOURCE_KEY_TYPE_PACK};
        auto v5 = resource_manager::get_pack_file_stats(v11, nullptr, nullptr, nullptr);

        auto func = [](region *self, bool a2) -> void
        {
            uint32_t v2;
            if ( a2 )
                v2 = self->flags | 0x4000;
            else
                v2 = self->flags & 0xFFFFBFFF;
        
            self->flags = v2;
        };

        func(v12, v5);
    }
}

bool terrain::district_load_callback(resource_pack_slot::callback_enum a1,
                                     resource_pack_streamer *a2,
                                     resource_pack_slot *a3,
                                     limited_timer *a4) {
    return (bool) CDECL_CALL(0x0055C350, a1, a2, a3, a4);
}

void terrain::unload_district_immediate(int a2)
{
    auto *district_partition = resource_manager::get_partition_pointer(6);
    assert(district_partition != nullptr);

    auto *district_streamer = district_partition->get_streamer();
    assert(district_streamer != nullptr);

    auto *strip_partition = resource_manager::get_partition_pointer(5);
    assert(strip_partition != nullptr);

    auto *strip_streamer = strip_partition->get_streamer();
    assert(strip_streamer != nullptr);

    do
    {
        do
        {
            district_streamer->flush(game::render_empty_list);
            strip_streamer->flush(game::render_empty_list);
        }
        while ( !district_streamer->is_idle() );
    }
    while ( !strip_streamer->is_idle() );

    auto *district_slots = district_streamer->get_pack_slots();
    assert(district_slots != nullptr);

    for ( auto a1 = 0u; a1 < district_slots->size(); ++a1 )
    {
        auto *district_slot = (*district_slots)[a1];
        assert(district_slot != nullptr);

        if ( district_slot->is_pack_ready() )
        {
            auto &v4 = district_slot->get_name_key();
            auto v5 = v4.m_hash;
            auto *the_eligible_pack_ptr = this->field_24.find_eligible_pack_by_packfile_name_hash(v5);
            auto *v11 = the_eligible_pack_ptr;
            assert(the_eligible_pack_ptr != nullptr);

            auto &v10 = v11->field_48;
            auto *reg = this->get_region(v10.field_4);
            assert(reg != nullptr);
            
            if ( reg->district_id == a2 )
            {
                district_streamer->unload(a1);
                district_streamer->flush(game::render_empty_list);
                this->force_streamer_refresh();
                return;
            }
        }
    }
}

int terrain::find_innermost_region(const vector3d &a1) {
    return THISCALL(0x00534890, this, &a1);
}

region *terrain::find_region(const vector3d &a2, const region *a3)
{
    TRACE("terrain::find_region");

    region *result;

    if constexpr (1) {
        if (a3 != nullptr && a3->obb->point_inside_or_on(a2)) {
            return (region *) a3;
        }

        assert(this->region_map != nullptr);

        simple_region_visitor visitor{a2, false};

        ++region::visit_key2();
        static_region_list_methods::init();
        this->region_map->traverse_point(a2, visitor);
        static_region_list_methods::term();

        assert(visitor.region_count <= 1);

        result = static_cast<region *>(visitor.region_count != 0 ? visitor.field_14[0] : nullptr);
    } else {
        result = (region *) THISCALL(0x0052DFF0, this, &a2, a3);
    }

    return result;
}

int terrain::get_region_index_by_name(const fixedstring<4> &a2)
{
    TRACE("terrain::get_region_index_by_name", a2.to_string());
    return THISCALL(0x0054F670, this, &a2);
}

region *terrain::get_region(int idx) {
    assert(idx >= 0);
    assert(idx < total_regions);

    return this->regions[idx];
}

int terrain::unlock_district(int a2) {
    return THISCALL(0x005148A0, this, a2);
}

int terrain::add_strip(const mString &a2) {
    auto result = find_strip(a2);
    if (result != -1) {
        return result;
    }

    rstrcpy(&this->strips[40 * this->total_strips], a2.c_str(), 33);

    return this->total_strips++;
}

int terrain::find_strip(const mString &a2) {
    for (int i = 0; i < this->total_strips; ++i) {
        if (_strcmpi(&this->strips[i * 40], a2.c_str()) == 0) {
            return i;
        }
    }

    return -1;
}

bool terrain::district_construct_callback(resource_pack_slot::callback_enum reason,
                                          resource_pack_streamer *a2,
                                          resource_pack_slot *which_pack_slot,
                                          limited_timer *a4) {
    assert(which_pack_slot != nullptr);
    assert(reason == resource_pack_slot::CALLBACK_CONSTRUCT);

    return (bool) CDECL_CALL(0x0055BFA0, reason, a2, which_pack_slot, a4);
}

bool terrain::district_destruct_callback(resource_pack_slot::callback_enum reason,
                                         resource_pack_streamer *a2,
                                         resource_pack_slot *which_pack_slot,
                                         limited_timer *a4) {
    if constexpr (0) {
        auto *ter = g_world_ptr()->get_the_terrain();

        assert(ter != nullptr);

        assert(reason == resource_pack_slot::CALLBACK_DESTRUCT);

        assert(which_pack_slot != nullptr);

        return false;

    } else {
        return (bool) CDECL_CALL(0x00552A20, reason, a2, which_pack_slot, a4);
    }
}

void terrain::register_region_change_callback(void (*a3)(bool, region *)) {
    if constexpr (1) {
        auto *v2 = region_change_callbacks();
        if (region_change_callbacks() == nullptr) {
            region_change_callbacks() = new _std::list<void (*)(bool, region *)>{};
        }

        assert(region_change_callbacks() != nullptr);

        auto *v4 = v2->m_head;
        auto *v5 = v2;

        thiscall_call _Buynode = CAST(_Buynode, 0x006B78D0);

        auto *v6 = (decltype(v4)) _Buynode(v2, v4, v4->_Prev, &a3);

        thiscall_call sub_566E00 = CAST(sub_566E00, 0x00566E00);
        sub_566E00(v5, 1u);
        v4->_Prev = v6;
        v6->_Prev->_Next = v6;

    } else {
        THISCALL(0x0053FC90, this, a3);
    }
}

void terrain::show_obbs() {
    if constexpr (0) {
        sp_log("show_obbs");

        if (1) //(j_debug_render_get_ival((debug_render_items_e) 21) || SHOW_OBBS || SHOW_DISTRICTS)
        {
            color32 v15[9] = {
                color32{255, 255, 255, 255},
                color32{127, 127, 127, 255},
                color32{255, 0, 0, 255},
                color32{0, 255, 0, 255},
                color32{0, 0, 255, 255},
                color32{0, 255, 255, 255},
                color32{255, 0, 255, 255},
                color32{255, 127, 0, 255},
                color32{127, 0, 127, 255}
            };

            int v14 = 0;
            std::for_each(this->regions, this->regions + this->total_regions,
            [&v14, &v15](auto *reg)
            {
                if ((debug_render_get_ival(OBBS) >= 2 || os_developer_options::instance()->get_flag(mString{"SHOW_OBBS"})) &&
                    reg->field_98 != nullptr) {
                    if (v14 >= 9) {
                        v14 = 0;
                    }

                    reg->field_98->set_color(v15[v14]);
                } else if (debug_render_get_ival(OBBS) == 1) {
                    auto *v2 = g_world_ptr()->get_hero_ptr(0);

                    auto *v3 = v2->get_primary_region();
                    if (reg == v3) {
                        if (reg->field_98 != nullptr) {
                            auto v4 = color32{255, 0, 0, 255};
                            reg->field_98->set_color(v4);
                        }
                    }
                }

#if 0
                auto sub_A15D90 = [](region *self) -> subdivision_node_obb_base * {
                    

                    if (self->field_98 != nullptr) {
                        return sub_6A0867(self->field_98);
                    }

                    return nullptr;
                };

                if (debug_render_get_ival(debug_render_items_e{21}) == 3 && sub_A15D90(v12)) {
                    auto v7 = color32{255, 255, 0, 255};
                    auto *v5 = sub_A15D90(v12);
                    sub_67923A(v5, v7, 1, 0.079999998);
                }

                if (SHOW_DISTRICTS) {
                    if (v12->obb != nullptr) {
                        auto v6 = color32{255, 255, 0, 255};
                        sub_67923A(v12->obb, v6, 0, 0.079999998);
                    }
                }
#endif

                ++v14;
            });
        }
    } else {
        ;
    }
}

void terrain::find_ideal_terrain_packs(_std::vector<ideal_pack_info> *a2) {
    THISCALL(0x00552C50, this, a2);
}

void terrain::find_ideal_terrain_packs_internal(const vector3d &a2,
                                                region *a3,
                                                _std::vector<region *> *a4,
                                                _std::vector<ideal_pack_info> *a5) {
    THISCALL(0x0054EC50, this, &a2, a3, a4, a5);
}

//FIXME
void terrain::start_streaming(void (*callback)(void))
{
    TRACE("terrain::start_streaming");

    if constexpr (0)
    {
        load_complete_callback() = callback;
        auto *district_partition = resource_manager::get_partition_pointer(RESOURCE_PARTITION_DISTRICT);
        assert(district_partition != nullptr);

        auto *district_streamer = district_partition->get_streamer();
        assert(district_streamer != nullptr);

        district_streamer->set_active(true);

        auto *strip_partition = resource_manager::get_partition_pointer(RESOURCE_PARTITION_STRIP);
        assert(strip_partition != nullptr);

        auto *strip_streamer = strip_partition->get_streamer();
        assert(strip_streamer != nullptr);

        strip_streamer->set_active(true);

        int v8 = 0;

        for (auto i = 0; i < this->total_regions; ++i) {
            auto &reg = this->regions[i];

            if (reg != nullptr) {
                if (reg->mash_info != nullptr) {
                    v8 += reg->get_multiblock_number();
                }
            }
        }

        resource_pack_streamer *streamers[2];
        streamers[0] = strip_streamer;
        streamers[1] = district_streamer;

        bool (*callbacks[2])(resource_pack_slot::callback_enum,
                             resource_pack_streamer *,
                             resource_pack_slot *,
                             limited_timer *);
        callbacks[0] = nullptr;
        callbacks[1] = terrain::district_load_callback;

        this->field_24.init(v8 + this->total_strips,
                            2,
                            streamers,
                            callbacks,
                            find_ideal_terrain_packs_callback);

        this->field_24.field_0 = true;

        for (int i = 0; i < this->total_strips; ++i) {
            auto *v23 = (char *) &this->strips[40 * i];

            string_hash hash{v23};

            resource_key v24;
            v24.set(hash, RESOURCE_KEY_TYPE_PACK);

            if (resource_manager::get_pack_file_stats(v24, nullptr, nullptr, nullptr)) {
                eligible_pack_token a4{1, i};

                this->field_24.add_eligible_pack(v23, a4, strip_streamer);
            }
        }

        for (int reg_idx = 0; reg_idx < this->total_regions; ++reg_idx) {
            auto *reg = this->regions[reg_idx];
            if (reg != nullptr) {
                auto *mash_info = reg->mash_info;
                if (mash_info != nullptr) {
                    auto *str = mash_info->field_0.to_string();

                    eligible_pack_token pack_token{2, reg_idx};

                    auto *new_pack = this->field_24.add_eligible_pack(str,
                                                                      pack_token,
                                                                      district_streamer);

                    _std::vector<eligible_pack *> eps{};

                    thiscall_call _Insert_n = CAST(_Insert_n, 0x0056A260);

                    _Insert_n(&eps, nullptr, 1, &new_pack);

                    for (auto j = 1; j < this->regions[reg_idx]->get_multiblock_number(); ++j)
                    {
                        mString a1{0,
                                   "%s_m%d",
                                   this->regions[reg_idx]->mash_info->field_0.to_string(),
                                   j};

                        auto *v18 = this->field_24.add_eligible_pack(a1.c_str(),
                                                                     eligible_pack_token{2, reg_idx},
                                                                     district_streamer);

                        if (eps.size() < eps.capacity()) {
                            auto *v19 = eps.m_last;
                            *eps.m_last = v18;
                            eps.m_last = v19 + 1;
                        } else {
                            _Insert_n(&eps, eps.m_last, 1, &v18);
                        }
                    }

                    assert(eps.size() == regions[reg_idx]->get_multiblock_number());

                    thiscall_call copy = CAST(copy, 0x0056C880);

                    copy(&this->regions[reg_idx]->field_108, &eps);
                }
            }
        }

        this->field_24.fixup_eligible_pack_parent_child_relationships();

        this->force_streamer_refresh();

    }
    else {
        THISCALL(0x0055C3F0, this, callback);
    }
}

void terrain::set_district_variant(int a2, int a3, bool a4) {
    THISCALL(0x00557480, this, a2, a3, a4);
}

region *terrain::find_outermost_region(const vector3d &a2) {
    assert(region_map != nullptr);

    if constexpr (1) {
        simple_region_visitor a3{a2, true};

        ++region::visit_key2();
        static_region_list_methods::init();
        this->region_map->traverse_point(a2, a3);

        scratchpad_stack::pop(static_region_list_methods::scratchpad(), 64);
        static_region_list_methods::scratchpad() = nullptr;

        if (a3.region_count == 0) {
            return nullptr;
        }

        if (a3.region_count == 1) {
            return static_cast<region *>(a3.field_14[0]);
        }

        for (int i = 0; i < a3.region_count; ++i) {
            auto *reg = static_cast<region *>(a3.field_14[i]);
            if (reg != nullptr && !reg->is_interior()) {
                return reg;
            }
        }

        return static_cast<region *>(a3.field_14[0]);

    } else {
        return (region *) THISCALL(0x00523EC0, this, &a2);
    }
}

void terrain::un_mash_audio_boxes(char *a1, int *a2, region *a3) {
    a3->field_E0.un_mash(a1, a2, a3);
}

void terrain::un_mash_region_paths(char *a1, int *a2, region *a3) {
    a3->field_104->un_mash(a1, a2, a3);
}

bool terrain::un_mash_traffic_paths(char *a2, int *a3, region *reg, traffic_path_brew &a5) {
    bool v6 = !((traffic_path_graph *) a2)->un_mash(a2, a3, reg, a5);
    if (reg != nullptr) {
        if (v6) {
            assert(0 && "There is traffic data attached to a district");

            reg->field_100 = (traffic_path_graph *) a2;
        } else {
            reg->field_100 = nullptr;
        }

    } else {
        assert(traffic_ptr == nullptr);

        if (v6) {
            this->traffic_ptr = (traffic_path_graph *) a2;
        } else {
            this->traffic_ptr = nullptr;
        }
    }
    return !v6;
}

void terrain::force_streamer_refresh() {
    auto &v21 = this->field_18;
    v21[0] = 3.4028235e38;
    v21[1] = 3.4028235e38;
    v21[2] = 3.4028235e38;
}

void terrain::sub_557130() {
    auto &v1 = resource_manager::partitions()->m_first;
    auto *district_streamer = &v1[6]->streamer;
    auto *strip_streamer = &v1[5]->streamer;
    auto *v4 = &this->field_24;
    do {
        district_streamer->flush(game::render_empty_list, 0.02);
        strip_streamer->flush(game::render_empty_list, 0.02);
        v4->prioritize();
        if (v4->field_0) {
            for (auto i = v4->field_14.m_first; i != v4->field_14.m_last; ++i) {
                (*i)->frame_advance(0.0);
            }
        }

    } while (!v4->sub_537F80());

    v4->clear();
}

region *terrain::get_district(int a1) {
    return region_lookup_cache::lookup_by_district_id(a1);
}

void terrain::find_regions(const vector3d &a2, _std::vector<region *> *regions) {
    assert(regions != nullptr);

    assert(region_map != nullptr);

    if constexpr (0) {
    } else {
        THISCALL(0x005444F0, this, &a2, regions);
    }
}

_std::vector<region *> *terrain::sub_6DC8A0(vector3d a2) {
    if (terrain::regions_for_point() != nullptr) {
        auto v3 = &terrain::regions_for_point()->m_first;
        auto v4 = terrain::regions_for_point();
        auto v5 = terrain::regions_for_point()->m_first;
        if (v5) {
            operator delete(v5);
        }

        *v3 = nullptr;
        v4->m_last = nullptr;
        v4->m_end = nullptr;
    } else {
        terrain::regions_for_point() = new _std::vector<region *>{};
    }

    for (int i = 0; i < this->total_regions; ++i) {
        auto *v15 = this->regions[i];
        auto *v8 = v15;
        if (v15->is_inside_or_on(a2)) {
            auto v9 = terrain::regions_for_point()->m_first;
            auto size = terrain::regions_for_point()->size();

            if (v9 && size < terrain::regions_for_point()->m_end - v9) {
                auto v11 = &terrain::regions_for_point()->m_last;
                auto v12 = terrain::regions_for_point()->m_last;
                *v12 = v8;
                *v11 = v12 + 1;
            } else {
                THISCALL(0x0048E660,
                         terrain::regions_for_point(),
                         terrain::regions_for_point()->end(),
                         1,
                         &v15);
            }
        }
    }

    return terrain::regions_for_point();
}

void terrain::unlock_district_pack_slot(int slot_idx) {
    if constexpr (1) {
        auto *district_partition = resource_manager::get_partition_pointer(6);
        assert(district_partition != nullptr);

        auto &pack_slots = district_partition->get_pack_slots();
        assert(slot_idx >= 0 && slot_idx < pack_slots.size());

        assert(pack_slots[slot_idx]->is_empty() || pack_slots[slot_idx]->is_pack_unloading());

        auto &slot = pack_slots.at(slot_idx);

        auto *v2 = &this->field_24;
        auto *v3 = this->field_24.field_14.m_first;
        if (v3 != this->field_24.field_14.m_last) {
            auto &v4 = slot;
            do {
                auto *v5 = *v3;
                if ((*v3)->my_resource_pack_streamer == &v4->field_88->streamer) {
                    slot = v4;

                    thiscall_call sub_5058F0 = CAST(sub_5058F0, 0x005058F0);
                    sub_5058F0(&v5->field_1C, &slot);
                }

                ++v3;
            } while (v3 != v2->field_14.m_last);
        }

    } else {
        THISCALL(0x0053FFA0, this, slot_idx);
    }
}

void terrain::frame_advance(Float a2) {
    if constexpr (1) {
        entity *ent;

        IGOZoomOutMap *v3;

        if (!os_developer_options::instance()->get_flag(13) ||
            (v3 = g_femanager().IGO->field_44, v3->field_5C4) || v3->field_5C3) {
            ent = g_world_ptr()->get_hero_ptr(0);
        } else {
            auto *game_ptr = g_game_ptr();
            auto *v5 = comic_panels::get_current_view_camera(0);

            if (v5 != nullptr) {
                ent = (actor *) v5;
            } else {
                auto *wds = game_ptr->the_world;
                ent = game_ptr->field_5C;

                if (ent == wds->field_234[0]) {
                    ent = wds->field_234[0];
                }
            }
        }

        const vector3d pos = ent->get_abs_position();

        auto vec1 = pos - this->field_18;

        if (auto len2 = vec1.length2(); len2 > STREAMING_BUBBLE_RADIUS2) {
            this->field_24.prioritize();
            this->field_18 = pos;
        }

        this->field_24.frame_advance(a2);
    } else {
        THISCALL(0x00556FF0, this, a2);
    }
}

void find_ideal_terrain_packs_callback(_std::vector<ideal_pack_info> *a1) {
    auto *ter = g_world_ptr()->get_the_terrain();

    ter->find_ideal_terrain_packs(a1);
}

void terrain_patch()
{
    {
        FUNC_ADDRESS(address, &terrain::start_streaming);
        REDIRECT(0x0055D1BF, address);
    }
    return;

    {
        FUNC_ADDRESS(address, &terrain::update_region_pack_info);
        REDIRECT(0x00559893, address);
    }

    {
        FUNC_ADDRESS(address, &terrain::get_region_index_by_name);
        REDIRECT(0x0055CE58, address);
    }

    {
        FUNC_ADDRESS(address, &terrain::find_region);
        REDIRECT(0x0055CF7F, address);
    }

    {
        FUNC_ADDRESS(address, &terrain::frame_advance);
        REDIRECT(0x005582AA, address);
    }

}
