#include "character_anim_controller.h"

#include "common.h"
#include "nal_skeleton.h"
#include "trace.h"

#include <cassert>

VALIDATE_SIZE(character_anim_controller, 0x70);

static constexpr auto CHARACTER_ANIMTYPE_NAME = "Character";

void character_anim_controller::play_base_layer_anim(
        nalAnimClass<nalAnyPose> *anim_ptr,
        Float a3,
        Float a4,
        bool a5,
        bool a6,
        void *a7)
{
    TRACE("character_anim_controller::play_base_layer_anim");

    assert(anim_ptr->GetSkeleton()->GetAnimTypeName() == tlFixedString(CHARACTER_ANIMTYPE_NAME));

    this->my_player.PlayModifier(
        anim_ptr,
        static_cast<decltype(this->my_player)::usm_anim_player_modifier_type>(a5),
        a4,
        bit_cast<decltype(this->my_player)::nalPlayMethod *>(&this->field_54),
        0.0,
        0,
        1.0,
        bit_cast<void *>(a3),
        a6,
        a7);
}

void character_anim_controller_patch()
{
    FUNC_ADDRESS(address, &character_anim_controller::play_base_layer_anim);
    SET_JUMP(0x004A6220, address);
}
