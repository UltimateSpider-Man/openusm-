#include "memoryunitmanager.h"

#include "common.h"
#include "func_wrapper.h"
#include "log.h"

#include <string.h>

namespace MemoryUnitManager {

VALIDATE_SIZE(Container, 0x288);

Var<Observer *> mObserver{0x00984818};

Var<eStatus> mLastError{0x009847CC};

Container::Container(const char *a2) {
    strcpy(this->field_248, a2);

    this->field_240 = 0;
    this->field_244 = 0;
}

void RegisterObserver(Observer *a1) {
    mObserver() = a1;
}

void Initialize(uint32_t a1) {
    CDECL_CALL(0x007B16D0, a1);
}

bool Service() {
    return (bool) CDECL_CALL(0x007B1EE0);
}

int LoadGameSync(const Container &a1) {
    if (MemoryUnitManager::SaveGame(a1) == 0) {
        while (Service()) {
            ;
        }
    }

    return mLastError().field_0;
}

int SaveGame(const Container &a1) {
    return CDECL_CALL(0x007B1FF0, &a1);
}

unsigned int GetGameSaveSize(unsigned int a1) {
    return a1;
}

} // namespace MemoryUnitManager
