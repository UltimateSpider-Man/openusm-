#include "city_lights.h"

#include "func_wrapper.h"
#include "ngl.h"
#include "parse_generic_mash.h"
#include "common.h"

VALIDATE_SIZE(city_lights, 0x24);

void city_lights::load_from_file(const mString &a2) {
    THISCALL(0x0051B5C0, this, &a2);
}

void city_lights::update(Float a1, nglMatrix &a2, nglMatrix &a3) {
    THISCALL(0x00527EB0, this, a1, &a2, &a3);
}

void city_lights::un_mash_start(generic_mash_header *a1, void *a2, generic_mash_data_ptrs *a3, void *)
{
    this->un_mash(a1, a2, a3);
}

void city_lights::un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *a4)
{
    uint32_t v4 = 16 - ((uint32_t) a4->field_4 % 16);
    if (v4 < 16) {
        a4->field_4 += v4;
    }

    uint32_t v5 = 4 - ((uint32_t) a4->field_4 % 4);
    if (v5 < 4) {
        a4->field_4 += v5;
    }

    this->field_0 = (char *) a4->field_4;
    uint32_t v6 = ((uint32_t) a4->field_4) + 3072;
    uint32_t v7 = 4 - ((uint32_t) a4->field_4 % 4);
    a4->field_4 = (uint8_t *) v6;
    if (v7 < 4) {
        a4->field_4 += v7;
    }

    this->field_4 = (char *) a4->field_4;
    uint32_t v8 = ((uint32_t) a4->field_4) + 3072;
    uint32_t v9 = 4 - ((uint32_t) a4->field_4 % 4);
    a4->field_4 = (uint8_t *) v8;
    if (v9 < 4) {
        a4->field_4 += v9;
    }

    this->field_8 = (char *) a4->field_4;
    a4->field_4 += 768;
}
