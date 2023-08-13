#include "cached_special_effect.h"

#include "fx_cache.h"

#include "common.h"

#include "func_wrapper.h"

VALIDATE_SIZE(cached_special_effect, 64u);

cached_special_effect::cached_special_effect() {
    this->field_0 = resource_key();
    this->field_8 = resource_key();
    this->field_24 = 0;
    this->field_3C = 0;
    this->field_3D = 0;
    this->field_10[1] = 0.0f;
    this->field_10[2] = 0.0f;
    this->field_10[0] = 1.0f;
    this->field_8.m_hash.source_hash_code = 0;
    this->field_8.m_type = RESOURCE_KEY_TYPE_NONE;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_0.m_hash.source_hash_code = 0;
    this->field_0.m_type = RESOURCE_KEY_TYPE_NONE;
    this->field_34 = 0;
    this->field_36 = 0;
    this->field_24 = 0;
    this->field_28 = 0;
    this->field_30 = nullptr;
    this->field_8.m_type = RESOURCE_KEY_TYPE_ENTITY;
    this->field_2C = -1.0f;
    this->field_3C = 0;
    this->field_3D = 0;
    this->field_38 = 5;
}

void cached_special_effect::frame_advance(Float a2) {
    auto *v2 = this->field_30;
    if (v2 != nullptr) {
        v2->frame_advance(a2);
    }
}

void cached_special_effect::spawn(bool a1,
                                  const vector3d &a2,
                                  const vector3d &a3,
                                  handheld_item *a6,
                                  entity_base *a7,
                                  entity_base *a8,
                                  const vector3d &a9,
                                  bool a10,
                                  bool a11) {
    THISCALL(0x004EFC00, this, a1, &a2, &a3, a6, a7, a8, &a9, a10, a11);
}

void cached_special_effect::fill_cache() {
    THISCALL(0x004D4E10, this);
}
