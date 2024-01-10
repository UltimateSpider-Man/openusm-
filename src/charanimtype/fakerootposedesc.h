#pragma once

namespace FakerootPoseDesc {

struct PerAnimData {
    struct EventIterator {
        const PerAnimData *m_pAnimData;
        struct {
        } *m_pLoc;
        bool field_8;

        EventIterator(const PerAnimData *a2);

        void operator++();

        bool IsIteratorValid() const
        {
            return this->m_pLoc != nullptr;
        }
    };

    char field_0[0x20];
    int numTotalSignals;
    int field_24;
    int field_28;
    int field_2C;
    int field_30;

    EventIterator GetStartIterator() const;
};

}
