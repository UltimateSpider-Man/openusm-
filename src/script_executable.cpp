#include "script_executable.h"

#include "func_wrapper.h"

#include "script_object.h"
#include "trace.h"
#include "common.h"
#include "parse_generic_mash.h"
#include "utility.h"

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
    assert(( flags & SCRIPT_EXECUTABLE_FLAG_UN_MASHED ) != 0);

    assert(( flags & SCRIPT_EXECUTABLE_FLAG_LINKED ) != 0);

    assert(( flags & SCRIPT_EXECUTABLE_FLAG_FROM_MASH ) != 0);

    this->constructor_common();
    for ( auto i = 0; i < this->total_script_objects; ++i )
    {
        this->field_28[i]->sub_5AB420();
    }
}

void script_executable::un_mash_start(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, [[maybe_unused]] void *a5)
{
    this->un_mash(a2, a3, a4);
}

void script_executable::un_mash(generic_mash_header *header, void *a3, generic_mash_data_ptrs *a4)
{
    TRACE("script_executable::un_mash");

    if constexpr (1)
    {
        if ( (this->flags & 4) != 0 )
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

            int v7 = this->field_24;
            this->field_20 = (int)a4->field_0;
            auto *v8 = &a4->field_0[v7];
            a4->field_0 = v8;
            auto v9 = 4 - (bit_cast<int>(a4->field_0) % 4u);
            if ( v9 < 4 )
            {
                a4->field_0 = &v8[v9];
            }

            auto v10 = this->total_script_objects;
            this->field_28 = (script_object **)a4->field_0;
            a4->field_0 += 4 * v10;
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
                
                this->field_28[i] = (script_object *)a4->field_0;
                a4->field_0 += 0x34;

                assert(((int) header) % 4 == 0);
                auto *v37 = this->field_28[i];
                v37->un_mash(header, this, v37, a4);
            }

            this->global_script_object = *this->field_28;
            auto v14 = 4 - ((int) a4->field_0 % 4);
            if ( v14 < 4 )
            {
                a4->field_0 += v14;
            }

            auto v15 = this->total_script_objects;
            this->script_objects_by_name = (script_object **)a4->field_0;
            a4->field_0 += 4 * v15;
            for ( auto j = 0; j < this->total_script_objects; ++j )
            {
                this->script_objects_by_name[j] = this->field_28[(int)this->script_objects_by_name[j]];
            }

            auto v17 = 4 - ((int) a4->field_0 % 4);
            if ( v17 < 4 )
            {
                a4->field_0 += v17;
            }

            auto v18 = this->permanent_string_table_size;
            this->permanent_string_table = CAST(this->permanent_string_table, a4->field_0);
            a4->field_0 += 4 * v18;
            for ( auto k = 0; k < this->permanent_string_table_size; ++k )
            {
                auto v20 = 4 - ((int)a4->field_0 % 4);
                if ( v20 < 4 )
                {
                    a4->field_0 += v20;
                }

                auto v21 = *(uint32_t *)a4->field_0;
                auto v22 = a4->field_0 + 4;
                a4->field_0 = v22;
                this->permanent_string_table[k] = (char *) v22;
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

            auto v25 = 0x1C * this->field_58;
            this->field_54 = (int)a4->field_0;
            auto *v26 = &a4->field_0[v25];
            a4->field_0 = v26;
            auto v27 = 4 - ((int) a4->field_0 % 4u);
            if ( v27 < 4 )
            {
                a4->field_0 = &v26[v27];
            }

            int a2a = 0;
            bool v36 = false;
            if ( this->field_58 > 0 )
            {
                generic_mash_data_ptrs *a5 = nullptr;
                do
                {
                    assert(((int)header) % 4 == 0);

                    auto v28 = this->field_54;
                    auto v29 = *(int *)((char *)&a5[3].field_0 + v28);
                    auto *v30 = (char *)a5 + v28;
                    auto *v31 = this->script_objects_by_name[v29];
                    if ( *((uint32_t *)v30 + 4) == -1 )
                    {
                        auto v32 = 4 - ((int) a4->field_0 % 4);
                        if ( v32 < 4 )
                        {
                            a4->field_0 += v32;
                        }

                        *((uint32_t *)v30 + 2) = (uint32_t) a4->field_0;
                        a4->field_0 += 36;
                        auto **v33 = (script_object **)*((uint32_t *)v30 + 2);
                        auto *v34 = v33[4];
                        *v33 = v31;
                        auto v35 = (unsigned int)v33[7] | 8;
                        v33[4] = (script_object *)(v31->parent->field_20 + 2 * ((unsigned int)v34 >> 1));
                        v33[7] = (script_object *)v35;
                    }

                    v36 = ++a2a < this->field_58;
                    a5 = (generic_mash_data_ptrs *)((char *)a5 + 28);
                }
                while ( v36 );
            }

            this->constructor_common();
            this->flags |= 4u;
        }
    }
    else
    {
        THISCALL(0x005B01F0, this, header, a3, a4);
    }
}

void script_executable::register_allocated_stuff_callback(int a1, void (*a2)(script_executable *, _std::list<uint32_t> &, _std::list<mString> &))
{
    THISCALL(0x005AF460, this, a1, a2);
}

void script_executable_patch()
{
    {
        FUNC_ADDRESS(address, &script_executable::un_mash);
        REDIRECT(0x005B0850, address);
    }
}
