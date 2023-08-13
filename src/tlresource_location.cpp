#include "tlresource_location.h"

#include "common.h"

VALIDATE_SIZE(tlresource_location, 12u);

void tlresource_location::un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *) {
    ;
}

tlresource_type tlresource_location::get_type() const {
    return static_cast<tlresource_type>(this->m_type & 0xFF);
}

uint32_t tlresource_location::get_size() {
    return this->m_type >> 8;
}
