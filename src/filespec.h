#pragma once

#include "mstring.h"

struct filespec {
    mString m_dir;
    mString m_name;
    mString m_ext;

    filespec() = default;

    //0x0055DAF0
    filespec(const mString &a2, const mString &a3, const mString &a4);

    //0x00501A40
    filespec(const mString &a2);

    //0x004AD750
    ~filespec() = default;

    //0x0055DB60
    [[nodiscard]] mString fullname();

    [[nodiscard]] mString sub_55DBF0();

    //0x005BBF90
    void extract(const mString &a2);
};

extern void filespec_patch();
