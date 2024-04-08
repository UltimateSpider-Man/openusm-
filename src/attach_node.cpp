#include "attach_node.h"

#include "common.h"
#include "mash_info_struct.h"
#include "trace.h"

VALIDATE_SIZE(attach_node, 0x28);

void attach_node::unmash(mash_info_struct *a1, void *)
{
    TRACE("attach_node::unmash");

    a1->unmash_class_in_place(this->field_0, this);

    a1->unmash_class_in_place(this->field_10, this);
}
