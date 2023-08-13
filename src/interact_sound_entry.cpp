#include "interact_sound_entry.h"

#include "common.h"
#include "mash_info_struct.h"

VALIDATE_SIZE(interact_sound_entry, 0x14);

void interact_sound_entry::unmash(mash_info_struct *a1, void *)
{
    a1->unmash_class_in_place(this->field_0, this);
}
