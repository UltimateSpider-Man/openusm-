#include "animation_controller.h"

#include "common.h"
#include "func_wrapper.h"
#include "oldmath_po.h"
#include "trace.h"

VALIDATE_SIZE(animation_controller, 0x10);

void animation_controller::get_camera_root_abs_po(po &arg0)
{
    TRACE("animation_controller::get_camera_root_abs_po");

    THISCALL(0x004A8990, this, &arg0);
}
