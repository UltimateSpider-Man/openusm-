#include "nal_component.h"

#include "nal_system.h"

template<>
void nalComponent<nalComponentU8Base, spideySignalData, spideySignal>::Process(
    const nalGeneric::nalComponentInfo *a1, void *&a2, void *&) {
    for (int i = 0; i < a1->field_28; ++i) {
        a2 = static_cast<char *>(a2) + 1;
    }
}
