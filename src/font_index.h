#pragma once

struct font_index {
    int value;

    font_index() = default;
    font_index(int p) : value(p) {}

    operator int() const {
        return value;
    }
};
