#pragma once

#include <cstdint>

#include "mash_virtual_base.h"
#include "mstring.h"
#include "mvector.h"
#include "string_hash.h"

struct combo_system_move : mash_virtual_base {
    struct trigger_info : mash_virtual_base
    {
        int field_4;
        int field_8;
    };

    struct target_info : mash_virtual_base {
        int field_4;
    };

    struct link_info : mash_virtual_base
    {
        string_hash field_4;
        int field_8;
        int field_C;
        int field_10;

        //virtual
        void _unmash(mash_info_struct *a1, void *a3);

        //virtual
        int get_mash_sizeof();
    };

    struct range_info : mash_virtual_base
    {};

    struct requirements : mash_virtual_base {
        trigger_info field_4;
        target_info field_10;
        int field_18;
        range_info field_1C;
        int field_20;
        int field_24;
        int field_28;
        int field_2C;
        mVector<link_info> field_30;

        //0x00481470
        //virtual
        void _unmash(mash_info_struct *a1, void *a3);
    };

    struct dialation_info : mash_virtual_base
    {
        int field_4;
        int field_8;
        int field_C;
        int field_10;

        void _unmash(mash_info_struct *, void *);
    };

    struct results : mash_virtual_base {
        string_hash field_4;
        string_hash field_8;
        string_hash field_C;
        mString field_10;
        int field_20;
        int field_24;
        int field_28;
        int field_2C;
        int field_30;
        int field_34;
        int field_38;
        int field_3C;
        dialation_info field_40;
        dialation_info field_54;
        bool field_68;
        int field_6C;
        int field_70;
        int field_74;
        int field_78;

        //0x0048CBB0
        results(const results &a2);

        //virtual
        ~results(); 

        //0x00471B30
        //virtual
        void _unmash(mash_info_struct *, void *);
    };

    results field_4;
    requirements field_80;
    int field_C4;

    //0x00471BA0
    //virtual
    void _unmash(mash_info_struct *a2, void *a3);

    int get_mash_sizeof();
};

extern void combo_system_move_patch();
