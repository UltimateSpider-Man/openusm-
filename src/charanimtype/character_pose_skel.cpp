#include "character_pose_skel.h"

#include "charcomponentmanager.h"
#include "common.h"
#include "func_wrapper.h"
#include "tl_system.h"
#include "trace.h"

namespace nalChar {

VALIDATE_SIZE(nalCharSkeleton, 0x84);
VALIDATE_SIZE(nalCharPose, 0x10);

nalCharPose::nalCharPose(
    const nalChar::nalCharSkeleton *a2) : nalCompPose(a2)
{
    this->m_vtbl = 0x00891A3C;
    this->field_C = 0;
    this->InitializePoseDataFromSkel();
}

void nalCharPose::InitializePoseDataFromSkel()
{
    TRACE("nalCharPose::InitializePoseDataFromSkel");

    THISCALL(0x005F1290, this);
}

nalCharPose *nalCharSkeleton::GetDefaultPose()
{
    assert( this->m_theDefaultPose != nullptr && "Should have made one in Process");
    return this->m_theDefaultPose;
}

void nalCharSkeleton::Process()
{
    TRACE("nalCharSkeleton::Process");

    auto v1 = CharComponentManager::iCurrNumComponents();
    auto **v3 = (BaseComponent **)tlMemAlloc(4 * v1, 8u, 0);
    for ( int i = 0; i < v1; ++i ) {
        v3[i] = CharComponentManager::pCompArray()[i];
    }

    this->UnMash(this, v3, v1);
    tlMemFree(v3);

    auto *v5 = tlMemAlloc(0x10u, 8u, 0);
    this->m_theDefaultPose = new (v5) nalCharPose {this};
}

} // nalChar

void nalChar_patch()
{
    FUNC_ADDRESS(address, &nalChar::nalCharSkeleton::Process);
    SET_JUMP(0x005F28C0, address);
}
