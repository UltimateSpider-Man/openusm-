#include "eligible_pack_category.h"

#include "common.h"
#include "func_wrapper.h"

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

void eligible_pack_category::frame_advance(Float a2) {
    THISCALL(0x005513B0, this, a2);
}
