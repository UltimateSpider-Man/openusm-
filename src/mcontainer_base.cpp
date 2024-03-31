#include "mcontainer_base.h"

#include "common.h"

VALIDATE_SIZE(mContainer_base, 0x8);

void mContainer_base::clear()
{
    this->m_size = 0;
    this->field_0 = 0;
}

bool mContainer_base::is_pointer_in_mash_image(void *a3) const
{
    return int(a3) >= int(this) && int(a3) <= int(this) + this->field_0;
}
