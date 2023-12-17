#pragma once

#include "variable.h"

struct BaseComponent;

struct CharComponentManager {
    static inline Var<int> iCurrNumComponents {0x0096A558};

    static inline Var<BaseComponent **> pCompArray {0x0096A55C};
};
