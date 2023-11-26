#pragma once

#include "float.hpp"

#include <cassert>
#include <cstdint>

struct vector3d;
struct line_marker_base;
struct entity_base;

struct Grid;

template<typename T, uint32_t Num>
struct fixed_vector {
    static constexpr auto N = Num;

    T m_data[Num];

    uint32_t m_size{0};

    auto size() {
        return m_size;
    }

    auto &at(uint32_t index) {
        assert(index < m_size);

        return this->m_data[index];
    }

    void sub_CBF970(int index) {
        assert(index >= 0 && index < this->m_size);

        --this->m_size;
        for (int i = index; i < this->m_size; ++i) {
            this->m_data[i] = this->m_data[i + 1];
        }
    }

    void push_back(const T &a1) {
        assert(this->m_size < Num);

        this->m_data[this->m_size++] = a1;
    }

    void sort();

    void resize(int size, const T &a3);

    void emplace_back(Grid *grid,
                      const vector3d &a3,
                      const vector3d &a4,
                      const vector3d &a5,
                      Float a6,
                      line_marker_base *a7,
                      entity_base *a8);
};
