#pragma once

#include "fixedstring.h"
#include "float.hpp"
#include "hashstring.h"
#include "nfl_system.h"
#include "tl_system.h"
#include "variable.h"

#include <nalcomp/nal_pose_comp.h>

#include <memory>

struct BaseComponent {
    virtual ~BaseComponent() = default;

    virtual int GetType() = 0;
};

extern Var<tlInstanceBank> nalTypeInstanceBank;

extern Var<tlInstanceBank> nalComponentInstanceBank;

namespace CharComponentManager {
extern Var<BaseComponent **> pCompArray;

extern Var<int> iCurrNumComponents;
} // namespace CharComponentManager

namespace PanelComponentMgr {
extern Var<int *> comp_list;
}

struct nal_anim_control {};

struct nalAnyPose {};

struct nalBaseSkeleton;

template<typename T>
struct nalAnimClass {
    struct nalInstanceClass {};

    std::intptr_t m_vtbl;
    nalAnimClass<nalAnyPose> *field_4;
    tlFixedString field_8;
    int field_28;
    int field_2C;
    nalBaseSkeleton *Skeleton;
    int field_34;
    int field_38;
    int field_3C;
};

namespace nalChar {
struct nalCharAnim {
    struct vtbl {
        void *field_0;
        void *finalize;
        void *Process;
        void *Release;

        using CheckVersion_t = bool (nalCharAnim::*)();
        CheckVersion_t CheckVersion;

        vtbl(void *, void *, void *, void *, CheckVersion_t a4) : CheckVersion(a4) {}
    };

    std::intptr_t m_vtbl;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    int field_24;
    int field_28;
    uint32_t field_2C;

    bool CheckVersion() {
        return this->field_2C == 0x10003;
    }

    static int vtbl_ptr;
};

struct nalCharSkeleton;

struct nalCharPose : nalComp::nalCompPose {
    nalCharPose(const nalCharSkeleton *);

    //virtual
    void InitializePoseDataFromSkel();
};

struct nalCharSkeleton : nalComp::nalCompSkeleton {
    struct vtbl {
        void *Dummy;
        void *finalize;

        using Process_t = void (nalCharSkeleton::*)();
        Process_t Process;

        void *Release;

        using CheckVersion_t = bool (nalCharSkeleton::*)();
        CheckVersion_t CheckVersion;
    };

    int field_7C;
    nalCharPose *field_80;

    void Process();

    bool CheckVersion() {
        return this->Version == 0x10003;
    }

    static int vtbl_ptr;
};
} // namespace nalChar

namespace nalPanel {

struct nalPanelAnim {
    struct vtbl {
        void *field_0;
        void *finalize;
        void __fastcall (*Process)(void *);
        void *Release;
        bool (nalPanelAnim::*CheckVersion)();
    };

    std::intptr_t m_vtbl;
    uint32_t field_4;

    bool CheckVersion() {
        return this->field_4 == 0x300;
    }

    static int vtbl_ptr;
};

} // namespace nalPanel

namespace nalPed {

struct nalPedAnim {
    struct vtbl {
        void *field_0;
        void *finalize;
        void *Process;
        void *Release;

        using CheckVersion_t = bool (nalPedAnim::*)();
        CheckVersion_t CheckVersion;
    };

    static int vtbl_ptr;
};

struct nalPedSkeleton {
    struct vtbl {
        void *field_0;
        void *finalize;
        void *Process;
        void *Release;

        using CheckVersion_t = bool (nalPedAnim::*)();
        CheckVersion_t CheckVersion;
    };

    static int vtbl_ptr;
};

} // namespace nalPed

namespace nalCam {

struct nalCamAnim {
    struct vtbl {
        void *field_0;
        void *finalize;
        void *Process;
        void *Release;

        using CheckVersion_t = bool (nalCamAnim::*)();
        CheckVersion_t CheckVersion;
    };

    static int vtbl_ptr;
};

struct nalCamSkeleton {
    struct vtbl {
        void *field_0;
        void *finalize;
        void *Process;
        void *Release;

        using CheckVersion_t = bool (nalCamSkeleton::*)();
        CheckVersion_t CheckVersion;
    };

    static int vtbl_ptr;
};

} // namespace nalCam

struct nalAnimFile {
    uint32_t field_0;
    uint32_t field_4;
    int field_8;
    int num_skeletons;
    tlFixedString field_10;
    int field_30;
    char *field_34;
    int field_38[3];
    int field_44;
    tlFixedString field_48;
};

struct nalClientSceneAnim {};

struct nalStreamInstance {
    struct internal {
        int field_0[2];
        int *field_8;
    };

    std::intptr_t m_vtbl;
    int *field_4;
    int *field_8;
    int field_C;
    float field_10;
    float field_14;
    internal *field_18;
    int field_1C;
    nalClientSceneAnim *(*m_callback)(const tlFixedString &, void *);
    void *field_24;
    nflFileID field_28;
    int *field_2C;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    char *field_48[1];
    char *field_4C;
    int field_50[1];
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
    int field_64;
    int field_68;
    nflRequestID field_6C;
    int field_70;
    int field_74;
    uint8_t field_78;
    uint8_t field_79;

    //0x00492EF0
    void AdvanceStream();

    //0x004AD4C0
    //virtual
    ~nalStreamInstance();

    //0x00492EE0
    //virtual
    bool IsReady();

    //0x00498580
    //virtual
    bool Advance(Float dt);
};

//0x00492E70
extern nalStreamInstance *create_stream_instance(uint32_t a1,
                                                 uint32_t a2,
                                                 uint32_t a3,
                                                 int a4,
                                                 nalClientSceneAnim *(*p_cb)(const tlFixedString &,
                                                                             void *),
                                                 void *a6);

struct nalBaseSkeleton;

//0x0078DC60
extern nalBaseSkeleton *nalGetSkeleton(const tlFixedString &a1);

struct nalComponentU8Base {
    int *GetType();

    static inline int TypeID{0};
};

struct nalComponentStringBase {
    char *GetType();

    static inline Var<char> TypeID{0x00959560};
};

struct spideySignalData {};

struct spideySignal {};

struct nalComponentInitList;

namespace nalGeneric {

struct nalGenericAnim {
    std::intptr_t m_vtbl;
    int field_4[9];

    tlHashString field_28;
    int field_2C[9];
    int field_50;

    struct vtbl {};

    static int vtbl_ptr;
};

struct nalComponentInfo {
    tlHashString field_0;
    char field_4[0x1C];
    struct {
        std::intptr_t m_vtbl;
    } * field_20;
    int field_24;
    int field_28;
    int field_2C;
};

struct nalGenericSkeleton {
    std::intptr_t m_vtbl;
    uint32_t field_4;
    int field_8[8];

    tlHashString field_28;
    int field_2C[9];
    int field_50;
    int field_54[4];

    int field_64;
    int field_68;
    int field_6C;
    int field_70;
    int field_74;
    int field_78;
    int field_7C;
    int field_80;
    int field_84;
    int field_88;
    nalComponentInfo *field_8C;
    int field_90;
    int field_94;
    int field_98;
    int field_9C;
    int field_A0;
    int field_A4;
    nalComponentInfo *field_A8;
    int field_AC;
    int field_B0;
    int field_B4;
    int field_B8;
    int field_BC;
    int field_C0;
    int field_C4;
    int field_C8;
    int field_CC;
    int field_D0;
    int field_D4;
    int field_D8;
    int field_DC;
    int field_E0;

    struct vtbl {
        void *field_0;
        void *field_4;
        void (nalGenericSkeleton::*Process)();
        void (nalGenericSkeleton::*Release)();
        bool (nalGenericSkeleton::*CheckVersion)();
    };

    nalGenericSkeleton() {
        vtbl_ptr = (int) std::addressof(bit_cast<int *>(this)[0]);
    }

    //0x00793610
    void Process();

    void Release();

    bool CheckVersion() {
        return this->field_4 == 0x10200;
    }

    static int vtbl_ptr;
};

} // namespace nalGeneric

template<typename T>
T nalSkeletonPtrCast(T a1) {
    if (a1 != nullptr || *a1 != nalGeneric::nalGenericSkeleton::vtbl_ptr) {
        return nullptr;
    }

    return a1;
}

struct nalSceneAnim {
    int field_0;
    int field_4;
    int field_8;
    int field_C;
    tlFixedString field_10;
    int field_30;
    int field_34;
    int field_38;
    int field_3C;
    int field_40;
    int field_44;
    int field_48;
    int field_4C;
    tlFixedString field_50;
};

struct nalHeap;

//0x00783CF0
extern void nalInit(nalHeap *a1);

//0x00783C60
extern void nalExit();

//0x0078D9B0
extern void nalReleaseSceneAnimInternal(nalSceneAnim *a1);

//0x0078D8D0
extern bool nalLoadSceneAnimInternal(nalSceneAnim *a1);

//0x0078D540
extern bool nalLoadAnimFileInternal(nalAnimFile *anim_file);

extern void nalSetSkeletonDirectory(tlResourceDirectory<nalBaseSkeleton, tlFixedString> *a1);

extern void nalSetAnimFileDirectory(tlResourceDirectory<nalAnimFile, tlFixedString> *a1);

extern void nalSetAnimDirectory(tlResourceDirectory<nalAnimClass<nalAnyPose>, tlFixedString> *a1);

extern void nalSetSceneAnimDirectory(tlResourceDirectory<nalSceneAnim, tlFixedString> *a1);

extern void nalStreamInstance_patch();
