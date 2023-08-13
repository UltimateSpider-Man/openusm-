#pragma once

#include "actor.h"
#include "entity_base_vhandle.h"
#include "enum_anim_key.h"
#include "info_node.h"
#include "interaction_type_enum.h"

struct ai_interaction_data;
struct interaction;
struct from_mash_in_place_constructor;
struct attach_trigger_anim_key;
struct generic_interaction;

namespace ai {

struct als_inode;

struct interaction_inode : info_node {
    vhandle_type<actor> field_1C;
    als_inode *field_20;
    int field_24;
    int field_28;
    ai_interaction_data *field_2C;
    interaction *field_30;
    attach_trigger_anim_key *field_34;
    int field_38;
    int field_3C;
    int field_40;
    int target_interaction_type;
    bool field_48;
    bool field_49;

    //0x00483070
    interaction_inode();

    //0x004830B0
    interaction_inode(from_mash_in_place_constructor *a2);

    //0x00479850
    bool is_eligible(string_hash a2, bool a3);

    //0x004514B0
    bool is_in_master_mode();

    //0x004639E0
    [[nodiscard]] string_hash get_chosen_interact_state_id();

    //0x00451340
    void set_curr_anim(enum_anim_key::key_enum a2);

    //0x00451500
    actor *get_target();

    //0x00463980
    void set_flag_from_param(const string_hash &a2, interaction_type_enum a3);

    //0x0046E380
    void set_scripted_start(actor *a2, generic_interaction *a3);
};
} // namespace ai

extern void interaction_inode_patch();
