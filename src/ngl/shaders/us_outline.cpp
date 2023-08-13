#include "us_outline.h"

#include <ngl_dx_shader.h>

#include "func_wrapper.h"
#include "utility.h"
#include "variable.h"

void sub_411830() {
    int i = 0;

    static Var<IDirect3DPixelShader9 *> dword_970770{0x00970770};
    //static Var<const DWORD *> off_939CD8{0x00939CD8};

    {
        static const char text[] =
            "tex t0\n"
            "mul r0, t0, c0\n";

        nglCreatePShader(&(&dword_970770())[i++], text);
    }

    {
        static const char text[] = "mov r0, c0\n";
        nglCreatePShader(&(&dword_970770())[i++], text);
    }
}

void us_outline_patch() {
    REDIRECT(0x004118D9, sub_411830);
}
