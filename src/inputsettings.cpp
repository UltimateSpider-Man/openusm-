#include "inputsettings.h"

#include "common.h"
#include "func_wrapper.h"
#include "input.h"

Var<InputSettings *> g_inputSettingsMenu{0x00965C0C};
Var<InputSettings *> g_inputSettingsInGame{0x00965C10};
Var<InputSettings *> g_inputSettings2{0x00965C14};
Var<InputSettings *> g_inputSettings3{0x00965C18};
Var<InputSettings *> g_inputSettings4{0x00965C1C};

VALIDATE_SIZE(InputSettings, 0xE2Cu);

InputSettings::InputSettings() {
    this->field_1 = false;
    this->field_2 = true;
    this->field_3 = false;
    this->field_4 = 0.99000001;
    this->field_8 = 10.0;
    this->field_C = 0;
    this->field_10 = 0;
    this->field_14 = 1.0;
    this->field_18 = {};
}

void InputSettings::internal_struct::sub_821E70() {
    this->field_0 = 0;
    memset(&this->field_4, 0, sizeof(this->field_4));
}

void InputSettings::internal_struct::set_key(InputAction a2, uint32_t a3, int value) {
    this->set(a2, a3, InputType::Key, value);
}

void InputSettings::internal_struct::set_mouse(InputAction a2, uint32_t a3, InputMouse value) {
    this->set(a2, a3, InputType::Mouse, static_cast<int>(value));
}

void InputSettings::internal_struct::set(InputAction a2,
                                         uint32_t a3,
                                         InputType input_type,
                                         int value) {
    if constexpr (1) {
        auto v2 = static_cast<uint32_t>(a2);
        auto v5 = v2 + 1;
        if (v5 <= this->field_0) {
            v5 = this->field_0;
        }

        this->field_0 = v5;
        auto &v6 = this->field_4[v2][a3];
        v6.m_input_type = input_type;
        v6.m_value = value;
        v6.field_8 = 0.0f;

    } else {
        THISCALL(0x00821FD0, this, a2, a3, input_type, value);
    }
}

void InputSettings::internal_struct::operator=(const InputSettings::internal_struct &a2) {
    this->field_0 = a2.field_0;
    std::memcpy(this->field_4, a2.field_4, sizeof(this->field_4));
}

void InputSettings::internal_struct::find_and_clear(InputType input_type, int value) {
    if (this->field_0) {
        for (auto v3 = 0u; v3 < this->field_0; ++v3) {
            for (auto i = 0u; i < 6u; ++i) {
                auto &v4 = this->field_4[v3][i];

                if (v4.m_input_type == input_type && v4.m_value == value) {
                    v4.m_input_type = InputType::None;
                    v4.m_value = 0;
                    v4.field_8 = 0.0f;
                }
            }
        }
    }
}

void InputSettings::internal_struct::find_and_clear(InputType input_type) {
    if (this->field_0) {
        for (auto v2 = 0u; v2 < this->field_0; ++v2) {
            for (auto i = 0u; i < 6u; ++i) {
                auto &v3 = this->field_4[v2][i];

                if (v3.m_input_type == input_type) {
                    v3.m_input_type = InputType::None;
                    v3.m_value = 0;
                    v3.field_8 = 0.0f;
                }
            }
        }
    }
}

void InputSettings::internal_struct::clear(int a2, int a3) {
    auto &v3 = this->field_4[a2][a3];
    v3.m_input_type = InputType::None;
    v3.m_value = 0;
    v3.field_8 = 0.0f;
}

float InputSettings::internal_struct::sub_821E90(InputAction a2) {
    if constexpr (1) {
        auto idx = static_cast<uint32_t>(a2);
        if (idx >= this->field_0) {
            return 0.0f;
        }

        auto result = 0.0f;

        float v17 = 0.0;
        if (this->field_4[idx][0].m_input_type != InputType::None) {
            auto v2 = this->field_4[idx][0].field_8;
            auto v5 = std::abs(v2);
            if (v5 > 0.0f) {
                result = v2;
                v17 = v5;
            }
        }

        if (this->field_4[idx][1].m_input_type != InputType::None) {
            auto v6 = this->field_4[idx][1].field_8;
            auto v7 = std::abs(v6);
            if (v7 > v17) {
                result = v6;
                v17 = v7;
            }
        }

        if (this->field_4[idx][2].m_input_type != InputType::None) {
            auto v8 = this->field_4[idx][2].field_8;
            auto v9 = std::abs(v8);
            if (v9 > v17) {
                result = v8;
                v17 = v9;
            }
        }

        if (this->field_4[idx][3].m_input_type != InputType::None) {
            auto v10 = this->field_4[idx][3].field_8;
            auto v11 = std::abs(v10);
            if (v11 > v17) {
                result = v10;
                v17 = v11;
            }
        }

        if (this->field_4[idx][4].m_input_type != InputType::None) {
            auto v12 = this->field_4[idx][4].field_8;
            auto v13 = std::abs(v12);
            if (v13 > v17) {
                result = v12;
                v17 = v13;
            }
        }

        if (this->field_4[idx][5].m_input_type != InputType::None) {
            auto v16 = this->field_4[idx][5].field_8;
            if (std::abs(v16) > v17) {
                result = v16;
            }
        }

        return result;

    } else {
        float (__fastcall *func)(void *, void *, uint32_t) = CAST(func, 0x00821E90);

        return func(this, nullptr, static_cast<uint32_t>(a2));
    }
}

void sub_5828B0() {
    auto v0 = Input::instance()->sub_820080();
    if (v0 > 4) {
        v0 = 4;
    }

    auto v1 = 3;
    if (v0 > 0) {
        auto v2 = v0;
        do {
            g_inputSettingsMenu()->field_18.set(InputAction::Jump, v1, (InputType) v1, 21);
            g_inputSettingsMenu()->field_18.set(InputAction::Kick, v1, (InputType) v1, 24);
            g_inputSettingsMenu()->field_18.set(InputAction::Forward, v1, (InputType) v1, 4);
            g_inputSettingsMenu()->field_18.set(InputAction::Backward, v1, (InputType) v1, 3);
            g_inputSettingsMenu()->field_18.set(InputAction::TurnLeft, v1, (InputType) v1, 2);
            g_inputSettingsMenu()->field_18.set(InputAction::TurnRight, v1, (InputType) v1, 1);
            ++v1;
            --v2;
        } while (v2);
    }
}
