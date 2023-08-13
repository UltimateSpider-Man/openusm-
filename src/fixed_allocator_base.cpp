#include "fixed_allocator_base.h"

#include "memory.h"

#include <cassert>

void *fixed_allocator_base::alloc(int size)
{
    return arch_memalign(this->m_alignment, size);
}

void fixed_allocator_base::release(void *)
{
    assert(nullptr && "fixed_allocator_base cannot release memory");
}
