#include "force_transitions.h"

#include "common.h"
#include "mash_info_struct.h"

namespace als
{
    VALIDATE_SIZE(force_transitions, 0x18);

    void force_transitions::unmash(mash_info_struct *a1, void *)
    {
        a1->unmash_class_in_place(this->field_0, this);
        a1->unmash_class_in_place(this->field_4, this);
    }
}
