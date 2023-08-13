#include "color32.h"

color color32::to_color() {
    auto result = color{this->field_0[2] / 255.f,
                        this->field_0[1] / 255.f,
                        this->field_0[0] / 255.f,
                        this->field_0[3] / 255.f};
    return result;
}

int color32::to_int(color32 color) {
    auto v1 = (color[3] << 24);
    auto v2 = (color[2] << 16) | v1;
    auto v3 = (color[1] << 8) | v2;
    return (color[0] | v3);
}

uint8_t color32::get_alpha() {
    return this->field_0[3];
}

void color32::set_alpha(uint8_t v) {
    field_0[3] = v;
}

void color32::set_blue(uint8_t v) {
    field_0[2] = v;
}

void color32::set_green(uint8_t v) {
    field_0[1] = v;
}

void color32::set_red(uint8_t v) {
    field_0[0] = v;
}
