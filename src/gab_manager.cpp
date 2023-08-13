#include "gab_manager.h"

#include "common.h"
#include "func_wrapper.h"
#include "mash_info_struct.h"

VALIDATE_SIZE(gab_database, 0x14);

Var<_std::list<gab_history_entry> *> s_gab_history{0x00968514};

Var<gab_database *> s_gab_database{0x00968510};

gab_database::gab_database(from_mash_in_place_constructor *a2) {
    THISCALL(0x005E0E80, this, a2);
}

void gab_database::destruct_mashed_class() {
    THISCALL(0x005E0860, this);
}

void gab_database::unmash(mash_info_struct *a1, void *a3) {
    THISCALL(0x005DF4A0, this, a1, a3);
}

void gab_manager::create_inst() {
    CDECL_CALL(0x005D7E20);
}

void gab_manager::delete_inst() {
    delete s_gab_history();
    s_gab_history() = nullptr;
}

void gab_manager::frame_advance(Float a1) {
    CDECL_CALL(0x005D1DA0, a1);
}

void gab_manager::set_gab_database(gab_database *a1) {
    s_gab_database() = a1;
}

gab_database *gab_manager::get_gab_database() {
    return s_gab_database();
}
