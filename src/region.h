#pragma once

#include "astar.h"
#include "mstring.h"
#include "region_audio_box_set.h"
#include "variable.h"
#include "vector3d.h"
#include "fixedstring.h"

#include <vector.hpp>

template<typename base_type, int number_of_bits>
struct fixed_bitvector;

struct oriented_bounding_box_root_node;
struct region_mash_info;
struct light_source;
struct subdivision_node_obb_base;
struct dynamic_proximity_map_stack;
struct entity;
struct traffic_path_graph;
struct ai_region_paths;
struct eligible_pack;
struct dynamic_rtree_root_t;
struct lego_map_root_node;

struct region
{
    dynamic_rtree_root_t *collision_proximity_map;
    void *ai_proximity_map;
    void *visibility_map;
    void *light_proximity_map;
    void *parking_proximity_map;

    int empty14[2];

    dynamic_proximity_map_stack *current_proximity_map_stack;
    int field_20;
    int field_24;
    void *meshes;
    region_mash_info *mash_info;
    void *region_entities;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    _std::vector<light_source *> *lights;
    uint32_t flags;
    uint32_t visited;
    int field_58;
    int field_5C;
    int field_60;
    subdivision_node_obb_base *obb;
    _std::vector<unsigned short> neighbors;

    mString field_78;
    mString field_88;

    oriented_bounding_box_root_node *field_98;

    lego_map_root_node *field_9C;
    fixed_bitvector<uint, 2048> *bitvector_of_legos_rendered_last_frame;
    vector3d field_A4;
    vector3d field_B0;
    float field_BC;
    int district_id;
    int field_C4;
    int field_C8;
    int strip_id;
    int multiblock_number;
    int field_D4;
    int *field_D8;
    int field_DC;
    region_audio_box_set field_E0;
    traffic_path_graph *field_100;
    ai_region_paths *field_104;
    _std::vector<eligible_pack *> field_108;

    int field_118[7];

    struct region_astar_search_record : astar_search_record {
        _std::vector<void *> field_24;
        vector3d field_34;
        float field_40;

        region_astar_search_record();

        void setup(void *search_start, void *a2);
    };

    //0x0053B4B0
    region(const mString &a2);

    static inline Var<uint32_t> visit_key{0x0095C914};

    static void prepare_for_visiting()
    {
        ++visit_key();
    } 

    void constructor_common();

    int get_district_id();

    bool is_loaded();

    bool is_locked() const
    {
        return this->flags & 1;
    }

    ai_region_paths *get_region_path_graph();

    void sub_5452D0();

    //0x0052E760
    bool is_inside_or_on(const vector3d &a2);

    //0x00544F60
    void create_proximity_maps();

    //0x00519E00
    mString *get_scene_id(bool a2);

    //0x00519E20
    void set_district_variant(int a2);

    //0x00519C70
    float get_ground_level() const;

    //0x00545700
    void remove(entity *a3);

    bool has_quad_paths();

    bool is_interior();

    traffic_path_graph *get_traffic_path_graph();

    void set_ambient(uint8_t a2, uint8_t a3, uint8_t a4);

    inline auto get_multiblock_number() {
        return this->multiblock_number;
    }

    //0x0053B380
    static region *__nw(uint32_t);

    //0x00519BB0
    fixedstring<8> &get_name();

    static inline Var<int> visit_key2{0x0095C91C};

    static inline Var<region *> all_regions{0x0095C924};

    static inline Var<int> number_of_allocated_regions{0x0095C920};
};
