#pragma once

#include "entity.h"
#include "entity_base_vhandle.h"
#include "local_collision.h"
#include "simple_queue.h"
#include "variable.h"
#include "vector3d.h"

struct line_info_local_query {};

struct line_info {
    vector3d field_0;
    vector3d field_C;
    vector3d hit_pos;
    vector3d hit_norm;
    vector3d field_30;
    vector3d field_3C;
    vhandle_type<entity> field_48;
    subdivision_node_obb_base *field_4C;
    local_collision::entfilter_base *ent_filter;
    local_collision::obbfilter_base *obb_filter;
    bool field_58;
    bool field_59;
    bool field_5A;
    bool field_5C;

    //0x0052EDD0
    line_info();

    line_info(const vector3d &a2, const vector3d &a3);

    ~line_info();

    void render(int num, bool a3);

    //0x0048C9D0
    void clear();

    //0x0052EE20
    bool check_collision(const local_collision::entfilter_base &a2,
                         const local_collision::obbfilter_base &a3,
                         line_info_local_query *a4);

    //0x006B6E00
    void copy(const line_info &a2);

    //0x0052EE00
    bool remove_to_collision_check_queue();

    bool release_mem();

    //0x0052F120
    static void frame_advance(int a1);

    static inline Var<simple_queue<line_info *, 16>> queued_collision_checks{0x009223F8};
};

#ifndef TEST_CASE

extern int num_debug_line_info[2];

extern std::array<line_info[64], 2> debug_line_info;

#endif

//0x0068A9D0
extern bool is_noncrawlable_surface(line_info &a1);

extern void line_info_patch();
