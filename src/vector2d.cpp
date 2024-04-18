#include "vector2d.h"

#ifdef USE_GLM
#include <glm/gtx/norm.hpp>
#endif

#include <cmath>
#include <cstdio>

const char *vector2d::to_string() const {
    static char str[40];

    sprintf(str, "vector2d{%.2f, %.2f}", arr[0], arr[1]);
    return str;
}

float vector2d::length2() const {
#ifndef USE_GLM
    return (this->arr[0] * this->arr[0] + this->arr[1] * this->arr[1]);
#else
    return glm::length2(glm::vec2{this->arr[0], this->arr[1]});
#endif
}

float vector2d::length() const {
    return std::sqrt(this->length2());
}

vector2d vector2d::operator+(const vector2d &a1) const {
    return vector2d {
        this->arr[0] + a1[0],
        this->arr[1] + a1[1]
    };
}

vector2d vector2d::operator*(float a1) const {
    return vector2d {this->arr[0] * a1, this->arr[1] * a1};
}

vector2d & vector2d::operator*=(float a2)
{
    this->arr[0] *= a2;
    this->arr[1] *= a2;
}

vector2d & vector2d::operator/=(float a2)
{
    this->arr[0] *= (1.0 / a2);
    this->arr[1] *= (1.0 / a2);
}
