#pragma once

#include "nal_anim_controller.h"

#include <nal_generic.h>
#include <nal_system.h>

struct actor;
struct nalBaseSkeleton;

namespace als {
struct als_meta_anim_table_shared;
}

struct generic_anim_controller : nal_anim_controller {

    struct gen_base_play_method {
        std::intptr_t m_vtbl;
        generic_anim_controller *field_4;

        gen_base_play_method(generic_anim_controller *a2) {
            this->m_vtbl = 0x00880B40;
            this->field_4 = a2;
        }
    };

    struct gen_mod_play_method {
        std::intptr_t m_vtbl;
        generic_anim_controller *field_4;

        gen_mod_play_method(generic_anim_controller *a2) {
            this->m_vtbl = 0x00880B58;
            this->field_4 = a2;
        }
    };

    int field_10;
    gen_base_play_method field_54;
    gen_mod_play_method field_5C;
    nalGeneric::nalGenericConstComponentHandle<nalPositionOrientation> field_64;
    nalGeneric::nalGenericConstComponentHandle<nalPositionOrientation> field_74;
    nalGeneric::nalGenericComponentHandle<float> field_84;
    nalGeneric::nalGenericComponentHandle<nalPositionOrientation> field_94;
    nalGeneric::nalGenericComponentHandle<unsigned char> field_A4;
    nalGeneric::nalGenericConstComponentHandle<float> field_B4;
    nalGeneric::nalGenericConstComponentHandle<float> field_C4;
    nalGeneric::nalGenericConstComponentHandle<float> field_D4;
    nalGeneric::nalGenericConstComponentHandle<float> field_E4;
    nalGeneric::nalGenericConstComponentHandle<float> field_F4;

    generic_anim_controller(actor *, nalBaseSkeleton *, unsigned int, als::als_meta_anim_table_shared *);
};
