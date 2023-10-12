#include "script_object.h"

#include "chunk_file.h"

#include "func_wrapper.h"
#include "memory.h"
#include "script_executable.h"
#include "vm_executable.h"
#include "vm_thread.h"
#include "common.h"
#include "trace.h"
#include "utility.h"

#include <cassert>

VALIDATE_SIZE(script_object, 0x34);
VALIDATE_SIZE(script_object::function, 0x10);

VALIDATE_SIZE(script_instance, 0x44);

VALIDATE_SIZE(vm_symbol, 0x4C);

script_object::script_object()
{
    this->instances = nullptr;
    this->flags = 0;
    this->constructor_common();
}

void script_object::constructor_common() {
    TRACE("script_object::constructor_common");

    assert(instances == nullptr);

    THISCALL(0x005A0750, this);

    assert(instances != nullptr);
}

script_object::~script_object()
{
    if ( (this->flags & 2) != 0 ) {
        this->destructor_common();
    } else {
        this->destroy();
    }

    if ( (this->static_data.flags & 1) == 0 ) {
        auto &buffer = this->static_data.buffer;
        if ( buffer != nullptr ) {
            mem_dealloc(buffer, this->static_data.size());

            this->static_data.buffer = nullptr;
            this->static_data.m_size = 0;
        }
    }
}

void script_object::destructor_common()
{
    if ( this->instances != nullptr ) {
        while ( !this->instances->empty() ) {
            auto begin = this->instances->begin();
            auto v5 = begin;
            this->instances->erase(v5);
            auto *v3 = v5._Ptr;
            if ( v3 != nullptr ) {
                delete v3;
            }
        }

        mem_dealloc(this->instances, sizeof(*this->instances));
        this->instances = nullptr;
    }

    this->global_instance = nullptr;
}

void script_object::destroy()
{
    if ( debug_info != nullptr ) {
        this->debug_info->~debug_info_t();
        operator delete(debug_info);
        this->debug_info = nullptr;
    }

    if ( this->funcs != nullptr ) {
        for ( auto i = 0; i < this->total_funcs; ++i ) {
            auto &v5 = this->funcs[i];
            if ( v5 != nullptr ) {
                v5->~vm_executable();
                operator delete(v5);
            }
        }

        operator delete[](this->funcs);
        this->funcs = nullptr;
        this->total_funcs = 0;
    }

    this->destructor_common();
}

void script_object::create_destructor_instances() {
    THISCALL(0x005AF320, this);
}

void script_object::sub_5AB420() {
    this->constructor_common();
    if ( this->is_global_object() ) {
        this->create_auto_instance(0.0);
    }
}

simple_list<vm_thread>::iterator script_instance::delete_thread(
        simple_list<vm_thread>::iterator a3) {
    TRACE("script_instance::delete_thread");

    simple_list<vm_thread>::iterator iter{};
    THISCALL(0x005AAE60, this, &iter, a3);
    return iter;
}

void script_instance::dump_threads_to_file(FILE *a2) {
    TRACE("script_instance::dump_threads_to_file");

    for ( auto &v7 : this->threads ) {
        if ( (v7.flags & 1) == 0 ) {
            auto *exec = v7.get_executable();
            auto &name = exec->get_name();
            auto *v4 = name.to_string();
            auto *v3 = this->name.to_string();
            fprintf(a2, "%s %s\n", v3, v4);
        }
    }
}

void script_instance::run(bool a2)
{
    TRACE("script_instance::run");

    this->flags |= 2u;
    this->build_parameters();
    auto it = this->threads.begin();
    auto end = this->threads.end();
    while (it != end) {
        auto *t = it._Ptr;
        assert(t != nullptr);
        if ( (a2 || (t->flags & 1) == 0) && t->run() ) {
            it = this->delete_thread(it);
        } else {
            ++it;
        }
    }
}

void script_instance::run_callbacks(
        script_instance_callback_reason_t a2,
        vm_thread *a3)
{
    TRACE("script_instance::run_callbacks");

    for ( auto &v1 : this->field_38 ) {
        this->m_callback(a2, this, a3, v1);
    }
}

void script_instance::build_parameters() {
    TRACE("script_instance::build_parameters");

    if constexpr (1) {
        if ( this->field_28 != nullptr ) {
            assert(parent != nullptr);

            static const string_hash inst_name {"__parms_builder"};
            auto *v6 = parent->add_instance(inst_name, nullptr, nullptr);
            vm_thread t {v6, this->field_28};
            t.run();
            this->parent->remove_instance(v6);
            t.inst = nullptr;
            t.ex = nullptr;
            auto *v12 = t.get_data_stack().buffer;
            assert(threads.size() == 1);

            auto *v11 = this->threads._first_element;
            auto constructor_parmsize = this->parent->get_constructor_parmsize();
            auto v4 = v12;
            auto &stack = v11->get_data_stack();
            stack.push(v4, constructor_parmsize);
            if ( !this->field_28->is_from_mash() )
            {
                auto *v10 = this->field_28;
                auto *v9 = v10;
                if ( v10 != nullptr )
                {
                    delete v9;
                }
            }

            this->field_28 = nullptr;
        }
    } else {
        THISCALL(0x005AF500, this);
    }
}

int script_object::get_constructor_parmsize() {
    auto *func = this->get_func(0);
    auto v2 = func->get_parms_stacksize();
    if ( !func->is_static() ) {
        v2 -= 4;
    }

    return v2;
}

void script_object::run(bool a2)
{
    TRACE("script_object::run");

    for (auto &v1 : (*this->instances) ) {
        v1.run(a2);
    }
}

bool script_object::has_threads() const
{
    if (this->instances != nullptr) {

        for (auto &v1 : (*this->instances)) {
            if (v1.has_threads()) {
                return true;
            }
        }
    }

    return false;
}

void script_object::dump_threads_to_file(FILE *a2) {
    TRACE("script_object::dump_threads_to_file");

    if ( this->instances != nullptr ) {
        for ( auto &v2 : (*this->instances) ) {
            v2.dump_threads_to_file(a2);
        }
    }
}

script_instance *script_object::add_instance(string_hash a2, char *a3, vm_thread **a4) {
    TRACE("script_object::add_instance");

    return (script_instance *) THISCALL(0x005AB120, this, a2, a3, a4);
}

script_instance *script_object::add_instance(string_hash a2, vm_executable *parms_builder) {
    TRACE("script_object::add_instance", a2.to_string());

    assert(!is_global_object() && "please don't create global object instances with this method");

    //assert(parms_builder->is_from_mash() && "this function should only be used for mashed parms_builders");

    if constexpr (0) {
        auto *mem = mem_alloc(sizeof(script_instance));
        auto *inst = new (mem) script_instance{a2, this->data_blocksize, 0};
        assert(inst != nullptr);

        this->add(inst);

        auto *func = this->get_func(0);
        assert(func->get_name() == this->name);

        auto *t = inst->add_thread(func);
        *(DWORD *)t->dstack.SP = (int)inst;
        t->dstack.SP += 4;

        inst->field_28 = parms_builder;
        assert(parent != nullptr);
        if ( inst->field_28 != nullptr ) {
            inst->field_28->link(this->parent);
        }

        return inst;
    } else {
        return (script_instance *) THISCALL(0x005AB200, this, a2, parms_builder);
    }
}

void script_object::remove_instance(script_instance *a2)
{
    TRACE("script_object::remove_instance");
    THISCALL(0x005ADC60, this, a2);
}

script_instance *script_object::sub_5AB030(string_hash a2, int a3)
{
    auto *mem = mem_alloc(sizeof(script_instance));
    auto *inst = new (mem) script_instance{a2, this->data_blocksize, a3 | 4u};
    assert(inst != nullptr);
    this->add(inst);
    return inst;
}

void script_object::add(script_instance *a2) {
    TRACE("script_object::add");

    if constexpr (0) {
        assert(instances != nullptr);

        a2->parent = this;
        this->instances->emplace_back(a2);
    } else {
        THISCALL(0x0059ECC0, this, a2);
    }
}

void script_object::link(const script_executable *a2) {
    TRACE("script_object::link");

    for ( auto i = 0; i < this->total_funcs; ++i ) {
        auto &x = this->funcs[i];
        x->link(a2);
    }
}

void script_object::un_mash(generic_mash_header *a2, void *a3, void *a4, generic_mash_data_ptrs *a5) {
    TRACE("script_object::un_mash");

    THISCALL(0x005AB350, this, a2, a3, a4, a5);

    sp_log("flags = 0x%08X", this->flags);
    //assert(this->debug_info == nullptr);
}

void script_object::create_auto_instance(Float arg0) {
    TRACE("script_object::create_auto_instance");

    THISCALL(0x005AAEF0, this, arg0);
}

vm_executable *script_object::get_func(int i)
{
    assert(funcs != nullptr);

    assert(i >= 0);

    assert(i < total_funcs);

    return this->funcs[i];
}

int script_object::find_func(string_hash a2) const {
    return THISCALL(0x0058EF80, this, a2);
}

void vm_symbol::read(chunk_file *file) {
    this->field_0 = file->read<mString>();
    this->field_C = file->read<mString>();

    this->field_30 = file->read<int>();
    this->field_34 = file->read<int>();

    this->field_38 = file->read<bool>();

    this->field_18 = file->read<mString>();
    this->field_24 = file->read<mString>();
}

void script_object::read(chunk_file *file, script_object *so)
{
    TRACE("script_object::load");

    auto *mem = mem_alloc(sizeof(debug_info_t));
    so->debug_info = new (mem) debug_info_t{}; 
    assert(so->debug_info != nullptr);

    assert(so->parent != nullptr);

    chunk_flavor cf = file->read<chunk_flavor>();

    sp_log("so->flags = 0x%08X", so->flags);
    if ( cf == CHUNK_EXTERNAL ) {
        so->flags |= SCRIPT_OBJECT_FLAG_EXTERNAL;
        cf = file->read<chunk_flavor>();
    }

    if ( cf == CHUNK_GLOBAL ) {
        so->flags |= SCRIPT_OBJECT_FLAG_GLOBAL;
    }

    if ( cf == CHUNK_STANDARD ) {
        cf = file->read<chunk_flavor>();
        if ( cf == CHUNK_PARENT )
        {
            auto v39 = file->read<uint32_t>();
            auto *system_string = so->parent->get_system_string(v39);
            so->debug_info->field_0 = string_hash {system_string};
            cf = file->read<chunk_flavor>();
        }
    } else {
        cf = file->read<chunk_flavor>();
    }

    if ( cf == CHUNK_NSTATIC ) {
        auto i = file->read<int>();
        while ( i ) {
            vm_symbol v38{};
            v38.read(file);

            so->debug_info->field_4.push_back(v38);
            --i;
        }

        cf = file->read<chunk_flavor>();
    }

    sp_log("%s", cf.field_0);
    assert(cf == CHUNK_STATIC_BLOCKSIZE);

    so->static_data = file->read<int>();
    cf = file->read<chunk_flavor>();

    while ( cf == CHUNK_STAT_INIT ) {
        auto v36 = file->read<int>();
        auto v35 = file->read<int>();
        auto *buffer = so->static_data.get_buffer();
        auto *v34 = (float *) &buffer[v36];
        if ( v35 != 0 )
        {
            if ( v35 == 1 )
            {
                auto v31 = file->read<float>();
                *v34 = v31;
            }
            else if ( v35 == 2 )
            {
                auto v30 = file->read<int>();
                auto *str = so->parent->get_system_string(v30);
                auto *pso = so->parent->find_object(string_hash {str}, nullptr);
                assert(pso);

                v30 = file->read<int>();
                [[maybe_unused]] auto *v27 = pso->parent->get_system_string(v30);
                auto v26 = 0;
                chunk_flavor v25 {"UNREG"};
                v25 = file->read<chunk_flavor>();
                if ( v25 == CHUNK_PARMS )
                {
                    //v26 = pso->sub_6870D3(string_hash {v27}, file, nullptr);
                }
                else if ( v25 == CHUNK_NULL )
                {
                    //v26 = (string_hash *)pso->add_instance(string_hash {v27}, this, nullptr);
                }
                else if ( v25 == CHUNK_GAME_INIT )
                {
                    //v26 = (string_hash *)pso->sub_68757E(string_hash {v27}, nullptr);
                }
                else
                {
                    assert(0 && "bad sx file");
                }

                *bit_cast<DWORD *>(v34) = v26;
            }
        }
        else
        {
            auto v33 = file->read<int>();
            auto *permanent_string = so->parent->get_permanent_string(v33);
            *(DWORD *)v34 = (int)permanent_string;
        }

        cf = file->read<chunk_flavor>();
    }

    if ( cf == CHUNK_NDATA ) {
        auto i = file->read<int>();
        while ( i != 0 ) {
            vm_symbol v23{};
            v23.read(file);
            so->debug_info->field_10.push_back(v23);
            --i;
        }

        cf = file->read<chunk_flavor>();
    }

    assert(cf == CHUNK_DATA_BLOCKSIZE);

    so->data_blocksize = file->read<int>();
    cf = file->read<chunk_flavor>();
    if ( cf == chunk_flavor {"desidx"} ) {
        so->field_28 = file->read<int>();
        cf = file->read<chunk_flavor>();
    } else {
        so->field_28 = -1;
    }

    assert(cf == CHUNK_FUNCS);
    so->total_funcs = file->read<int>();
    sp_log("so->total_funcs = %d", so->total_funcs);
    if ( so->total_funcs > 0 ) {
        so->funcs = (vm_executable **)operator new(4 * so->total_funcs);
        assert(so->funcs != nullptr);

        for ( auto i = 0; i < so->total_funcs; ++i )
        {
            auto *mem = mem_alloc(sizeof(vm_executable));
            auto *x = new (mem) vm_executable {so};
            assert(x != nullptr);

            vm_executable::read(file, x);
            so->funcs[i] = x;
        }
    }

    if ( so->is_global_object() ) {
        so->create_auto_instance(0.0);
    }
}

script_instance::script_instance(
        string_hash a2,
        int Size,
        unsigned int a4)
{
    THISCALL(0x005AAA40, this, a2, Size, a4);
}

int *script_instance::register_callback(
    void (*p_cb)(script_instance_callback_reason_t, script_instance *, vm_thread *, void *),
    void *a3) {
    return (int *) THISCALL(0x005A33F0, this, p_cb, a3);
}

vm_thread *script_instance::add_thread(const vm_executable *ex, const char *parms) {
    TRACE("script_instance::add_thread");

    auto *nt = this->add_thread(ex);
    assert(nt != nullptr);

    if ( parms != nullptr ) {
        auto v5 = ex->get_parms_stacksize();
        nt->get_data_stack().push(parms, v5);
    }

    nt->PC = ex->buffer;
    return nt;
}

void script_instance::massacre_threads(const vm_executable *a2, const vm_thread *a3)
{
    THISCALL(0x005ADB80, this, a2, a3);
}

void script_instance::kill_thread(const vm_executable *a2, const vm_thread *a3)
{
    THISCALL(0x005AD8D0, this, a2, a3);
}

vm_thread *script_instance::add_thread(const vm_executable *a2) {
    TRACE("script_instance::add_thread");

    if constexpr (0) {
        auto *mem = vm_thread::pool().allocate_new_block();
        auto *nt = new (mem) vm_thread{this, a2};
        assert(nt != nullptr);

        this->threads.emplace_back(nt);

        if ( (this->flags & 1) != 0 ) {
            nt->set_suspended(true);
        }

        return nt;
    } else {
        return (vm_thread *) THISCALL(0x005AAC20, this, a2);
    }
}

bool script_instance::has_threads() const {
    return (this->threads.size() != 0);
}

void script_instance_patch() {
    {
        FUNC_ADDRESS(address, &script_instance::run);
        SET_JUMP(0x005AF660, address);
    }
}
