#include "vm_executable.h"

#include "chunk_file.h"
#include "common.h"
#include "func_wrapper.h"
#include "memory.h"
#include "opcodes.h"
#include "script_library_class.h"
#include "slc_manager.h"
#include "script_var_container.h"
#include "script_manager.h"
#include "script_executable.h"
#include "script_object.h"
#include "trace.h"
#include "vtbl.h"

VALIDATE_SIZE(vm_executable, 0x24u);

vm_executable::vm_executable(script_object *so) : owner(so) {
}

vm_executable::~vm_executable()
{
    if ( (this->flags & 4) == 0 ) {
        this->destroy();
    }
}

void vm_executable::destroy()
{
    THISCALL(0x005AF2C0, this);
}

void vm_executable::un_mash(
        generic_mash_header *,
        void *a3,
        void *,
        generic_mash_data_ptrs *)
{
    TRACE("vm_executable::un_mash");

    assert(!is_un_mashed());
    this->owner = CAST(owner, a3);
    assert((flags & VM_EXECUTABLE_FLAG_FROM_MASH ) != 0);

    auto offset = bit_cast<uint32_t>(this->buffer);
    auto *se = this->owner->parent;

    this->buffer = se->get_exec_code(offset);
    this->flags |= VM_EXECUTABLE_FLAG_UN_MASHED;

    assert(this->debug_info == nullptr);
}

void vm_executable::link(const script_executable *a2) {
    TRACE("vm_executable::link");

    this->link_un_mash(a2);
}

void vm_executable::link_un_mash(const script_executable *a2) {
    TRACE("vm_executable::link_un_mash", this->fullname.to_string());

    {
        printf("permanent_string_table: %d\n", a2->permanent_string_table_size);
        for (auto i = 0; i < a2->permanent_string_table_size; ++i) {
            auto *str = a2->get_permanent_string(i);
            printf("%s\n", str);
        }

        printf("\n");
        printf("system_string_table: %d\n", a2->system_string_table_size);
        for (auto i = 0; i < a2->system_string_table_size; ++i) {
            auto *str = a2->get_system_string(i);
            printf("%s\n", str);
        }

        printf("\n");
    }

    if constexpr (1) {
        if (!this->is_linked()) {
            uint16_t *buffer = this->buffer;
            this->flags |= VM_EXECUTABLE_FLAG_LINKED;
            auto *v5 = a2;
            while ( buffer < &this->buffer[this->buffer_len] ) {
                auto opword = *buffer++;
                [[maybe_unused]] auto dsize = 4u;
                if ( (opword & OP_DSIZE_FLAG) != 0 ) {
                    dsize = *buffer++;
                }

                auto argtype = opcode_arg_t(opword & OP_ARGTYPE_MASK);
                printf("argtype = %d %s\n", argtype, opcode_arg_t_str[argtype]);

                if constexpr (0) {
                    using func_t = void (*)(vm_executable &, const script_executable *, uint16_t *&);

                    auto empty = [](vm_executable &, const script_executable *, uint16_t *&) {};

                    auto skip_two_word = [](vm_executable &, const script_executable *, uint16_t *&buffer) {
                        buffer += 2;
                    };

                    auto skip_one_word = [](vm_executable &, const script_executable *, uint16_t *&buffer) {
                        ++buffer;
                    };

                    static auto set_buffer = [](uint16_t *&buffer, uint32_t addr) {
                        *(buffer - 2) = addr >> 16;
                        *(buffer - 1) = addr & 0x0000FFFF;
                    };
                     
                    auto get_string = [](vm_executable &ex, const script_executable *, uint16_t *&buffer) -> void {
                        uint32_t idx = *buffer;
                        auto *str = ex.owner->get_parent()->get_permanent_string(idx);
                        printf("str = %s\n", str);
                        auto addr = uint32_t(str);
                        buffer += 2;
                        set_buffer(buffer, addr);
                    };

                    auto get_static_data = [](vm_executable &, const script_executable *se, uint16_t *&buffer) {
                        auto idx = *buffer++;
                        auto *so = se->find_object(idx);
                        assert(so != nullptr);

                        auto offset = *buffer++;
                        assert(offset < so->get_static_data_size());

                        auto addr = int(so->get_static_data_buffer() + offset);
                        set_buffer(buffer, addr);
                    };

                    auto get_static_func = [](vm_executable &, const script_executable *se, uint16_t *&buffer) {
                        auto idx = *buffer++;
                        auto func_idx = *buffer++;
                        auto *so = se->find_object(idx);
                        assert(so != nullptr);

                        auto *v8 = so->get_func(func_idx);
                        v8->link(se);
                        auto addr = int(v8);
                        set_buffer(buffer, addr);
                    };

                    auto get_library_func = [](vm_executable &, const script_executable *, uint16_t *&buffer) {
                        auto class_idx = *buffer++;
                        auto *slc = slc_manager::get_class(class_idx);
                        assert(slc != nullptr);

                        auto func_idx = *buffer++;
                        auto *func = slc->get_func(func_idx);
                        if (func == nullptr) {
                            assert(0 &&
                                  "your scripts are out-of-sync with this executable, try:\n"
                                  "  - make sure your executable is up-to-date\n"
                                  "  - force re-compile scripts, pack, build executable");
                        }

                        auto addr = int(func);
                        set_buffer(buffer, addr);
                    };
                    
                    auto get_class_value = [](vm_executable &ex, const script_executable *, uint16_t *&buffer) {
                        auto idx = *buffer++;
                        auto *slc = slc_manager::get_class(idx);
                        assert(slc != nullptr);

                        assert(slc->get_size() == 4);

                        auto v10 = *buffer++;
                        auto *ps = ex.owner->get_parent()->get_permanent_string(v10);
                        mString v17 {ps};

                        uint32_t (__fastcall *find_instance)(script_library_class *, void *, mString *) = CAST(find_instance, get_vfunc(slc->m_vtbl, 4));
                        auto addr = find_instance(slc, nullptr, &v17);
                        set_buffer(buffer, addr);
                    };

                    auto get_signal_value = [](vm_executable &ex, const script_executable *, uint16_t *&buffer) {
                        auto idx = *buffer;
                        auto *v16 = ex.owner->get_parent()->get_permanent_string(idx);

                        buffer += 2;
                        mString v18 {v16};

                        assert(resolve_signal_callback() != nullptr);

                        uint32_t v7;
                        resolve_signal_callback()(v18.c_str(), &v7);

                        auto addr = v7;
                        set_buffer(buffer, addr);
                    };
                    
                    auto get_var_addr = [](vm_executable &, const script_executable *, uint16_t *&buffer) {
                        auto offset = *buffer++;
                        auto v15 = *buffer++;

                        auto addr = (v15 == 1
                                ? (int) script_manager::get_game_var_address(offset)
                                : (int) script_manager::get_shared_var_address(offset)
                                );

                        assert(addr != 0 && "make sure you pack after you compile a script");
                        set_buffer(buffer, addr);
                    };

                    auto get_error = [](vm_executable &, const script_executable *, uint16_t *&) {
                        assert(0 && "found an unresolved external reference in a script executable!!!");
                    };

                    func_t funcs_table[] = {
                        empty, // OP_ARG_NULL
                        skip_two_word,                          // OP_ARG_NUM
                        skip_two_word,                          // OP_ARG_NUMR
                        get_string,                             // OP_ARG_STR
                        skip_one_word,                          // OP_ARG_WORD
                        skip_one_word,                          // OP_ARG_PCR
                        skip_one_word,                          // OP_ARG_SPR
                        skip_one_word,                          // OP_ARG_POPO
                        get_static_data,                        // OP_ARG_SDR
                        get_static_func,                        // OP_ARG_SFR
                        get_library_func,                       // OP_ARG_LFR
                        get_class_value,                        // OP_ARG_CLV
                        empty,                                  // 12
                        empty,                                  // 13
                        empty,                                  // 14
                        get_signal_value,                       // OP_ARG_SIG
                        get_signal_value,                       // OP_ARG_PSIG
                        get_var_addr,                           // 17
                        get_error,                                        // 18
                        get_error,                                        // 19
                        get_error,                                        // 20
                        get_error,                                        // 21
                        get_error,                                         // 22
                    };

                    funcs_table[argtype]((*this), v5, buffer);
                } else {
                    switch ( argtype )
                    {
                    case OP_ARG_NULL:
                        break;
                    case OP_ARG_NUM:
                    case OP_ARG_NUMR:
                        buffer += 2;
                        break;
                    case OP_ARG_STR: {
                        uint32_t idx = *buffer;
                        auto *str = this->owner->get_parent()->get_permanent_string(idx);
                        printf("str = %s\n", str);
                        auto addr = uint32_t(str);
                        buffer += 2;
                        *(buffer - 2) = addr >> 16;
                        *(buffer - 1) = addr & 0x0000FFFF;
                        break;
                    }
                    case OP_ARG_WORD:
                    case OP_ARG_PCR:
                    case OP_ARG_SPR:
                    case OP_ARG_POPO:
                        ++buffer;
                        break;
                    case OP_ARG_SDR: {
                        auto idx = *buffer++;
                        auto *so = v5->find_object(idx);
                        assert(so != nullptr);

                        auto offset = *buffer++;
                        assert(offset < so->get_static_data_size());

                        auto addr = int(so->get_static_data_buffer() + offset);

                        *(buffer - 2) = addr >> 16;
                        *(buffer - 1) = addr & 0x0000FFFF;
                        break;
                    }
                    case OP_ARG_SFR: {
                        auto idx = *buffer++;
                        auto func_idx = *buffer++;
                        auto *so = v5->find_object(idx);
                        assert(so != nullptr);

                        auto *v8 = so->get_func(func_idx);
                        v8->link(v5);
                        auto addr = int(v8);

                        *(buffer - 2) = addr >> 16;
                        *(buffer - 1) = addr & 0x0000FFFF;
                        break;
                    }
                    case OP_ARG_LFR: {
                        auto class_idx = *buffer++;
                        auto *slc = slc_manager::get_class(class_idx);
                        assert(slc != nullptr);

                        auto func_idx = *buffer++;
                        auto *func = slc->get_func(func_idx);
                        if (func == nullptr) {
                            assert(0 &&
                                  "your scripts are out-of-sync with this executable, try:\n"
                                  "  - make sure your executable is up-to-date\n"
                                  "  - force re-compile scripts, pack, build executable");
                        }

                        auto addr = int(func);
                        *(buffer - 2) = addr >> 16;
                        *(buffer - 1) = addr & 0x0000FFFF;
                        break;
                    }
                    case OP_ARG_CLV: {
                        auto idx = *buffer++;
                        auto *slc = slc_manager::get_class(idx);
                        assert(slc != nullptr);

                        assert(slc->get_size() == 4);

                        auto v10 = *buffer++;
                        auto *ps = this->owner->get_parent()->get_permanent_string(v10);
                        mString v17 {ps};

                        uint32_t (__fastcall *find_instance)(script_library_class *, void *, mString *) = CAST(find_instance, get_vfunc(slc->m_vtbl, 4));
                        auto addr = find_instance(slc, nullptr, &v17);

                        *(buffer - 2) = addr >> 16;
                        *(buffer - 1) = addr & 0x0000FFFF;
                        break;
                    }
                    case OP_ARG_SIG:
                    case OP_ARG_PSIG: {
                        auto idx = *buffer;
                        auto *v16 = this->owner->get_parent()->get_permanent_string(idx);

                        buffer += 2;
                        mString v18 {v16};

                        assert(resolve_signal_callback() != nullptr);

                        uint32_t v7;
                        resolve_signal_callback()(v18.c_str(), &v7);

                        auto addr = v7;
                        *(buffer - 2) = addr >> 16;
                        *(buffer - 1) = addr & 0x0000FFFF;
                        break;
                    }
                    case 17: {
                        auto offset = *buffer++;
                        auto v15 = *buffer++;

                        auto addr = (v15 == 1
                                ? (int) script_manager::get_game_var_address(offset)
                                : (int) script_manager::get_shared_var_address(offset)
                                );

                        assert(addr != 0 && "make sure you pack after you compile a script");

                        *(buffer - 2) = addr >> 16;
                        *(buffer - 1) = addr & 0x0000FFFF;
                        break;
                    }
                    case 18:
                    case 19:
                    case 20:
                    case 21:
                    case 22:
                        assert(0 && "found an unresolved external reference in a script executable!!!");
                        return;
                    default:
                        assert(0 && "unknown arg type");
                        return;
                    }
                }
            }
        }
    } else {
        THISCALL(0x0059F000, this, a2);
    }
}

void vm_executable::write(chunk_file *file, const vm_executable *x, const std::set<string_hash> &set) {
    TRACE("vm_executable::serialize");

    assert(x->debug_info == nullptr);

    assert(x != nullptr);
    assert(x->owner != nullptr);

    file->write(CHUNK_VM_EXECUTABLE);

    sp_log("x->fullname = %s", x->fullname.to_string());
    auto v16 = script_executable::get_system_string_index(set, x->fullname);
    file->write(v16);

#ifdef TARGET_XBOX
    cf = file->read<chunk_flavor>();
    chunk_flavor v6 {"extern"};
    if ( cf == v6 )
    {
        script_manager::run_callbacks((script_manager_callback_reason)4, nullptr, "extern no longer supported");
    }
    else
    {
        assert(cf == chunk_flavor {"defined"});
    }
#endif

    sp_log("x->flags = 0x%08X", x->flags);

#ifdef TARGET_XBOX
    cf = file->read<chunk_flavor>();
    if ( cf == chunk_flavor {"static"} )
    {
        x->flags |= 1u;
    }
    else
    {
        assert(cf == chunk_flavor {"nostatic"});
    }

    cf = file->read<chunk_flavor>();
    if ( cf == chunk_flavor {"srcfile"} )
    {
        auto v43 = file->read<mString>();
        [[maybe_unused]] auto v42 = file->read<int>();
        cf = file->read<chunk_flavor>();
    }

    auto v41 = -1;
    if ( cf == chunk_flavor {"Nparms"} )
    {
        v41 = 0;
        x->debug_info->field_24 = file->read<int>();
        if ( x->debug_info->field_24 > 0 )
        {
            x->debug_info->parameters = new void *[x->debug_info->field_24];
            assert(x->debug_info->parameters != nullptr);

            for ( auto i = 0; i < x->debug_info->field_24; ++i ) {
                auto v17 = file->read<unsigned>();
                auto *v10 = x->owner->get_parent();
                auto *v11 = v10->get_system_string(v17);
                
                mString v39 {v11};
                auto *v38 = v10->find_library_class(v39);
                if ( v38 == nullptr )
                {
                    v38 = slc_manager::get(v39.c_str());
                    if ( v38 == nullptr )
                    {
                        auto v37 = "library class " + v39 + " not found.";
                        auto *v13 = v37.c_str();
                        script_manager::run_callbacks((script_manager_callback_reason)4, nullptr, v13);
                    }
                }

                x->debug_info->parameters[i] = v38;
                auto size = v38->get_size();
                v41 += size;
            }
        }

        cf = file->read<chunk_flavor>();
    }
#endif

    file->write(CHUNK_PARMS_STACKSIZE);

    file->write(x->parms_stacksize);

#ifdef TARGET_XBOX
    if ( v41 != -1 )
    {
        if ( x->parms_stacksize == v41 )
        {
            assert(( x->flags & VM_EXECUTABLE_FLAG_STATIC ) != 0);
        }
        else
        {
            assert(( x->flags & VM_EXECUTABLE_FLAG_STATIC ) == 0);
        }
    }
#endif

#ifdef TARGET_XBOX
    auto cf = file->read<chunk_flavor>();
    while ( cf == CHUNK_PARMS_NAME )
    {
        struct {
            mString field_0;
            mString field_C;
        } v36 {};

        v36.field_0 = file->read<mString>();
        v36.field_C = file->read<mString>();
        cf = file->read<chunk_flavor>();
    }
#endif

    file->write(CHUNK_CODESIZE);

    file->write(x->buffer_len * 2);

    file->write(CHUNK_CODE);

    auto *v15 = x->owner->get_parent();
    uint32_t offset = ((int)x->buffer - (int) v15->get_exec_code(0));
    file->write(offset);
}

void vm_executable::read(chunk_file *file, vm_executable *x) {
    TRACE("vm_executable::load");

    auto *mem = mem_alloc(0x24);
    x->debug_info = new (mem) debug_info_t {};

    assert(x->debug_info != nullptr);

    assert(x != nullptr);

    assert(x->owner != nullptr);

    chunk_flavor cf {"UNREG"};
    cf = file->read<chunk_flavor>();
    assert(cf == CHUNK_VM_EXECUTABLE);

    auto v16 = file->read<unsigned>();
    auto *parent = x->owner->get_parent();
    auto *system_string = parent->get_system_string(v16);
    mString v46 {system_string};
    auto a3 = v46.find("(", 0);
    mString v45 = (a3 == -1 ? v46 : v46.substr(0, a3));

    x->name = string_hash {v45.c_str()};
    x->fullname = string_hash {v46.c_str()};

    cf = file->read<chunk_flavor>();
    if ( cf == chunk_flavor {"extern"} ) {
        script_manager::run_callbacks((script_manager_callback_reason)4, nullptr, "extern no longer supported");
    } else {
        assert(cf == chunk_flavor {"defined"});
    }

    cf = file->read<chunk_flavor>();
    if ( cf == chunk_flavor {"static"} ) {
        x->flags |= 1u;
    } else {
        assert(cf == chunk_flavor {"nostatic"});
    }

    cf = file->read<chunk_flavor>();

    if ( cf == chunk_flavor {"srcfile"} ) {
        auto v43 = file->read<mString>();
        [[maybe_unused]] auto v42 = file->read<int>();
        cf = file->read<chunk_flavor>();
    }

    auto v41 = -1;
    if ( cf == chunk_flavor {"Nparms"} ) {
        v41 = 0;
        x->debug_info->field_24 = file->read<int>();
        if ( x->debug_info->field_24 > 0 )
        {
            x->debug_info->parameters = (void **)operator new(4 * x->debug_info->field_24);
            assert(x->debug_info->parameters != nullptr);

            for ( auto i = 0; i < x->debug_info->field_24; ++i )
            {
                auto v17 = file->read<unsigned>();
                auto *v10 = x->owner->get_parent();
                auto *v11 = v10->get_system_string(v17);
                
                mString v39 {v11};
                auto *v38 = v10->find_library_class(v39);
                if ( v38 == nullptr )
                {
                    v38 = slc_manager::get(v39.c_str());
                    if ( v38 == nullptr )
                    {
                        auto v37 = "library class " + v39 + " not found.";
                        auto *v13 = v37.c_str();
                        script_manager::run_callbacks((script_manager_callback_reason)4, nullptr, v13);
                    }
                }

                x->debug_info->parameters[i] = v38;
                auto size = v38->get_size();
                v41 += size;
            }
        }

        cf = file->read<chunk_flavor>();
    }

    assert(cf == CHUNK_PARMS_STACKSIZE);

    x->parms_stacksize = file->read<int>();

    if ( v41 != -1 ) {
        if ( x->parms_stacksize == v41 )
        {
            assert(( x->flags & VM_EXECUTABLE_FLAG_STATIC ) != 0);
        }
        else
        {
            assert(( x->flags & VM_EXECUTABLE_FLAG_STATIC ) == 0);
        }
    }

    cf = file->read<chunk_flavor>();

    while ( cf == CHUNK_PARMS_NAME ) {
        struct {
            mString field_0;
            mString field_C;
        } v36 {};

        v36.field_0 = file->read<mString>();
        v36.field_C = file->read<mString>();
        cf = file->read<chunk_flavor>();
    }

    assert(cf == CHUNK_CODESIZE);

    auto v35 = file->read<int>();
    x->buffer_len = v35 / 2;

    cf = file->read<chunk_flavor>();
    assert(cf == CHUNK_CODE);

    auto offset = file->read<unsigned>();
    auto *v15 = x->owner->get_parent();
    x->buffer = v15->get_exec_code(offset);
}

void vm_executable_patch() {

    {
        FUNC_ADDRESS(address, &vm_executable::link_un_mash);
        SET_JUMP(0x0059F000, address);
    }
}
