#pragma once

struct vector2d;

struct vector2di {
    int x, y;

    vector2di() = default;

    vector2di(int a1, int a2);

    vector2di(const vector2d &a2);
};
