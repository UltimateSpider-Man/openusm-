#include "alter_conditions.h"

#include "mash_info_struct.h"
#include "common.h"

namespace als
{
    VALIDATE_SIZE(alter_conditions, 0xC);

    void alter_conditions::unmash(mash_info_struct *a1, void *a3)
    {
        a1->unmash_class_in_place(this->field_8, this);
    }
}
