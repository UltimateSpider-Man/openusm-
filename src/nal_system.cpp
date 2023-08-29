#include "nal_system.h"

#include "common.h"
#include "func_wrapper.h"
#include "log.h"
#include "nal_component.h"
#include "nfl_system.h"
#include "tl_system.h"
#include "tlresource_directory.h"
#include "trace.h"
#include "utility.h"
#include "vtbl.h"

#include <nal_list.h>
#include <nal_skeleton.h>

#include <cassert>

VALIDATE_SIZE(nalStreamInstance, 0x7C);
VALIDATE_OFFSET(nalStreamInstance, m_callback, 0x20);

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

Var<BaseComponent **> CharComponentManager::pCompArray{0x0096A55C};

Var<int> CharComponentManager::iCurrNumComponents{0x0096A558};

Var<int *> PanelComponentMgr::comp_list{0x0096F7DC};

int *nalComponentU8Base::GetType() {
    return &TypeID;
}

char *nalComponentStringBase::GetType() {
    sp_log("%d", TypeID());

    return &TypeID();
}

nalBaseSkeleton *nalGetSkeleton(const tlFixedString &a1) {
    auto &Find = get_vfunc(nalSkeletonDirectory()->m_vtbl, 0xC);

    return (nalBaseSkeleton *) Find(nalSkeletonDirectory(), &a1);
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
    if constexpr (1) {
        tlStackRangeInit();
        if (tlScratchPadRefCount()++ == 0) {
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

bool nalStreamInstance::IsReady() {
    //sp_log("nalStreamInstance::IsReady(): %d", this->field_1C);

    return this->field_1C == 5;
}

nalStreamInstance::~nalStreamInstance() {
    THISCALL(0x004AD4C0, this);
}

void nalStreamInstance::AdvanceStream() {
    THISCALL(0x00492EF0, this);

    //sp_log("nalStreamInstance::AdvanceStream(): %d", v2);
}

bool nalStreamInstance::Advance(Float dt) {
#if 1
    sp_log("%d", this->field_1C);
#endif

    bool result = (bool) THISCALL(0x00498580, this, dt);

    //sp_log("nalStreamInstance::Advance(): post %d", this->field_1C);

    return result;
}

nalStreamInstance *create_stream_instance(uint32_t a1,
                                          uint32_t a2,
                                          uint32_t a3,
                                          [[maybe_unused]] int a4,
                                          nalClientSceneAnim *(*p_cb)(const tlFixedString &, void *),
                                          void *a6) {
    //sp_log("create_stream_instance(): a1 = %d", a1);

    if constexpr (1) {
        nalStreamInstance *result = static_cast<nalStreamInstance *>(
            tlMemAlloc(sizeof(nalStreamInstance), 8u, 0));
        if (result == nullptr) {
            return nullptr;
        }

        result->m_callback = p_cb;
        result->field_24 = a6;
        result->field_28.field_0 = a1;
        result->field_4 = nullptr;
        result->field_8 = nullptr;
        result->field_C = 0;
        result->field_10 = 0.0;
        result->field_14 = 0.0;
        result->field_18 = nullptr;
        result->field_1C = 0;
        result->field_44 = 0;
        result->field_78 = 0;
        result->field_79 = 0;
        result->m_vtbl = 0x00880A88;
        result->field_5C = a2;
        result->field_70 = a3;

        return result;
    } else {
        return (nalStreamInstance *) CDECL_CALL(0x00492E70, a1, a2, a3, a4, p_cb, a6);
    }
}

namespace nalChar {

VALIDATE_SIZE(nalCharSkeleton, 0x84);
VALIDATE_SIZE(nalCharPose, 0x10);

nalCharPose::nalCharPose(const nalCharSkeleton *a2) : nalComp::nalCompPose(a2) {
    if constexpr (0) {
        m_vtbl = 0x00891A3C;
        field_C = 0;
        this->InitializePoseDataFromSkel();
    } else {
        THISCALL(0x005F2860, this, a2);
    }
}

void nalCharPose::InitializePoseDataFromSkel() {
    THISCALL(0x005F1290, this);
}

void nalCharSkeleton::Process() {
    auto v1 = CharComponentManager::iCurrNumComponents();
    BaseComponent **v3 = static_cast<decltype(v3)>(tlMemAlloc(4 * v1, 8, 0));
    for (int i = 0; i < v1; ++i) {
        v3[i] = CharComponentManager::pCompArray()[i];
    }

    auto &UnMash = get_vfunc(this->m_vtbl, 0x40);
    UnMash(this, this, v3, v1);
    tlMemFree(v3);
    auto *mem = tlMemAlloc(sizeof(nalCharPose), 8, 0);
    this->field_80 = new (mem) nalCharPose{this};
}
} // namespace nalChar

namespace nalGeneric {

VALIDATE_SIZE(nalGenericSkeleton, 0xE4);
VALIDATE_SIZE(nalComponentInfo, 0x30);
VALIDATE_OFFSET(nalGenericSkeleton, field_64, 0x64);

void nalGenericSkeleton::Process() {
    if constexpr (1) {
        auto v2 = this->field_64;
        auto v3 = this->field_6C;
        this->field_68 = (int) &this->field_E0;
        auto *v4 = (char *) &this->field_E0 + v2;
        auto v5 = 48 * this->field_74;
        this->field_70 = (int) v4;
        auto v6 = (uint32_t) &v4[v3 + 3] & 0xFFFFFFFC;
        this->field_78 = v6;
        auto v7 = v5 + v6 + 3;
        auto v8 = 5 * this->field_7C;
        auto v9 = this->field_94;
        v7 &= 0xFFFFFFFC;
        this->field_84 = v7;
        auto v10 = (v7 + 8 * v8 + 3) & 0xFFFFFFFC;
        auto v11 = v10 + 48 * this->field_88;
        this->field_8C = CAST(field_8C, v10);
        auto v12 = v11 + v9 - 1;
        auto v13 = this->field_9C;
        auto v14 = ~(v9 - 1) & v12;
        auto v15 = (this->field_90 + v14 + 3) & 0xFFFFFFFC;
        this->field_A0 = v15;
        auto v16 = v13 + v15 + 3;
        auto v17 = this->field_B0;
        v16 &= 0xFFFFFFFC;
        auto v18 = (char *) (v16 + 0x30 * this->field_A4);
        this->field_A8 = CAST(field_A8, v16);
        auto v19 = (int) &v18[v17 - 1];
        auto v20 = this->field_B8;
        auto v21 = ~(v17 - 1) & v19;
        auto v22 = this->field_AC;
        this->field_B4 = v21;
        auto v23 = v22 + v21 + 3;
        auto v24 = this->field_C4;
        v23 &= 0xFFFFFFFC;
        this->field_BC = v23;
        this->field_98 = v14;
        this->field_C8 = ~(v24 - 1) & (v23 + v20 + v24 - 1);
        this->field_CC = (int) this;
        this->field_D0 = v14;

        //sp_log("%s", this->field_8C[0].field_0.c_str());

        if (this->field_88 > 0) {
            for (int i = 0; i < this->field_88; ++i) {
                this->field_8C[i].field_20 = static_cast<decltype(this->field_8C[i].field_20)>(
                    nalComponentInstanceBank().Search(this->field_8C[i].field_0)->field_20);
            }
        }

        if (this->field_A4 > 0) {
            for (int i = 0; i < this->field_A4; ++i) {
                this->field_A8[i].field_20 = static_cast<decltype(this->field_A8[i].field_20)>(
                    nalComponentInstanceBank().Search(this->field_A8[i].field_0)->field_20);
            }
        }

        auto v29 = this->field_A0;

        auto *v30 = this->field_8C;
        auto v38 = this->field_98;

        auto v37 = v29;
        if (this->field_88 > 0) {
            for (int i = 0; i < this->field_88; ++i) {
                auto &Process = get_vfunc(v30->field_20->m_vtbl, 0x10);
                Process(v30->field_20, v30, &v38, &v37);

                ++v30;
            }
        }

        auto v34 = this->field_BC;
        auto *v35 = this->field_A8;
        v38 = this->field_B4;

        v37 = v34;
        if (this->field_A4 > 0) {
            for (int i = 0; i < this->field_A4; ++i) {
                auto &Process = get_vfunc(v35->field_20->m_vtbl, 0x10);

                Process(v35->field_20, v35, &v38, &v37);

                ++v35;
            }
        }

    } else {
        THISCALL(0x00793610, this);
    }
}

void nalGenericSkeleton::Release() {
    ;
}
} // namespace nalGeneric

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
        auto **skeletons = (nalBaseSkeleton **) tlMemAlloc(4 * anim_file->num_skeletons,
                                                           8,
                                                           0x2000000u);

        for (auto i = 0; i < anim_file->num_skeletons; ++i)
        {
            auto &Find = get_vfunc(nalSkeletonDirectory()->m_vtbl, 0xC);

            skeletons[i] = (nalBaseSkeleton *) Find(nalSkeletonDirectory(), &v1[i]);
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

        while (anim_class != nullptr) {
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

            auto &CheckVersion = get_vfunc(anim_class->m_vtbl, 0xC);

            if (!CheckVersion(anim_class)) {
                auto *v3 = &anim_class->field_8;
                auto *v9 = v3->to_string();
                auto v4 = anim_class->field_2C;
                error("Unsupported anim version %x (%s).\n", v4, v9);
            }

            anim_class->field_3C = 0;

            auto &Process = get_vfunc(anim_class->m_vtbl, 0x4);
            Process(anim_class);

            auto &Add = get_vfunc(nalAnimDirectory()->m_vtbl, 0x10);
            if (Add(nalAnimDirectory(), anim_class)) {
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

void nalStreamInstance_patch() {
    REDIRECT(0x0055F8F4, nalConstructSkeleton);

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
        FUNC_ADDRESS(address, &nalChar::nalCharSkeleton::Process);
        set_vfunc(0x00891F90, address);
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

    REDIRECT(0x005AD21F, nalInit);

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
