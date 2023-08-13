#include "beam.h"

#include "camera.h"
#include "debug_render.h"
#include "func_wrapper.h"
#include "game.h"
#include "geometry_manager.h"
#include "local_collision.h"
#include "ngl.h"
#include "ngl_dx_vertexdef.h"
#include "pcuv_shadermaterial.h"
#include "trace.h"

#include <cmath>

beam::beam()
{

}

void beam::_render(Float a1)
{
    TRACE("beam::render");

    THISCALL(0x005406D0, this, a1);
}

void beam::frame_advance_all_beams(Float a3) {
    CDECL_CALL(0x0051CED0, a3);
}

bool sub_CB3D60(unsigned int a5) {
    nglCreateMesh(0x40000, a5, 0, nullptr);
    assert(nglScratch() != nullptr);
    return (nglScratch() != nullptr);
}

void sub_78EA60(vector3d &a1, float a2) {
    auto v4 = a1.length2();
    if (v4 > (0.0000099999997 * 0.0000099999997)) {
        auto v3 = [](float a1) {
            return 1.0 / std::sqrt(a1);
        }(v4) * a2;

        a1 *= v3;
    }
}

void sub_CB4800(const vector3d &a1, const vector3d &arg4, int a3, float a4, void *a6)
{
    auto v44 = arg4 - a1;
    auto a3a = v44.length2();
    if (a3a >= 9.9999997e-10) {
        a3a = std::sqrt(a3a);
        auto v42 = v44 / a3a;

        auto camera_pos = g_game_ptr()->get_current_view_camera(0)->get_abs_position();

        auto v40 = camera_pos - a1;
        auto v39 = camera_pos - arg4;
        auto v38 = v40.length2();
        auto v37 = v39.length2();

        auto sub_6BAED0 = [](float a1) { return 1.0 / std::sqrt(a1); };

        if (v38 != 0.0) {
            auto v17 = 0.5 * a4;

            v40 *= sub_6BAED0(v38) * v17;
        }

        if (v37 != 0.0) {
            auto v18 = 0.5 * a4;
            v39 *= sub_6BAED0(v37) * v18;
        }

        v40 += a1;
        v39 += arg4;

        auto sub_CB4C90 = [](float a1) {
            return 1.0 - 0.75 / ((0.25 * 0.25) * a1 + 1.0);
        };

        auto v36 = sub_CB4C90(v38);
        auto v35 = sub_CB4C90(v37);
        auto v5 = a1 + arg4;
        auto v6 = v5 * 0.5;
        auto v34 = v6 - camera_pos;
        auto v33 = vector3d::cross(v34, v42);
        if (v33.length2() >= 9.9999997e-10 || geometry_manager::is_scene_analyzer_enabled()) {
            sub_78EA60(v33, a4 * 0.5);
            vector3d v32{};
            vector3d v31{};
            vector3d v30{};
            vector3d a4a{};
            auto v7 = v33 * v36;
            v32 = v40 - v7;

            auto v9 = v33 * v36;
            v31 = v40 + v9;

            auto v11 = v33 * v35;
            v30 = v39 + v11;

            auto v13 = v33 * v35;
            a4a = v39 - v13;
            sub_CB3F80(v32, v31, v30, a4a, a3, a6);
        }
    }
}

void beam_patch()
{
    {
        FUNC_ADDRESS(address, &beam::_render);
        set_vfunc(0x00889B9C, address);
    }
}
