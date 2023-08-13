#include "static_region_list_methods.h"

#include "common.h"
#include "func_wrapper.h"
#include "scratchpad_stack.h"
#include "stack_allocator.h"
#include "variables.h"

VALIDATE_SIZE(static_region_list_methods, 0x4);

void static_region_list_methods::init() {
    CDECL_CALL(0x00513F90);
}

void static_region_list_methods::term() {
    if constexpr (1) {
        scratchpad_stack::stk().current -= (scratchpad_stack::stk().alignment + 63) &
            ~(scratchpad_stack::stk().alignment - 1);

        if (scratchpad_stack::stk().current == scratchpad_stack::stk().segment) {
            tlScratchpadLocked() = false;
        }

        scratchpad() = nullptr;
    } else {
        CDECL_CALL(0x00513FF0);
    }
}

int static_region_list_methods::traverse_sphere(const subdivision_node &a2,
                                                const vector3d &arg4,
                                                float a4,
                                                subdivision_visitor &a3) {
    traverse_test a1;

    a1.field_0 = 0;
    a1.field_4 = arg4;
    a1.field_10 = a4;

    return this->traverse_using_test(a1, a2, a3);
}

int static_region_list_methods::traverse_all(const subdivision_node &a2,
                                             subdivision_visitor &a3,
                                             bool) {
    traverse_test a1;

    static Var<vector3d> ZEROVEC_5{0x0095C968};

    a1.field_0 = 2;
    a1.field_4 = ZEROVEC_5();
    a1.field_10 = 0.0;
    return this->traverse_using_test(a1, a2, a3);
}

int static_region_list_methods::traverse_line_segment(const subdivision_node &a2,
                                                      const vector3d &,
                                                      const vector3d &,
                                                      subdivision_visitor &visitor) {
    return this->traverse_all(a2, visitor, false);
}

int static_region_list_methods::traverse_point(const subdivision_node &a1,
                                               const vector3d &a2,
                                               subdivision_visitor &a3) {
    traverse_test v6;
    v6.field_0 = 1;
    v6.field_4 = a2;
    v6.field_10 = 0.0;
    return this->traverse_using_test(v6, a1, a3);
}

int static_region_list_methods::traverse_using_test(const traverse_test &a1,
                                                    const subdivision_node &a2,
                                                    subdivision_visitor &a3) {
    return THISCALL(0x00513E50, this, &a1, &a2, &a3);
}
