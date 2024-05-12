#include "nal_system.h"

#include "common.h"
#include "func_wrapper.h"
#include "log.h"
#include "nal_anim.h"
#include "nal_component.h"
#include "nfl_system.h"
#include "osassert.h"
#include "tl_system.h"
#include "tlresource_directory.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

#include <nal_list.h>
#include <nal_skeleton.h>

#include <cassert>

VALIDATE_OFFSET(nalGeneric::nalGenericSkeleton, field_50, 0x50);

Var<tlInstanceBank> nalTypeInstanceBank{0x009770E8};

Var<tlInstanceBank> nalComponentInstanceBank{0x00977100};

template<>
Var<tlInstanceBankResourceDirectory<nalAnimFile, tlFixedString> *>
    tlresource_directory<nalAnimFile, tlFixedString>::system_dir{0x009609F4};

template<>
Var<tlInstanceBankResourceDirectory<nalBaseSkeleton, tlFixedString> *>
    tlresource_directory<nalBaseSkeleton, tlFixedString>::system_dir{0x009609E8};

template<>
Var<tlInstanceBankResourceDirectory<nalAnimClass<nalAnyPose>, tlFixedString> *>
    tlresource_directory<nalAnimClass<nalAnyPose>, tlFixedString>::system_dir{0x009609F0};

template<>
Var<tlInstanceBankResourceDirectory<nalSceneAnim, tlFixedString> *>
    tlresource_directory<nalSceneAnim, tlFixedString>::system_dir{0x009609EC};

Var<tlInstanceBankResourceDirectory<nalBaseSkeleton, tlFixedString> *> nalSkeletonDirectory =
    (0x00977178);

Var<tlInstanceBankResourceDirectory<nalAnimFile, tlFixedString> *> nalAnimFileDirectory{0x0097716C};

Var<tlInstanceBankResourceDirectory<nalAnimClass<nalAnyPose>, tlFixedString> *> nalAnimDirectory{
    0x00977170};

Var<tlInstanceBankResourceDirectory<nalSceneAnim, tlFixedString> *> nalSceneAnimDirectory{
    0x00977168};

Var<int *> PanelComponentMgr::comp_list{0x0096F7DC};

void * BaseComponent::ApplyPublicPerSkelDataOffset(uint32_t a1, void *a2) const
{
    void * (__fastcall *func)(const void *, void *, uint32_t, void *) = CAST(func, get_vfunc(this->m_vtbl, 0x8));
    return func(this, nullptr, a1, a2);
}

void BaseComponent::SkelPoseProcess(uint32_t a1, void *a2, void *a3) const
{
    void (__fastcall *func)(const void *, void *, uint32_t, void *, void *) = CAST(func, get_vfunc(this->m_vtbl, 0x3C));
    func(this, nullptr, a1, a2, a3);
}

void BaseComponent::PoseDataFree(uint32_t a2, void *a3) const
{
    void (__fastcall *func)(const void *, void *, uint32_t, void *) = CAST(func, get_vfunc(this->m_vtbl, 0x50));
    func(this, nullptr, a2, a3);
}

int *nalComponentU8Base::GetType() {
    return &TypeID;
}

char *nalComponentStringBase::GetType() {
    sp_log("%d", TypeID());

    return &TypeID();
}

nalBaseSkeleton *nalGetSkeleton(const tlFixedString &a1) {
    nalBaseSkeleton * (__fastcall *Find)(void *, void *, const tlFixedString *) = CAST(Find, get_vfunc(nalSkeletonDirectory()->m_vtbl, 0xC));

    return Find(nalSkeletonDirectory(), nullptr, &a1);
}

struct nalHeap {
    std::intptr_t m_vtbl;
    uint32_t field_4;
    int field_8;
};

struct nalAnimCache {
    nalHeap *field_0;
    int field_4;
    int field_8;
};

static Var<void *> dword_970D64{0x00970D64};

static Var<char[1]> nalAnimPath{0x00976FC8};

static Var<char[1]> nalSkeletonPath{0x00976EC8};

static Var<nalHeap> nalDefaultHeap{0x00946A84};

static Var<nalAnimCache> nalAnimationCache{0x00977114};

static Var<nalHeap *> nalAnimationHeap{0x00976EC0};

void nalInit(nalHeap *a1) {
    TRACE("nalInit");

    if constexpr (1) {
        tlStackRangeInit();
        if (tlScratchPadRefCount++ == 0) {
            dword_970D64() = tlMemAlloc(0x4000, 16, 0x2000000u);
        }

        nalAnimPath()[0] = 0;
        nalSkeletonPath()[0] = 0;
        auto *mem = tlMemAlloc(20, 8, 0x2000000u);

        nalAnimFileDirectory() = new (mem)
            tlInstanceBankResourceDirectory<nalAnimFile, tlFixedString>{};

        mem = tlMemAlloc(0x14, 8, 0x2000000u);
        nalAnimDirectory() = new (mem)
            tlInstanceBankResourceDirectory<nalAnimClass<nalAnyPose>, tlFixedString>{};

        mem = tlMemAlloc(0x14, 8, 0x2000000u);
        nalSceneAnimDirectory() = new (mem)
            tlInstanceBankResourceDirectory<nalSceneAnim, tlFixedString>{};

        mem = tlMemAlloc(0x14, 8, 0x2000000u);
        nalSkeletonDirectory() = new (mem)
            tlInstanceBankResourceDirectory<nalBaseSkeleton, tlFixedString>{};

        nalTypeInstanceBank().Init();
        nalComponentInstanceBank().Init();
        nalInitListInit();

        auto *v10 = a1;
        if (v10 == nullptr) {
            nalDefaultHeap().field_4 = 0x100000;
            nalDefaultHeap().field_8 = 0;
            v10 = &nalDefaultHeap();
        }

        nalAnimationCache().field_8 = 0;
        nalAnimationCache().field_4 = 0;
        nalAnimationHeap() = v10;
        nalAnimationCache().field_0 = v10;

    } else {
        CDECL_CALL(0x00783CF0, a1);
    }
}

void nalExit() {
    CDECL_CALL(0x00783C60);
}

void nalReleaseSceneAnimInternal(nalSceneAnim *a1) {
    CDECL_CALL(0x0078D9B0, a1);
}

bool nalLoadSceneAnimInternal(nalSceneAnim *a1) {
    return (bool) CDECL_CALL(0x0078D8D0, a1);
}

bool nalLoadAnimFileInternal(nalAnimFile *anim_file)
{
    TRACE("nalLoadAnimFileInternal", anim_file->field_10.to_string(), 
            anim_file->field_48.to_string());

    if (anim_file->field_0 != 0x10101)
    {
        error("Unsupported anim file version %x, current version is %x.\n",
              anim_file->field_0,
              0x10101);
    }

    if constexpr (1)
    {
        auto *v1 = &anim_file->field_48;
        auto **skeletons = static_cast<nalBaseSkeleton **>(tlMemAlloc(4 * anim_file->num_skeletons,
                                                           8,
                                                           0x2000000u));

        for (auto i = 0; i < anim_file->num_skeletons; ++i)
        {
            nalBaseSkeleton * (__fastcall *Find)(void *, void *, const tlFixedString *) = CAST(Find, get_vfunc(nalSkeletonDirectory()->m_vtbl, 0xC));

            skeletons[i] = Find(nalSkeletonDirectory(), nullptr, &v1[i]);
            if (skeletons[i] == nullptr)
            {
                auto v8 = anim_file->field_10.to_string();
                auto v3 = v1[i].to_string();
                error(
                    "The skeleton resource file %s was not found while loading animfile %s. "
                    "Perhaps something is wrong with the packer?\n",
                    v3,
                    v8);

                assert(0);
            }
        }

        nalAnimClass<nalAnyPose> *anim_class = nullptr;
        if (anim_file->field_34 != nullptr) {
            anim_file->field_34 += (unsigned int) anim_file;
            anim_class = CAST(anim_class, anim_file->field_34);
        }

        while (anim_class != nullptr)
        {
            if (anim_class->field_4) {
                anim_class->field_4 += (unsigned int) anim_class;
            }

            auto *v7 = skeletons[anim_class->field_28];
            anim_class->Skeleton = v7;
            auto *instance = nalTypeInstanceBank().Search(v7->field_28);
            if (instance == nullptr) {
                assert(0 && "couldn't find animation type instance");
            }

            auto vtbl = static_cast<nalInitListAnimType *>(instance->field_20)->anim_vtbl_ptr;
            anim_class->m_vtbl = vtbl;

            bool (__fastcall *CheckVersion)(void *) = CAST(CheckVersion, get_vfunc(anim_class->m_vtbl, 0xC));

            if (!CheckVersion(anim_class)) {
                auto *v3 = &anim_class->field_8;
                auto *v9 = v3->to_string();
                auto v4 = anim_class->Version;
                error("Unsupported anim version %x (%s).\n", v4, v9);
            }

            anim_class->InstanceCount = 0;

            void (__fastcall *Process)(void *) = CAST(Process, get_vfunc(anim_class->m_vtbl, 0x4));
            Process(anim_class);

            bool (__fastcall *Add)(void *, void *, nalAnimClass<nalAnyPose> *) = CAST(Add, get_vfunc(nalAnimDirectory()->m_vtbl, 0x10));
            if (Add(nalAnimDirectory(), nullptr, anim_class)) {
                auto *v6 = anim_class->field_8.to_string();
                sp_log("Duplicate anim %s found.\n", v6);
            }
        }

        tlMemFree(skeletons);
        anim_file->field_4 |= 8u;
        return true;
    } else {
        return (bool) CDECL_CALL(0x0078D540, anim_file);
    }
}

void nalSetSkeletonDirectory(tlResourceDirectory<nalBaseSkeleton, tlFixedString> *a1) {
    nalSkeletonDirectory() = CAST(nalSkeletonDirectory(), a1);
}

void nalSetAnimFileDirectory(tlResourceDirectory<nalAnimFile, tlFixedString> *a1) {
    nalAnimFileDirectory() = CAST(nalAnimFileDirectory(), a1);
}

void nalSetAnimDirectory(tlResourceDirectory<nalAnimClass<nalAnyPose>, tlFixedString> *a1) {
    nalAnimDirectory() = CAST(nalAnimDirectory(), a1);
}

tlResourceDirectory<nalAnimClass<nalAnyPose>, tlFixedString> *nalGetAnimDirectory()
{
    return nalAnimDirectory();
}

void nalSetSceneAnimDirectory(tlResourceDirectory<nalSceneAnim, tlFixedString> *a1) {
    nalSceneAnimDirectory() = CAST(nalSceneAnimDirectory(), a1);
}

void nalStreamInstance_patch()
{

    REDIRECT(0x005AD21F, nalInit);

    REDIRECT(0x0055F8F4, nalConstructSkeleton);
    return;


    {
        FUNC_ADDRESS(address, &nalGeneric::nalGenericSkeleton::Process);
        set_vfunc(0x008BD3D8, address);
    }

    {
        FUNC_ADDRESS(address, &nalComponentU8Base::GetType);
        SET_JUMP(0x004AE4C0, address);
    }

    {
        FUNC_ADDRESS(address, &nalComponentStringBase::GetType);
        SET_JUMP(0x004AE4D0, address);
    }

    {
        FUNC_ADDRESS(address, &nalComponentInitList::Register);
        //set_vfunc(0x00880958, address);
    }

    {
        FUNC_ADDRESS(address, &nalComp::nalCompSkeleton::UnMash);
        set_vfunc(0x00891FC8, address);
        set_vfunc(0x008AA300, address);
    }

#if 0
    {
        FUNC_ADDRESS(address, &nalStreamInstance::IsReady);
        set_vfunc(0x00880A8C, address);
    }

    //nalStreamInstance::Advance
    {
        REDIRECT(0x004985FB, nflReadFileAsync);

        REDIRECT(0x00498622, nflGetRequestInfo);

        REDIRECT(0x0049862B, nflGetRequestState);

        REDIRECT(0x004986FF, tlMemAlloc);
    }

    {
        FUNC_ADDRESS(address, &nalStreamInstance::Advance);
        //set_vfunc(0x00880A90, address);
    }

    {
        FUNC_ADDRESS(address, &nalStreamInstance::AdvanceStream);
        REDIRECT(0x00498943, address);
    }
#endif
}
