#include "eligible_pack_category.h"

#include "common.h"
#include "func_wrapper.h"
#include "resource_pack_streamer.h"

VALIDATE_SIZE(eligible_pack_category, 0x28);

eligible_pack_category::eligible_pack_category(eligible_pack_streamer *a2,
                                               resource_pack_streamer *a3,
                                               bool(__cdecl *a4)(resource_pack_slot::callback_enum,
                                                                 resource_pack_streamer *,
                                                                 resource_pack_slot *,
                                                                 limited_timer *)) {
    THISCALL(0x00543100, this, a2, a3, a4);
}

eligible_pack_category::~eligible_pack_category() {
    THISCALL(0x0053E640, this);
}

bool eligible_pack_category::is_pack_slot_locked(resource_pack_slot *a2)
{
    for ( auto &v1 : this->field_1C )
    {
        if ( v1 == a2 ) {
            return true;
        }
    }

    return false;
}

void eligible_pack_category::lock_pack_slot(resource_pack_slot *s)
{
    if ( s->is_pack_ready() ) {
        this->my_resource_pack_streamer->unload(s);
    }

    assert(!is_pack_slot_locked( s ));
    this->field_1C.push_back(s);
}

void eligible_pack_category::unlock_pack_slot(resource_pack_slot *s)
{
    assert(is_pack_slot_locked( s ) );

    assert(s->is_empty() || s->is_pack_unloading());

    {
        auto end = this->field_1C.end();
        auto it = this->field_1C.begin();
        while ( it != end )
        {
            if ( (*it) == s ) {
                it = this->field_1C.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void eligible_pack_category::frame_advance(Float a2) {
    THISCALL(0x005513B0, this, a2);
}
