#include "mic.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(mic, 0x80);

mic::mic(entity *a2, const string_hash &a3) : entity(a3, 0) {
    float *ZEROVEC_5 = bit_cast<float *>(0x0095C968);

    if (a2 != nullptr) {
        this->set_parent(a2);
    }

    float *v4 = this->field_68;
    v4[0] = ZEROVEC_5[0];
    v4[1] = ZEROVEC_5[1];
    v4[2] = ZEROVEC_5[2];

    v4 = this->field_74;
    v4[0] = ZEROVEC_5[0];
    v4[1] = ZEROVEC_5[1];
    v4[2] = ZEROVEC_5[2];
}

void mic::frame_advance(Float a2) {
    THISCALL(0x0051D9A0, this, a2);
}
