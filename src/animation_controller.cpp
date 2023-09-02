#include "animation_controller.h"

#include "als_meta_anim_table_shared.h"
#include "common.h"
#include "func_wrapper.h"
#include "oldmath_po.h"
#include "nal_system.h"
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
    animation_controller::anim_ctrl_handle result;
    THISCALL(0x0049BA90, this, &result, &a3, a4, a5, a6, a7, a8);

    return result;
}

animation_controller::anim_ctrl_handle animation_controller::play_base_layer_anim(
        const string_hash &a3,
        Float a4,
        uint32_t a5,
        bool a6)
{
    TRACE("animation_controller::play_base_layer_anim");

    if constexpr (0) {
    } else {
        animation_controller::anim_ctrl_handle result;
        THISCALL(0x0049B9A0, this, &result, &a3, a4, a5, a6);

        return result;
    }
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

bool animation_controller::is_anim_active(float a1) 
{
    auto func = get_vfunc(m_vtbl, 0x2C);
    return (bool) func(this, a1);
}

//TODO
void *get_anim_by_hash(
        const string_hash &a1,
        const als::als_meta_anim_table_shared *a2,
        actor *a3) {
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
            void * (__thiscall *field_8)(void *, uint32_t);
        } * vtbl = CAST(vtbl, nalGetAnimDirectory()->m_vtbl);

        auto v5 = a1.source_hash_code;
        auto *v15 = vtbl->field_8(
                          nalGetAnimDirectory(),
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
                    auto *v15 = vtbl->field_8(
                                            nalGetAnimDirectory(),
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
}
