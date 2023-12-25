#pragma once

#include "mash_virtual_base.h"
#include "fixedstring.h"

struct from_mash_in_place_constructor;
struct nalBaseSkeleton;

namespace als
{
    struct als_meta_anim_base : mash_virtual_base
    {
        int field_4;
        tlFixedString field_8;

        als_meta_anim_base() {
            this->m_vtbl = 0x00875458;
        }

        als_meta_anim_base(from_mash_in_place_constructor *)
        {}

        //virtual
        void _unmash(mash_info_struct *a1, void *a3);

        const tlFixedString & get_anim_name() const;

        //virtual
        bool is_anim_looping() const;

        //virtual
        bool is_anim_trajectory_relative() const;

        //virtual
        nalBaseSkeleton *get_skeleton();

        //virtual
        float get_anim_duration() const;

        //virtual
        int get_mash_sizeof() const;
    };
}

extern void als_meta_anim_base_patch();
