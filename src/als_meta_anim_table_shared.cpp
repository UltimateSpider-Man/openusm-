#include "als_meta_anim_table_shared.h"
#include "common.h"

namespace als {

    VALIDATE_SIZE(als_meta_anim_table_shared, 0x18);

    void als_meta_anim_table_shared::unmash(mash_info_struct *a1, void *a3)
    {
        a1->unmash_class_in_place(this->field_0, this);
    }
}
