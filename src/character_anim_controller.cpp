#include "character_anim_controller.h"

#include "charcomponentbase.h"
#include "character_pose_skel.h"
#include "common.h"
#include "nal_skeleton.h"
#include "trace.h"

#include <cassert>

VALIDATE_SIZE(character_anim_controller, 0x70);

static constexpr auto CHARACTER_ANIMTYPE_NAME = "Character";

character_anim_controller::character_anim_controller(
        actor *a2,
        nalBaseSkeleton *new_skel,
        unsigned int a4,
        const als::als_meta_anim_table_shared *a5)
        : nal_anim_controller(a2, new_skel, a4, a5),
            field_54(this),
            field_5C(this),
            field_64(nullptr),
            field_68(nullptr),
            field_6C(nullptr)
{
    this->m_vtbl = 0x00880F90;

    assert(new_skel->GetAnimTypeName() == tlFixedString(CHARACTER_ANIMTYPE_NAME));

    struct {
        uint32_t field_0;
        int field_4;
        int field_8;
        int field_C;
        int field_10;
        int field_14;
        char *field_18;
    } *NamedPerSkelData = CAST(NamedPerSkelData, bit_cast<nalChar::nalCharSkeleton *>(new_skel)->GetNamedPerSkelData(static_cast<CharComponentBase::Names>(1)));

    if ( NamedPerSkelData != nullptr )
    {
        this->field_6C = new_skel;
        tlFixedString v14 {"shake_root"};
        tlFixedString v13 {"camera_root"};
        
        for ( uint32_t a5a = 0; a5a < NamedPerSkelData->field_0; ++a5a )
        {
            auto *v9 = bit_cast<tlFixedString *>(&NamedPerSkelData->field_18[0x30 * a5a]);
            if ( *v9 == v13 ) {
                this->field_64 = v9;
            }

            if ( *v9 == v14 )
            {
                this->field_68 = v9;
            }
        }
    }
}

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
