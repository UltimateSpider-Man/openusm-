#pragma once

#include "variable.h"

#include <vector.hpp>

struct vector3d;
struct glass_house;

struct glass_house_manager {
    //0x00520890
    static bool is_enabled();

    //0x00538570
    static bool is_point_in_glass_house(const vector3d &a1);

    static void show_glass_houses();

    static inline Var<bool> enabled{0x00921D78};

    static inline Var<_std::vector<glass_house *> [3]> glass_houses{0x0096007C};
};

extern void glass_house_manager_patch();
