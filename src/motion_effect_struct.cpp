#include "motion_effect_struct.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(motion_effect_struct, 0x30u);

motion_effect_struct::motion_effect_struct(entity_base_vhandle a2, const mString &a3) {
    THISCALL(0x004DC560, this, a2, &a3);
}

motion_effect_struct::~motion_effect_struct() {
    THISCALL(0x004E56D0, this);
}

void motion_effect_struct::render_all_motion_fx(camera &a2, hull &a3)
{
    CDECL_CALL(0x004EFB20, &a2, &a3);
}

void motion_effect_struct::render_trail(vector3d a1,
                                        vector3d a4,
                                        vector3d a7,
                                        vector2d a10,
                                        vector2d a12,
                                        vector2d a14,
                                        color32 a16,
                                        color32 a17,
                                        color32 a18,
                                        bool a19,
                                        vector3d a20,
                                        vector3d a23) {
    THISCALL(0x004DC820, this, a1, a4, a7, a10, a12, a14, a16, a17, a18, a19, a20, a23);
}

void motion_effect_struct::record_all_motion_fx(Float a1) {
    CDECL_CALL(0x004EFA50, a1);
}
