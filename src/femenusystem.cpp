#include "femenusystem.h"

#include "common.h"
#include "femenu.h"
#include "func_wrapper.h"
#include "input_mgr.h"
#include "utility.h"
#include "vtbl.h"

#include <cassert>

VALIDATE_SIZE(FEMenuSystem, 0x2C);

bool getButtonState(int a2, int a3);

FEMenuSystem::FEMenuSystem(int a2, int a3) {
    if constexpr (1) {
        this->field_10 = a2;
        this->m_vtbl = 0x00893A98;
        auto *v4 = static_cast<FEMenu **>(operator new(4 * a2));

        this->field_8 = a3;
        this->field_4 = v4;
        this->m_count = 0;
        this->m_index = -1;
        this->field_28 = 0;
        this->field_29 = 1;

        {
            auto *vtbl = bit_cast<fastcall_call(*)[1]>(this->m_vtbl);
            void (__fastcall *func)(void *) = CAST(func, (*vtbl)[7]);

            func(this);
        }

        for (int i = 0; i < this->m_count; ++i) {
            auto *menu = this->field_4[i];

            auto *vtbl = bit_cast<fastcall_call(*)[1]>(menu->m_vtbl);
            void (__fastcall *func)(void *) = CAST(func, (*vtbl)[3]);

            func(menu);
        }
    } else {
        THISCALL(0x00618760, this, a2, a3);
    }
}

void FEMenuSystem::MakeActive(int idx) {
    if constexpr (1) {
        auto idx = this->m_index;
        if (idx != -1) {
            FEMenu *v4 = this->field_4[idx];

            if (idx < 0) {
                v4 = nullptr;
            }

            auto *v5 = this->field_4[idx];
            auto *vtbl = bit_cast<fastcall_call(*)[1]>(v5->m_vtbl);

            void (__fastcall *func)(void *, void *, void *) = CAST(func, (*vtbl)[12]);

            func(v5, nullptr, v4);
            //->OnDeactivate(v5, v4);
        }

        this->m_index = idx;
        if (idx >= 0) {
            auto *v6 = this->field_4[idx];

            auto *vtbl = bit_cast<fastcall_call(*)[1]>(v6->m_vtbl);
            void (__fastcall *func)(void *) = CAST(func, (*vtbl)[11]);

            func(v6);
            //v6->vtbl->onActivate(v6);
        }

        {
            auto *vtbl = bit_cast<std::intptr_t(*)[1]>(this->m_vtbl);
            auto func = (*vtbl)[7];

            assert(func == 0x00629960);
            this->UpdateButtonDown();
        }
    } else {
        THISCALL(0x0060B610, this, idx);
    }
}

void FEMenuSystem::UpdateButtonDown() {
    if constexpr (1) {
        auto *v2 = this->field_18;

        for (int v1 = 0; v1 < 8; ++v1) {
            for (int i = 1; i < 0x4000; i *= 2) {
                auto v4 = getButtonState(i, v1);

                if (v4) {
                    v2[0] |= i;
                } else {
                    v2[0] &= ~(int16_t) i;
                }
            }
            ++v2;
        }
    } else {
        THISCALL(0x00629960, this);
    }
}

void FEMenuSystem::OnButtonPress(int a2, int a3)
{
    if constexpr (1)
	{
        const auto idx = this->m_index;

        if (idx >= 0) {
            auto *v5 = this->field_4[idx];

            {
                auto *vtbl = bit_cast<fastcall_call(*)[1]>(v5->m_vtbl);

                void (__fastcall *field_6C)(void *, void *, int, int) = CAST(field_6C, (*vtbl)[27]);

                field_6C(v5, nullptr, a3, a2);
            }

            auto *vtbl = bit_cast<fastcall_call(*)[1]>(this->m_vtbl);
            int (__fastcall *field_34)(void *) = CAST(field_34, (*vtbl)[13]);

            if (!field_34(this) || a3 == input_mgr::instance()->field_58.field_0 - 1000000)
			{
                if (a2 > 128)
				{
                    if (a2 > 2048)
					{
                        if (a2 == 4096)
						{
                            auto *v19 = this->field_4[this->m_index];

                            auto *vtbl = bit_cast<fastcall_call(*)[1]>(v19->m_vtbl);
                            void (__fastcall *field_64)(void *, void *, int) = CAST(field_64, (*vtbl)[25]);

                            field_64(v19, nullptr, a3);
                        } else if (a2 == 8192) {
                            auto *v18 = this->field_4[this->m_index];

                            auto *vtbl = bit_cast<fastcall_call(*)[1]>(v18->m_vtbl);
                            void (__fastcall *field_68)(void *, void *, int) = CAST(field_68, (*vtbl)[26]);

                            field_68(v18, nullptr, a3);
                        }

                    } else {
                        switch (a2) {
                        case 2048: {
                            auto *v17 = this->field_4[this->m_index];

                            auto *vtbl = bit_cast<fastcall_call(*)[1]>(v17->m_vtbl);
                            void (__fastcall *field_60)(void *, void *, int) = CAST(field_60, (*vtbl)[24]);

                            field_60(v17, nullptr, a3);
                            break;
                        }
                        case 256: {
                            auto *v16 = this->field_4[this->m_index];

                            auto *vtbl = bit_cast<fastcall_call(*)[1]>(v16->m_vtbl);
                            void (__fastcall *field_54)(void *, void *, int) = CAST(field_54, (*vtbl)[21]);

                            field_54(v16, nullptr, a3);
                            break;
                        }
                        case 512: {
                            auto *v15 = this->field_4[this->m_index];

                            auto *vtbl = bit_cast<fastcall_call(*)[1]>(v15->m_vtbl);
                            void (__fastcall *field_58)(void *, void *, int) = CAST(field_58, (*vtbl)[22]);

                            field_58(v15, nullptr, a3);
                            break;
                        }
                        case 1024: {
                            auto *v14 = this->field_4[this->m_index];

                            auto *vtbl = bit_cast<fastcall_call(*)[1]>(v14->m_vtbl);
                            void (__fastcall *field_5C)(void *, void *, int) = CAST(field_5C, (*vtbl)[23]);

                            field_5C(v14, nullptr, a3);
                            break;
                        }
                        }
                    }

                } else if (a2 == 128) {
                    auto *v13 = this->field_4[this->m_index];

                    auto *vtbl = bit_cast<fastcall_call(*)[1]>(v13->m_vtbl);
                    void (__fastcall *field_50)(void *, void *, int) = CAST(field_50, (*vtbl)[20]);

                    field_50(v13, nullptr, a3); // OnTriangle()
                } else {
                    switch (a2) {
                    case 1: {
                        auto *v6 = this->field_4[this->m_index];

                        auto *vtbl = bit_cast<fastcall_call(*)[1]>(v6->m_vtbl);
                        void (__fastcall *field_34)(void *, void *, int) = CAST(field_34, (*vtbl)[13]);

                        field_34(v6, nullptr, a3);
                        break;
                    }
                    case 2: {
                        auto *v7 = this->field_4[this->m_index];

                        auto *vtbl = bit_cast<fastcall_call(*)[1]>(v7->m_vtbl);
                        void (__fastcall *field_38)(void *, void *, int) = CAST(field_38, (*vtbl)[14]);

                        field_38(v7, nullptr, a3);
                        break;
                    }
                    case 4: {
                        auto *v8 = this->field_4[this->m_index];

                        auto *vtbl = bit_cast<fastcall_call(*)[1]>(v8->m_vtbl);
                        void (__fastcall *field_3C)(void *, void *, int) = CAST(field_3C, (*vtbl)[15]);

                        field_3C(v8, nullptr, a3); // character_view::onUp()
                        break;
                    }
                    case 8: {
                        auto *v9 = this->field_4[this->m_index];

                        auto *vtbl = bit_cast<fastcall_call(*)[1]>(v9->m_vtbl);
                        void (__fastcall *field_40)(void *, void *, int) = CAST(field_40, (*vtbl)[16]);

                        field_40(v9, nullptr, a3); // character_view::onDown()
                        break;
                    }
                    case 16: {
                        auto *v10 = this->field_4[this->m_index];

                        auto *vtbl = bit_cast<fastcall_call(*)[1]>(v10->m_vtbl);
                        void (__fastcall *field_44)(void *, void *, int) = CAST(field_44, (*vtbl)[17]);

                        field_44(v10, nullptr, a3);
                        break;
                    }
                    case 32: {
                        auto *v11 = this->field_4[this->m_index];

                        auto *vtbl = bit_cast<fastcall_call(*)[1]>(v11->m_vtbl);
                        void (__fastcall *field_48)(void *, void *, int) = CAST(field_48, (*vtbl)[18]);

                        field_48(v11, nullptr, a3);
                        break;
                    }
                    case 64: {
                        auto *v12 = this->field_4[this->m_index];

                        auto *vtbl = bit_cast<fastcall_call(*)[1]>(v12->m_vtbl);
                        void (__fastcall *field_4C)(void *, void *, int) = CAST(field_4C, (*vtbl)[19]);

                        field_4C(v12, nullptr, a3);
                        break;
                    }
                    default:
                        return;
                    }
                }
            }
        }
    } else {
        THISCALL(0x006187D0, this, a2, a3);
    }
}

void FEMenuSystem::OnButtonRelease(int a2, int a3) {
    if constexpr (1) {
        auto idx = this->m_index;
        if (idx >= 0) {
            auto **v4 = this->field_4;
            if (auto *menu = v4[idx]; menu != nullptr) {
                void (__fastcall *func)(void *, void *, int, int) = CAST(func, get_vfunc(menu->m_vtbl, 0x70));
                func(menu, nullptr, a3, a2);

                //menu->OnButtonRelease(v4[idx], a3, a2);
            }
        }
    } else {
        THISCALL(0x0060B6B0, this, a2, a3);
    }
}

int sub_618A40(int a2, int a3) {
    if constexpr (1) {
        auto v2 = input_mgr::instance()->get_control_state(a2, device_id_t{a3 + 1000000});
        if (v2 > 0.5) {
            return 1;
        }

        if (v2 >= -0.5) {
            return 0;
        }

        return -1;
    } else {
        return CDECL_CALL(0x00618A40, a2, a3);
    }
}

bool getButtonState(int a2, int a3) {
    if constexpr (1) {
        int a2a;
        int v2;
        bool v3;

        if (a2 <= 128) {
            if (a2 != 128) {
                switch (a2) {
                case 1: {
                    return equal(1.0f,
                                 input_mgr::instance()->get_control_state(93,
                                                                          device_id_t{a3 +
                                                                                      1000000}));
                }
                case 2: {
                    return equal(1.0f,
                                 input_mgr::instance()->get_control_state(92,
                                                                          device_id_t{a3 +
                                                                                      1000000}));
                }

                case 4: {
                    if (sub_618A40(110, a3) == -1) {
                        return true;
                    }

                    v2 = sub_618A40(106, a3);
                    goto LABEL_8;
                }
                case 8: {
                    if (sub_618A40(110, a3) == 1) {
                        return true;
                    }

                    v3 = sub_618A40(106, a3) == 1;
                    break;
                }
                case 16: {
                    if (sub_618A40(111, a3) == -1) {
                        return true;
                    }

                    v2 = sub_618A40(107, a3);
                LABEL_8:
                    v3 = v2 == -1;
                    break;
                }
                case 32: {
                    if (sub_618A40(111, a3) == 1) {
                        return true;
                    }

                    v3 = sub_618A40(107, a3) == 1;
                    break;
                }
                case 64: {
                    return equal(1.0f,
                                 input_mgr::instance()->get_control_state(80,
                                                                          device_id_t{a3 +
                                                                                      1000000}));
                }
                default:
                    return false;
                }

                return v3;
            }

            return equal(1.0f,
                         input_mgr::instance()->get_control_state(82, device_id_t{a3 + 1000000}));
        }

        if (a2 > 2048) {
            if (a2 == 4096) {
                a2a = 85;
            } else {
                if (a2 != 8192) {
                    return false;
                }

                a2a = 88;
            }

        } else {
            switch (a2) {
            case 2048:
                a2a = 87;
                break;
            case 256:
                a2a = 83;
                break;
            case 512:
                a2a = 81;
                break;
            case 1024:
                a2a = 84;
                break;
            default:
                return false;
            }
        }
        return equal(1.0f, input_mgr::instance()->get_control_state(a2a, device_id_t{a3 + 1000000}));
    } else {
        return (bool) CDECL_CALL(0x00618A90, a2, a3);
    }
}

void FEMenuSystem::UpdateButtonPresses() {
    //sp_log("FEMenuSystem::UpdateButtonPresses():");

#if 0

    int v2 = 0;
    for (const auto &v3 : this->field_18) {
        for (int i = 1; i < 16384; i *= 2) {
            auto *vtbl = bit_cast<fastcall_call(*)[16]>(this->m_vtbl);

            if (v3 & i && !getButtonState(i, v2)) {
                this->field_18[v2] &= ~static_cast<uint16_t>(i);

                void (__fastcall *func)(void *, void *, int, int) = CAST(func, (*vtbl)[15]);
                if (bit_cast<std::intptr_t>(func) == 0x0060B6B0) {
                    this->OnButtonRelease(i, v2);
                } else {
                    func(this, nullptr, i, v2);
                }

                return;
            }

            if (!(v3 & i) && getButtonState(i, v2)) {
                this->field_18[v2] |= static_cast<uint16_t>(i);

                auto *func = (*vtbl)[14];
                if (bit_cast<std::intptr_t>(func) == 0x006187D0) {
                    this->OnButtonPress(i, v2);
                } else {
                    func(this, i, v2);
                }

                return;
            }
        }

        ++v2;
    }
#else
    THISCALL(0x006298D0, this);
#endif
}

void FEMenuSystem_patch() {
    {
        FUNC_ADDRESS(address, &FEMenuSystem::OnButtonPress);
        //set_vfunc(0x00893AD0, address);
    }

    {
        FUNC_ADDRESS(address, &FEMenuSystem::UpdateButtonPresses);
        //set_vfunc(0x00893E18, address);
    }
}
