#include "fe_mission_text.h"

#include "func_wrapper.h"
#include "utility.h"

fe_mission_text::fe_mission_text()
{

}

void fe_mission_text::set_flavor(int a2) {
    this->field_B0 = a2;
}

void fe_mission_text::set_text(string a2) {
    sp_log("fe_mission_text::set_text: %s", a2.data);

    THISCALL(0x0060D440, this, a2);
}

void fe_mission_text::SetShown(bool a2) {
    sp_log("fe_mission_text::SetShown: %d", a2);

    THISCALL(0x0061AA00, this, a2);
}

void fe_mission_text_patch() {
    {
        FUNC_ADDRESS(address, &fe_mission_text::set_text);
        REDIRECT(0x00672EBC, address);
    }

    {
        FUNC_ADDRESS(address, &fe_mission_text::SetShown);
        REDIRECT(0x00672ECB, address);
    }
}
