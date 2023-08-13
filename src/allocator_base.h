#pragma once

struct allocator_base
{
    int m_alignment;

    virtual ~allocator_base() = default;

    virtual void *alloc(int size);

    virtual void release(void *mem);
};
