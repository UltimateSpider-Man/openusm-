#include "attach_interact_data.h"

#include "common.h"
#include "mash_info_struct.h"
#include "trace.h"

VALIDATE_SIZE(attach_interact_data, 0x14);

void attach_interact_data::unmash(mash_info_struct *a1, void *)
{
    TRACE("attach_interact_data::unmash");

    a1->unmash_class_in_place(this->field_0, this);
}
