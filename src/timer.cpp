#include "timer.h"

#include "common.h"
#include "func_wrapper.h"

#include <profileapi.h>

VALIDATE_SIZE(Timer, 0x58);

Var<Timer *> g_timer{0x00965BF0};

Timer::Timer(Float a2, Float a3) {
    this->field_24 = QueryPerformanceFrequency(&this->field_0);
    this->field_8.LowPart = 0;
    this->field_8.HighPart = 0;
    this->field_10 = 0;
    this->field_14 = 0;
    this->field_1C = 0;
    this->field_20 = 0;
    this->field_3C = 0;
    this->field_54 = 0;
    this->field_40 = 0;
    this->field_44 = 0;
    this->field_48 = 0;
    this->field_4C = 0;
    this->field_50 = 0;
    this->field_18 = 1000;
    this->field_28 = a2;
    this->field_2C = a3;
    this->field_38 = 1;
    this->field_30 = 1.0 / a2;
    this->field_34 = 1.0 / a3;
}

double Timer::sub_5821D0() {
    return (double) THISCALL(0x005821D0, this);
}

void Timer::sub_582180() {
    if (this->field_24) {
        QueryPerformanceCounter(&this->field_8);
        this->field_3C = 0;
        this->field_54 = 0;
        this->field_40 = 0;
        this->field_44 = 0;
        this->field_4C = 0;
    } else {
        DWORD v2 = GetTickCount();
        this->field_3C = 0;
        this->field_54 = 0;
        this->field_40 = 0;
        this->field_44 = 0;
        this->field_4C = 0;
        this->field_1C = v2;
    }
}
