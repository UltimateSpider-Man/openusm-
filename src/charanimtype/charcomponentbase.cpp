#include "charcomponentbase.h"

#include "string_hash.h"
#include "trace.h"
#include "utility.h"

#include <cassert>

uint32_t CharComponentBase::GetType()
{
    TRACE("CharComponentBase::GetType");

    if ( this->field_8 == 0 ) {
        if ( this->field_C != nullptr ) {
            this->field_8 = to_hash(this->field_C);
        } else {
            assert(0 && "You did not override GetType. You need to do this or set m_TheType or set m_strTypeString.");
        }
    }

    return this->field_8;
}

void CharComponentBase_patch()
{
    FUNC_ADDRESS(address, &CharComponentBase::GetType);
    SET_JUMP(0x005EC4B0, address);
}
