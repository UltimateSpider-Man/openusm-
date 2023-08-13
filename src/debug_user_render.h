#pragma once

#include "color32.h"

struct mString;

extern void insertDebugString(int index, const mString &a1, color32 color);

extern void renderDebugStrings();
