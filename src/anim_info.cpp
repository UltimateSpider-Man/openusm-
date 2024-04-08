#include "anim_info.h"

#include "common.h"
#include "parse_generic_mash.h"

VALIDATE_SIZE(anim_info, 0x24);

void anim_info::un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *a4)
{
    if ( (this->field_1C & 0x2000000) != 0 )
    {
        auto v4 = 8 - ((int)a4->field_4 & 7);
        if ( v4 < 8 )
        {
            a4->field_4 += v4;
        }

        auto v5 = 4 - ((int)a4->field_4 & 3);
        if ( v5 < 4 )
        {
            a4->field_4 += v5;
        }

        this->field_14 = (int)a4->field_4;
        a4->field_4 += 16;
    }
    else
    {
        this->field_14 = 0;
    }

    if ( (this->field_1C & 0x4000000) != 0 )
    {
        auto v6 = 4 - ((int)a4->field_4 & 3);
        if ( v6 < 4 )
        {
            a4->field_4 += v6;
        }

        this->field_18 = (int)a4->field_4;
        a4->field_4 += 0x34;
    }
    else
    {
        this->field_18 = 0;
    }
}
