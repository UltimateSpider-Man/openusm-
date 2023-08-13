#include "base_ai_data.h"

#include "base_ai_core.h"
#include "common.h"
#include "memory.h"

VALIDATE_SIZE(base_ai_data, 0x18);
VALIDATE_OFFSET(base_ai_data, field_14, 0x14);

void base_ai_data::post_entity_mash() {
    this->field_14->post_entity_mash();
}

void base_ai_data::destruct_mashed_class() {
    auto *v2 = this->field_14;
    if (v2 != nullptr) {
        (*this->field_14).~ai_core();

        mem_dealloc(v2, sizeof(*v2));
    }

    this->field_0.destruct_mashed_class();
    this->field_8.sub_6D6EB0();
}
