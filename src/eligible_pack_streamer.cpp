#include "eligible_pack_streamer.h"

#include "common.h"
#include "eligible_pack.h"
#include "eligible_pack_category.h"
#include "eligible_pack_token.h"
#include "func_wrapper.h"
#include "memory.h"
#include "resource_pack_streamer.h"
#include "utility.h"

#include <cassert>

VALIDATE_SIZE(eligible_pack_streamer, 0x38);

void eligible_pack_streamer::init(
    int a2,
    int num_streamers,
    resource_pack_streamer **streamers,
    bool(__cdecl **callbacks)(resource_pack_slot::callback_enum,
                              resource_pack_streamer *,
                              resource_pack_slot *,
                              limited_timer *),
    void(__cdecl *get_ideal_pack_info)(_std::vector<ideal_pack_info> *)) {
    //
    if constexpr (1) {
        this->clear();

        assert(get_ideal_pack_info != nullptr);

        this->get_ideal_pack_info_callback = get_ideal_pack_info;

        assert(num_streamers > 0);
        assert(streamers != nullptr);

        thiscall_call reserve = CAST(reserve, 0x0056E660);

        reserve(&this->field_14, num_streamers);
        {
            for (int i = 0; i < num_streamers; ++i) {
                eligible_pack_category *the_category = new eligible_pack_category{this,
                                                                                  streamers[i],
                                                                                  callbacks[i]};

                if (this->field_14.size() < this->field_14.capacity()) {
                    auto v13 = this->field_14.m_last;
                    *v13 = the_category;
                    this->field_14.m_last = v13 + 1;
                } else {
                    thiscall_call _Insert_n = CAST(_Insert_n, 0x0056A260);

                    _Insert_n(&this->field_14, this->field_14.m_last, 1, &the_category);
                }
            };
        }

    } else {
        THISCALL(0x00547C50, this, a2, num_streamers, streamers, callbacks, get_ideal_pack_info);
    }
}

void eligible_pack_streamer::clear() {
    THISCALL(0x00547BA0, this);
}

int compare_eligible_pack_names(const void *a1, const void *a2) {
    return CDECL_CALL(0x0050EC30, a1, a2);
}


eligible_pack *eligible_pack_streamer::find_eligible_pack_by_packfile_name_hash(string_hash a2)
{
    if constexpr (1)
    {
        for ( auto &ep : this->eligible_packs )
        {
            if ( a2 == ep->field_44 )
            {
                return ep;
            }

        }

        return nullptr;
    }
    else
    {
        assert(0);
    }

}

void eligible_pack_streamer::fixup_eligible_pack_parent_child_relationships() {
    for (auto &pack : this->eligible_packs) {
        pack->fixup_family(this);
    }
}

eligible_pack *eligible_pack_streamer::add_eligible_pack(const char *a2,
                                                         const eligible_pack_token &a3,
                                                         resource_pack_streamer *a4) {
    if constexpr (0)
    {
        eligible_pack_category *the_category = nullptr;

        for (auto &pack_cat : this->field_14) {
            if (pack_cat->my_resource_pack_streamer == a4) {
                the_category = pack_cat;
                break;
            }
        }

        assert(the_category != nullptr);

        auto *mem = mem_alloc(sizeof(eligible_pack));
        eligible_pack *v9 = new (mem) eligible_pack{a2, a3, the_category};

        if (this->eligible_packs.size() < this->eligible_packs.capacity()) {
            auto *v12 = this->eligible_packs.m_last;
            *v12 = v9;
            this->eligible_packs.m_last = v12 + 1;
        } else {
            thiscall_call _Insert_n = CAST(_Insert_n, 0x0056A260);

            _Insert_n(&this->eligible_packs, this->eligible_packs.m_last, 1, &v9);
        }

        auto v14 = this->eligible_packs.size();
        qsort(this->eligible_packs.m_first, v14, 4u, compare_eligible_pack_names);
        return v9;
    } else {
        return (eligible_pack *) THISCALL(0x00551290, this, a2, &a3, a4);
    }
}

void eligible_pack_streamer::prioritize() {
    THISCALL(0x00547D80, this);
}

void eligible_pack_streamer::frame_advance(Float a2) {
    if (this->field_0) {
        for (auto &ep_cat : this->field_14) {
            ep_cat->frame_advance(a2);
        }
    }
}

bool eligible_pack_streamer::sub_537F80() {
    if (!this->field_0) {
        return true;
    }

    auto v2 = this->field_14.m_first;
    auto v3 = this->field_14.m_last;
    if (v2 == v3) {
        return true;
    }

    while (1) {
        auto *v4 = (*v2)->my_resource_pack_streamer;
        if (v4->currently_streaming || v4->field_6C.m_size) {
            return false;
        }

        auto *v5 = v4->pack_slots;
        if (v5 != nullptr) {
            auto v6 = v5->m_first;
            for (auto i = v5->m_last; v6 != i; ++v6) {
                auto v8 = (*v6)->m_slot_state;
                if (v8) {
                    if (v8 != 4) {
                        return false;
                    }
                }
            }
        }

        if (++v2 == v3) {
            return true;
        }
    }
}

void eligible_pack_streamer_patch() {
    {
        FUNC_ADDRESS(address, &eligible_pack_streamer::init);
        REDIRECT(0x0055C4A5, address);
    }
}
