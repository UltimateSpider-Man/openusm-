#include "als_request_data.h"

#include "common.h"
#include "func_wrapper.h"

namespace als {
VALIDATE_SIZE(request_data, 0x14);

request_data::request_data()
{
    clear();
}
 
void request_data::clear()
{
    this->did_transition_occur = false;
    this->field_1 = false;
    this->field_2 = false;
    this->field_3 = false;
    this->field_4 = false;
    this->field_8 = {0};
}

void request_data::sub_4ADF40(const request_data &a2)
{
    THISCALL(0x004ADF40, this, &a2);
}

}
