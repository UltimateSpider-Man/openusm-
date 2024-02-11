#pragma once

struct singleton {
    int m_vtbl;

    singleton() = default;

    //virtual
    ~singleton() = default;
};
