#include "so_data_block.h"

#include "common.h"
#include "memory.h"
#include "parse_generic_mash.h"

VALIDATE_SIZE(so_data_block, 0xC);

so_data_block::so_data_block(int a2)
{
    this->m_size = 0;
    this->buffer = nullptr;
    this->flags = 0;
    this->init(a2);
}

void so_data_block::operator=(int a2) {
    clear();
    this->init(a2);
}

void so_data_block::set_to_zero() {
    if ( this->m_size > 0 ) {
        assert(buffer != nullptr);
        memset(this->buffer, 0, this->m_size);
    }
}

void so_data_block::init(int a2)
{
    //assert(!is_from_mash());

    this->m_size = a2;
    if ( a2 != 0 )
    {
        this->buffer = (char *)mem_alloc(a2);
        assert(buffer != nullptr);
        memset(this->buffer, 0, a2);
    }
    else
    {
        this->buffer = nullptr;
    }
}

void so_data_block::clear()
{
    if ( !this->is_from_mash() )
    {
        if ( this->buffer != nullptr )
        {
            mem_dealloc(this->buffer, this->m_size);
            this->buffer = nullptr;
            this->m_size = 0;
        }
    }
}

void so_data_block::un_mash(
        generic_mash_header *,
        void *,
        generic_mash_data_ptrs *a4)
{
    auto v4 = 4 - (unsigned int)a4->field_0 % 4;
    if ( v4 < 4 ) {
        a4->field_0 += v4;
    }

    this->buffer = (char *)a4->field_0;
    a4->field_0 += this->m_size;
    assert(( this->flags & SO_DATA_BLOCK_FLAG_FROM_MASH ) != 0);
}
