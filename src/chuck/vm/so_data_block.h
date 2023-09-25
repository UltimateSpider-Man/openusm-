#pragma once

inline constexpr auto SO_DATA_BLOCK_FLAG_FROM_MASH = 1u;

struct so_data_block
{
    int m_size;
    char *buffer;
    int field_8;

    so_data_block() = default;
    so_data_block(int a2);

    void operator=(int a2);

    void init(int a2);

    void clear();

    auto size() const {
        return m_size;
    }

    bool is_from_mash() const {
        return (this->field_8 & SO_DATA_BLOCK_FLAG_FROM_MASH) != 0;
    }

    auto *get_buffer() const {
        return buffer;
    }

    bool is_address_in_buffer(int a2) const {
        return a2 >= (int)this->buffer && a2 < (int)&this->buffer[this->m_size];
    }
};
