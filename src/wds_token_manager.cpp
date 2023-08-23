#include "wds_token_manager.h"

#include "func_wrapper.h"
#include "mash_info_struct.h"
#include "resource_manager.h"
#include "script_manager.h"
#include "terrain.h"
#include "token_def.h"
#include "token_def_list.h"
#include "trace.h"
#include "utility.h"
#include "wds.h"

#include <cassert>

void wds_token_manager_region_change_callback(bool a1, region *a2) {
    CDECL_CALL(0x00558660, a1, a2);
}

void wds_token_manager::initialize(const resource_key &a2) {
    TRACE("wds_token_manager::initialize", a2.get_platform_string(3).c_str());

    if constexpr (1) {
        assert(tokens == nullptr);
        assert(g_world_ptr() != nullptr);

        this->field_8 = 0.0;
        auto *the_terrain = g_world_ptr()->get_the_terrain();

        int size;
        auto *res = resource_manager::get_resource(a2, &size, nullptr);

        if (res != nullptr) {

            {
                if (mString {"CITY_ARENA.TOKENS"} == a2.get_platform_string(3)) {
                    assert(16948 == size);
                }
            }

#ifndef TARGET_XBOX
            mash_info_struct info_struct{res, size};
#else
            mash_info_struct info_struct {mash::UNMASH_MODE, res, size, true};
#endif

            info_struct.unmash_class(this->tokens, nullptr
#ifdef TARGET_XBOX
            , mash::NORMAL_BUFFER
#endif 
                    );

            mash_info_struct::construct_class(this->tokens);

            this->field_C = (int) script_manager::get_game_var_address(mString{"gv_token_tally"},
                                                                       nullptr,
                                                                       nullptr);

            this->token_collected_array = (int)
                script_manager::get_game_var_address(mString{"gv_token_collected"},
                                                     nullptr,
                                                     nullptr);

            the_terrain->register_region_change_callback(wds_token_manager_region_change_callback);
            region *v15 = nullptr;
            for (int i = 0; i < this->tokens->field_0.m_size; ++i) {
                auto *def = this->tokens->field_0.m_data[i];
                v15 = the_terrain->find_region(def->field_10, v15);
                if (v15 == nullptr) {
                    sp_log("Token was placed outside of world < %f, %f, %f >",
                           def->field_10[0],
                           def->field_10[1],
                           def->field_10[2]);

                    assert(0);
                }

                def->field_28 = v15;
            }

            this->field_4 = 0;
        } else {
            auto str = a2.m_hash.to_string();

            sp_log("Could not find token resource %s", str);

            assert(0);
        }

    } else {
        THISCALL(0x005586A0, this, &a2);
    }
}

void wds_token_manager::frame_advance(Float a1) {
    THISCALL(0x00555B50, this, a1);
}

void wds_token_manager_patch()
{
    {
        FUNC_ADDRESS(address, &wds_token_manager::initialize);
        REDIRECT(0x0055B377, address);
    }

    {
        FUNC_ADDRESS(address, &token_def_list::unmash);
        REDIRECT(0x005587B3, address);
    }
}
