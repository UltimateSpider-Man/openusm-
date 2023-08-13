#include "resource_pack_group.h"

#include "func_wrapper.h"
#include "parse_generic_mash.h"

#include "common.h"

VALIDATE_SIZE(resource_pack_group, 0x20u);

int resource_pack_group::get_pack_slot(const mString &a2) {
    return THISCALL(0x0054C950, this, &a2);
}

int resource_pack_group::get_first_free_slot() {
    return THISCALL(0x00531EA0, this);
}

void resource_pack_group::un_mash(generic_mash_header *a2,
                                  [[maybe_unused]] void *a3,
                                  generic_mash_data_ptrs *a4) {
    if constexpr (1) {
        std::memcpy(this, a4->field_0, 8);
        a4->field_0 += 8;

        this->field_8.custom_un_mash(a2, &this->field_8, a4, nullptr);

        if (uint32_t v6 = 4 - ((uint32_t) a4->field_0 % 4); v6 < 4) {
            a4->field_0 += v6;
        }

        auto v7 = this->field_1C;
        this->field_14 = a4->field_0;
        a4->field_0 += 4 * v7;
    } else {
        THISCALL(0x0051F070, this, a2, a3, a4);
    }
}
