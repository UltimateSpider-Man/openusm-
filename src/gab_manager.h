#pragma once

#include "float.hpp"
#include "variable.h"

#include <list.hpp>

struct mash_info_struct;
struct from_mash_in_place_constructor;

struct gab_history_entry {};

struct gab_database {
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;

    //0x005E0E80
    gab_database(from_mash_in_place_constructor *a2);

    //0x005E0860
    void destruct_mashed_class();

    //0x005DF4A0
    void unmash(mash_info_struct *a1, void *a3);
};

struct gab_manager {
    gab_manager();

    //0x005D7E20
    static void create_inst();

    static void delete_inst();

    //0x005D1DA0
    static void frame_advance(Float a1);

    static void set_gab_database(gab_database *a1);

    static gab_database *get_gab_database();
};

extern Var<_std::list<gab_history_entry> *> s_gab_history;

extern Var<gab_database *> s_gab_database;
