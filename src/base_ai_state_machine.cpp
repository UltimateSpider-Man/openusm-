#include "base_ai_state_machine.h"

#include "ai_state_swing.h"
#include "base_ai_core.h"
#include "base_ai_res_state_graph.h"
#include "base_state.h"
#include "common.h"
#include "func_wrapper.h"
#include "launch_layer_state.h"
#include "log.h"
#include "mashed_state.h"
#include "memory.h"
#include "mstring.h"
#include "resource_key.h"
#include "state_trans_action.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

#include <cassert>

namespace ai {

VALIDATE_SIZE(ai_state_machine, 0x48u);

ai_state_machine::ai_state_machine(ai::ai_core *a2, const ai::state_graph *a3, string_hash a4) {
    this->my_curr_mode = PRE_TEST;
    this->my_core = a2;
    this->field_C = a3;
    this->my_parent = nullptr;
    this->field_1C = {};
    auto &v5 = this->field_30;
    this->field_2C = 0;

    this->field_38 = nullptr;
    this->field_3C = nullptr;
    this->field_40 = nullptr;
    this->field_8 = a2->field_64;
    auto *v6 = this->field_C;
    this->my_curr_state = nullptr;
    this->field_14 = nullptr;
    v5.source_hash_code = a4.source_hash_code;
    this->field_44 = 2;
    auto v7 = v6->get_size_memory_block();
    if (v7 > 0) {
        this->field_38 = mem_alloc(v7);
    }

    this->field_34 = true;
}

void ai_state_machine::advance_curr_state(Float a2, bool a3) {
    TRACE("ai::ai_state_machine::advance_curr_state");

    if constexpr (1) {
        assert(my_curr_state != nullptr);

        state_trans_messages v4 {TRANS_TOTAL_MSGS};

        if (!a3 || this->my_curr_state->is_flag_set(mashed_state::IS_INTERRUPT_STATE)) {
            printf("frame_advance: 0x%08X\n", this->my_curr_state->m_vtbl);
            v4 = this->my_curr_state->frame_advance(a2);
        }

        if (v4 == TRANS_TOTAL_MSGS) {
            if (this->my_curr_mode != 2) {
                this->process_transition(a2);
            }
        } else {
            this->process_transition_message(a2, v4);
        }

        assert(my_curr_state != nullptr);

    } else {
        THISCALL(0x0069F870, this, a2, a3);
    }
}

state_trans_action ai_state_machine::sub_697AC0(Float a3, const state_trans_action &a4) {

    if (a4.the_action != 4)
    {
        if (this->field_34)
        {
           auto *v5 = this->field_C; 
           auto v6 = v5->field_20.size();
           if (v6 > 0)
           {
               auto &v7 = v5->field_20;

               auto it = v7.begin();
               auto end = v7.end();
               while (it != end)
               {
                    auto *state = *it._Ptr;
                    state->activate(this, nullptr, nullptr, nullptr, static_cast<base_state::activate_flag_e>(1));
                    auto trans_action = state->check_transition(a3);

                    state->deactivate(nullptr);
                    if (!(trans_action.the_action == 3 || trans_action.the_action == 4)) {
                        return trans_action;
                    }

                    ++it;
               }

           }

        }
    }

    return a4;
}

void ai_state_machine::process_transition(Float a2) {
    TRACE("ai_state_machine::process_transition");

    if constexpr (1) {
        sp_log("0x%08X", this->my_curr_state->m_vtbl);
        state_trans_action a3 = this->my_curr_state->check_transition(a2);

        a3 = this->sub_697AC0(a2, a3);

        ai::state_trans_action v3 = this->check_keyword_overrides(a3);

        a3.the_action = v3.the_action;

        a3.field_4 = v3.field_4;
        a3.the_message = v3.the_message;
        a3.field_C = v3.field_C;
        if (a3.the_action) {
            if (a3.the_action == 1) {
                this->process_return();
            } else {
                if (a3.the_action == state_trans_action::MACHINE_EXIT) {
                    this->process_machine_exit(a3.the_message);
                }
            }
        } else {
            this->transition_state(a3.field_4, a3.field_C);
        }
    } else {
        THISCALL(0x0069ED60, this, a2);
    }
}

void ai_state_machine::process_transition_message(Float a2, state_trans_messages the_msg)
{
    TRACE("ai_state_machine::process_transition_message");

    assert(my_curr_state != nullptr);

    if constexpr (1) {
        assert(my_curr_state != nullptr);

        auto a3a = bit_cast<ai::enhanced_state *>(this->my_curr_state)->process_message(a2, the_msg);
        a3a = this->sub_697A00(a2, the_msg, a3a);
        auto v4 = this->check_keyword_overrides(a3a);
        auto the_action = v4.the_action;
        a3a.the_action = the_action;

        string_hash v6 = v4.field_4;

        a3a.field_4 = v6;
        auto the_message = v4.the_message;
        a3a.the_message = the_message;
        if ( the_action != 0 ) {
            switch (the_action) {
            case 1:
                this->process_return();
                break;
            case state_trans_action::MACHINE_EXIT:
                this->process_machine_exit(the_message);
                break;
            default:
                assert((the_msg != TRANS_FAILURE_MSG)
                        && (the_msg != TRANS_SUCCESS_MSG)
                        && "You must process a state exit message either in the state's transition or the default one.");
                break;
            }
        }
        else
        {
            auto v8 = v4.field_C;
            this->transition_state(v6, v8);
        }
    } else {
        THISCALL(0x0069ECA0, this, a2, the_msg);
    }
}

state_trans_action ai_state_machine::sub_697A00(
        Float a3,
        int a4,
        const ai::state_trans_action &a5)
{

    ai::state_trans_action out;
    THISCALL(0x00697A00, this, &out, a3, a4, &a5);
    return out;
}

void ai_state_machine::process_mode(Float a2, bool a3) {
    TRACE("ai::ai_state_machine::process_mode");

    if constexpr (1) {
        base_state *v9;

        printf("this->my_curr_mode = %d\n", this->my_curr_mode);
        switch (this->my_curr_mode) {
        case PRE_TEST: {
            mashed_state *initial_state;
            if (this->field_30.source_hash_code == string_hash{}) {
                initial_state = this->field_C->field_1C;
            } else {
                initial_state = this->field_C->find_state(this->field_30);
            }

            assert(initial_state != nullptr &&
                   "We need to find the initial state, not finding it would be bad ");

            this->field_30.source_hash_code = 0;
            auto *v6 = static_cast<base_state *>(
                mash_virtual_base::create_subclass_by_enum(initial_state->field_14));
            auto *v7 = this->field_C;

            this->my_curr_state = v6;

            assert(this->my_curr_state != nullptr);

            v6->activate(this, v7->field_1C, nullptr, nullptr, static_cast<base_state::activate_flag_e>(0));

            assert(!my_curr_state->is_flag_set(mashed_state::IS_INTERRUPT_STATE));
            this->my_curr_mode = static_cast<decltype(my_curr_mode)>(1);
            this->process_mode(a2, false);
            break;
        }
        case 1: {
            this->advance_curr_state(a2, a3);
            return;
        }
        case 2: {
            if (this->field_2C == 0) {
                this->my_curr_mode = static_cast<decltype(my_curr_mode)>(1);
                this->process_mode(a2, false);
            }
            return;
        }
        case 3: {
            if (this->field_1C.size()) {
                return;
            }

            v9 = this->my_curr_state;
            this->my_curr_mode = PROCESSING_EXIT_REQUEST;
            if (this->my_curr_state != nullptr) {
                this->process_transition_message(a2, TRANS_MACHINE_EXIT_REQUEST_MSG);
            }

            if (v9 == this->my_curr_state) {
                this->my_core->do_machine_exit(this);
            } else {
                assert(my_curr_state != nullptr);
                this->process_mode(a2, false);
            }

            return;
        }
        case PROCESSING_EXIT_REQUEST: {
            state_trans_messages v10 = this->my_curr_state->frame_advance(a2);
            if (v10 == TRANS_TOTAL_MSGS) {
                if (this->my_curr_mode != 2) {
                    this->process_transition(a2);
                }

            } else {
                this->process_transition_message(a2, v10);
            }

            return;
        }
        case 5: {
            auto *v11 = this->field_1C.m_first;
            if (v11 == nullptr || !(this->field_1C.m_last - v11)) {
                this->my_core->do_machine_exit(this);
            }

            return;
        }
        default:
            return;
        }

    } else {
        THISCALL(0x006A1590, this, a2, a3);
    }
}

void ai_state_machine::process_machine_exit(ai::state_trans_messages a2) {
    TRACE("ai_state_machine::process_machine_exit");

    if constexpr (1) {
        this->field_44 = a2;

        if ( this->field_1C.size() != 0 ) {
            this->my_curr_mode = static_cast<decltype(my_curr_mode)>(5);
            for (auto i = 0u; i < this->field_1C.size(); ++i) {
                auto *v6 = this->field_1C[i];
                v6->my_curr_mode = static_cast<decltype(v6->my_curr_mode)>(3);
                for (auto j = 0u; i < v6->field_1C.size(); ++j) {
                    v6->field_1C[j]->request_exit();
                }
            }
        } else {
            this->my_core->do_machine_exit(this);
        }

    } else {
        THISCALL(0x0069BCE0, this, a2);
    }
}

void ai_state_machine::process_return() {
    TRACE("ai_state_machine::process_return");

    if constexpr (1) {
        assert(my_curr_state != nullptr);

        assert(my_curr_state->is_flag_set(mashed_state::IS_INTERRUPT_STATE) &&
               "Must be in an interruptable state to respond to a return command.");

        auto *v2 = this->my_curr_state;
        auto *v3 = v2->my_mashed_state;

        v2->deactivate(this->field_3C);
        auto *v4 = this->my_curr_state;
        if (v4 != nullptr) {
            delete v4;
        }

        auto *v5 = static_cast<base_state *>(
            mash_virtual_base::create_subclass_by_enum(this->field_3C->field_14));
        auto *v7 = this->field_40;
        auto *v6 = this->field_3C;
        this->my_curr_state = v5;

        assert(my_curr_state != nullptr);
        v5->activate(this, v6, v3, v7, base_state::ACTIVATE_FLAG_FROM_INTERUPT);
    } else {
        THISCALL(0x00687FD0, this);
    }
}

void ai_state_machine::request_exit() {
    this->my_curr_mode = static_cast<decltype(my_curr_mode)>(3);
    for (auto &v3 : this->field_1C) {
        v3->request_exit();
    }
}

string_hash ai_state_machine::get_initial_state_id() {
    string_hash result;
    THISCALL(0x006880E0, this, &result);

    return result;
}

void ai_state_machine::sub_69BAA0()
{
    auto curr_mode = this->my_curr_mode;
    if ( curr_mode != 3 && curr_mode != 5 && curr_mode != 4 ) {
        this->request_exit();
    }
}

bool ai_state_machine::transition_state(string_hash arg0, const param_block *a3) {
    TRACE("ai_state_machine::transition_state");

    assert(my_curr_state != nullptr);
    if constexpr (1) {
        auto *v4 = this->field_C;

        auto *the_state = v4->find_state(arg0);
        if (the_state != nullptr) {
            auto *v13 = bit_cast<ai::base_state *>(this->my_curr_state);
            auto *v14 = v13->my_mashed_state;
            if (v14->is_flag_set(0)) {
                if (!the_state->is_flag_set(0)) {
                    this->field_3C = nullptr;
                    this->field_40 = nullptr;
                }
            } else if (the_state->is_flag_set(0)) {
                this->field_3C = v14;
                this->field_40 = v13->field_10;
            }

            this->field_14 = v13->my_mashed_state;
            v13->deactivate(the_state);
            auto *v15 = this->my_curr_state;
            if (v15 != nullptr) {
                void (_fastcall *finalize)(void *, void *, bool) = CAST(finalize, get_vfunc(v15->m_vtbl, 0x8));
                finalize(v15, nullptr, true);
            }

            auto *v16 = static_cast<ai::base_state *>(
                mash_virtual_base::create_subclass_by_enum(the_state->field_14));
            base_state::activate_flag_e v25 = static_cast<base_state::activate_flag_e>(0);
            auto *v24 = a3;
            auto *v23 = this->field_14;
            this->my_curr_state = v16;

            printf("activate: 0x%08X\n", v16->m_vtbl);
            v16->activate(this, the_state, v23, v24, v25);
            return false;
        }


        auto *cur_child_machine = this;
        for ( auto *cur_parent = this->my_parent; cur_parent != nullptr; cur_parent = cur_parent->my_parent ) {
            assert(cur_child_machine->my_parent == cur_parent);

            auto *v7 = cur_parent->field_C;
            if (v7->find_state(arg0)) {
                assert(cur_parent->get_curr_state() != nullptr);

                ai::launch_layer_state *v8 = CAST(v8, cur_parent->get_curr_state());
                if ( cur_parent->my_curr_state->is_or_is_subclass_of({330}) ) {
                    if (auto v9 = cur_child_machine->get_name();
                        v8->get_layer_resource_key() != v9 )
                    {
                        this->sub_69BAA0();
                        return cur_parent->transition_state(arg0, nullptr);
                    }
                }

                mString local_string2 = v8->get_name().to_string();

                string_hash v17 = this->my_curr_state->get_name();
                auto *v18 = v17.to_string();
                mString v32{v18};

                resource_key v19 = this->get_name();
                auto v20 = v19.m_hash;
                auto *v21 = v20.to_string();
                mString local_string0{v21};

                mString local_string1 = cur_parent->get_name().m_hash.to_string();

                auto *v22 = arg0.to_string();
                mString local_string3{v22};

                sp_log(
                    "Layer %s Tried to change parent layer %s's state to %s. The current state of the "
                    "parent layer is %s.\n"
                    "\n"
                    "This is not allowed! The parent layer MUST be in the state that spawned the "
                    "current "
                    "layer (directly or indirectly)",
                    local_string0.c_str(),
                    local_string1.c_str(),
                    local_string3.c_str(),
                    local_string2.c_str());

                cur_parent = nullptr;
                cur_child_machine = nullptr;
                break;
            }

            cur_child_machine = cur_parent;
        }

        return false;
    } else {
        return THISCALL(0x0069BAC0, this, arg0, a3);
    }
}

resource_key ai_state_machine::get_name() {
    auto result = this->field_C->sub_6B68F0();
    return result;
}

void ai_state_machine::add_as_child(ai_state_machine *a2) {
    THISCALL(0x006A1530, this, a2);
}

state_trans_action ai_state_machine::check_keyword_overrides(const state_trans_action &a3) {
    TRACE("ai_state_machine::check_keyword_overrides");

    ai::state_trans_action result;

    if (a3.the_action != 0) {
        return a3;
    }

    auto v3 = a3.field_4;

    if (v3 == ai::ai_state_machine::prev_state_id_hash()) {
        if (this->my_curr_state->is_flag_set(mashed_state::IS_INTERRUPT_STATE)) {

            result = ai::state_trans_action {1, string_hash {0}, TRANS_TOTAL_MSGS, nullptr};
            return result;
        } else {
            assert(this->get_prev_mashed_state() != nullptr && "No previous state to return to");
        }

        auto name = this->get_prev_mashed_state()->get_name();
        result = ai::state_trans_action {0, name, TRANS_TOTAL_MSGS, nullptr}; 
        return result;
    }

    if (v3 == ai::ai_state_machine::initial_state_id_hash()) {
        auto initial_state = this->get_initial_state_id();

        result = ai::state_trans_action {0, initial_state, TRANS_TOTAL_MSGS, nullptr};
        return result;
    }

    return a3;
}

} // namespace ai

void ai_state_machine_patch() {

    {
        FUNC_ADDRESS(address, &ai::ai_state_machine::process_mode);
        SET_JUMP(0x006A1590, address);
    }

    {
        FUNC_ADDRESS(address, &ai::ai_state_machine::transition_state);
        REDIRECT(0x0069EE08, address);
        //REDIRECT(0x0069ED51, address);
    }

    {
        FUNC_ADDRESS(address, &ai::ai_state_machine::process_return);
        SET_JUMP(0x00687FD0, address);
    }

    {
        FUNC_ADDRESS(address, &ai::ai_state_machine::process_transition);
        SET_JUMP(0x0069ED60, address);
    }
}
