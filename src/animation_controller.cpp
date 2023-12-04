#include "animation_controller.h"

#include "als_nal_meta_anim.h"
#include "als_meta_anim_table_shared.h"
#include "common.h"
#include "func_wrapper.h"
#include "oldmath_po.h"
#include "nal_anim_comp.h"
#include "nal_system.h"
#include "nal_skeleton.h"
#include "resource_manager.h"
#include "string_hash.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

VALIDATE_SIZE(animation_controller, 0x10);

void animation_controller::get_camera_root_abs_po(po &arg0)
{
    TRACE("animation_controller::get_camera_root_abs_po");

    THISCALL(0x004A8990, this, &arg0);
}

animation_controller::anim_ctrl_handle animation_controller::play_layer_anim(
        const string_hash &a3,
        unsigned int a4,
        Float a5,
        unsigned int a6,
        bool a7,
        als::layer_types a8)
{
    TRACE("animation_controller::play_layer_anim");

    animation_controller::anim_ctrl_handle result;
    THISCALL(0x0049BA90, this, &result, &a3, a4, a5, a6, a7, a8);

    return result;
}

animation_controller::anim_ctrl_handle animation_controller::get_base_anim_handle()
{
    anim_ctrl_handle v3{};
    v3.field_0 = true;
    v3.field_8 = this;
    return v3;
}

double sub_497DD0(nalComp::nalCompAnim *a1, int a2)
{
    if ( (a2 & 0x20) != 0 ) {
        return 0.0;
    }

    if ( (a2 & 0x40) != 0 ) {
        return 0.13333;
    }

    constexpr float flt_880AFC = 0.26666;
    if ( (a2 & 0x80u) != 0 ) {
        return flt_880AFC;
    }

    if ( (a2 & 0x100) == 0 ) {
        return 0.0;
    }

    auto v3 = a1->field_38 * 0.2;
    auto v4 = v3;
    if ( v3 >= 0.5) {
        return flt_880AFC;
    }

    if ( flt_880AFC >= (double)v4 ) {
        return v4;
    }

    return flt_880AFC;
}

animation_controller::anim_ctrl_handle *animation_controller::_play_base_layer_anim(
        animation_controller::anim_ctrl_handle *out,
        const string_hash &a3,
        Float a4,
        uint32_t a5,
        bool a6)
{
    *out = this->play_base_layer_anim(a3, a4, a5, a6);
    return out;
}

animation_controller::anim_ctrl_handle animation_controller::play_base_layer_anim(
        const string_hash &a3,
        Float a4,
        uint32_t a5,
        bool a6)
{
    TRACE("animation_controller::play_base_layer_anim", a3.to_string());

    animation_controller::anim_ctrl_handle result;

    if constexpr (1) {
        auto *anim_by_hash = (als::als_nal_meta_anim *) get_anim_by_hash(a3, this->field_C, this->field_4);
        if ( anim_by_hash == nullptr ) {
            auto v6 = a3.to_string();
            error(
              "Animation %s was referred to by an ALS but couldn't be found (likely 'externed' but never provided for us)",
              v6);
        }

        struct {
            int field_0;
            actor *field_4;
        } v22 {};
        v22.field_0 = 0;
        v22.field_4 = this->field_4;

        auto *v8 = (nalBaseSkeleton *)anim_by_hash->field_30;
        auto AnimTypeName = v8->GetAnimTypeName();
        tlFixedString v18 = AnimTypeName;

        auto sub_8226E0 = [this](tlFixedString a2) -> bool
        {
            auto AnimTypeName = this->field_8->GetAnimTypeName();
            return AnimTypeName == a2;
        };

        if ( !sub_8226E0(v18) ) {
            auto v10 = this->field_8->GetAnimTypeName();
            auto *v2 = v10.to_string();
            auto &v11 = this->field_8->field_8;
            auto *v3 = v11.to_string();
            auto *v12 = anim_by_hash->field_30;
            auto v13 = v12->GetAnimTypeName();
            auto *v4 = v13.to_string();
            auto v14 = anim_by_hash->field_8;
            auto *v15 = v14.to_string();
            error(
              "Attempted to play an animation \"%s\" of animtype \"%s\" on a character skeleton \"%s\" of animtype \"%s\". They a"
              "re not compatible. Please have this animation altered to use the correct character's skeleton.",
              v15,
              v4, 
              v3,
              v2);
        }

        auto v21 = sub_497DD0((nalComp::nalCompAnim *) anim_by_hash, a5);
        this->play_base_layer_anim(
            (nalAnimClass<nalAnyPose> *) anim_by_hash,
            a4,
            v21,
            a6,
            (a5 & 0x4000) != 0,
            &v22
            );

        result = this->get_base_anim_handle();
    } else {
        animation_controller::anim_ctrl_handle result;
        THISCALL(0x0049B9A0, this, &result, &a3, a4, a5, a6);
    } 

    return result;
}

void animation_controller::play_base_layer_anim(
        nalAnimClass<nalAnyPose> *a2,
        Float a3,
        Float a4,
        bool a5,
        bool a6,
        void *a7)
{
    void (__fastcall *func)(
            void *,
            void *,
            nalAnimClass<nalAnyPose> *a2,
            Float a3,
            Float a4,
            bool a5,
            bool a6,
            void *a7) = CAST(func, get_vfunc(m_vtbl, 0x8));
    func(this, nullptr, a2, a3, a4, a5, a6, a7);
}

void animation_controller::anim_ctrl_handle::set_anim_speed(Float a2)
{
    struct {
        char field_0[0x58];
        void (__thiscall *field_58)(void *, Float);
        void (__thiscall *field_5C)(void *, Float, Float);
    } * vtbl = CAST(vtbl, this->field_8->m_vtbl);

    if ( this->field_0 ) {
        vtbl->field_58(this->field_8, a2);
    } else {
        vtbl->field_5C(
            this->field_8,
            a2,
            this->field_4);
    }
}

bool animation_controller::anim_ctrl_handle::is_anim_active()
{
    if ( this->field_8 != nullptr && this->field_0 ) {
        return true;
    }

    return this->field_8 != nullptr && this->field_8->is_anim_active(this->field_4);
}

int animation_controller::anim_ctrl_handle::sub_4AD230()
{
    return THISCALL(0x004AD230, this);
}

float animation_controller::anim_ctrl_handle::sub_4AD210()
{
    float (__fastcall *func)(void *) = CAST(func, 0x004AD210);
    return func(this);
}

bool animation_controller::is_anim_active(Float a1) 
{
    if constexpr (0) {
        //return this->my_player.IsAnimActive(a1);
    } else {
        bool (__fastcall *func)(void *, void *, Float) = CAST(func, get_vfunc(m_vtbl, 0x2C));
        return func(this, nullptr, a1);
    }
}

void animation_controller::frame_advance(Float a2, bool a3, bool a4)
{
    sp_log("0x%08X", m_vtbl);
    void (__fastcall *func)(void *, void *, Float, bool, bool) = CAST(func, get_vfunc(m_vtbl, 0x70));
    func(this, nullptr, a2, a3, a4);
}

//TODO
void *get_anim_by_hash(
        const string_hash &a1,
        const als::als_meta_anim_table_shared *a2,
        actor *a3)
{
    TRACE("get_anim_by_hash", a1.to_string());

    if constexpr (0) {
        if ( a2 != nullptr ) {
            auto *v9 = a3;
            string_hash v8 = a1;
            auto *nal_meta_anim = a2->get_nal_meta_anim(v8, v9);
            if ( nal_meta_anim != nullptr ) {
                return nal_meta_anim;
            }
        }

        struct {
            char field_0[0x8];
            void * (__fastcall *Find)(void *, void *, uint32_t);
        } * vtbl = CAST(vtbl, nalGetAnimDirectory()->m_vtbl);

        auto v5 = a1.source_hash_code;
        auto *v15 = vtbl->Find(
                          nalGetAnimDirectory(),
                          nullptr,
                          v5);
        if ( v15 == nullptr )
        {
            auto *partition_pointer = resource_manager::get_partition_pointer(RESOURCE_PARTITION_MISSION);
            if ( partition_pointer != nullptr )
            {
                auto &pack_slots = partition_pointer->get_pack_slots();
                if ( !pack_slots.empty() )
                {
                    auto *__old_context = resource_manager::get_and_push_resource_context(RESOURCE_PARTITION_MISSION);
                    auto v7 = a1.source_hash_code;
                    v15 = vtbl->Find(
                                            nalGetAnimDirectory(),
                                            nullptr,
                                            v7);
                    resource_manager::pop_resource_context();

                    assert(resource_manager::get_resource_context() == __old_context);
                }
            }
        }

        return v15;
    } else {
        return (void *) CDECL_CALL(0x0049B910, &a1, a2, a3);
    }
}

void animation_controller_patch() {

    REDIRECT(0x0049B9B5, get_anim_by_hash);

    {
        animation_controller::anim_ctrl_handle * (animation_controller::*func)(
            animation_controller::anim_ctrl_handle *,
            const string_hash &a3,
            Float a4,
            uint32_t a5,
            bool a6) = &animation_controller::_play_base_layer_anim;
        FUNC_ADDRESS(address, func);
        REDIRECT(0x004A652D, address);
    }

}
