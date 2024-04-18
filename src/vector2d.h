#pragma once

#include "float.hpp"

struct vector2d {
    float arr[2];

    const float &operator[](int idx) const {
        return arr[idx];
    }

    float &operator[](int idx) {
        return arr[idx];
    }

    vector2d operator+(const vector2d &a1) const;

    vector2d operator-(const vector2d &a3) const
    {
        return {this->arr[0] - a3[0], this->arr[1] - a3[1]};
    }

    vector2d operator*(float a1) const;

    vector2d & operator*=(float a2);

    vector2d & operator/=(float a2);

    const char *to_string() const;

    float length2() const;

    float length() const;
};
