#include "ai_interaction_data.h"

#include "anim_record.h"
#include "attach_interact_data.h"
#include "binary_search_array_cmp.h"
#include "config.h"
#include "func_wrapper.h"
#include "common.h"

#include <cstdint>

VALIDATE_SIZE(ai_interaction_data, 0xA8);

ai_interaction_data::ai_interaction_data() {}

int *ai_interaction_data::does_anim_exist(enum_anim_key::key_enum a2, bool a3) {
#if 0
    enum_anim_key v8;
    v8.field_4 = a2.field_0;

    return this->does_anim_exist(static_cast<anim_key *>(&v8), a3);
#else
    assert(0);
    return nullptr;
#endif
}

void ai_interaction_data::unregister_interactor(vhandle_type<actor> a2) {
    THISCALL(0x0069AA50, this, a2);
}

int *ai_interaction_data::does_anim_exist(const anim_key *a2, [[maybe_unused]] bool a3) {
#if 0
    anim_key *a1 = const_cast<anim_key *>(a2);

    int v2 = -1;

    if (binary_search_array_cmp<anim_key *, int >(&a1,
                                                    this->field_1C.m_data,
                                                    0,
                                                    this->field_1C.m_size,
                                                    &v2,
                                                    anim_key::compare)) {
        int *result = CAST(result, this->field_24[static_cast<uint16_t>(v2)]);
        return result;
    }

    return nullptr;
#else
    assert(0);
    return nullptr;
#endif
}

void ai_interaction_data::destruct_mashed_class()
{
    THISCALL(0x006B5400, this);
}

void ai_interaction_data::register_interactor(vhandle_type<actor> a3) {
    THISCALL(0x0069F2F0, this, a3);
}

void ai_interaction_data::unmash(mash_info_struct *a1, void *)
{
    a1->unmash_class_in_place(this->field_1C, this);

    a1->unmash_class_in_place(this->field_44, this);
    a1->unmash_class_in_place(this->field_48, this);
    a1->unmash_class_in_place(this->field_4C, this);
    a1->unmash_class_in_place(this->field_50, this);

    a1->unmash_class_in_place(this->field_54, this);

    a1->unmash_class_in_place(this->field_6C, this);

    a1->unmash_class_in_place(this->field_80, this);

    a1->unmash_class_in_place(this->field_94, this);

#ifdef TARGET_XBOX
    {
        uint8_t class_mashed = -1;
        class_mashed = *a1->read_from_buffer(mash::SHARED_BUFFER, 1, 1);
        assert(class_mashed == 0xAF || class_mashed == 0);
    }
#endif

    if ( this->field_68 != nullptr )
    {
        a1->unmash_class(this->field_68, this
#ifdef TARGET_XBOX
                , mash::NORMAL_BUFFER
#endif
                );
    }
}
