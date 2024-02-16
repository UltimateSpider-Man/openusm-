#include "input_mgr.h"

#include "common.h"
#include "func_wrapper.h"
#include "game.h"
#include "input.h"
#include "input_device.h"
#include "pc_input_mgr.h"
#include "pc_joypad_device.h"
#include "rumble_manager.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

#include <cassert>

Var<bool> pc_inserted_devices{0x00965EBD};

VALIDATE_SIZE(input_mgr, 0x5Cu);

VALIDATE_SIZE(input_mgr::control_map, 12);

input_mgr::input_mgr() {
    THISCALL(0x005E0EA0, this);
}

input_mgr::~input_mgr() {
    THISCALL(0x005E0870, this);
}

void input_mgr::create_inst() {
    if constexpr (1) {
        input_mgr::instance() = new input_mgr{};
    } else {
        CDECL_CALL(0x005EB840);
    }
}

void input_mgr::register_control(const game_control &control) {
    if constexpr (0) {
        _std::map<int, game_control> *map = &this->control_map;

        assert(map->find(control.name) == map->end());

        auto &v2 = map->operator[](control.name);

        v2 = control;
        //

    } else {
        THISCALL(0x005E0920, this, &control);
    }
}

static Var<uint32_t> PreviousConnected{0x009874F4};

BOOL __cdecl GetDeviceChanges([[maybe_unused]] void *a1,
                              unsigned int *pdwInsertions,
                              unsigned int *pdwRemovals) {
    auto v3 = PreviousConnected();
    auto CurrentConnected = Input::instance()->m_current_connected;
    *pdwInsertions = CurrentConnected & ~PreviousConnected();
    PreviousConnected() = CurrentConnected;
    *pdwRemovals = v3 & ~CurrentConnected;
    return false;
}

void input_mgr::scan_devices() {
    if constexpr (1) {
        if (!pc_inserted_devices()) {
            pc_inserted_devices() = true;
            for (auto i = 0u; i < 4u; ++i) {
                if (pc_input_mgr::instance()->pad[i]) {
                    this->insert_device(pc_input_mgr::instance()->pad[i]);
                }
            }
        }

        uint32_t dwInsertions;
        uint32_t dwRemovals;
        GetDeviceChanges(nullptr, &dwInsertions, &dwRemovals);
        for (auto j = 0u; j < 4u; ++j) {
            pc_input_mgr::instance()->pad[j]->field_8C = pc_input_mgr::instance()->pad[j]->field_88;
            if (((1 << j) & dwInsertions) != 0) {
                pc_input_mgr::instance()->pad[j]->field_88 = 0;
                auto *v4 = pc_input_mgr::instance();
                v4->pad[j]->field_70 = InputOpen(0, j);
                InputGetCapabilities(pc_input_mgr::instance()->pad[j]->field_70,
                                     &pc_input_mgr::instance()->pad[j]->field_48);
                pc_input_mgr::instance()->pad[j]->field_4 = j + 1000000;
                pc_input_mgr::instance()->pad[j]->poll();
            }
        }
        if (this->field_58.field_0 == -1 || this->field_26) {
            auto v5 = 0u;
            while (!pc_input_mgr::instance()->pad[v5]->is_connected()) {
                if (++v5 >= 4) {
                    return;
                }
            }

            this->field_58.field_0 = v5 + 1000000;
            if (g_game_ptr() != nullptr) {
                g_game_ptr()->setup_inputs_p();
            }
        }

    } else {
        THISCALL(0x00599090, this);
    }
}

void input_mgr::frame_advance(Float a2) {
    THISCALL(0x005DAB20, this, a2);
}

float input_mgr::get_control_state(int a2, device_id_t a3) const
{
    TRACE("input_mgr::get_control_state");

    if constexpr (1)
    {
#if 0
        auto it = this->control_map.find(a2);
#else

        auto it = [this, a2]() {
            decltype(this->control_map)::iterator it;
            THISCALL(0x005E47A0, &this->control_map, &it, &a2); 
            assert(it != this->control_map.end());
            return it;
        }();
#endif

        auto &pair = *it;
        auto *control = &pair.second;
        auto &list = control->mapping;
        float a1 = 0.0;
        bool v17 = false;
        auto v16 = list.size();

        for ( auto &axis : list )
        {
            --v16;
            auto id = axis.m_device_id;
            if ( a3.field_0 != -1 && a3.field_0 != id )
            {
                if ( v17 || v16 != 0 )
                {
                    continue;
                }

                id = a3.field_0;
            }

            v17 = true;
            auto *device = this->get_device(device_id_t{id});
            if ( device!= nullptr && device->is_connected() )
            {
                auto v12 = device->get_axis_state(axis.field_4, axis.field_8);
                if ( control->type == 0 )
                {
                    auto func = [](float a1) -> float
                    {
                        if ( a1 < -0.75 )
                        {
                            return -1.0;
                        }

                        if ( a1 > 0.75 )
                        {
                            return 1.0;
                        }

                        return 0.0f;
                    };

                    v12 = func(v12);
                }

                a1 += v12;
            }
        }

        a1 = std::clamp(a1, -1.f, 1.f);
        return a1;
    }
    else
    {
        return (float) THISCALL(0x005D86D0, this, a2, a3);
    }
}

void input_mgr::insert_device(input_device *a2)
{
    if constexpr(0)
    {
        auto *v2 = a2;
        auto id = a2->get_id();
        auto found_device = (input_device *) THISCALL(0x005E8400, &this->field_8, &id);
        found_device = v2;
        
        if ( v2->get_id() < 0xF4240 || v2->get_id() > 0xF4247 )
        {
            if ( v2->get_id() < 0x1E8480 || v2->get_id() > 0x1E8480 )
            {
                if ( v2->get_id() >= 3000000 && v2->get_id() <= 3000000 )
                    *((DWORD *)&this[0xFFFE027F] + v2->get_id() - 0x14) = (DWORD)v2;
            }
            else
            {
                *((DWORD *)&this[0xFFFEAC55] + v2->get_id() - 0xF) = (DWORD)v2;
            }
        }
        else
        {
            *((DWORD *)&this[0xFFFF562B] + v2->get_id() - 0x11) = (DWORD)v2;
        }
    }
    else
    {

        THISCALL(0x005DC140, this, a2);
    }
}

void input_mgr::set_control_state_monkey_callback(float (*a2)(int)) {
    this->m_state_callback = a2;
}

void input_mgr::set_control_delta_monkey_callback(float (*a2)(int)) {
    this->m_delta_callback = a2;
}

input_device *input_mgr::get_device_from_map(device_id_t a2) const {
    return (input_device *) THISCALL(0x005D59B0, this, a2);
}

void input_mgr::poll_devices() {
    if constexpr (1) {
        sp_log("input_mgr::poll_devices(): %d", this->field_8.size());

        auto end = this->field_8.end();
        auto begin = this->field_8.begin();
        if (begin != end) {
            do {
                void (__fastcall *poll)(void *) = CAST(poll, get_vfunc(begin->second->m_vtbl, 0x20));
                poll(begin->second);

                ++begin;

            } while (begin != end);
        }

    } else {
        THISCALL(0x005D5A60, this);
    }
}

float input_mgr::get_control_delta(control_id_t control, device_id_t a3) const {
    if constexpr (1) {
        if (m_delta_callback != nullptr) {
            return m_delta_callback(control);
        }

        auto it = [this, control]() {
            _std::map<int, game_control>::iterator it;

            THISCALL(0x005E47A0, &this->control_map, &it, &control);

            assert(it != control_map.end());

            const auto &ctrl = it->second;
            const auto &dalist = ctrl.mapping;

            return it;
        }();

        auto &dalist = it->second.mapping;
        int size = dalist.size();
        auto *v6 = dalist.m_head;
        auto *v7 = v6->_Next;
        bool v8 = false;
        bool v9 = v6->_Next == v6;
        float result = 0;

        for (auto it_list = dalist.begin(); it_list != dalist.end(); ++it_list) {

            --size;

            int id = it_list->m_device_id;

            if (a3 != -1 && a3 != id) {
                ++it_list;
                if (v8 || size != 0) {
                    continue;
                }

                id = a3;
            }

            v8 = true;

            if (input_device *v12 = this->get_device_from_map(device_id_t{id});
                v12 != nullptr && v12->is_connected()) {
                auto v18 = v7->_Myval.field_4;

                float v17;
                if (it._Ptr->_Myval.second.type != 0)
                {
                    v17 = v12->get_axis_delta(v18, v7->_Myval.field_8);
                }
                else 
                {
                    auto sub_C079D0 = [](float a1) -> float {
                        if (a1 < -0.75) {
                            return -1.0;
                        }

                        float v2 = (a1 <= 0.75 ? 0.0 : 1.0);
                        return v2;
                    };

                    auto axis_old_state = v12->get_axis_old_state(v18, v7->_Myval.field_8);
                    auto v21 = sub_C079D0(axis_old_state);

                    auto axis_state = v12->get_axis_state(v7->_Myval.field_4, v7->_Myval.field_8);
                    auto v16 = sub_C079D0(axis_state);

                    auto v17 = v16 - v21;
                    if (v17 >= 0.0f)
                    {
                        if (v17 > 0.0f)
                        {
                            v17 = 0.0f;
                        }
                    }
                    else
                    {
                        v17 = -1.f;
                    }
                }

                result += v17;
            }
        }

        return result;

        if (!v9) {
            while (1) {
                auto v10 = v7->_Myval.m_device_id;
                auto v11 = size - 1;
                int v21 = v11;
                if (a3.field_0 != -1 && a3.field_0 != v10) {
                    if (v8 || v11 != 0.0) {
                        goto LABEL_29;
                    }

                    v10 = a3.field_0;
                }

                v8 = true;

                if (input_device *v12 = this->get_device_from_map(device_id_t{v10});
                    v12 != nullptr && v12->is_connected()) {
                    auto v18 = v7->_Myval.field_4;

                    float v17;
                    if (it._Ptr->_Myval.second.type) {
                        v17 = v12->get_axis_delta(v18, v7->_Myval.field_8);

                    } else {
                        auto sub_C079D0 = [](float a1) -> float {
                            if (a1 < -0.75) {
                                return -1.0;
                            }

                            float v2;
                            if (a1 <= 0.75) {
                                v2 = 0.0;
                            } else {
                                v2 = 1.0;
                            }

                            return v2;
                        };

                        auto axis_old_state = v12->get_axis_old_state(v18, v7->_Myval.field_8);
                        auto v21 = sub_C079D0(axis_old_state);

                        auto axis_state = v12->get_axis_state(v7->_Myval.field_4,
                                                              v7->_Myval.field_8);
                        auto v16 = sub_C079D0(axis_state);

                        auto v17 = v16 - v21;
                        if (v17 >= 0.0f) {
                            if (v17 > 0.0f) {
                                v17 = 0.0f;
                            }

                        } else {
                            v17 = -1.f;
                        }
                    }

                    result += v17;
                }

            LABEL_29:
                v7 = v7->_Next;
                if (v7 == it._Ptr->_Myval.second.mapping.m_head) {
                    return result;
                }

                size = v21;
            }
        }

        return result;
    } else {
        return (float) THISCALL(0x005D87C0, this, control, a3);
    }
}

input_device *input_mgr::get_device(device_id_t id) const {
    if constexpr (1) {
        static constexpr device_id_t INVALID_DEVICE_ID = {-1};

        auto IS_JOYSTICK_DEVICE = [](device_id_t id) -> bool {
            return id >= 0xF4240 && id <= 0xF4247;
        };

        auto IS_KEYBOARD_DEVICE = [](device_id_t id) -> bool { return id == 0x1E8480; };

        auto IS_MOUSE_DEVICE = [](device_id_t id) -> bool { return id == 0x2DC6C0; };

        assert(id == INVALID_DEVICE_ID ||
                IS_JOYSTICK_DEVICE(id) ||
                IS_KEYBOARD_DEVICE(id) ||
                IS_MOUSE_DEVICE(id));

        if (id.field_0 <= 0x1E8480) {
            if (IS_KEYBOARD_DEVICE(id)) {
                return this->field_50;
            }

            if (IS_JOYSTICK_DEVICE(id)) {
                return (input_device *) *((uint32_t *) &this[0xFFFF562B] + id.field_0 - 0x11);
            }

            return this->get_device_from_map(id);
        }

        if (!IS_MOUSE_DEVICE(id)) {
            return this->get_device_from_map(id);
        }

        return this->field_54;
    } else {
        return (input_device *) THISCALL(0x0055E850, this, id);
    }
}

void input_mgr::clear_mapping() {
    if constexpr (1)
    {
        for (auto &pair : this->control_map)
        {
            pair.second.type = {};
        }
    }
    else
    {
        THISCALL(0x005DC2A0, this);
    }
}

void input_mgr::map_control(int a2, device_id_t a3, int a4) {
    if constexpr (1) {
        int v4 = a3.field_0;

        _std::map<device_id_t, input_device *>::iterator it;
        THISCALL(0x00569CE0, &this->field_8, &it, &a3);

        if (it._Ptr != this->field_8._Myhead) {
            auto *v6 = it._Ptr->_Myval.second;
            if (v6 != nullptr)
            {
                device_axis v9;
                v9.m_device_id = v4;
                v9.field_8 = a4;
                v9.field_4 = v6->get_axis_id(a4);
                if (v9.field_4 != -1)
                {
                    this->map_control(a2, v9);
                }
            }
        }

    } else {
        THISCALL(0x005D8660, this, a2, a3, a4);
    }
}

int input_mgr::map_control(int a2, const device_axis &a3) {
    if constexpr (1) {
        _std::map<int, game_control>::iterator it;

        THISCALL(0x005E47A0, &this->control_map, &it, &a2);

        using node_t = typename _std::list<device_axis>::_Node;

        auto *list = &it._Ptr->_Myval.second.mapping;

        node_t *v3 = list->m_head;

        auto *v5 = (node_t *) THISCALL(0x005E3A10, list, v3, v3->_Prev, a3);
        auto result = THISCALL(0x005E3A50, list, 1u);
        v3->_Prev = v5;
        v5->_Prev->_Next = v5;
        return result;
    } else {
        return THISCALL(0x005D8610, this, a2, &a3);
    }
}

void input_mgr_patch() {
    FUNC_ADDRESS(address, &input_mgr::get_control_delta);
    REDIRECT(0x00552FD4, address);

    {
        FUNC_ADDRESS(address, &input_mgr::get_control_state);
        //SET_JUMP(0x005D86D0, address);
    }

    {
        FUNC_ADDRESS(address, &input_mgr::get_device_from_map);
        //SET_JUMP(0x0055E850, address);
    }
}
