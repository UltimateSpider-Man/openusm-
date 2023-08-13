#pragma once

#include "variable.h"

namespace MemoryUnitManager {

struct eOperation {
    int field_0;
};

struct eStatus {
    int field_0;
};

struct Container {
    int empty[144];
    int field_240;
    int field_244;
    char field_248[64];

    //0x007B1160
    Container(const char *a2);
};

struct Observer {};

extern void RegisterObserver(Observer *a1);

extern void Initialize(uint32_t a1);

extern bool Service();

extern int LoadGameSync(const Container &a1);

//0x007B1720
extern unsigned int GetGameSaveSize(unsigned int a1);

extern Var<Observer *> mObserver;

extern Var<eStatus> mLastError;

//0x007B1FF0
extern int SaveGame(const Container &a1);

} // namespace MemoryUnitManager
