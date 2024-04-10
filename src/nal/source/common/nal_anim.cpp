#include "nal_anim.h"

#include "common.h"
#include "nal_skeleton.h"
#include "vtbl.h"

VALIDATE_SIZE(nalAnimClass<nalAnyPose>::nalInstanceClass, 0x14);

template<>
void *nalAnimClass<nalAnyPose>::VirtualCreateInstance(nalBaseSkeleton *Skel)
{
    void * (__fastcall *func)(void *, void *, nalBaseSkeleton *) = CAST(func, get_vfunc(m_vtbl, 0x10));
    return func(this, nullptr, Skel);
}

template<>
void * nalAnimClass<nalAnyPose>::CreateInstance(nalBaseSkeleton *skeleton)
{
    if ( skeleton != nullptr )
    {
        assert((skeleton == nullptr || Compatible(GetSkeleton(),skeleton)) && "attempt to create an instance without a compatible skeleton");
    }

    return this->VirtualCreateInstance(skeleton);
}

bool Compatible(nalBaseSkeleton *a1, nalBaseSkeleton *a2)
{
    return (a2->m_vtbl == a1->m_vtbl);
}
