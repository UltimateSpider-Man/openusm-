#include "token_def_list.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"

VALIDATE_SIZE(token_def_list, 0x38);

token_def_list::token_def_list(from_mash_in_place_constructor *a2) {
    TRACE("token_def_list::token_def_list");
    THISCALL(0x005DEDA0, this, a2);
}

int token_def_list::unmash(mash_info_struct *a2, void *a3) {
    TRACE("token_def_list::unmash");

    return THISCALL(0x005DD200, this, a2, a3);
}
