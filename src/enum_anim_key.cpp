#include "enum_anim_key.h"

#include "common.h"
#include "func_wrapper.h"
#include "vtbl.h"

VALIDATE_SIZE(anim_key, 0x4);

anim_key::anim_key()
{
    this->m_vtbl = 0x008738E8;
}

int anim_key::get_mash_sizeof()
{
    auto &func = get_vfunc(m_vtbl, 0x1C);
    return func(this);
}

#if 0
int anim_key::compare(anim_key **a1, int *a2) {
    struct Vtbl {
        int empty[6];
        thiscall_call field_18;
    };

    enum_anim_key **_a1 = CAST(_a1, a1);

    Vtbl *vtbl = CAST(vtbl, get_vtbl((bit_cast<int **>(*_a1))[0]));

    return vtbl->field_18(*_a1, *(const anim_key **) (*a2 + 4));
}
#endif
