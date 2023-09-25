#pragma once

#include "mstring.h"
#include "variable.h"

#include <vector.hpp>

#include <set>

struct script_library_class;

struct slc_manager {
    //0x005AD720
    static void init();

    //0x005A5200
    static void kill();

    static script_library_class *get(const char *a1);

    //0x0059EC00
    static void un_mash_all_funcs();
};

extern Var<_std::vector<script_library_class *> *> slc_manager_class_array;

inline std::set<script_library_class *> *slc_manager_classes = nullptr;

//0x005AB800
extern void register_standard_script_libs();

extern void slc_manager_patch();
