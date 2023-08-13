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
