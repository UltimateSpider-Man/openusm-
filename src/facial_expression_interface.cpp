#include "facial_expression_interface.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(facial_expression_interface, 0x7C);

facial_expression_interface::facial_expression_interface(actor *a1) {
    THISCALL(0x006D1670, this, a1);
}

void facial_expression_interface::add_to_facial_expression_ifc_list() {
    THISCALL(0x006CFE50, this);
}

void facial_expression_interface::frame_advance_all_facial_expression_ifc(Float a1) {
    CDECL_CALL(0x006C9940, a1);
}

void facial_expression_interface::un_mash(generic_mash_header *,
                                          actor *a3,
                                          void *,
                                          generic_mash_data_ptrs *) {
    this->field_4 = a3;
    this->field_8 = false;
    this->add_to_facial_expression_ifc_list();
    this->field_C = a3;
}
