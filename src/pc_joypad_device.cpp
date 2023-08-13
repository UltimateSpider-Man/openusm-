#include "pc_joypad_device.h"

#include "app.h"
#include "common.h"
#include "femanager.h"
#include "frontendmenusystem.h"
#include "func_wrapper.h"
#include "game.h"
#include "input.h"
#include "inputsettings.h"
#include "pausemenusystem.h"
#include "utility.h"
#include "variables.h"

VALIDATE_SIZE(InputState, 0x20);

VALIDATE_SIZE(pc_joypad_device, 0x9Cu);
VALIDATE_OFFSET(pc_joypad_device, field_70, 0x70);

VALIDATE_SIZE(InputCapabilities, 0x28);

int sub_81D1C0(int a1) {
    if constexpr (1) {
        auto result = 0u;
        if (!a1) {
            uint32_t v2 = Input::instance()->field_129D0;
            if (v2) {
                result = 1;
            }

            if (v2 > 1) {
                result |= 2u;
            }

            if (v2 > 2) {
                result |= 4u;
            }

            if (v2 > 3) {
                result |= 8u;
            }
        }

        return result;
    } else {
        return CDECL_CALL(0x0081D1C0, a1);
    }
}

int InputOpen(int a1, unsigned int a2) {
    if constexpr (1) {
        uint32_t result;

        if (a1 || a2 >= Input::instance()->field_129D0) {
            result = 0;
        } else {
            result = a2 + 1;
        }

        return result;
    } else {
        return CDECL_CALL(0x0081D0F0, a1, a2);
    }
}

#include <xinput.h>

void InputGetCapabilities(int a1, InputCapabilities *pCapabilities) {
    if constexpr (1) {
        if (Input::instance()->sub_820570(a1 - 1)) {
            pCapabilities->field_0 = XINPUT_DEVTYPE_GAMEPAD;
        }

        if (Input::instance()->sub_820590(a1 - 1)) {
            pCapabilities->field_20 = 0xFFFF;
            pCapabilities->field_24 = 0xFFFF;
        }
    }

    else {
        CDECL_CALL(0x0081D180, a1, pCapabilities);
    }
}

pc_joypad_device::pc_joypad_device(int in_port) : input_device() {
    if constexpr (0) {
        auto v3 = (!g_master_clock_is_up());

        this->m_vtbl = 0x0088EA80;
        if (v3) {
            timeBeginPeriod(1u);
        }

        this->field_94 = timeGetTime();
        this->field_98 = 0;
        auto v4 = sub_81D1C0(0);

        this->field_4 = in_port + 1000000;
        this->field_90 = in_port;
        auto v5 = v4 & (1 << in_port);
        if (v5) {
            this->field_8C = false;
            this->field_88 = false;
        } else {
            this->field_8C = true;
            this->field_88 = true;
        }

        if (v5) {
            std::memset(&this->m_axis_state, 0, sizeof(this->m_axis_state));
            auto v6 = InputOpen(0, in_port);
            this->field_70 = v6;
            if (v6) {
                InputGetCapabilities(v6, &this->field_48);
            }

            std::memset(&this->field_74, 0, sizeof(this->field_74));
        }

    } else {
        THISCALL(0x005991E0, this, in_port);
    }
}

float pc_joypad_device::get_axis_state(Axis a2, [[maybe_unused]] int a3) {
    float result;

    if (a2 == 22) {
        result = (this->field_88 == 1);

    } else {
        InputState input_state = this->m_axis_state;
        result = this->get_axis_state(a2, input_state);
    }
    return result;
}

float pc_joypad_device::get_axis_old_state(Axis a2, [[maybe_unused]] int a3) {
    if (a2 == 22) {
        return this->field_8C;
    }

    auto v5 = this->m_axis_old_state;
    return this->get_axis_state(a2, v5);
}

float pc_joypad_device::get_axis_delta(Axis a2, [[maybe_unused]] int a3) {
    if (a2 == 22) {
        return (this->field_88 - this->field_8C);
    }

    InputState axis_state;
    std::memcpy(&axis_state, &this->m_axis_state, sizeof(axis_state));
    auto v7 = this->get_axis_state(a2, axis_state);

    auto a2a = v7;
    std::memcpy(&axis_state, &this->m_axis_old_state, sizeof(axis_state));
    return a2a - this->get_axis_state(a2, axis_state);
}

bool pc_joypad_device::is_connected() {
    return this->field_88 == 0;
}

void pc_joypad_device::clear_state() {
    std::memset(&this->m_axis_state, 0, sizeof(this->m_axis_state));
    std::memset(&this->m_axis_old_state, 0, sizeof(this->m_axis_old_state));
}

int InputGetState(unsigned int dwUserIndex, InputState *pState) {
    if constexpr (1) {
        Input::instance()->poll();
        auto *v2 = (InputSettings *) *(&Input::instance()->m_current_connected + dwUserIndex);
        auto &v20 = pState->field_4;
        *(uint32_t *) &pState->field_4 = 0;
        *(uint32_t *) &pState->m_punch = 0;
        *(uint32_t *) &pState->field_C = 0;
        pState->field_10 = 0;
        pState->field_14 = 0;
        auto *v3 = &v2->field_18;
        pState->field_18 = 0;
        pState->field_1C = 0;

        constexpr float flt_8BD430 = -32767.0f;
        constexpr float flt_889EE4 = 32767.0f;

        int v4 = v3->sub_821E90(InputAction::TurnLeft) * flt_8BD430;
        int v5 = v3->sub_821E90(InputAction::TurnRight) * flt_889EE4;
        auto v6 = std::abs(v5);
        auto v7 = std::abs(v4);
        if (v7 <= v6) {
            if (v7 != v6) {
                pState->field_10 = v5;
            }
        } else {
            pState->field_10 = v4;
        }

        int v8 = v3->sub_821E90(InputAction::Forward) * flt_889EE4;
        int v9 = v3->sub_821E90(InputAction::Backward) * flt_8BD430;
        auto v10 = std::abs(v9);
        auto v11 = std::abs(v8);
        if (v11 <= v10) {
            if (v11 != v10)
                pState->field_14 = v9;
        } else {
            pState->field_14 = v8;
        }

        int v12 = v3->sub_821E90(InputAction::CameraLeft) * flt_8BD430;
        int v13 = v3->sub_821E90(InputAction::CameraRight) * flt_889EE4;
        auto v14 = std::abs(v13);
        auto v15 = std::abs(v12);
        if (v15 <= v14) {
            if (v15 != v14) {
                pState->field_18 = v13;
            }
        } else {
            pState->field_18 = v12;
        }

        int v16 = v3->sub_821E90(InputAction::CameraUp) * flt_889EE4;
        int v17 = v3->sub_821E90(InputAction::CameraDown) * flt_8BD430;
        auto v18 = std::abs(v17);
        auto v19 = std::abs(v16);
        if (v19 <= v18) {
            if (v19 != v18) {
                pState->field_1C = v17;
            }
        } else {
            pState->field_1C = v16;
        }

        constexpr float flt_871978 = 255.f;

        pState->m_jump = v3->sub_821E90(InputAction::Jump) * flt_871978;
        pState->m_stick_to_walls = v3->sub_821E90(InputAction::StickToWalls) * flt_871978;
        pState->m_punch = v3->sub_821E90(InputAction::Punch) * flt_871978;
        pState->m_kick = v3->sub_821E90(InputAction::Kick) * flt_871978;
        pState->m_black_button = v3->sub_821E90(InputAction::BlackButton) * flt_871978;
        pState->m_throw_web = v3->sub_821E90(InputAction::ThrowWeb) * flt_871978;
        pState->field_C = v3->sub_821E90(static_cast<InputAction>(10u)) * flt_871978;
        pState->field_D = v3->sub_821E90(static_cast<InputAction>(11u)) * flt_871978;
        if (0.0f != v3->sub_821E90(InputAction::Pause)) {
            v20 |= 0x10u;
        }

        if (0.0f != v3->sub_821E90(InputAction::BackButton)) {
            v20 |= 0x20u;
        }

        if (0.0f != v3->sub_821E90(static_cast<InputAction>(14u))) {
            v20 |= 0x40u;
        }

        if (0.0f != v3->sub_821E90(InputAction::CameraCenter)) {
            v20 |= 0x80u;
        }

        if (0.0f != v3->sub_821E90(static_cast<InputAction>(24u))) {
            v20 |= 1u;
        }

        if (0.0f != v3->sub_821E90(static_cast<InputAction>(25u))) {
            v20 |= 2u;
        }

        if (0.0f != v3->sub_821E90(static_cast<InputAction>(26u))) {
            v20 |= 4u;
        }

        if (0.0f != v3->sub_821E90(static_cast<InputAction>(27u))) {
            v20 |= 8u;
        }

        return 0;

    } else {
        return CDECL_CALL(0x0081D240, dwUserIndex, pState);
    }
}

void pc_joypad_device::poll() {
    if constexpr (1) {
        static Var<bool> dword_967CE4{0x00967CE4};

        if (this->field_70 == 1) {
            if ((g_femanager().m_pause_menu_system != nullptr && g_femanager().m_pause_menu_system->m_index != -1) ||
                (g_femanager().m_fe_menu_system != nullptr && g_femanager().m_fe_menu_system->m_index != -1) ||
                dword_967CE4()) {
                if (((g_femanager().m_pause_menu_system != nullptr && g_femanager().m_pause_menu_system->m_index != -1) ||
                     (g_femanager().m_fe_menu_system != nullptr && g_femanager().m_fe_menu_system->m_index != -1)) &&
                    dword_967CE4()) {
                    dword_967CE4() = false;
                    Input::instance()->sub_8203F0(0, g_inputSettingsMenu());
                }
            } else {
                dword_967CE4() = true;
                Input::instance()->sub_8203F0(0, g_inputSettingsInGame());
            }
        }

        if (this->field_70 && !this->field_88) {
            if (this->field_8C) {
                this->clear_state();
            }

            uint32_t v3 = this->field_70;
            std::memcpy(&this->m_axis_old_state,
                        &this->m_axis_state,
                        sizeof(this->m_axis_old_state));
            auto v2 = InputGetState(v3, &this->m_axis_state);
            if (v2 != 0) {
                assert(0);

                this->field_98 = 0;
                mString a1{0, "state %d", v2};

                return;
            }

            Var<BOOL> dword_9363E4{0x009363E4};

            if (g_game_ptr() != nullptr) {
                if (dword_9363E4()) {
                    if (this->m_axis_state.m_black_button > 50u) {
                        dword_9363E4() = false;
                    }
                }

                if (!dword_9363E4() && this->m_axis_state.m_black_button == 0) {
                    dword_9363E4() = true;
                }
            }
        }

    } else {
        THISCALL(0x0058E5C0, this);
    }
}

double sub_58E7F0(int a1) {
    float result = 0.0f;
    float v3 = a1;
    auto a1a = v3;
    if (v3 > 7000.0f || a1a < -7000.0f) {
        if (a1 <= 0) {
            result = -(((double) -a1 - 7000.0f) * 0.000038809329f);
        } else {
            result = (a1a - 7000.0f) * 0.000038809329f;
        }
    }

    if (std::abs(result) < 0.1f) {
        result = 0.0f;
    }

    return result;
}

float pc_joypad_device::get_axis_state(Axis axis, InputState input_state) {
    auto result = 0.0f;

    float v5;
    bool v4;
    double a2a;
    switch (axis) {
    case 0: {
        if ((input_state.field_4 & 4) != 0) {
            return (-1.0f);
        }

        v4 = (input_state.field_4 & 8) == 0;

        if (v4) {
            return 0.0f;
        }

        return 1.0f;
    }
    case 1:
        if ((input_state.field_4 & 1) != 0) {
            return (-1.0f);
        }

        v4 = (input_state.field_4 & 2) == 0;

        if (v4) {
            return 0.0f;
        }

        return 1.0f;

    case 2: {
        a2a = sub_58E7F0(input_state.field_10);
        if ((input_state.field_4 & 8) != 0) {
            result = 1.0f;
            v5 = (-1.0f);

            if (a2a == v5) {
                return 0.0f;
            }

            return result;
        }

        if ((input_state.field_4 & 4) == 0) {
            return a2a;
        }

        result = (-1.0f);
        v5 = 1.0f;
        if (a2a == v5) {
            return 0.0f;
        }

        return result;
    }
    case 3: {
        a2a = -sub_58E7F0(input_state.field_14);
        if ((input_state.field_4 & 1) != 0) {
            result = (-1.0f);
            v5 = 1.0f;
        } else {
            if ((input_state.field_4 & 2) == 0) {
                return a2a;
            }
        }

        if (a2a == v5) {
            return 0.0f;
        }

        return result;
    }
    case 4:
        return sub_58E7F0(input_state.field_10);
    case 5:
        return -sub_58E7F0(input_state.field_14);
    case 6: {
        v4 = (input_state.field_4 & 0x40) == 0;
        if (v4) {
            return 0.0f;
        }

        return 1.0f;
    }
    case 7:
        return sub_58E7F0(input_state.field_18);
    case 8:
        return -sub_58E7F0(input_state.field_1C);
    case 9: {
        if ((input_state.field_4 & 0x80u) != 0) {
            return 1.0f;
        }

        return 0.0f;
    }
    case Axis::Jump: {
        if (input_state.m_jump > 30u) {
            return 1.0f;
        }

        return 0.0f;
    }
    case 11: {
        if (input_state.m_stick_to_walls > 30u) {
            return 1.0f;
        }

        return 0.0f;
    }
    case 12:
    case 15: {
        return 0.0f;
    }
    case 13: {
        if (input_state.m_punch > 30u) {
            return 1.0f;
        }

        return 0.0f;
    }
    case 14: {
        if (input_state.m_kick > 30u) {
            return 1.0f;
        }

        return 0.0f;
    }
    case 16: {
        return (input_state.field_C * 0.0039215689f);
    }
    case 17: {
        return (input_state.field_D * 0.0039215689f);
    }
    case 18: {
        if (input_state.m_black_button <= 30u) {
            return 0.0f;
        }

        return 1.0f;
    }
    case 19: {
        if (input_state.m_throw_web > 30u) {
            return 1.0f;
        }

        return 0.0f;
    }
    case 20: {
        v4 = (input_state.field_4 & 0x10) == 0;
        if (v4) {
            return 0.0f;
        }

        return 1.0f;
    }
    case 21: {
        v4 = (input_state.field_4 & 0x20) == 0;
        if (v4) {
            return 0.0f;
        }

        return 1.0f;
    }
    case 22: {
        v4 = this->field_88 == 0;
        if (v4) {
            return 0.0f;
        }

        return 1.0f;
    }
    default:

        assert(0 && "Invalid axis.");

        return result;
    }
}

void pc_joypad_device_patch() {
    {
        FUNC_ADDRESS(address, &pc_joypad_device::poll);
        set_vfunc(0x0088EAA0, address);
    }
}
