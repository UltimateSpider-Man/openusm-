#include "script_var_container.h"

#include "func_wrapper.h"
#include "common.h"

#include <cassert>

VALIDATE_SIZE(script_var_container, 0x1Cu);

constexpr auto SCRIPT_VAR_FLAG_UN_MASHED = 4u;

void script_var_container::un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *a5)
{
    assert(( flags & SCRIPT_VAR_FLAG_UN_MASHED ) == 0);
    this->un_mash(a2, a3, a4);
}

void script_var_container::un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4)
{
    THISCALL(0x00599440, this, a2, a3, a4);
}

void *script_var_container::get_script_var_address(const char *a2, script_library_class **a3) {
    return (void *) THISCALL(0x005A0520, this, a2, a3);
}
