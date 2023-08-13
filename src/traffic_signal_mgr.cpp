#include "traffic_signal_mgr.h"

#include "func_wrapper.h"

traffic_signal_mgr::traffic_signal_mgr() {}

void traffic_signal_mgr::frame_advance(Float a1) {
    m_state_timer().field_0 = m_state_timer().field_0 - a1;
    if (m_state_timer().field_0 < 0.0) {
        m_state_timer().field_0 = 0.0;
    }

    if (m_state_timer().field_0 <= 0.0) {
        switch_to_next_state();
    }
}

void traffic_signal_mgr::switch_to_next_state() {
    CDECL_CALL(0x005528D0);
}
