#pragma once

#include "float.hpp"

struct euler_direction {
    float m_heading;
    float m_pitch;

    euler_direction();

    void set(Float a1, Float a2);
};
