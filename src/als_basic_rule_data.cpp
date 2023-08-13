#include "als_basic_rule_data.h"

#include "mash_info_struct.h"
#include "common.h"
#include "trace.h"

namespace als
{
    namespace basic_rule_data
    {
        VALIDATE_SIZE(post_action_rule_set, 0x28u);

        void rule_action::unmash(mash_info_struct *a1, void *a3)
        {
            a1->unmash_class_in_place(this->field_8, this);

#ifdef TARGET_XBOX
            {
                uint8_t class_mashed = -1;
                class_mashed = *a1->read_from_buffer(mash::SHARED_BUFFER, 1, 1);
                assert(class_mashed == 0xAF || class_mashed == 0);
            }
#endif

            if (this->field_4 != nullptr)
            {
                a1->unmash_class(this->field_4, this
#ifdef TARGET_XBOX
                    , mash::NORMAL_BUFFER
#endif
                        );
            }
        }

        void post_action_rule_set::unmash(mash_info_struct *a1, void *a3)
        {
            TRACE("post_action_rule_set::unmash");

            a1->unmash_class_in_place(this->field_0, this);
            a1->unmash_class_in_place(this->field_14, this);
        }
            
    }
}
