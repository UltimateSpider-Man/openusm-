#include "event_type.h"

#include "binary_search_array_cmp.h"
#include "common.h"
#include "event_callback.h"
#include "event_recipient_entry.h"
#include "event_type.h"
#include "func_wrapper.h"

VALIDATE_SIZE(event_type, 0x2C);

event_type::event_type(string_hash a2, bool a3) {
    THISCALL(0x004E18B0, this, a2, a3);
}

event_recipient_entry * event_type::sub_4EE580(entity_base_vhandle a2)
{
    int a5 = -1;
    if ( !this->field_18 )
    {
        std::sort(this->field_8.begin(), this->field_8.end());
        this->field_18 = true;
    }

    auto v7 = this->field_8.size();

    if ( binary_search_array_cmp<entity_base_vhandle, event_recipient_entry *>(
            &a2,
            &this->field_8[0],
            0,
            v7,
            &a5,
            compare_deref<entity_base_vhandle, event_recipient_entry *>) )
    {
        return this->field_8[a5];
    }
    else
    {
        return nullptr;
    }
}

event_recipient_entry * event_type::create_recipient_entry(entity_base_vhandle a2)
{
    if constexpr (0)
    {
        auto *ret_val = this->sub_4EE580(a2);
        if ( ret_val == nullptr )
        {
            ret_val = new event_recipient_entry {a2, false};
            assert(ret_val != nullptr);

            if ( ret_val != nullptr )
            {
                this->field_8.push_back(ret_val);
                this->field_18 = false;
            }
        }

        return ret_val;
    }
    else
    {
        return (event_recipient_entry *) THISCALL(0x004EE620, this, a2);
    }
}

void event_type::raise_event(entity_base_vhandle a2, event *a3)
{
    if constexpr (0)
    {}
    else
    {
        THISCALL(0x004EE6C0, this, a2, a3);
    }
}

bool event_type::callback_exists(int a2) const
{
    if ( a2 == 0 ) {
        return false;
    }

    for ( auto &v1 : this->field_1C )
    {
        if (v1->id == a2 ) {
            return true;
        }
    }

    for ( auto &v1 : this->field_8 )
    {
        if (v1->callback_exists(a2)) {
            return true;
        }
    }

    return false;
}
