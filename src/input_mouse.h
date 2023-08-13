#pragma once

#include <cstdint>

enum class InputMouse : std::uint8_t {
    Unknown = 0,
    Unknown1 = 1,
    Unknown2 = 2,
    Unknown3 = 3,
    Unknown4 = 4,
    LookUp = 5,
    LookDown = 6,
    LookLeft = 7,
    LookRight = 8,
    LeftButton = 9,
    RightButton = 10,
    MiddleButton = 11,
};
