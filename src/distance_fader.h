#pragma once

#include "float.hpp"
#include "variable.h"

struct distance_fader {
    //0x0051A200
    static int get_fade_index_for_fade_distance(Float a1);

    //0x0051A330
    static int estimate_fade_index_for_bounding_sphere(Float sphere_radius);

    static inline Var<float[16]> fade_radii{0x00921EC8};

    static inline Var<float[16]> fade_distances{0x00921E48};

    static inline Var<float[16]> fade_distances2{0x00921E88};
};

inline constexpr auto FADE_DISTANCE_MASK = 0xF;
