#include "als_res_data.h"

#include "common.h"

VALIDATE_SIZE(als_res_data, 0x10);

als_res_data::als_res_data()
{

}

void als_res_data::unmash(mash_info_struct *a2, void *a3)
{
    this->field_0.unmash(a2, this);
}
