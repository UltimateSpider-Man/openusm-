#include "als_post_layer_alter.h"

#include "mash_info_struct.h"
#include "common.h"

namespace als
{
    VALIDATE_SIZE(post_layer_alter, 0x1Cu);

    void post_layer_alter::unmash(mash_info_struct *a1, void *)
    {
        a1->unmash_class_in_place(this->field_4, this);
        a1->unmash_class_in_place(this->field_18, this);
    }
}
