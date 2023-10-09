#include "slc_manager.h"

#include "func_wrapper.h"
#include "utility.h"
#include "resource_key.h"
#include "resource_manager.h"
#include "script_manager.h"
#include "script_library_class.h"
#include "trace.h"
#include "variables.h"

#if !SLC_MANAGER_STANDALONE
Var<_std::vector<script_library_class *> *> slc_manager_class_array{0x00965EC8};
#else

static std::vector<script_library_class *> *g_slc_manager_class_array {nullptr};
Var<std::vector<script_library_class *> *>
    slc_manager_class_array {(int) &g_slc_manager_class_array};

#endif

void register_standard_script_libs() {
    CDECL_CALL(0x005AB800);
}

void construct_client_script_libs() {
    CDECL_CALL(0x0058F9C0);
}

void destruct_client_script_libs()
{
    CDECL_CALL(0x0058FA50);
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

        if (slc_manager_class_array() == nullptr) {
            using slc_manager_class_array_t = std::decay_t<decltype(*slc_manager_class_array())>;
            slc_manager_class_array() = new slc_manager_class_array_t {};
        }

        register_standard_script_libs();
        chuck_register_script_libs();
        construct_client_script_libs();
    }
    else
    {
        CDECL_CALL(0x005AD720);
    }

    if constexpr (0) {
        uint32_t i {0};
        for (auto &slc : (*slc_manager_class_array())) {
            printf("slc: %u %s\n", i++, slc->get_name());
        }
        assert(0);
    }
}

void slc_manager::add(script_library_class *slc)
{
    TRACE("slc_manager::add");

    assert(slc_manager_classes != nullptr);
    auto ret = slc_manager_classes->insert(slc);
    if ( !ret.second ) {
        auto name = slc->get_name();
        sp_log("slc already exists %s", name);
        assert(0);
    }

    assert(slc_manager_class_array() != nullptr);
    slc_manager_class_array()->push_back(slc);
}

void slc_manager::kill() {
    TRACE("slc_manager::kill");

    if constexpr (1) {
        destruct_client_script_libs();
        if ( slc_manager_class_array() != nullptr ) {
            for ( auto &slc : (*slc_manager_class_array()) ) {
                if ( slc != nullptr ) {
                    delete slc;
                }
            }

            if ( slc_manager_class_array() != nullptr ) {
                delete slc_manager_class_array();
            }

            slc_manager_class_array() = nullptr;
        }
    } else {
        CDECL_CALL(0x005A5200);
    }
}

script_library_class *slc_manager::get_class(int class_index)
{
    assert(slc_manager_class_array() != nullptr);

    assert(class_index >= 0);

    assert(class_index < slc_manager_class_array()->size());

    return slc_manager_class_array()->at(class_index);
}

script_library_class *slc_manager::get(const char *a1)
{
    assert(slc_manager_classes != nullptr);

    script_library_class v9{};
    v9.store_name(a1);
    auto it = slc_manager_classes->find(&v9);
    auto end = slc_manager_classes->end();
    if ( it != end ) {
        return (*it);
    }

    return nullptr;
}

void slc_manager::un_mash_all_funcs()
{
    TRACE("slc_manager::un_mash_all_funcs");

    assert(!script_manager::using_chuck_old_fashioned());
    assert(!g_is_the_packer());

    auto a1 = create_resource_key_from_path("all_slc_functions_mac", RESOURCE_KEY_TYPE_SLF);
    sp_log("%s", a1.get_platform_string(3).c_str());

    auto *image = bit_cast<char *>(resource_manager::get_resource(a1, nullptr, nullptr));
    assert(image != nullptr);

    assert(slc_manager_class_array() != nullptr);

    auto total_classes = bit_cast<int *>(image)[0];
    auto *buffer = image + 4;

    assert(total_classes == slc_manager_class_array()->size());
    
    for ( auto &slc : (*slc_manager_class_array()) ) {
        slc->total_funcs = bit_cast<int *>(buffer)[0];
        buffer += 4;
        assert(slc->funcs == nullptr);

        if ( slc->total_funcs > 0 ) {
            slc->funcs = CAST(slc->funcs, buffer);
            buffer += 4 * slc->total_funcs;
            slc->field_1C |= 1u;
        }
    }
}

void slc_manager_patch()
{
    SET_JUMP(0x005AD720, slc_manager::init);

    SET_JUMP(0x005A5200, slc_manager::kill);

    SET_JUMP(0x005A5280, slc_manager::add);

    SET_JUMP(0x0059EC00, slc_manager::un_mash_all_funcs);

    REDIRECT(0x005AD778, chuck_register_script_libs);
}
