#include "memory.h"

#include "debugutil.h"
#include "func_wrapper.h"
#include "os_developer_options.h"
#include "slab_allocator.h"
#include "utility.h"
#include "variable.h"

#include <cstdio>
#include <cstdlib>

Var<bool> mem_first_malloc{0x009224F0};

Var<bool> mem_first_memalign{0x009224F1};
Var<bool> mem_first_allocation{0x009224E8};

static Var<int> dword_965EC0{0x00965EC0};

void *mem_alloc(size_t Size) {
    void *mem;

    if (slab_allocator::get_max_object_size() < Size) {
        mem = operator new(Size);
    } else {
        mem = slab_allocator::allocate(Size, nullptr);
    }

    return mem;
}

void mem_dealloc(void *a1, size_t Size) {
    if (Size <= slab_allocator::get_max_object_size()) {
        slab_allocator::deallocate(a1, nullptr);
    } else {
        operator delete(a1);
    }
}

//0x0058EC30
void *arch_memalign_internal(size_t Alignment, size_t Size) {
    if constexpr (1) {
        void *result = _aligned_malloc(Size, Alignment);
        void *v3 = result;
        if (result != nullptr) {
            result = v3;
            dword_965EC0() += _msize(*(void **) (((unsigned int) result & 0xFFFFFFFC) - 4));
        }
        return result;
    } else {
        return bit_cast<void *>(CDECL_CALL(0x0058EC30, Alignment, Size));
    }
}

void mem_on_first_allocation() {
    if (mem_first_allocation()) {
        debug_print_va("MEMTRACK is OFF");
        mem_print_stats("very first allocation");
        mem_first_allocation() = false;
    }
}

void *arch_memalign(size_t Alignment, size_t Size) {
    if constexpr (0) {
        if (mem_first_memalign()) {
            mem_on_first_allocation();

            mem_first_memalign() = false;
        }

        auto *mem = arch_memalign_internal(Alignment, Size);
        if (mem == nullptr) {
            debug_print_va("tried to allocate %d bytes", Size);
            mem_print_stats("mem_memalign failed");
        }

        return mem;

    } else {
        return (void *) CDECL_CALL(0x005357B0, Alignment, Size);
    }
}

void mem_freealign(void *Memory) {
    if (Memory != nullptr) {
        dword_965EC0() -= _msize(*(void **) (((unsigned int) Memory & 0xFFFFFFFC) - 4));
        _aligned_free(Memory);
    }
}

void mem_print_stats(const char *a1) {
    debug_print_va("mem_print_stats: %s\n", a1);
    debug_print_va("peak: %10lu   curr: %10lu   free: %10lu\n", 0ul, 0ul, 0ul);
}

void *arch_malloc(size_t Size) {
    if (mem_first_malloc()) {
        mem_on_first_allocation();

        mem_first_malloc() = false;
    }

    auto *mem = malloc(Size);
    dword_965EC0() += _msize(mem);

    if (mem == nullptr) {
        debug_print_va("tried to allocate %d bytes", Size);
        mem_print_stats("mem_memalloc failed");

        os_developer_options().set_flag(mString{"ENABLE_LONG_CALLSTACK"}, false);
    }

    return mem;
}

void memory_patch() {
    REDIRECT(0x0059F684, arch_malloc);

    REDIRECT(0x00550E6B, arch_memalign_internal);
}
