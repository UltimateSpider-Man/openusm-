#include "als_meta_anim_table_shared.h"
#include "als_nal_meta_anim.h"
#include "common.h"
#include "func_wrapper.h"
#include "trace.h"

namespace als {

    VALIDATE_SIZE(als_meta_anim_table_shared, 0x18);

    void als_meta_anim_table_shared::unmash(mash_info_struct *a1, void *a3)
    {
        a1->unmash_class_in_place(this->field_0, this);
    }

    als_nal_meta_anim *als_meta_anim_table_shared::get_nal_meta_anim(
            string_hash a2,
            actor *a3) const {
        TRACE("als_meta_anim_table_shared::get_nal_meta_anim");

        if constexpr (1) {

            if constexpr (0) {
                for ( auto i = 0; i < this->field_0.size(); ++i )
                {
                    auto &v5 = this->field_14[i].field_8;
                    sp_log("%s", v5.to_string());
                }
            }

            for ( auto i = 0; i < this->field_0.size(); ++i )
            {

#if 0
                auto &v4 = a2.source_hash_code;
                auto &v5 = this->field_14[i].field_8;

                if ( v4 == v5.m_hash )
#else

                if ( string_hash {"ULTIMATE_SPIDERMAN"} == a2 )
#endif
                {

                    if ( this->field_14[i].is_delay_create() ) {
                        this->field_14[i].delay_create(a3);
                    }

                    auto *v7 = &this->field_14[i];
                    return v7;
                }

                ++i;
            }

            return nullptr;
            
        } else {
            return (als_nal_meta_anim *) THISCALL(0x004992B0, this, a2, a3);
        }
    }
}
