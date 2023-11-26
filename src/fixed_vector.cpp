#include "fixed_vector.h"

#include "ai_find_best_swing_anchor.h"
#include "func_wrapper.h"
#include "grid.h"
#include "quick_anchor_info.h"
#include "vector4d.h"

#include <cassert>

template<>
void fixed_vector<quick_anchor_info, 100>::sort() {
    auto *begin = this->m_data;
    auto *end = &this->m_data[m_size];
    auto size = end - begin;

    ::sort(begin, end, size);
}

template<>
void fixed_vector<quick_anchor_info, 100>::resize(int size, const quick_anchor_info &a3) {
    assert(unsigned(size) <= N);

    auto v3 = this->m_size;
    if (v3 < size) {
        if (v3 < size) {
            auto v4 = size - v3;
            do {
                this->m_data[this->m_size] = a3;

                --v4;
                ++this->m_size;
            } while (v4);

            assert(this->m_size == size);
        }
    } else {
        this->m_size = size;
    }
}

template<>
void fixed_vector<quick_anchor_info, 100>::emplace_back(Grid *grid,
                                                        const vector3d &a3,
                                                        const vector3d &a4,
                                                        const vector3d &a5,
                                                        Float a6,
                                                        line_marker_base *a7,
                                                        entity_base *a8) {
    if constexpr (1) {
        vector4d a2a{a3[0], a3[1], a3[2], 1.f};

        if (grid == nullptr || !grid->sub_48CEB0(a2a)) {
            quick_anchor_info anchor_info{};

            anchor_info.m_position = a3;

            anchor_info.m_normal = a4;

            anchor_info.field_18 = a5;

            anchor_info.field_24 = a6;
            anchor_info.field_28 = (entity_base *) a7;
            anchor_info.field_2C = a8;
            if (this->m_size >= 99) {
                this->sort();

                this->resize(50, quick_anchor_info{});
            }

            this->push_back(anchor_info);

        } else {
            THISCALL(0x004900B0, this, grid, &a3, &a4, &a5, a6, a7, a8);
        }
    }
}
