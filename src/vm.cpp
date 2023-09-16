#include "vm.h"

#include "common.h"
#include "debug_render.h"
#include "debug_string.h"
#include "fe_mission_text.h"
#include "femanager.h"
#include "femultilinetext.h"
#include "func_wrapper.h"
#include "game.h"
#include "glass_house_manager.h"
#include "igofrontend.h"
#include "localized_string_table.h"
#include "log.h"
#include "resource_key.h"
#include "resource_pack_location.h"
#include "resource_manager.h"
#include "script_manager.h"
#include "trace.h"
#include "utility.h"

#include <script_executable.h>
#include <script_object.h>
#include <vm_thread.h>

VALIDATE_SIZE(vm_stack, 0x18C);

mString generate_pack_name(const char *a2, vm_stack &stack) {
    mString v6{stack.my_thread->inst->parent->parent->field_0.to_string()};

    mString a1a{0, "%s_%s", a2, v6.c_str()};

    a1a.truncate(32);
    mString v4{};

    resource_key_type type = RESOURCE_KEY_TYPE_NONE;
    resource_key::calc_resource_string_and_type_from_path(a1a.c_str(), &v4, &type);

    return v4;
}

bool slf__is_point_inside_glass_house__vector3d__t::operator()(
    vm_stack &a1, script_library_class::function::entry_t) {
    sp_log("is_point_inside_glass_house");

    auto *v5 = a1.SP - 12;
    a1.SP = v5;
    auto a1a = 0.0f;
    if (glass_house_manager::is_point_in_glass_house(*((const vector3d *) v5))) {
        a1a = 1.0;
    }

    a1.push((const char *) &a1a, 4);

    return 1;
}

bool slf__angle_between__vector3d__vector3d__t::operator()(vm_stack &stack,
                                                           script_library_class::function::entry_t) {
    auto *v4 = (vector3d *) (stack.SP - sizeof(vector3d) * 2);
    stack.SP = (char *) v4;
    auto a2a = compute_angle_between_vectors(*v4, *(v4 + 1));
    *(float *) stack.SP = a2a;
    stack.SP += 4;
    return true;
}

bool slf__set_mission_text__num__t::operator()(vm_stack &stack,
                                               script_library_class::function::entry_t) {
#if 1

    auto *v2 = (float *) (stack.SP - 4);
    stack.SP = (char *) v2;
    float *v3 = (float *) ((char *) v2 - (uint64_t) (*v2 * 4.0f));
    stack.SP = (char *) v3;
    auto *v4 = g_game_ptr()->field_7C->lookup_scripttext_string((uint64_t) *v3);
    mString a2a{v4};

    sp_log("%s", a2a.c_str());

    mString result_string{};

    auto v5 = a2a.find("%", 0);
    auto v6 = (v5 == -1) - 2;
    if (v5 != -1) {
        auto v7 = v3 + 1;
        do {
            auto v8 = a2a.substr(v6 + 2, v5 - v6 - 2);
            sp_log("%s", v8.c_str());

            result_string += v8;
            sp_log("result_string: %s", result_string.c_str());

            switch (a2a.c_str()[v5 + 1]) {
            case '%':
                result_string.append("%");
                break;
            case 'd': {
                mString v9 = mString::from_int((uint64_t) *v7);

                result_string += v9;

                ++v7;
                break;
            }
            case 'f': {
                mString v10{*v7};

                result_string += v10;

                ++v7;
                break;
            }
            case 's': {
                auto v11 = g_game_ptr()->field_7C->lookup_scripttext_string((uint64_t) *v7);
                result_string.append(v11);
                ++v7;
                break;
            }
            case 'z': {
                result_string.append(*bit_cast<const char **>(v7));
                ++v7;
                break;
            }
            default:
                break;
            }

            v6 = v5;
            if (v5 + 2 >= a2a.size()) {
                break;
            }

            v5 = a2a.find("%", v5 + 2);
        } while (v5 != -1);
    }

    if (v6 == -1) {
        result_string = a2a;

    } else if (v6 + 2 < a2a.size()) {
        auto v12 = a2a.substr(v6 + 2, 0xFFFFFFFF);

        result_string += v12;
    }

    mString v14{result_string.c_str()};

    result_string = FEMultiLineText::ReplaceEndlines(v14).c_str();

    sp_log("result_string: %s", result_string.c_str());

    mString temp_string{result_string.c_str()};

    g_femanager().IGO->field_20->set_text(*bit_cast<fe_mission_text::string *>(&temp_string));
    g_femanager().IGO->field_20->SetShown(1);

    return true;
#else
    return (bool) THISCALL(0x00672C00, this, &stack, a2);
#endif
}

bool slf__bring_up_dialog_box_title__num__num__num__t::operator()(
    vm_stack &stack, script_library_class::function::entry_t a2) {
    sp_log("script_library_class::function::entry_t: %d", a2);

    return (bool) THISCALL(0x00673240, this, &stack, a2);
}

bool slf__set_mission_text_box_flavor__num__t::operator()(vm_stack &a1,
                                                          script_library_class::function::entry_t) {
    auto num = a1.pop_num();

    sp_log("num = %d %f", num, num);

    g_femanager().IGO->field_20->set_flavor(num);
    return true;
}

bool __stdcall slf__get_pack_size__str__t__cl(vm_stack *a1, int v40)
{
    TRACE("slf__get_pack_size__str__t__cl");

    auto v3 = a1->SP - 4;
    a1->SP = v3;
    auto out_key = create_resource_key_from_path(*(const char **)v3, RESOURCE_KEY_TYPE_PACK);
    resource_pack_location a2{};
    resource_manager::get_pack_file_stats(out_key, &a2, nullptr, nullptr);
    auto v4 = (double)a2.loc.m_size;
    if ( a2.loc.m_size < 0 )
    {
        v4 += 4.2949673e9;
    }

    float a1a = v4;
    *(float *)a1->SP = a1a;
    a1->SP += 4;
    return true;
}

bool __stdcall slf__add_3d_debug_str__vector3d__vector3d__num__str__t__cl(vm_stack *a2, int _7C)
{
    TRACE("slf__add_3d_debug_str__vector3d__vector3d__num__str__t::operator()");

    a2->SP += -32;
    struct {
        vector3d field_0;
        vector3d field_C;
        float field_18;
        const char *field_1C;
    } *a3 = CAST(a3, a2->SP);

    mString v9 {a3->field_1C};
    auto v8 = a3->field_18;
    uint8_t v7 = (a3->field_C[2] * 255.0);
    uint8_t v6 = (a3->field_C[1] * 255.0);
    uint8_t v3 = (a3->field_C[0] * 255.0);
    color32 v4 {v3, v6, v7, 255};
    add_3d_debug_str(a3->field_0, v4, v8, v9);
    return 1;
}

void vm_patch()
{
    SET_JUMP(0x00676D70, slf__get_pack_size__str__t__cl);

    {
        set_vfunc(0x0089A854, slf__add_3d_debug_str__vector3d__vector3d__num__str__t__cl);
    }

#if 0
    {
        FUNC_ADDRESS(address, &slf__bring_up_dialog_box_title__num__num__num__t::operator());
        set_vfunc(0x0089BC34, address);
    }

    {
        FUNC_ADDRESS(address, &slf__set_mission_text_box_flavor__num__t::operator());
        set_vfunc(0x0089BC68, address);
    }

    {
        FUNC_ADDRESS(address, &slf__is_point_inside_glass_house__vector3d__t::operator());
        set_vfunc(0x0089A544, address);
    }
#endif

    {
        FUNC_ADDRESS(address, &slf__set_mission_text__num__t::operator());
        //set_vfunc(0x0089BBFC, address);
    }
}
