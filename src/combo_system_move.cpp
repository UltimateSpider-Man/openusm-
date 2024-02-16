#include "combo_system_move.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

VALIDATE_SIZE(combo_system_move::requirements, 0x44);
VALIDATE_SIZE(combo_system_move::results, 0x7C);
VALIDATE_SIZE(combo_system_move::dialation_info, 0x14);
VALIDATE_SIZE(combo_system_move::link_info, 0x14);

VALIDATE_SIZE(combo_system_move, 0xC8);


void combo_system_move::dialation_info::_unmash(mash_info_struct *a1, void *a3)
{
    TRACE("combo_system_move::dialation_info::unmash");
    ;
}

void combo_system_move::link_info::_unmash(mash_info_struct *a1, void *a3)
{
    TRACE("combo_system_move::link_info::unmash");

    a1->unmash_class_in_place(this->field_4, this);
}

int combo_system_move::link_info::get_mash_sizeof()
{
    int (__fastcall *func)(combo_system_move::link_info *) = CAST(func, get_vfunc(m_vtbl, 0x18));
    return func(this);
}

combo_system_move::results::results(const results &a2) {
    THISCALL(0x0048CBB0, this, &a2);
}

combo_system_move::results::~results()
{
    THISCALL(0x0043C0A0, this);
}

void combo_system_move::results::_unmash(mash_info_struct *a1, void *a3)
{
    TRACE("combo_system_move::results::unmash");

    if constexpr (1)
    {
        a1->unmash_class_in_place(this->field_4, this);
        a1->unmash_class_in_place(this->field_8, this);
        a1->unmash_class_in_place(this->field_C, this);
        a1->unmash_class_in_place(this->field_10, this);

        a1->unmash_class_in_place(this->field_40, this);

        a1->unmash_class_in_place(this->field_54, this);
    }
    else
    {
        THISCALL(0x00471B30, this, a1, a3);
    }
}

void combo_system_move::requirements::_unmash(mash_info_struct *a1, void *a3)
{
    TRACE("combo_system_move::requirements::unmash");

    if constexpr (1)
    {
        a1->unmash_class_in_place(this->field_4, this);

        a1->unmash_class_in_place(this->field_10, this);

        a1->unmash_class_in_place(this->field_1C, this);

        a1->unmash_class_in_place(this->field_30, this);
    }
    else
    {
        THISCALL(0x00481470, this, a1, a3);
    }
}

void combo_system_move::_unmash(mash_info_struct *a2, void *a3)
{
    TRACE("combo_system_move::unmash");

    mash_virtual_base::fixup_vtable(&this->field_4);
    this->field_4.unmash(a2,this);

    mash_virtual_base::fixup_vtable(&this->field_80);
    this->field_80.unmash(a2, this);
}

int combo_system_move::get_mash_sizeof()
{
    int (__fastcall *func)(combo_system_move *) = CAST(func, get_vfunc(m_vtbl, 0x18));
    return func(this);
}

void combo_system_move_patch()
{
    {
        FUNC_ADDRESS(address, &combo_system_move::dialation_info::_unmash);
        set_vfunc(0x00873738, address);
    }
    {
        FUNC_ADDRESS(address, &combo_system_move::link_info::_unmash);
        set_vfunc(0x008737A8, address);
    }

    {
        FUNC_ADDRESS(address, &combo_system_move::requirements::_unmash);
        set_vfunc(0x0087B8A4, address);
    }

    {
        FUNC_ADDRESS(address, &combo_system_move::results::_unmash);
        set_vfunc(0x00879FC4, address);
    }

    {
        FUNC_ADDRESS(address, &combo_system_move::_unmash);
        set_vfunc(0x0087B8C0, address);
    }
}
