#pragma once

#include "float.hpp"
#include "variable.h"

#include <vector.hpp>

#include <cstdint>

struct actor;
struct generic_mash_header;
struct generic_mash_data_ptrs;

struct facial_expression_interface {
    std::intptr_t m_vtbl;
    actor *field_4;
    bool field_8;
    actor *field_C;

    int field_10[27];

    //0x006D1670
    facial_expression_interface(actor *a1);

    //0x006C9940
    static void frame_advance_all_facial_expression_ifc(Float a1);

    //0x006CFE50
    void add_to_facial_expression_ifc_list();

    //0x006D1760
    void un_mash(generic_mash_header *, actor *a3, void *, generic_mash_data_ptrs *);

    static inline Var<_std::vector<facial_expression_interface> *> all_facial_expression_interfaces{
        0x0096C9AC};
};
