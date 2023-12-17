#include "als_transition_rule.h"

#include "func_wrapper.h"
#include "mash_info_struct.h"

#include "common.h"
#include "trace.h"

namespace als
{
    VALIDATE_SIZE(base_transition_rule, 0x24);

    VALIDATE_SIZE(implicit_transition_rule, 0x24u);
    VALIDATE_SIZE(explicit_transition_rule, 0x28u);
    VALIDATE_SIZE(incoming_transition_rule, 0x2Cu);
    VALIDATE_SIZE(layer_transition_rule, 0x18u);

    void base_transition_rule::unmash(mash_info_struct *a1, void *)
    {
        a1->unmash_class_in_place(this->field_0, this);
        a1->unmash_class_in_place(this->field_14, this);

#ifdef TARGET_XBOX
        {
            uint8_t class_mashed = -1;
            class_mashed = *a1->read_from_buffer(mash::SHARED_BUFFER, 1, 1);
            assert(class_mashed == 0xAF || class_mashed == 0);
        }
#endif

        if (this->field_20 != nullptr)
        {
            a1->unmash_class(this->field_20, this
#ifdef TARGET_XBOX
                , mash::NORMAL_BUFFER
#endif
                    );
        }
    }

    void layer_transition_rule::unmash(mash_info_struct *a1, void *)
    {
        a1->unmash_class_in_place(this->field_8, this);
    }

    bool layer_transition_rule::can_transition(als_data &a2) const
    {
        TRACE("als::layer_transition_rule::can_transition");

        return (bool) THISCALL(0x0049FF50, this, &a2);
    }

    void explicit_transition_rule::unmash(mash_info_struct *a1, void *a3)
    {
        base_transition_rule::unmash(a1, a3);
        a1->unmash_class_in_place(this->field_24, this);
    }

    void implicit_transition_rule::unmash(mash_info_struct *a1, void *a3)
    {
        base_transition_rule::unmash(a1, a3);
    }

    void incoming_transition_rule::unmash(mash_info_struct *a1, void *a3)
    {
        base_transition_rule::unmash(a1, a3);
    }

}
