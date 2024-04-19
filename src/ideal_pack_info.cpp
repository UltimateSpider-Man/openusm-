#include "ideal_pack_info.h"

#include "common.h"

#include <cassert>

VALIDATE_SIZE(ideal_pack_info, 0x8);

ideal_pack_info::ideal_pack_info(eligible_pack *a2, float a3)
{
    this->my_eligible_pack = a2;
    this->field_4 = a3;

    assert(my_eligible_pack != nullptr);
}
