#pragma once

#include <cstdint>

template<typename T0, typename T1>
struct tlResourceDirectory {
    std::intptr_t m_vtbl;

    struct Iterator {
        std::intptr_t m_vtbl;
    };

    /* virtual */ ~tlResourceDirectory() = default;

    /* virtual */ const char *DirectoryName() {
        return "Unnamed";
    }

    T0 *Find(unsigned int);

    int Add(T0 *);

    /* virtual */ void ReleaseAll(bool a2, bool a3, int a4);

    /* virtual */ T0 *Load(const T1 &);

    /* virtual */ int Release(T0 *a2, int a3, bool a4);

    T0 *StandardLoad(const T1 &);

    int StandardRelease(T0 *a2, int a3, bool a4);
};

extern void tlResourceDirectory_patch();
