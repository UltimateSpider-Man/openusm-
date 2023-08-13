#include "allocator_base.h"

#include "memory.h"

void *allocator_base::alloc(int size)
{
    return arch_memalign(this->m_alignment, size);
}

void allocator_base::release(void *mem)
{
    mem_freealign(mem);
}
