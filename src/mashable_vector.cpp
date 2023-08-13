#include "mashable_vector.h"

#include "anim_info.h"
#include "anim_map_ptr_entry.h"
#include "common.h"
#include "district_graph_container.h"
#include "entity_base_vhandle.h"
#include "fixedstring.h"
#include "func_wrapper.h"
#include "log.h"
#include "oldmath_po.h"
#include "parse_generic_mash.h"
#include "resource_allocation_pool.h"
#include "resource_location.h"
#include "resource_pack_group.h"
#include "tlresource_location.h"
#include "utility.h"

VALIDATE_SIZE(mashable_vector<int>, 8u);

auto rebase(uint8_t *&ptr, uint32_t i) -> void
{
    uint32_t v9 = i - ((uint32_t) ptr % i);
    if (v9 < i) {
        ptr += v9;
    }
}


//0x004C7F50
template<>
void mashable_vector<resource_directory *>::custom_un_mash([[maybe_unused]] generic_mash_header *a2,
                                                           [[maybe_unused]] void *a3,
                                                           generic_mash_data_ptrs *a4,
                                                           [[maybe_unused]] void *a5) {
    //sp_log("mashable_vector<resource_directory *>::custom_un_mash():");

    assert(from_mash());

    if (this->m_shared)
    {
        rebase(a4->field_4, 4u);

        rebase(a4->field_4, 4u);

        this->m_data = CAST(m_data, a4->field_4);
        a4->field_4 += 4 * this->m_size;

        rebase(a4->field_4, 4u);
    }
    else
    {
        rebase(a4->field_0, 4u);

        rebase(a4->field_0, 4u);

        this->m_data = CAST(m_data, a4->field_0);
        a4->field_0 += 4 * this->m_size;

        rebase(a4->field_0, 4u);
    }
}

//0x004C72E0
template<>
void mashable_vector<dsg_region_container>::custom_un_mash(generic_mash_header *a2,
                                                           [[maybe_unused]] void *a3,
                                                           generic_mash_data_ptrs *a4,
                                                           [[maybe_unused]] void *a5) {
    if (this->m_shared) {
        sp_log("dsg_region_container's cannot be shared!");
        assert(0);
    } else {
        uint32_t v6 = 4 - ((uint32_t) a4->field_0 % 4);
        if (v6 < 4) {
            a4->field_0 += v6;
        }

        uint32_t v7 = 4 - ((uint32_t) a4->field_0 % 4);
        if (v7 < 4) {
            a4->field_0 += v7;
        }

        this->m_data = (dsg_region_container *) a4->field_0;
        a4->field_0 += 84 * this->m_size;
        
        for (auto i = 0u; i < this->m_size; ++i)
        {
            this->m_data[i].un_mash(a2, &this->m_data[i], a4);
        }

        uint32_t v11 = 4 - ((uint32_t) a4->field_0 % 4);
        if (v11 < 4) {
            a4->field_0 += v11;
        }
    }
}

//0x004C7380
template<>
void mashable_vector<dsg_box_container>::custom_un_mash(generic_mash_header *a2,
                                                        [[maybe_unused]] void *a3,
                                                        generic_mash_data_ptrs *a4,
                                                        [[maybe_unused]] void *a5) {
    if (this->m_shared) {
        sp_log("dsg_box_container's cannot be shared!");
        assert(0);
    } else {
        uint32_t v6 = 4 - ((uint32_t) a4->field_0 % 4);
        if (v6 < 4) {
            a4->field_0 += v6;
        }

        uint32_t v7 = 4 - ((uint32_t) a4->field_0 % 4);
        if (v7 < 4) {
            a4->field_0 += v7;
        }

        auto v8 = 52 * this->m_size;
        this->m_data = (dsg_box_container *) a4->field_0;
        size_t v9 = 0;
        a4->field_0 += v8;
        if (this->m_size) {
            size_t v10 = 0;
            do {
                this->m_data[v10].un_mash(a2, &this->m_data[v10], a4);
                ++v9;
                ++v10;
            } while (v9 < this->m_size);
        }

        uint32_t v11 = 4 - ((uint32_t) a4->field_0 % 4);
        if (v11 < 4) {
            a4->field_0 += v11;
        }
    }
}

//0x004C7DC0
template<>
void mashable_vector<resource_location>::custom_un_mash(generic_mash_header *header,
                                                        [[maybe_unused]] void *a3,
                                                        generic_mash_data_ptrs *a4,
                                                        [[maybe_unused]] void *a5)
{
    assert(from_mash());

    if (this->m_shared)
    {
        rebase(a4->field_4, 8u);

        auto v24 = bit_cast<uint32_t *>(a4->field_4)[0];
        a4->field_4 += 4;

        auto v11 = bit_cast<uint32_t *>(a4->field_4)[0];
        a4->field_4 += 4;
        a4->field_4 += 4;

        auto *v9 = bit_cast<uint32_t *>(a4->field_4);
        a4->field_4 += 4;

        rebase(a4->field_4, 8u);

        rebase(a4->field_4, 4u);

        this->m_data = (value_t *) a4->field_4;
        a4->field_4 += sizeof(value_t) * this->m_size;
        if (v9[0] != 0)
        {
            a4->field_0 += v24;
            a4->field_4 += v11 - sizeof(value_t) * this->m_size;
        }
        else
        {
            for (auto i = 0u; i < this->m_size; ++i)
            {
                assert(((int)header) % 4 == 0);
                this->m_data[i].un_mash(header, &this->m_data[i], a4);
            }
        }

        ++(v9[0]);

        rebase(a4->field_4, 4u);

    } else {

        rebase(a4->field_0, 8u);

        rebase(a4->field_0, 4u);

        this->m_data = (value_t *) a4->field_0;
        a4->field_0 += sizeof(value_t) * this->m_size;

        for (auto i = 0u; i < this->m_size; ++i)
        {
            assert(((int)header) % 4 == 0);
            this->m_data[i].un_mash(header, &this->m_data[i], a4);
        }

        rebase(a4->field_0, 4u);
    }
}

//0x004C8020
template<>
void mashable_vector<tlresource_location>::custom_un_mash(generic_mash_header *header,
                                                          [[maybe_unused]] void *a3,
                                                          generic_mash_data_ptrs *a4,
                                                          [[maybe_unused]] void *a5)
{
    assert(from_mash());

    if (this->is_shared())
    {
        rebase(a4->field_4, 8u);

        auto offset = *bit_cast<uint32_t *>(a4->field_4);
        a4->field_4 += 4;

        auto offset1 = *bit_cast<uint32_t *>(a4->field_4);
        a4->field_4 += 4;
        a4->field_4 += 4;

        auto *v9 = bit_cast<int *>(a4->field_4);
        a4->field_4 += 4;

        rebase(a4->field_4, 8u);

        rebase(a4->field_4, 4u);

        this->m_data = CAST(m_data, a4->field_4);
        a4->field_4 += sizeof(value_t) * this->m_size;

        if (v9[0] != 0)
        {
            a4->field_0 += offset;
            a4->field_4 += offset1 - sizeof(value_t) * this->m_size;
        }
        else
        {
            for (int i = 0; i < this->m_size; ++i) {
                assert(((int) header) % 4 == 0);
                this->m_data[i].un_mash(header, &this->m_data[i], a4);
            }
        }

        ++v9[0];

        rebase(a4->field_4, 4u);

    } else {

        rebase(a4->field_0, 8u);

        rebase(a4->field_0, 4u);

        this->m_data = CAST(m_data, a4->field_0);
        a4->field_0 += sizeof(value_t) * this->m_size;

        for (int i = 0; i < this->m_size; ++i)
        {
            assert(((int) header) % 4 == 0);
            this->m_data[i].un_mash(header, &this->m_data[i], a4);
        }

        rebase(a4->field_0, 4u);
    }
}

//0x004C81B0
template<>
void mashable_vector<resource_pack_group>::custom_un_mash(generic_mash_header *header,
                                                          [[maybe_unused]] void *a3,
                                                          generic_mash_data_ptrs *a4,
                                                          [[maybe_unused]] void *a5) {
    assert(from_mash());

    if (this->is_shared()) {

        rebase(a4->field_4, 8u);

#if 0
        auto offset = *bit_cast<uint32_t *>(a4->field_4);
        a4->field_4 += 4;

        auto offset1 = *bit_cast<uint32_t *>(a4->field_4);
        a4->field_4 += 4;
        a4->field_4 += 4;

        auto *v9 = bit_cast<int *>(a4->field_4);
        a4->field_4 += 4;

#else
        struct {
            uint32_t offset;
            uint32_t offset1;
            uint32_t empty;
            uint32_t field_C;
        } *ptr = CAST(ptr, a4->field_4);

        auto offset = ptr->offset;
        auto offset1 = ptr->offset1;
        auto *v9 = &ptr->field_C;

        a4->field_4 += sizeof(*ptr);
#endif

        rebase(a4->field_4, 8u);

        rebase(a4->field_4, 4u);

        this->m_data = CAST(m_data, a4->field_4);
        a4->field_4 += sizeof(value_t) * this->m_size;

        if (v9[0]) {
            a4->field_0 += offset;
            a4->field_4 += offset1 - sizeof(value_t) * this->m_size;
        } else if (this->m_size) {
            for (int i = 0; i < this->m_size; ++i) {
                assert(((int) header) % 4 == 0);
                this->m_data[i].un_mash(header, &this->m_data[i], a4);
            }
        }

        ++v9[0];

        rebase(a4->field_4, 4u);

    } else {

        rebase(a4->field_0, 8u);

        rebase(a4->field_0, 4u);

        this->m_data = CAST(m_data, a4->field_0);
        a4->field_0 += sizeof(value_t) * this->m_size;

        if (this->m_size) {
            for (int i = 0; i < this->m_size; ++i) {
                assert(((int) header) % 4 == 0);
                this->m_data[i].un_mash(header, &this->m_data[i], a4);
            }
        }


        rebase(a4->field_0, 4u);
    }
}

//0x004C8740
template<>
void mashable_vector<resource_allocation_pool>::custom_un_mash(generic_mash_header *header,
                                                               [[maybe_unused]] void *a3,
                                                               generic_mash_data_ptrs *a4,
                                                               [[maybe_unused]] void *a5) {
    if (this->is_shared()) {
        rebase(a4->field_4, 4u);

        auto offset = *bit_cast<uint32_t *>(a4->field_4);
        a4->field_4 += 4;

        auto offset1 = *bit_cast<uint32_t *>(a4->field_4);
        a4->field_4 += 4;

        auto *v9 = bit_cast<int *>(a4->field_4);
        a4->field_4 += 4;

        rebase(a4->field_4, 4u);

        rebase(a4->field_4, 4u);

        this->m_data = (value_t *) a4->field_4;
        a4->field_4 += sizeof(value_t) * this->m_size;

        if (v9[0]) {
            a4->field_0 += offset;
            a4->field_4 += offset1 - sizeof(value_t) * this->m_size;
        }
        else
        {
            for (int i = 0; i < this->m_size; ++i) {
                this->m_data[i].un_mash(header, &this->m_data[i], a4);
            }
        }

        ++v9[0];

        rebase(a4->field_4, 4u);

    } else {

        rebase(a4->field_0, 4u);

        rebase(a4->field_0, 4u);

        this->m_data = (value_t *) a4->field_0;
        a4->field_0 += sizeof(value_t) * this->m_size;

        for (int i = 0; i < this->m_size; ++i) {
            this->m_data[i].un_mash(header, &this->m_data[i], a4);
        }

        rebase(a4->field_0, 4u);
    }
}

//0x
template<>
void mashable_vector<fixedstring<4>>::custom_un_mash([[maybe_unused]] generic_mash_header *a2,
                                                     [[maybe_unused]] void *a3,
                                                     generic_mash_data_ptrs *a4,
                                                     [[maybe_unused]] void *a5) {
    assert(from_mash());

    if (this->is_shared()) {

        rebase(a4->field_4, 8u);

        rebase(a4->field_4, 4u);

        this->m_data = CAST(m_data, a4->field_4);
        a4->field_4 += sizeof(value_t) * this->m_size;

        rebase(a4->field_4, 4u);

    } else {

        rebase(a4->field_0, 8u);

        rebase(a4->field_0, 4u);

        this->m_data = CAST(m_data, a4->field_0);
        a4->field_0 += sizeof(value_t) * this->m_size;

        rebase(a4->field_0, 4u);
    }
}

//0x004C5F20
template<>
void mashable_vector<int>::custom_un_mash([[maybe_unused]] generic_mash_header *a2,
                                          [[maybe_unused]] void *a3,
                                          generic_mash_data_ptrs *a4,
                                          [[maybe_unused]] void *a5) {
    if (this->m_shared) {

        rebase(a4->field_4, 4u);

        rebase(a4->field_4, 4u);

        this->m_data = bit_cast<value_t *>(a4->field_4); 
        a4->field_4 += 4 * this->m_size;

        rebase(a4->field_4, 4u);

    } else {

        rebase(a4->field_0, 4u);

        rebase(a4->field_0, 4u);

        this->m_data = bit_cast<value_t *>(a4->field_0);
        a4->field_0 += 4 * this->m_size;

        rebase(a4->field_0, 4u);
    }
}

template<>
void mashable_vector<po>::custom_un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *a4, void *)
{
    TRACE("mashable_vector<po>::custom_un_mash");

    if ( this->m_shared )
    {
        auto v5 = 16 - ((int)a4->field_4 % 16);
        if ( v5 < 16 )
            a4->field_4 += v5;

        auto v6 = 4 - ((int)a4->field_4 % 4);
        if ( v6 < 4 )
        {
            a4->field_4 += v6;
        }

        this->m_data = (po *)a4->field_4;
        a4->field_4 += this->m_size << 6u;
        auto v8 = 4 - ( bit_cast<uint32_t>(a4->field_4) % 4u );
        if ( v8 < 4 )
        {
            a4->field_4 += v8;
        }
    }
    else
    {
        auto v9 = 16 - ((int)a4->field_0 % 16);
        if ( v9 < 16 )
        {
            a4->field_0 += v9;
        }
        
        auto v10 = 4 - ((int)a4->field_0 % 4);
        if ( v10 < 4 )
        {
            a4->field_0 += v10;
        }
        
        this->m_data = (po *)a4->field_0;
        a4->field_0 += this->m_size << 6u;
        auto v12 = 4 - (bit_cast<uint32_t>(a4->field_0) % 4u);
        if ( v12 < 4 )
        {
            a4->field_0 += v12;
        }
    }
}

template<>
void mashable_vector<entity_base *>::custom_un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *a4, void *)
{
    TRACE("mashable_vector<entity_base *>::custom_un_mash");

    if ( this->m_shared)
    {
        auto v5 = 4 - ((int)a4->field_4 & 3);
        if ( v5 < 4 )
        {
            a4->field_4 += v5;
        }

        auto v6 = 4 - ((int)a4->field_4 & 3);
        if ( v6 < 4 )
        {
            a4->field_4 += v6;
        }

        this->m_data = (entity_base **)a4->field_4;

        a4->field_4 += 4 * this->m_size;

        auto v8 = 4 - (bit_cast<uint32_t>(a4->field_4) & 4u);
        if ( v8 < 4 )
        {
            a4->field_4 += v8;
        }
    }
    else
    {
        auto v9 = 4 - ((int)a4->field_0 & 3);
        if ( v9 < 4 )
            a4->field_0 += v9;

        auto v10 = 4 - ((int)a4->field_0 & 3);
        if ( v10 < 4 )
        {
            a4->field_0 += v10;
        }
        
        this->m_data = (entity_base **)a4->field_0;
        a4->field_0 += 4 * this->m_size;
        auto v12 = 4 - (bit_cast<uint32_t>(a4->field_0) % 4u);
        if ( v12 < 4 )
        {
            a4->field_0 += v12;
        }
    }
}

template<>
void mashable_vector<int8_t>::custom_un_mash(generic_mash_header *, void *, generic_mash_data_ptrs *a4, void *)
{
    if ( this->m_shared )
    {
        auto v5 = 4 - ((int)a4->field_4 & 3);
        if ( v5 < 4 )
        {
            a4->field_4 += v5;
        }

        auto v6 = 4 - ((int)a4->field_4 & 3);
        if ( v6 < 4 )
        {
            a4->field_4 += v6;
        }

        this->m_data = CAST(m_data, a4->field_4);
        a4->field_4 += this->m_size;

        auto v8 = 4 - (bit_cast<int>(a4->field_4) % 4u);
        if ( v8 < 4 )
        {
            a4->field_4 += v8;
        }
    }
    else
    {
        auto v9 = 4 - ((int)a4->field_0 & 3);
        if ( v9 < 4 )
        {
            a4->field_0 += v9;
        }

        auto v10 = 4 - ((int)a4->field_0 & 3);
        if ( v10 < 4 )
        {
            a4->field_0 += v10;
        }
        
        this->m_data = CAST(m_data, a4->field_0);
        a4->field_0 += this->m_size;
        auto v12 = 4 - (bit_cast<int>(a4->field_0) % 4u);
        if ( v12 < 4 )
        {
            a4->field_0 += v12;
        }
    }
}

template<>
void mashable_vector<anim_info>::custom_un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *a5)
{
    if ( this->m_shared )
    {
        auto v7 = 8 - ((int)a4->field_4 & 7);
        if ( v7 < 8 )
        {
            a4->field_4 += v7;
        }

        auto v8 = (int)a4->field_4;
        auto v9 = (int *)(v8 + 4);
        auto a4a = *(DWORD *)v8;
        auto v10 = (uint8_t *)(v8 + 16);
        a4->field_4 = (uint8_t *)(v8 + 4);
        auto v11 = *(DWORD *)(v8 + 4);
        auto v12 = 8 - (((BYTE)v8 + 16) & 7);
        a4->field_4 = v10;
        if ( v12 < 8 )
        {
            a4->field_4 = &v10[v12];
        }

        auto v13 = 4 - ((int)a4->field_4 & 3);
        if ( v13 < 4 )
        {
            a4->field_4 += v13;
        }

        this->m_data = (anim_info *)a4->field_4;
        a4->field_4 += 0x24 * this->m_size;
        auto v14 = 0;
        if ( v9[2] )
        {
            a4->field_0 += a4a;
            a4->field_4 += v11 - 0x24 * this->m_size;
        }
        else if ( this->m_size )
        {
            auto a4b = 0;
            do
            {
                this->m_data[a4b].un_mash(a2, &this->m_data[a4b], a4);
                ++v14;
                ++a4b;
            }
            while ( v14 < this->m_size );
        }

        ++v9[2];
        auto v15 = 4 - ((int)a4->field_4 & 3);
        if ( v15 < 4 )
        {
            a4->field_4 += v15;
        }
    }
    else
    {
        auto v16 = 8 - ((int)a4->field_0 & 7);
        if ( v16 < 8 )
            a4->field_0 += v16;

        auto v17 = 4 - ((int)a4->field_0 & 3);
        if ( v17 < 4 )
            a4->field_0 += v17;

        this->m_data = (anim_info *)a4->field_0;
        auto v18 = 0;
        a4->field_0 += 36 * this->m_size;
        if ( this->m_size )
        {
            auto v19 = 0;
            do
            {
                this->m_data[v19].un_mash(a2, &this->m_data[v19], a4);
                ++v18;
                ++v19;
            }
            while ( v18 < this->m_size );
        }

        auto v20 = 4 - ((int)a4->field_0 & 3);
        if ( v20 < 4 )
            a4->field_0 += v20;
    }
}

template<>
void mashable_vector<anim_map_ptr_entry>::custom_un_mash(generic_mash_header *a2, void *a3, generic_mash_data_ptrs *a4, void *)
{
    if ( this->m_shared )
    {
        auto v7 = 8 - ((int)a4->field_4 & 7);
        if ( v7 < 8 )
        {
            a4->field_4 += v7;
        }

        auto v8 = (int)a4->field_4;
        auto v24 = *(DWORD *)v8;
        auto v9 = (int *)(v8 + 4);
        auto v10 = (uint8_t *)(v8 + 16);
        a4->field_4 = (uint8_t *)(v8 + 4);
        auto v11 = *(DWORD *)(v8 + 4);
        auto v12 = 8 - (((BYTE)v8 + 16) & 7);
        auto a4a = v9;
        a4->field_4 = v10;
        if ( v12 < 8 )
        {
            a4->field_4 = &v10[v12];
        }

        auto v13 = 4 - ((int)a4->field_4 & 3);
        if ( v13 < 4 )
        {
            a4->field_4 += v13;
        }

        auto v14 = this->m_size;
        this->m_data = (anim_map_ptr_entry *)a4->field_4;
        a4->field_4 += 0x10 * v14;
        if ( v9[2] )
        {
            a4->field_0 += v24;
            a4->field_4 += v11 - 16 * this->m_size;
        }
        else
        {
            auto v15 = 0;
            if ( this->m_size )
            {
                auto v16 = 0;
                do
                {
                    this->m_data[v16].field_8.custom_un_mash(a2, &this->m_data[v16].field_8, a4, nullptr);
                    ++v15;
                    ++v16;
                }
                while ( v15 < this->m_size );

                v9 = a4a;
            }
        }

        ++v9[2];
        auto v17 = 4 - ((int)a4->field_4 & 3);
        if ( v17 < 4 )
        {
            a4->field_4 += v17;
        }
    }
    else
    {
        auto v18 = 8 - ((int)a4->field_0 & 7);
        if ( v18 < 8 )
            a4->field_0 += v18;

        auto v19 = 4 - ((int)a4->field_0 & 3);
        if ( v19 < 4 )
            a4->field_0 += v19;

        auto v20 = this->m_size;
        this->m_data = (anim_map_ptr_entry *)a4->field_0;
        auto v21 = 0;
        a4->field_0 += 16 * v20;
        if ( this->m_size )
        {
            auto v22 = 0;
            do
            {
                this->m_data[v22].field_8.custom_un_mash(a2, &this->m_data[v22].field_8, a4, nullptr);
                ++v21;
                ++v22;
            }
            while ( v21 < this->m_size );
        }

        auto v23 = 4 - ((int)a4->field_0 & 3);
        if ( v23 < 4 )
        {
            a4->field_0 += v23;
        }
    }
}


void mashable_vector_patch() {
    {
        FUNC_ADDRESS(address, &mashable_vector<resource_directory *>::custom_un_mash);
        REDIRECT(0x0051F70B, address);
    }

#if 0
    {
        FUNC_ADDRESS(address, &mashable_vector<resource_location>::custom_un_mash);
        REDIRECT(0x0051F718, address);
    }
#endif
}
