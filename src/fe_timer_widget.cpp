#include "fe_timer_widget.h"

#include "common.h"
#include "func_wrapper.h"

VALIDATE_SIZE(fe_timer_widget, 0x30);

fe_timer_widget::fe_timer_widget() {
    this->m_vtbl = 0x00894F48;
    this->field_2C = 540.0;
    this->field_4 = nullptr;
    this->field_8 = nullptr;
    this->field_C = nullptr;
    this->field_10 = nullptr;
    this->field_14 = nullptr;
    this->field_18 = nullptr;
    this->field_1C = nullptr;
    this->field_24 = 0.0;
    this->field_28 = 0;
    this->field_29 = 0;
    this->field_2A = 0;
}

void fe_timer_widget::SetShown(bool a2) {
    THISCALL(0x006280F0, this, a2);
}
