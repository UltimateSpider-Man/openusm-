#pragma once

struct so_data_block
{
    int m_size;
    char *buffer;
    int field_8;

    auto size() const {
        return m_size;
    }

    auto *get_buffer() const {
        return buffer;
    }

    bool is_address_in_buffer(int a2) const {
        return a2 >= (int)this->buffer && a2 < (int)&this->buffer[this->m_size];
    }
};
