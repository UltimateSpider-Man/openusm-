#pragma once

#include <cstdint>

#include "script_library_class.h"
#include <vm_stack.h>

#include <vector.hpp>

struct mString;
struct script_instance;

struct slf__is_point_inside_glass_house__vector3d__t {
    std::intptr_t m_vtbl;

    //0x00661F70
    bool operator()(vm_stack &a1, script_library_class::function::entry_t);
};

struct slf__angle_between__vector3d__vector3d__t {
    std::intptr_t m_vtbl;

    //0x00672070
    //virtual
    bool operator()(vm_stack &stack, script_library_class::function::entry_t a2);
};

struct slf__set_mission_text__num__t : script_library_class::function {
    //0x00672C00
    //virtual
    bool operator()(vm_stack &stack, script_library_class::function::entry_t a2);
};

struct slf__bring_up_dialog_box_title__num__num__num__t {
    std::intptr_t m_vtbl;

    //0x00673240
    //virtual
    bool operator()(vm_stack &stack, script_library_class::function::entry_t a2);
};

struct slf__set_mission_text_box_flavor__num__t {
    //0x00673640
    //virtual
    bool operator()(vm_stack &stack, script_library_class::function::entry_t);
};

//0x00660500
extern mString *generate_pack_name(mString *out, const char *a2, vm_stack &stack);

extern void vm_patch();
