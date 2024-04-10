#include "terrain.h"

#include "actor.h"
#include "ai_region_paths.h"
#include "camera.h"
#include "comic_panels.h"
#include "common.h"
#include "debug_render.h"
#include "district_graph_container.h"
#include "dynamic_rtree.h"
#include "eligible_pack.h"
#include "eligible_pack_category.h"
#include "eligible_pack_token.h"
#include "femanager.h"
#include "filespec.h"
#include "func_wrapper.h"
#include "game.h"
#include "igofrontend.h"
#include "igozoomoutmap.h"
#include "memory.h"
#include "mstring.h"
#include "oldmath_po.h"
#include "oriented_bounding_box_root_node.h"
#include "os_developer_options.h"
#include "parse_generic_mash.h"
#include "proximity_map.h"
#include "proximity_map_construction.h"
#include "region.h"
#include "region_lookup_cache.h"
#include "region_mash_info.h"
#include "resource_key.h"
#include "resource_manager.h"
#include "rstr.h"
#include "scratchpad_stack.h"
#include "simple_region_visitor.h"
#include "stack_allocator.h"
#include "subdivision_static_region_list.h"
#include "subdivision_node_obb_base.h"
#include "subdivision_visitor.h"
#include "texture_to_frame_map.h"
#include "trace.h"
#include "traffic_path_graph.h"
#include "utility.h"
#include "vector3d.h"
#include "wds.h"

VALIDATE_SIZE(terrain, 0x8C);
VALIDATE_SIZE((*terrain::strips), 0x28);
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
                parse_generic_object_mash(dsg, res,
                    nullptr, nullptr, nullptr, 0u, 0u, nullptr);
            assert(!allocated_mem);
            assert(dsg != nullptr && "we have no dsg!!!");

            dsg->setup_terrain(this);
        }

        for (int idx = 0; idx < this->total_regions; ++idx)
        {
            auto *reg = this->get_region(idx);
            int v19 = 1;
            while ( 1 )
            {
                auto &v4 = reg->get_scene_id(false);
                mString a1a {{0}, "%s_v%d", v4.c_str(), v19};
                auto v12 = create_resource_key_from_path(a1a.c_str(), RESOURCE_KEY_TYPE_PACK);
                auto v15 = !resource_manager::get_pack_file_stats(v12, nullptr, nullptr, nullptr);
                if ( v15 ) {
                    break;
				}

                ++v19;
            }

            reg->field_C8 = v19;
        }

        resource_manager::add_resource_pack_modified_callback(terrain_packs_modified_callback);

        this->field_18 = vector3d {3.4028235e38, 3.4028235e38, 3.4028235e38};

    }
    else
    {
        THISCALL(0x00559920, this, a2);
    }
}

terrain::~terrain()
{
    if constexpr (1)
    {
        if ( this->traffic_ptr != nullptr )
        {
            this->traffic_ptr->release_mem();
            this->traffic_ptr = nullptr;
        }

        collision_dynamic_rtree().term();
        this->region_map->initialized = false;

        this->region_proximity_map_allocator->free();
        operator delete(this->region_proximity_map_allocator);

        region_lookup_cache::term();

        if ( this->regions != nullptr )
        {
            for ( int i = this->total_regions - 1; i >= 0; --i )
            {
                auto *v7 = this->regions[i];
                if ( v7 != nullptr )
                {
                    v7->~region();
                    --region::number_of_allocated_regions();
                }
            }
            operator delete[](this->regions);
            this->regions = nullptr;
        }

        if ( this->strips != nullptr )
        {
            operator delete[](this->strips);
            this->strips = nullptr;
        }

        if ( terrain::regions_for_point() != nullptr )
        {
            for ( auto j = 0; j < this->total_regions; ++j ) {
                regions_for_point()->clear();
            }

            if (regions_for_point() != nullptr) {
                delete regions_for_point();
            }

            terrain::regions_for_point() = nullptr;
        }

        if ( terrain::region_change_callbacks() != nullptr ) {
            delete terrain::region_change_callbacks();
        }

    } else {
        THISCALL(0x0054E990, this);
    }
}

void terrain::init_region_proximity_map()
{
    TRACE("terrain::init_region_proximity_map");

    if ( this->region_map == nullptr )
    {
        if ( this->region_proximity_map_allocator == nullptr )
        {
            this->region_proximity_map_allocator = static_cast<stack_allocator *>(mem_alloc(sizeof(stack_allocator)));

            assert(region_proximity_map_allocator);
            auto status = this->region_proximity_map_allocator->allocate(0x4000, 4, 16);

            assert("Failed to allocate the memory for region lookup proximity map stack."
                    && status);
        }

        _std::vector<proximity_map_construction_leaf> v16;
        vector3d a4 {3.4028235e38, 3.4028235e38, 3.4028235e38};
        vector3d a5 {-3.4028235e38, -3.4028235e38, -3.4028235e38};
        for ( int i = 0; i < this->get_num_regions(); ++i )
        {
            auto *reg = this->get_region(i);

            vector3d a3{};
            vector3d a2{};
            auto *v2 = reg->obb;
            v2->get_extents(&a3, &a2);

            a4 = vector3d::min(a4, a3);
            a5 = vector3d::max(a5, a2);

            proximity_map_construction_leaf v9 {reg, a3, a2};
            v16.push_back(v9);
        }

        static_region_list_builder v8;
        this->region_map = create_static_proximity_map_on_the_stack(*this->region_proximity_map_allocator, v16, v8, a4, a5, 16);
    }
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
            if ( a2 ) {
                v2 = self->flags | 0x4000;
            } else {
                v2 = self->flags & 0xFFFFBFFF;
			}
        
            self->flags = v2;
        };

        func(v12, v5);
    }
}

bool terrain::district_load_callback(resource_pack_slot::callback_enum reason,
                                     resource_pack_streamer *streamer,
                                     resource_pack_slot *slot,
                                     limited_timer *a4)
{
	TRACE("terrain::district_load_callback");

	if constexpr (1) {

		bool result = false;
		switch ( reason )
		{
		case resource_pack_slot::CALLBACK_LOAD_STARTED:
			result = terrain::district_load_started_callback(reason, streamer, slot);
			break;
		case resource_pack_slot::CALLBACK_CONSTRUCT:
			result = terrain::district_construct_callback(reason, streamer, slot, a4);
			break;
		case resource_pack_slot::CALLBACK_PRE_DESTRUCT:
			result = terrain::district_pre_destruct_callback(reason, streamer, slot);
			break;
		case resource_pack_slot::CALLBACK_DESTRUCT:
			result = terrain::district_destruct_callback(reason, streamer, slot, a4);
			break;
		default:
			result = false;
			break;
		}

		return result;
	} else {
		return (bool) CDECL_CALL(0x0055C350, reason, streamer, slot, a4);
	}
}

void terrain::unload_district_immediate(int a2)
{
    auto *district_partition = resource_manager::get_partition_pointer(RESOURCE_PARTITION_DISTRICT);
    assert(district_partition != nullptr);

    auto *district_streamer = district_partition->get_streamer();
    assert(district_streamer != nullptr);

    auto *strip_partition = resource_manager::get_partition_pointer(RESOURCE_PARTITION_STRIP);
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

region *terrain::get_region(int idx)
{
	TRACE("terrain::get_region");

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

    rstrcpy(this->strips[this->total_strips].field_0, a2.c_str(), 33);

    return this->total_strips++;
}

int terrain::find_strip(const mString &a2) {
    for (int i = 0; i < this->total_strips; ++i) {
        if (_strcmpi(this->strips[i].field_0, a2.c_str()) == 0) {
            return i;
        }
    }

    return -1;
}

bool terrain::district_pre_destruct_callback(
		resource_pack_slot::callback_enum reason,
        resource_pack_streamer *,
        resource_pack_slot *which_pack_slot)
{
	assert(reason == resource_pack_slot::CALLBACK_PRE_DESTRUCT);

	auto *ter = g_world_ptr()->get_the_terrain();
	assert(ter != nullptr);

	assert(which_pack_slot != nullptr);

	auto &v3 = which_pack_slot->get_pack_token();
	auto *epack = ter->field_24.find_eligible_pack_by_token(v3);
	assert(epack != nullptr);

	auto &v4 = epack->get_token();
	auto *reg = ter->get_region(v4.field_4);
	reg->unload_progress.clear();
	return false;
}

bool terrain::district_construct_callback(resource_pack_slot::callback_enum reason,
                                          resource_pack_streamer *a2,
                                          resource_pack_slot *which_pack_slot,
                                          limited_timer *a4) {
    assert(which_pack_slot != nullptr);
    assert(reason == resource_pack_slot::CALLBACK_CONSTRUCT);

    return (bool) CDECL_CALL(0x0055BFA0, reason, a2, which_pack_slot, a4);
}

bool terrain::district_load_started_callback(resource_pack_slot::callback_enum ,
											 resource_pack_streamer *,
											 resource_pack_slot *a3)
{
	auto &v6 = a3->get_pack_token();
	auto *the_terrain = g_world_ptr()->get_the_terrain();
	auto *eligible_pack = the_terrain->field_24.find_eligible_pack_by_token(v6);
	auto v7 = eligible_pack->get_token().field_4;
	auto *reg = the_terrain->get_region(v7);
	[](auto &v4)
	{
		v4.field_0.clear();
	  	v4.field_4.clear();
	  	v4.field_C.clear();
	  	v4.field_10.clear();
	  	v4.field_14.clear();
	}(reg->field_118);
	return false;
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
    TRACE("terrain::register_region_change_callback");

    if constexpr (0) {
        auto *v2 = region_change_callbacks();
        if (region_change_callbacks() == nullptr) {
            region_change_callbacks() = new _std::list<void (*)(bool, region *)>{};
        }

        assert(region_change_callbacks() != nullptr);

        auto *v4 = v2->m_head;
        auto *v5 = v2;

        decltype(v4) (__fastcall *_Buynode)(void *, void *, decltype(v4), decltype(v4), void (**) (bool, region*) ) = CAST(_Buynode, 0x006B78D0);

        auto *v6 = _Buynode(v2, nullptr, v4, v4->_Prev, &a3);

        void (__fastcall *sub_566E00)(void *, void *, uint32_t) = CAST(sub_566E00, 0x00566E00);
        sub_566E00(v5, nullptr, 1u);
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

        for (auto i = 0; i < this->total_regions; ++i)
		{
            auto &reg = this->regions[i];
            if (reg != nullptr)
			{
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
            auto &strip = this->strips[i];

            string_hash hash{strip.field_0};

            resource_key v24 {hash, RESOURCE_KEY_TYPE_PACK};

            if (resource_manager::get_pack_file_stats(v24, nullptr, nullptr, nullptr))
			{
                eligible_pack_token a4{1, i};
                this->field_24.add_eligible_pack(strip.field_0, a4, strip_streamer);
            }
        }

        for (int reg_idx = 0; reg_idx < this->total_regions; ++reg_idx)
		{
            auto *reg = this->regions[reg_idx];
            if (reg != nullptr)
			{
                auto *mash_info = reg->mash_info;
                if (mash_info != nullptr)
				{
                    auto *str = mash_info->field_0.to_string();

                    eligible_pack_token pack_token{2, reg_idx};

                    auto *new_pack = this->field_24.add_eligible_pack(str,
                                                                      pack_token,
                                                                      district_streamer);

                    _std::vector<eligible_pack *> eps{};

                    void (__fastcall *_Insert_n)(void *, void *, void *, int, void *) = CAST(_Insert_n, 0x0056A260);

                    _Insert_n(&eps, nullptr, nullptr, 1, &new_pack);

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
                            _Insert_n(&eps, nullptr, eps.m_last, 1, &v18);
                        }
                    }

                    assert(eps.size() == regions[reg_idx]->get_multiblock_number());

                    void (__fastcall *copy)(void *, void *, void *) = CAST(copy, 0x0056C880);

                    copy(&this->regions[reg_idx]->field_108, nullptr, &eps);
                }
            }
        }

        this->field_24.fixup_eligible_pack_parent_child_relationships();

        this->force_streamer_refresh();

    }
    else
	{
        THISCALL(0x0055C3F0, this, callback);
    }
}

void terrain::set_district_variant(int district_id, int variant, bool a4)
{
	if constexpr (0) {
		assert(variant >= 0);

		auto *v5 = this->get_district(district_id);
		if ( v5 != nullptr )
		{
			auto *v7 = v5->get_scene_id(false).c_str();
			string_hash v23 {v7};

			auto *epack = this->field_24.find_eligible_pack_by_name(v23);
			if ( epack != nullptr )
			{
				for ( auto &v14 : this->field_70 )
				{
					if ( v14.field_0 == epack )
					{
						v14.field_8 = variant;
						return;
					}
				}

				auto &token = epack->get_token();
				auto *reg = this->get_region(token.field_4);
				if ( reg->get_district_variant() != variant )
				{
					auto *slot = this->field_24.get_eligible_pack_slot(epack);
					if ( slot != nullptr )
					{
						pack_switch_info_t v26 {epack, slot, variant};
						if constexpr (1) {
							this->field_70.push_back(v26);
						} else {
							THISCALL(0x005700A0, &this->field_70, v26);
						}
						if ( a4 )
						{
							reg->flags |= 0x20000u;
							this->unload_district_immediate(reg->get_district_id());
						}
					}
					else
					{
						reg->set_district_variant(variant);
						auto &v22 = reg->get_scene_id(true);
						epack->set_packfile_name(v22.c_str());
					}
				}
			}
		}

	} else {
		THISCALL(0x00557480, this, district_id, variant, a4);
	}
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

void terrain::un_mash_region_paths(char *a1, int *a2, region *reg) {
    reg->field_104 = CAST(reg->field_104, a1);
    reg->field_104->un_mash(a1, a2, reg);
}

bool terrain::un_mash_traffic_paths(char *a2, int *a3, region *reg, traffic_path_brew &a5) {
    TRACE("terrain::un_mash_traffic_paths");

    if constexpr (1) {
        bool v6 = !(bit_cast<traffic_path_graph *>(a2)->un_mash(a2, a3, reg, a5));
        if (reg != nullptr) {
            if (v6) {
                assert(0 && "There is traffic data attached to a district");

                reg->field_100 = bit_cast<traffic_path_graph *>(a2);
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
    } else {
        auto result = THISCALL(0x00514410, this, a2, a3, reg, &a5);
        return result;
    }
}

void terrain::force_streamer_refresh() {
    auto &v21 = this->field_18;
    v21[0] = 3.4028235e38;
    v21[1] = 3.4028235e38;
    v21[2] = 3.4028235e38;
}

void terrain::sub_557130()
{
    auto *district_partition = resource_manager::get_partition_pointer(RESOURCE_PARTITION_DISTRICT);
    assert(district_partition != nullptr);

    auto *district_streamer = district_partition->get_streamer();
    assert(district_streamer != nullptr);

    auto *strip_partition = resource_manager::get_partition_pointer(RESOURCE_PARTITION_STRIP);
    assert(strip_partition != nullptr);

    auto *strip_streamer = strip_partition->get_streamer();
    assert(strip_streamer != nullptr);

    do {
        district_streamer->flush(game::render_empty_list, 0.02);
        strip_streamer->flush(game::render_empty_list, 0.02);
        this->field_24.prioritize();
        this->field_24.frame_advance(0.0f);

    } while (!this->field_24.is_idle());

    this->field_24.clear();
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

region *terrain::find_region(string_hash a2) {
    TRACE("terrain::find_region", a2.to_string());

    if constexpr (0) {
    } else {
        return (region *) THISCALL(0x00534920, this, a2);
    }
}

_std::vector<region *> *terrain::get_region_info_for_point(vector3d a2)
{
    if (regions_for_point() != nullptr) {
        regions_for_point()->clear();
    } else {
        regions_for_point() = new _std::vector<region *>{};
    }

    for (int i = 0; i < this->total_regions; ++i)
    {
        auto *reg = this->regions[i];
        if (reg->is_inside_or_on(a2)) {
            regions_for_point()->push_back(reg);
        }
    }

    return terrain::regions_for_point();
}

void terrain::unlock_district_pack_slot(int slot_idx)
{
    if constexpr (1) {
        auto *district_partition = resource_manager::get_partition_pointer(RESOURCE_PARTITION_DISTRICT);
        assert(district_partition != nullptr);

        auto &pack_slots = district_partition->get_pack_slots();
        assert(slot_idx >= 0 && slot_idx < (int) pack_slots.size());

        assert(pack_slots[slot_idx]->is_empty() || pack_slots[slot_idx]->is_pack_unloading());

        auto &slot = pack_slots.at(slot_idx);
        this->field_24.unlock_pack_slot(slot);
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

void terrain::un_mash_obb(char *a2, int *a3, region *reg)
{
    TRACE("terrain::un_mash_obb");

    if constexpr (1) {
        if ( reg != nullptr )
        {
            reg->field_98 = (oriented_bounding_box_root_node *)((unsigned int)(a2 + 63) & 0xFFFFFFC0);
            reg->field_98->un_mash(a2, a3, reg);
            if (reg->field_98->field_30 == 0) {
                reg->field_98 = nullptr;
            }
        }
    } else {
        THISCALL(0x00514310, this, a2, a3, reg);
    }
}

void terrain::un_mash_texture_to_frame(char *a2, int *a3, region *reg)
{
    TRACE("terrain::un_mash_texture_to_frame");

    if constexpr (1) {
        *a3 = 0;
        auto total_frame_maps = *bit_cast<int *>(a2);
        char *a1 = a2 + 4;

        assert(total_frame_maps > 0);
        assert(reg->texture_to_frame_maps == nullptr);

        reg->m_total_frame_maps = total_frame_maps;
        reg->texture_to_frame_maps = (texture_to_frame_map **)(a1 + 4);
        a1 += 4;
        int v6 = (int) (a1 + 4 * total_frame_maps);
        for ( auto i = 0; i < total_frame_maps; ++i ) {
            *(int *)a1 = v6;
            v6 += 48;
            a1 += 4;
        }

        for ( auto j = 0; j < total_frame_maps; ++j )
        {
            reg->texture_to_frame_maps[j] = (texture_to_frame_map *)a1;
            int a2a;
            reg->texture_to_frame_maps[j]->un_mash(a1, &a2a);
            a1 += a2a;
        }

        *a3 = a1 - a2;
    } else {
        THISCALL(0x00514380, this, a2, a3, reg);
    }
}

void terrain_patch()
{
    {
        FUNC_ADDRESS(address, &terrain::start_streaming);
        REDIRECT(0x0055D1BF, address);
    }

    {
        FUNC_ADDRESS(address, &terrain::init_region_proximity_map);
        REDIRECT(0x00556CDD, address);
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

        region * (terrain::*func)(const vector3d &a2, const region *a3) = &terrain::find_region;
        FUNC_ADDRESS(address, func);
        REDIRECT(0x0055CF7F, address);
    }

    {
        FUNC_ADDRESS(address, &terrain::frame_advance);
        REDIRECT(0x005582AA, address);
    }

}
