#include "script_executable.h"

#include "func_wrapper.h"

#include "filespec.h"
#include "chunk_file.h"
#include "chuck_str.h"
#include "memory.h"
#include "script_manager.h"
#include "script_object.h"
#include "trace.h"
#include "common.h"
#include "parse_generic_mash.h"
#include "resource_key.h"
#include "utility.h"
#include "vm_executable.h"

VALIDATE_SIZE(script_executable, 0x5Cu);

script_executable::script_executable() {}

void script_executable::constructor_common()
{
    THISCALL(0x005AFC50, this);
}

bool script_executable::has_threads() {
    return (bool) THISCALL(0x0059BBA0, this);
}

constexpr auto SCRIPT_EXECUTABLE_FLAG_LINKED = 1u;
constexpr auto SCRIPT_EXECUTABLE_FLAG_FROM_MASH = 2u;
constexpr auto SCRIPT_EXECUTABLE_FLAG_UN_MASHED = 4u;

void script_executable::quick_un_mash()
{
    TRACE("script_executable::quick_un_mash");

    assert(( flags & SCRIPT_EXECUTABLE_FLAG_UN_MASHED ) != 0);

    assert(( flags & SCRIPT_EXECUTABLE_FLAG_LINKED ) != 0);

    assert(( flags & SCRIPT_EXECUTABLE_FLAG_FROM_MASH ) != 0);

    this->constructor_common();
    for ( auto i = 0; i < this->total_script_objects; ++i )
    {
        this->script_objects[i]->sub_5AB420();
    }
}

void script_executable::un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, [[maybe_unused]] void *a5)
{
    this->un_mash(a2, a3, a4);
}

script_object *script_executable::find_object(int index) const {
    assert(index >= 0);

    assert(index < total_script_objects);

    assert(script_objects_by_name != nullptr);

    return this->script_objects_by_name[index];
}

void script_executable::un_mash(generic_mash_header *header, void *a3, generic_mash_data_ptrs *a4)
{
    TRACE("script_executable::un_mash");

    if constexpr (1)
    {
        if ( (this->flags & SCRIPT_EXECUTABLE_FLAG_UN_MASHED) != 0 )
        {
            this->quick_un_mash();
        }
        else
        {
            assert(script_object_dummy_list == nullptr);
            
            if ( int v6 = 4 - ((int)a4->field_0 % 4);
                    v6 < 4 )
            {
                a4->field_0 += v6;
            }

            this->sx_exe_image = CAST(this->sx_exe_image, a4->field_0);
            a4->field_0 += this->sx_exe_image_size;
            auto v9 = 4 - (bit_cast<uint32_t>(a4->field_0) % 4u);
            if ( v9 < 4 )
            {
                a4->field_0 += v9;
            }

            this->script_objects = CAST(this->script_objects, a4->field_0);
            a4->field_0 += 4 * this->total_script_objects;
            for ( auto i = 0; i < this->total_script_objects; ++i )
            {
                auto v12 = 8 - ((int) a4->field_0 % 8);
                if ( v12 < 8 )
                {
                    a4->field_0 += v12;
                }

                auto v13 = 4 - ((int) a4->field_0 % 4);
                if ( v13 < 4 )
                {
                    a4->field_0 += v13;
                }
                
                this->script_objects[i] = bit_cast<script_object *>(a4->field_0);
                a4->field_0 += sizeof(script_object);

                assert(((int) header) % 4 == 0);
                auto *so = this->script_objects[i];
                so->un_mash(header, this, so, a4);
            }

            this->global_script_object = *this->script_objects;
            auto v14 = 4 - ((int) a4->field_0 % 4);
            if ( v14 < 4 )
            {
                a4->field_0 += v14;
            }

            this->script_objects_by_name = bit_cast<script_object **>(a4->field_0);
            a4->field_0 += 4 * this->total_script_objects;
            for ( auto i = 0; i < this->total_script_objects; ++i )
            {
                this->script_objects_by_name[i] = this->script_objects[(int)this->script_objects_by_name[i]];
            }

            auto v17 = 4 - ((int) a4->field_0 % 4);
            if ( v17 < 4 )
            {
                a4->field_0 += v17;
            }

            this->permanent_string_table = CAST(this->permanent_string_table, a4->field_0);
            a4->field_0 += 4 * this->permanent_string_table_size;
            for ( auto i = 0; i < this->permanent_string_table_size; ++i )
            {
                auto v20 = 4 - ((int)a4->field_0 % 4);
                if ( v20 < 4 )
                {
                    a4->field_0 += v20;
                }

                auto v21 = *bit_cast<uint32_t *>(a4->field_0);
                a4->field_0 += 4u;
                this->permanent_string_table[i] = (char *) a4->field_0;
                a4->field_0 += v21;
            }

            this->system_string_table = nullptr;
            this->system_string_table_size = 0;
            auto v23 = 4 - ((int)a4->field_0 % 4);
            if ( v23 < 4 )
            {
                a4->field_0 += v23;
            }

            auto v24 = 4 - ((int)a4->field_0 % 4);
            if ( v24 < 4 )
            {
                a4->field_0 += v24;
            }

            this->field_54 = CAST(field_54, a4->field_0);
            a4->field_0 += 0x1C * this->field_58;
            auto v27 = 4 - ((int) a4->field_0 % 4u);
            if ( v27 < 4 )
            {
                a4->field_0 += v27;
            }

            if ( this->field_58 > 0 )
            {
                for (int a5 = 0; a5 < this->field_58; ++a5)
                {
                    assert(((int)header) % 4 == 0);

                    auto *v30 = this->field_54 + a5;
                    
                    assert(v30->so_name == string_hash::INVALID_STRING_HASH);

                    auto *owner = this->find_object(v30->field_18);
                    assert(owner != nullptr);

                    if ( v30->field_10 == -1 )
                    {
                        auto v32 = 4 - ((int) a4->field_0 % 4);
                        if ( v32 < 4 )
                        {
                            a4->field_0 += v32;
                        }

                        v30->field_8 = CAST(v30->field_8, a4->field_0);
                        a4->field_0 += sizeof(vm_executable);

                        assert(((int) header) % 4 == 0);
                        v30->field_8->un_mash(header, owner, v30->field_8, a4);
                    }
                }
            }

            this->constructor_common();
            this->flags |= SCRIPT_EXECUTABLE_FLAG_UN_MASHED;
        }
    }
    else
    {
        THISCALL(0x005B01F0, this, header, a3, a4);
    }
}

vm_executable *script_executable::find_function_by_address(const uint16_t *a2) const {
    return (vm_executable *) THISCALL(0x0058F280, this, a2);
}

vm_executable *script_executable::find_function_by_name(string_hash a2) const {
    return (vm_executable *) THISCALL(0x0058F310, this, a2);
}

void script_executable::register_allocated_stuff_callback(int a1, void (*a2)(script_executable *, _std::list<uint32_t> &, _std::list<mString> &))
{
    THISCALL(0x005AF460, this, a1, a2);
}

void script_executable::sub_672318(script_object *a1, int a3)
{
    auto v7 = a1->name;
    int i;
    for ( i = 0; i < a3; ++i )
    {
        auto v4 = this->script_objects_by_name[i]->name;
        if ( v4 > v7 )
        {
            break;
        }
    }

    if ( i == a3 )
    {
        this->script_objects_by_name[a3] = a1;
    }
    else
    {
        for ( auto j = a3; j > i; --j ) {
            this->script_objects_by_name[j] = this->script_objects_by_name[j - 1];
        }

        this->script_objects_by_name[i] = a1;
    }
}

constexpr auto CHUCK_STR_MAX_LENGTH = 47u;

void script_executable::load(const resource_key &resource_id) {
    script_manager::run_callbacks((script_manager_callback_reason)3, this, nullptr);
    auto &a1a = resource_id.m_hash;
    auto *v2 = a1a.to_string();
    
    filespec v98 {mString {v2}};
    if ( v98.m_dir == mString::null() && script_manager::using_chuck_old_fashioned() )
    {
        v98.m_dir = mString {"scripts\\"};
    }

    auto *v3 = v98.m_name.c_str();

    fixedstring<8> v46 {v3};
    this->field_0 = {v46.to_string()};
    
    chunk_file v97 {};
    chunk_flavor v96 {"UNREG"};

    auto sub_67F252 = []() -> mString {
        return mString {".xb"};
    };

    auto v4 = sub_67F252();
    auto a2 = v4 + "sst";
    v98.m_ext = a2;

    auto a1b = v98.fullname();
    v97.open(a1b, 1);
    if ( !v97.is_open() )
    {
        auto a1c = v98.fullname();
        auto a2a = "unable to open " + a1c;
        auto v23 = a2a + " for reading";
        auto *v5 = v23.c_str();
        script_manager::run_callbacks((script_manager_callback_reason)4, nullptr, v5);
    }

    auto cf = v97.read<chunk_flavor>();
    assert(cf == chunk_flavor {"strngtbl"});

    this->system_string_table_size = v97.read<int>();
    this->system_string_table = static_cast<char **>(operator new(4 * this->system_string_table_size));
    assert(system_string_table != nullptr);

    for ( auto i = 0; i < this->system_string_table_size; ++i )
    {
        mString v94 = v97.read<mString>();
        auto v7 = v94.size();
        this->system_string_table[i] = static_cast<char *>(operator new(v7 + 1));
        assert(system_string_table[i] != nullptr);

        auto v21 = v94.size() + 1;
        auto *v8 = v94.c_str();
        chuck_strcpy(this->system_string_table[i], v8, v21);
    }
    
    chunk_file source{};
    chunk_flavor v92 {"UNREG"};

    auto v9 = sub_67F252();
    auto a2b = v9 + "pst";
    v98.m_ext = a2b;
    auto a1d = v98.fullname();
    source.open(a1d, 1);
    assert(source.is_open());

    cf = source.read<chunk_flavor>();
    assert(cf == chunk_flavor {"strngtbl"});

    this->permanent_string_table_size = source.read<int>();
    this->permanent_string_table = static_cast<char **>(operator new(4 * this->permanent_string_table_size));
    assert(permanent_string_table != nullptr);

    for ( auto j = 0; j < this->permanent_string_table_size; ++j )
    {
        mString v90 = source.read<mString>();
        auto v11 = v90.size();
        this->permanent_string_table[j] = static_cast<char *>(operator new(v11 + 1));

        assert(permanent_string_table[j] != nullptr);
        auto v22 = v90.size() + 1;
        auto *v12 = v90.c_str();
        chuck_strcpy(this->permanent_string_table[j], v12, v22);
    }

    chunk_file io{};
    chunk_flavor v88 {"UNREG"};
    
    auto v13 = sub_67F252();
    auto a2c = v13 + "sx";
    v98.m_ext = a2c;
    auto a1e = v98.fullname();
    io.open(a1e, 1);

    assert(io.is_open());

    auto v87 = v98.fullname();
    v87 += "l";

    assert(sx_exe_image == nullptr);

    filespec v86 {v87};
    os_file v85 {};
    auto a1f = v86.fullname();
    v85.open(a1f, 1);
    if ( v85.is_open() )
    {
        auto v14 = v85.get_size();
        this->sx_exe_image_size = v14;
        this->sx_exe_image = new uint16_t[v14 / 2];
        assert(sx_exe_image != nullptr);
        v85.read(this->sx_exe_image, v14);
    }

    if ( this->sx_exe_image == nullptr )
    {
        auto a1g = v87 + ": executable code file is missing; this is now required with the sx file";
        auto *v17 = a1g.c_str();
        script_manager::run_callbacks((script_manager_callback_reason)4, this, v17);
    }

    cf = io.read<chunk_flavor>();
    if ( cf != chunk_flavor{"scrobjs"} )
    {
        auto a2d = v98.fullname() + ": bad format; script objects were expected";
        auto *v19 = a2d.c_str();
        script_manager::run_callbacks((script_manager_callback_reason)4, this, v19);
    }

    this->total_script_objects = io.read<int>();

    assert(total_script_objects > 0);

    assert(script_objects == nullptr);

    this->script_objects = static_cast<script_object **>(operator new(4 * this->total_script_objects));
    this->script_objects_by_name = static_cast<script_object **>(operator new(4 * this->total_script_objects));
    //auto *v74 = mem_alloc(12);
    //this->script_object_dummy_list = new (v74) sub_69D1A3(v74);

    assert(script_objects != nullptr);
    assert(script_objects_by_name != nullptr);
    assert(script_object_dummy_list != nullptr);

    int v84 = 1;
    int v83 = 0;
    while ( v83 < this->total_script_objects )
    {
        cf = io.read<chunk_flavor>();
        if ( cf == SCR_OBJ )
        {
            auto *v76 = mem_alloc(sizeof(script_object));
            auto *so = new (v76) script_object{};
            assert(so != nullptr && "Couldn't create a script object");

            auto v81 = io.read<int>();
            auto *my_name = this->system_string_table[v81];

            assert(strlen( my_name ) < CHUCK_STR_MAX_LENGTH && "the CHUCK compiler should disallow this case");

            string_hash v42 {my_name};
            so->name = v42;
            so->parent = this;
#if 0
            this->sub_672318(so, v83);
            io.read(so);
            this->sub_682E34(so, &v84);
#endif
            ++v83;
        }
        else
        {
            auto a1i = v98.fullname();
            auto a2e = a1i + ": bad format; script object was expected";
            auto *v20 = a2e.c_str();
            script_manager::run_callbacks((script_manager_callback_reason)4, this, v20);
        }
    }

    cf = io.read<chunk_flavor>();
    assert(cf == CHUNK_END);

    script_manager::run_callbacks((script_manager_callback_reason)2, this, nullptr);
}

uint16_t * script_executable::get_exec_code(unsigned int offset) {

    TRACE("script_executable::get_exec_code", std::to_string(offset).c_str());

    assert(sx_exe_image != nullptr && "We should have loaded the executable code from the sxl or sxb file");

    assert(offset < (uint32_t) sx_exe_image_size && "offset into exec code is out of bounds... bad juju man");

    return sx_exe_image + (offset >> 1);
};


void script_executable_patch()
{
    {
        FUNC_ADDRESS(address, &script_executable::un_mash);
        REDIRECT(0x005B0850, address);
    }
}
