#pragma once

namespace ai {

enum state_trans_messages {
    TRANS_MACHINE_EXIT_REQUEST_MSG = 0,
    TRANS_SUCCESS_MSG              = 1,
    TRANS_FAILURE_MSG              = 2,
    TRANS_INTERRUPT_MSG            = 3,
    TRANS_TRANSITION_MSG           = 74,
    TRANS_TOTAL_MSGS               = 75,
};


} // namespace ai
