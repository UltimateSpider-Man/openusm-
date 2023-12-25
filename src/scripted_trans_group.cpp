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
        scripted_trans_group::transition_type trans_type,
        als_data a4,
        string_hash a5) const
{
    TRACE("scripted_trans_group::check_transition");

    sp_log("transition_type = %d", trans_type);

    if constexpr (0) {
        if ( test_all_trans_groups(data, this->field_4, trans_type, a4, a5) ) {
            return true;
        }

        switch (trans_type) {
        case IMPLICIT: {
            auto begin = this->field_14.m_data;
            auto end = begin + this->field_14.size();
            auto it = std::find_if(begin, end, [&a4](auto &trans_rule)
            {
                return trans_rule->can_transition(a4);
            });

            if (it != end) {
                (*it)->field_0.field_14.process_action(data);
                if ( (*it)->field_0.has_post_action() )
                {
                    data.field_10 = trans_type;
                    data.field_C = int(&(*it));
                }
            }

            break;
        }
        case EXPLICIT: {
            for (int i = 0; i < this->field_28.size(); ++i) 
            {
                auto *v11 = this->field_28.at(i);
                if ( v11->can_transition(a4, a5) ) {
                    v11->field_0.field_14.process_action(data);
                    if ( v11->field_0.has_post_action() )
                    {
                        data.field_10 = trans_type;
                        data.field_C = int(&v11);
                    }

                    break;
                }
            }

            break;
        }
        case LAYER: {
            if ( this->field_3C != nullptr ) {
                for (int i = 0; i < this->field_3C->size(); ++i )
                {
                    auto *trans_rule = this->field_3C->at(i);
                    if ( trans_rule->can_transition(a4) ) {
                        trans_rule->field_8.process_action(data);
                    }
                }
            }

            break;
        }
        default:
            assert(0 && "Unknown type specified for trans group.");
            break;
        }

        return false;
    } else {
        return (bool) THISCALL(0x004A0090, this, &data, trans_type, a4, a5);
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
