#include "mouselook_controller.h"

#include "camera.h"
#include "common.h"
#include "dolly_and_strafe_mcs.h"
#include "func_wrapper.h"
#include "input_mgr.h"
#include "theta_and_psi_mcs.h"
#include "trace.h"

VALIDATE_SIZE(mouselook_controller, 0x18u);

Var<mouselook_controller *> g_mouselook_controller{0x0095C17C};

mouselook_controller::mouselook_controller(
        dolly_and_strafe_mcs *a2,
        theta_and_psi_mcs *a3,
        camera *a4)
{
    this->field_8 = a2;
    this->m_vtbl = 0x00889114;
    this->field_C = a3;
    this->field_10 = a4;
    this->field_14 = input_mgr::instance()->field_58;
}

void mouselook_controller::reset()
{
    auto *v1 = this->field_C;
    if ( v1 != nullptr ) {
        v1->reset_angles();
    }
}

void mouselook_controller::_frame_advance(Float a2)
{
    TRACE("mouselook_controller::frame_advance");

    if constexpr (0)
    {}
    else
    {
        THISCALL(0x00528BB0, this, a2);
    }
}
