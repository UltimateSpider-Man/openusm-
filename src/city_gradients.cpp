#include "city_gradients.h"

#include "parse_generic_mash.h"
#include "common.h"

VALIDATE_SIZE(city_gradients, 0x1C);

void city_gradients::un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *a5)
{
   this->un_mash(a2, a3, a4);
}

void city_gradients::un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *a4) {
    uint32_t v4 = 16 - ((uint32_t) a4->field_4 % 16);
    if (v4 < 16) {
        a4->field_4 += v4;
    }

    uint32_t v5 = 4 - ((uint32_t) a4->field_4 % 4);
    if (v5 < 4) {
        a4->field_4 += v5;
    }

    this->field_10 = (int) a4->field_4;
    uint32_t v6 = 208 * this->field_8 + ((uint32_t) a4->field_4);
    uint32_t v7 = 4 -
        ((208 * static_cast<uint8_t>(this->field_8) + static_cast<uint8_t>((uint32_t) a4->field_4)) %
         4);
    a4->field_4 = CAST(a4->field_4, v6);
    if (v7 < 4) {
        a4->field_4 = CAST(a4->field_4, v7 + v6);
    }

    this->field_14 = (uint32_t) a4->field_4;
    uint32_t v8 = 16 * this->field_8 + ((uint32_t) a4->field_4);
    uint32_t v9 = 4 -
        ((16 * static_cast<uint8_t>(this->field_8) + static_cast<uint8_t>((uint32_t) a4->field_4)) %
         4);
    a4->field_4 = CAST(a4->field_4, v8);
    if (v9 < 4) {
        a4->field_4 = CAST(a4->field_4, v9 + v8);
    }

    this->field_18 = ((uint32_t) a4->field_4);
    a4->field_4 += 8 * this->field_C;
}
