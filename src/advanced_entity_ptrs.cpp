#include "advanced_entity_ptrs.h"

#include "common.h"
#include <func_wrapper.h>

VALIDATE_SIZE(advanced_entity_ptrs, 0x14);

advanced_entity_ptrs::advanced_entity_ptrs()
{

}
advanced_entity_ptrs::~advanced_entity_ptrs() {
    THISCALL(0x004EF1C0, this);
}

void advanced_entity_ptrs::un_mash(generic_mash_header *header,
                                   actor *arg4,
                                   void *a4,
                                   generic_mash_data_ptrs *a5) {
    THISCALL(0x004CFCE0, this, header, arg4, a4, a5);
}
