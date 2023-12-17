#include "scripted_trans_group.h"

#include "als_basic_rule_data.h"
#include "als_request_data.h"
#include "als_transition_rule.h"
#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"

namespace als
{
VALIDATE_SIZE(scripted_trans_group, 0x40u);

scripted_trans_group::scripted_trans_group()
{
    THISCALL(0x004AC950, this);
}

void scripted_trans_group::_unmash(mash_info_struct *a1, void *)
{
    TRACE("scripted_trans_group::unmash");

    a1->unmash_class_in_place(this->field_4, this);

    a1->unmash_class_in_place(this->field_14, this);

    a1->unmash_class_in_place(this->field_28, this);

#ifdef TARGET_XBOX
    {
    uint8_t class_mashed = -1;
    class_mashed = *a1->read_from_buffer(mash::SHARED_BUFFER, 1, 1);
    assert(class_mashed == 0xAF || class_mashed == 0);
    }
#endif

    if ( this->field_3C != nullptr )
    {
    a1->unmash_class(this->field_3C, this
#ifdef TARGET_XBOX
        , mash::NORMAL_BUFFER
#endif
            );
    }
}

bool scripted_trans_group::check_transition(
        request_data &data,
        scripted_trans_group::transition_type a3,
        als_data a4,
        string_hash a5)
{
    TRACE("scripted_trans_group::check_transition");

    if constexpr (0) {
        if ( test_all_trans_groups(data, &this->field_4, a3, a4, a5) ) {
            return true;
        }

        if ( a3 == 0 )
        {
            int v13 = 0;
            if ( this->field_14.m_size > 0 )
            {
                while ( !bit_cast<basic_rule_data *>(this->field_14.at(v13))->can_transition(a4) )
                {
                    if ( ++v13 >= this->field_14.m_size ) {
                        return false;
                    }
                }

                auto v14 = v13;
                this->field_14.at(v14)->field_14.process_action(data);
                if ( this->field_14.m_data[v14]->field_20 != nullptr )
                {
                    data.field_10 = static_cast<transition_type>(0);
                    data.field_C = int(&this->field_14.m_data[v14]);
                }
            }

            return false;
        }

        if ( a3 == 1 )
        {
            int v10 = 0;
            if ( this->field_28.size() > 0 )
            {
                while ( 1 )
                {
                    auto *v11 = this->field_28.m_data[v10];
                    if ( a5 == v11->field_24 && bit_cast<als::basic_rule_data *>(v11)->can_transition(a4) ) {
                        break;
                    }

                    if ( ++v10 >= this->field_28.m_size ) {
                        return false;
                    }
                }

                auto v12 = v10;
                this->field_28.at(v12)->field_14.process_action(data);
                if ( this->field_28.at(v12)->field_20 != nullptr )
                {
                    data.field_10 = static_cast<transition_type>(1);
                    data.field_C = int(&this->field_28.m_data[v12]);
                    return false;
                }
            }
            return false;
        }

        if ( a3 != 2 ) {
            return false;
        }

        auto *v8 = this->field_3C;
        if ( v8 == nullptr ) {
            return false;
        }

        auto v9 = 0;

        if ( v8->m_size <= 0 ) {
            return false;
        }

        do
        {
            if ( v8->at(v9)->can_transition(a4) ) {
                this->field_3C->at(v9)->field_8.process_action(data);
            }

            v8 = this->field_3C;
            ++v9;
        }
        while ( v9 < v8->m_size );

        return false;
    } else {
        return (bool) THISCALL(0x004A0090, this, &data, a3, a4, a5);
    }
}

}


void als_scripted_trans_group_patch()
{
    {
        FUNC_ADDRESS(address, &als::scripted_trans_group::_unmash);
        set_vfunc(0x0087E1BC, address);
    }
}
