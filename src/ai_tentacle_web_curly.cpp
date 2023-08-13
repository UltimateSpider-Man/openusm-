#include "ai_tentacle_web_curly.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(ai_tentacle_web_curly, 0x54);

ai_tentacle_web_curly::ai_tentacle_web_curly(ai_tentacle_info *a2)
    : ai_tentacle_dangle::ai_tentacle_dangle(a2) {
    if constexpr (1) {
        this->m_vtbl = 0x0087F1A4;
        this->field_24 = 0;
        this->field_2C = {};
    } else {
        THISCALL(0x00483DE0, this, a2);
    }
}

void ai_tentacle_web_curly::reset_curl() {
    this->field_50 = -1;
}

void ai_tentacle_web_curly::setup(vhandle_type<actor> a2, entity_base *a3) {
    THISCALL(0x00487470, this, a2, a3);
}
