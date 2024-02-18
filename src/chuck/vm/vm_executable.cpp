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
	if constexpr (0)
	{
		if ( this->debug_info != nullptr )
		{
			if ( this->debug_info->parameters != nullptr ) {
				operator delete[](this->debug_info->parameters);
			}

			if ( this->debug_info ) {
				THISCALL(0x005B7C90, debug_info);
				operator delete(this->debug_info);
			}

			this->debug_info = nullptr;
		}

		this->buffer = nullptr;
		this->flags &= ~2u;
	} else {
		THISCALL(0x005AF2C0, this);
	}
}

void vm_executable::un_mash(
        generic_mash_header *,
        void *a3,
        void *,
        generic_mash_data_ptrs *)
{
    TRACE("vm_executable::un_mash");

    assert(!this->is_un_mashed());

    this->owner = CAST(owner, a3);
    assert((flags & VM_EXECUTABLE_FLAG_FROM_MASH ) != 0);

    auto offset = bit_cast<uint32_t>(this->buffer);
    auto *se = this->owner->parent;

    this->buffer = se->get_exec_code(offset);
    this->flags |= VM_EXECUTABLE_FLAG_UN_MASHED;

    assert(this->debug_info == nullptr);

    sp_log("buffer_len = %d", this->buffer_len);
}

void vm_executable::link(const script_executable *a2)
{
    TRACE("vm_executable::link");

    this->link_un_mash(a2);
}

void vm_executable::link_un_mash(const script_executable *a2)
{
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

    if constexpr (1)
	{
        printf("buffer_len = %d", this->buffer_len);
        if ( !this->is_linked() )
		{
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

                if constexpr (1) {
                    auto get_string = [](vm_executable &ex, const script_executable *,
                            std::array<uint32_t, 2> indices) -> uint32_t {
                        uint32_t idx = indices[0];
                        auto *str = ex.owner->get_parent()->get_permanent_string(idx);
                        auto addr = uint32_t(str);
                        return addr;
                    };

                    auto get_static_data = [](vm_executable &, const script_executable *se,
                            std::array<uint32_t, 2> indices) -> uint32_t {
                        auto idx = indices[0];
                        auto *so = se->find_object(idx);
                        assert(so != nullptr);

                        auto offset = indices[1];
                        assert(offset < so->get_static_data_size());

                        auto addr = int(so->get_static_data_buffer() + offset);
                        return addr;
                    };

                    auto get_static_func = [](vm_executable &, const script_executable *se,
                            std::array<uint32_t, 2> indices) -> uint32_t {
                        auto idx = indices[0];
                        auto func_idx = indices[1];
                        auto *so = se->find_object(idx);
                        assert(so != nullptr);

                        auto *v8 = so->get_func(func_idx);
                        v8->link(se);
                        auto addr = int(v8);
                        return addr;
                    };

                    auto get_library_func = [](vm_executable &, const script_executable *,
                            std::array<uint32_t, 2> indices) -> uint32_t {
                        auto class_idx = indices[0];
                        auto *slc = slc_manager::get_class(class_idx);
                        assert(slc != nullptr);

                        auto func_idx = indices[1];
                        auto *func = slc->get_func(func_idx);
                        if (func == nullptr) {
                            assert(0 &&
                                  "your scripts are out-of-sync with this executable, try:\n"
                                  "  - make sure your executable is up-to-date\n"
                                  "  - force re-compile scripts, pack, build executable");
                        }

                        auto addr = int(func);
                        return addr;
                    };
                    
                    auto get_class_value = [](vm_executable &ex, const script_executable *,
                            std::array<uint32_t, 2> indices) -> uint32_t {
                        auto idx = indices[0];
                        auto *slc = slc_manager::get_class(idx);
                        assert(slc != nullptr);

                        assert(slc->get_size() == 4);

                        auto v10 = indices[1];
                        auto *ps = ex.owner->get_parent()->get_permanent_string(v10);
                        mString v17 {ps};

                        auto addr = slc->find_instance(v17);
                        return addr;
                    };

                    auto get_signal_value = [](vm_executable &ex, const script_executable *,
                            std::array<uint32_t, 2> indices) -> uint32_t {
                        auto idx = indices[0];
                        auto *v16 = ex.owner->get_parent()->get_permanent_string(idx);

                        mString v18 {v16};

                        assert(resolve_signal_callback() != nullptr);

                        uint32_t addr;
                        resolve_signal_callback()(v18.c_str(), &addr);

                        return addr;
                    };
                    
                    auto get_var_addr = [](vm_executable &, const script_executable *,
                            std::array<uint32_t, 2> indices) -> uint32_t {
                        auto offset = indices[0];
                        auto v15 = indices[1];

                        auto addr = (v15 == 1
                                ? (int) script_manager::get_game_var_address(offset)
                                : (int) script_manager::get_shared_var_address(offset)
                                );

                        assert(addr != 0 && "make sure you pack after you compile a script");
                        return addr;
                    };

                    enum cmd_e {
                        EMPTY,
                        SKIP,
                        PROCESS,
                        ERROR
                    };

                    struct {
                        cmd_e cmd;
                        uint8_t num_words;

                        using func_t = uint32_t (*)(vm_executable &, const script_executable *, std::array<uint32_t, 2>);
                        func_t func;

                        void operator()(vm_executable &ex, const script_executable *se, uint16_t *&buffer) {
                            switch (cmd) {
                            case EMPTY:
                                return;
                            case SKIP:
                                buffer += num_words;
                                break;
                            case PROCESS: {
                                auto addr = func(ex, se, {buffer[0], buffer[1]});
                     
                                buffer += 2;
                                *(buffer - 2) = addr >> 16;
                                *(buffer - 1) = addr & 0x0000FFFF;
                                break;
                            }
                            case ERROR: {
                                assert(0 && "found an unresolved external reference in a script executable!!!");
                                break;
                            }
                            }
                        }
                    } funcs_table[] = {
                        {.cmd = EMPTY}, // OP_ARG_NULL
                        {.cmd = SKIP, .num_words = 2u},                          // OP_ARG_NUM
                        {.cmd = SKIP, .num_words = 2u},                          // OP_ARG_NUMR
                        {.cmd = PROCESS, .func = get_string},                    // OP_ARG_STR
                        {.cmd = SKIP, .num_words = 1u},                          // OP_ARG_WORD
                        {.cmd = SKIP, .num_words = 1u},                          // OP_ARG_PCR
                        {.cmd = SKIP, .num_words = 1u},                          // OP_ARG_SPR
                        {.cmd = SKIP, .num_words = 1u},                          // OP_ARG_POPO
                        {.cmd = PROCESS, .func = get_static_data},                        // OP_ARG_SDR
                        {.cmd = PROCESS, .func = get_static_func},                        // OP_ARG_SFR
                        {.cmd = PROCESS, .func = get_library_func},                       // OP_ARG_LFR
                        {.cmd = PROCESS, .func = get_class_value},                        // OP_ARG_CLV
                        {.cmd = EMPTY},                                  // 12
                        {.cmd = EMPTY},                                  // 13
                        {.cmd = EMPTY},                                  // 14
                        {.cmd = PROCESS, .func = get_signal_value},                       // OP_ARG_SIG
                        {.cmd = PROCESS, .func = get_signal_value},                       // OP_ARG_PSIG
                        {.cmd = PROCESS, .func = get_var_addr},                           // 17
                        {.cmd = ERROR},                                        // 18
                        {.cmd = ERROR},                                        // 19
                        {.cmd = ERROR},                                        // 20
                        {.cmd = ERROR},                                        // 21
                        {.cmd = ERROR},                                         // 22
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

                        auto addr = slc->find_instance(v17);

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

void vm_executable::write(chunk_file *file, const vm_executable *x, const std::set<string_hash> &set)
{
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

    auto *mem = mem_alloc(sizeof(debug_info_t));
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
