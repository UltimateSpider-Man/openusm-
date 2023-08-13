#include "als_resource_handler.h"

#include "common.h"
#include "func_wrapper.h"
#include "trace.h"
#include "utility.h"
#include "resource_directory.h"
#include "worldly_pack_slot.h"
#include "mash_info_struct.h"
#include "als_animation_logic_system_shared.h"
#include "string_hash_dictionary.h"
#include "variables.h"

VALIDATE_SIZE(als_resource_handler, 0x14);

als_resource_handler::als_resource_handler(worldly_pack_slot *a2) {
    this->my_slot = a2;
    this->field_10 = RESOURCE_KEY_TYPE_ALS_FILE;
}

bool als_resource_handler::_handle(worldly_resource_handler::eBehavior a2,
                                          limited_timer *a3)
{
    TRACE("als_resource_handler::handle");

    return base_engine_resource_handler::_handle(a2, a3);
}

static constexpr auto handle_resource_hook = 1;

bool als_resource_handler::_handle_resource(worldly_resource_handler::eBehavior a2,
                                           resource_location *a3)
{
    TRACE("als_resource_handler::handle_resource", a3->field_0.get_platform_string(g_platform()).c_str());

    if constexpr (handle_resource_hook)
    {
        auto &v3 = this->my_slot->get_resource_directory();
        auto *resource = v3.get_resource(a3, nullptr);
        assert(resource != nullptr);

        auto *new_als = bit_cast<als::animation_logic_system_shared *>(resource);
        if ( a2 == UNLOAD )
        {
            new_als->destruct_mashed_class();
        }
        else
        {
            assert(new_als != nullptr);

#ifdef TARGET_XBOX
            mash_info_struct v5 {mash::UNMASH_MODE, resource, a3->m_size, true};
#else
            mash_info_struct v5 {resource, a3->m_size};
#endif

            v5.unmash_class(new_als, nullptr
#ifdef TARGET_XBOX
                , mash::NORMAL_BUFFER
#endif 
                    );

            mash_info_struct::construct_class(new_als);

#ifdef TARGET_XBOX
            a3->m_offset += v5.get_header_size();
#endif
        }

        ++this->field_C;
        return false;
    }
    else
    {
        return (bool) THISCALL(0x00568930, this, a2, a3);
    }
}

void als_resource_handler_patch()
{
    if constexpr (handle_resource_hook)
    {
        FUNC_ADDRESS(address, &als_resource_handler::_handle_resource);
        set_vfunc(0x00888A04, address);
    }

    {
        FUNC_ADDRESS(address, &als_resource_handler::_handle);
        set_vfunc(0x008889FC, address);
    }
}
