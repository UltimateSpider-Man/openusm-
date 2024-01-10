#include "fakerootposedesc.h"

#include "common.h"
#include "func_wrapper.h"
#include "utility.h"

#include <cassert>

namespace FakerootPoseDesc {

VALIDATE_SIZE(PerAnimData::EventIterator, 0xC);

PerAnimData::EventIterator PerAnimData::GetStartIterator() const
{
    return EventIterator {this};
}

PerAnimData::EventIterator::EventIterator(const FakerootPoseDesc::PerAnimData *a2)
{
    this->m_pAnimData = a2;
    this->m_pLoc = CAST(this->m_pLoc, a2->numTotalSignals
                            ? &this->m_pAnimData->field_30
                            : nullptr
                        );

    this->field_8 = false;
}

void PerAnimData::EventIterator::operator++()
{
    assert(this->m_pLoc != nullptr && "Attempting to use an EventIterator that is invalid.");

    THISCALL(0x005F3E30, this);
}

} //
