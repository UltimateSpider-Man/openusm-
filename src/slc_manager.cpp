#include "slc_manager.h"

#include "func_wrapper.h"
#include "utility.h"
#include "resource_key.h"
#include "resource_manager.h"
#include "script_manager.h"
#include "script_library_class.h"
#include "trace.h"
#include "variables.h"

Var<_std::vector<script_library_class *> *> slc_manager_class_array{0x00965EC8};

void register_standard_script_libs() {
    CDECL_CALL(0x005AB800);
}

void construct_client_script_libs() {
    CDECL_CALL(0x0058F9C0);
}

void chuck_register_script_libs()
{
    TRACE("chuck_register_script_libs");

    CDECL_CALL(0x0064EB60);
}

void slc_manager::init()
{
    TRACE("slc_manager::init");

    if constexpr (1) {
        if (slc_manager_classes == nullptr) {
            slc_manager_classes = new std::set<script_library_class *>{};
        }

        if (slc_manager_class_array() == nullptr)
        {
            slc_manager_class_array() = new _std::vector<script_library_class *>{};
        }

        register_standard_script_libs();
        chuck_register_script_libs();
        construct_client_script_libs();
    }
    else
    {
        CDECL_CALL(0x005AD720);
    }
}

void slc_manager::kill() {
    CDECL_CALL(0x005A5200);
}

script_library_class *slc_manager::get(const char *a1)
{
    assert(slc_manager_classes != nullptr);

    script_library_class v9{};
    v9.store_name(a1);
    auto it = slc_manager_classes->find(&v9);
    auto end = slc_manager_classes->end();
    if ( it == end )
    {
        return nullptr;
    }
    else
    {
        return (*it);
    }
}

void slc_manager::un_mash_all_funcs()
{
    TRACE("slc_manager::un_mash_all_funcs");

    assert(!script_manager::using_chuck_old_fashioned());
    assert(!g_is_the_packer());

    auto a1 = create_resource_key_from_path("all_slc_functions_mac", RESOURCE_KEY_TYPE_SLF);
    auto *image = (int *) resource_manager::get_resource(a1, nullptr, nullptr);
    assert(image != nullptr);

    assert(slc_manager_class_array() != nullptr);

    auto total_classes = image[0];
    auto *i = image + 1;

    assert(total_classes == slc_manager_class_array()->size());
    
    for ( auto &slc : (*slc_manager_class_array()))
    {
        auto v4 = *i;
        ++i;
        slc->total_funcs = v4;
        assert(slc->funcs == nullptr);

        if ( slc->total_funcs > 0 )
        {
            slc->funcs = (script_library_class::function **)i;
            i += slc->total_funcs;
            slc->field_1C |= 1u;
        }
    }
}

void slc_manager_patch()
{
    REDIRECT(0x0055C850, slc_manager::init);

    REDIRECT(0x0064FB00, slc_manager::un_mash_all_funcs);

    REDIRECT(0x005AD778, chuck_register_script_libs);
}
