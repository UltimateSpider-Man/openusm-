#include "vm_executable.h"

#include "common.h"
#include "func_wrapper.h"
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

constexpr auto VM_EXECUTABLE_FLAG_FROM_MASH = 4u;

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
    auto *v5 = this->owner->parent;

    this->buffer = v5->get_exec_code(offset);
    this->flags |= 8u;
}

void vm_executable::link_un_mash(const script_executable *a2)
{
    TRACE("vm_executable::link_un_mash");

    if constexpr (1) {
        if ( (this->flags & 2) == 0 )
        {
            uint16_t *buffer = this->buffer;
            this->flags |= 2u;
            auto *v5 = a2;
            while ( buffer < &this->buffer[this->buffer_len] )
            {
                auto opword = *buffer++;
                auto dsize = 4u;
                if ( (opword & OP_DSIZE_FLAG) != 0 ) {
                    dsize = *buffer++;
                }

                auto argtype = opcode_arg_t(opword & OP_ARGTYPE_MASK);
                printf("argtype = %d\n", argtype);
                switch ( argtype )
                {
                case 0:
                    break;
                case 1:
                case 2:
                    buffer += 2;
                    break;
                case 3: {
                    uint32_t idx = *buffer;
                    auto addr = uint32_t(this->owner->parent->permanent_string_table[idx]);
                    buffer += 2;
                    *(buffer - 2) = addr >> 16;
                    *(buffer - 1) = addr & 0x0000FFFF;
                    break;
                }
                case 4:
                case 5:
                case 6:
                case 7:
                    ++buffer;
                    break;
                case 8: {
                    auto idx = *buffer++;
                    auto *so = v5->script_objects_by_name[idx];
                    assert(so != nullptr);

                    auto offset = *buffer++;
                    auto addr = int(so->data.get_buffer() + offset);

                    *(buffer - 2) = addr >> 16;
                    *(buffer - 1) = addr & 0x0000FFFF;
                    break;
                }
                case OP_ARG_SFR: {
                    auto idx = *buffer++;
                    auto offset = *buffer++;
                    auto *so = v5->script_objects_by_name[idx];
                    assert(so != nullptr);

                    auto *v8 = so->funcs[offset];
                    v8->link_un_mash(v5);
                    auto addr = int(v8);

                    *(buffer - 2) = addr >> 16;
                    *(buffer - 1) = addr & 0x0000FFFF;
                    break;
                }
                case OP_ARG_LFR: {
                    auto idx = *buffer++;
                    auto *slc = slc_manager_class_array()->at(idx);
                    assert(slc != nullptr);

                    auto func_idx = *buffer++;
                    auto *v7 = slc->get_func(func_idx);
                    if (v7 == nullptr) {
                        assert(0 &&
                              "your scripts are out-of-sync with this executable, try:\n"
                              "  - make sure your executable is up-to-date\n"
                              "  - force re-compile scripts, pack, build executable");
                    }

                    auto addr = int(v7);
                    *(buffer - 2) = addr >> 16;
                    *(buffer - 1) = addr & 0x0000FFFF;
                    break;
                }
                case 11: {
                    auto idx = *buffer++;
                    auto *slc = slc_manager_class_array()->at(idx);
                    assert(slc != nullptr);

                    assert(slc->get_size() == 4);

                    auto v10 = *buffer++;
                    mString v17 {this->owner->parent->permanent_string_table[v10]};

                    void * (__fastcall *func)(void *, void *, mString *) = CAST(func, get_vfunc(slc->m_vtbl, 4));
                    auto *v7 = func(slc, 0, &v17);

                    auto addr = uint32_t(v7);
                    *(buffer - 2) = addr >> 16;
                    *(buffer - 1) = addr & 0x0000FFFF;
                    break;
                }
                case 15:
                case 16: {
                    auto idx = *buffer;
                    auto *v16 = this->owner->parent->permanent_string_table[idx];

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
                    auto v14 = *buffer++;
                    auto v15 = *buffer++;

                    auto *container = (v15 == 1
                            ? script_manager_game_var_container()
                            : script_manager_shared_var_container()
                            );

                    char *addr = container->script_var_block.buffer + v14;

                    assert(addr != nullptr && "make sure you pack after you compile a script");

                    *(buffer - 2) = bit_cast<uint16_t *>(&addr)[1];
                    *(buffer - 1) = bit_cast<uint16_t *>(&addr)[0];

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
    } else {
        THISCALL(0x0059F000, this, a2);
    }
}

void vm_executable_patch() {

    {
        FUNC_ADDRESS(address, &vm_executable::link_un_mash);
        SET_JUMP(0x0059F000, address);
    }
}
