#include "resource_pack_directory.h"
#include "common.h"
#include "func_wrapper.h"
#include "utility.h"

VALIDATE_SIZE(resource_pack_directory, 0x5C);

resource_pack_directory::resource_pack_directory() {
    if constexpr (1) {
        //this->field_4 = &tlresource_directory<nglTexture, tlFixedString>::`vtbl;
        this->field_8 = nullptr;
        //this->field_C = &tlresource_directory<nglMeshFile, tlFixedString>::`vtbl;
        this->field_10 = nullptr;
        //this->field_14 = (int) &tlresource_directory<nglMesh, tlHashString>::`vtbl;
        this->field_18 = nullptr;
        //this->field_1C = (int) &tlresource_directory<nglMorphSet, tlHashString>::`vtbl;
        this->field_20 = nullptr;
        //this->field_24 = (int) &tlresource_directory<nglMorphFile, tlFixedString>::`vtbl;
        this->field_28 = nullptr;
        //this->field_2C = (int) &tlresource_directory<nglMaterialBase, tlHashString>::`vtbl;
        this->field_30 = nullptr;
        //this->field_34 = (int) &tlresource_directory<nglMaterialFile, tlFixedString>::`vtbl;
        this->field_38 = nullptr;
        //this->field_3C = (int) &tlresource_directory<nalAnimFile, tlFixedString>::`vtbl;
        this->field_40 = nullptr;
        //this->field_44 = (int) &tlresource_directory<nalAnimClass<nalAnyPose>, tlFixedString>::`vtbl;
        this->field_48 = nullptr;
        //this->field_4C = (int) &tlresource_directory<nalSceneAnim, tlFixedString>::`vtbl;
        this->field_50 = nullptr;
        //this->field_54 = (int) &tlresource_directory<nalBaseSkeleton, tlFixedString>::`vtbl;
        this->field_58 = nullptr;
        this->field_0 = nullptr;

    } else {
        THISCALL(0x0052A9A0, this);
    }
}

void resource_pack_directory::set_resource_directory(resource_directory *directory) {
    this->field_0 = directory;
    this->field_8 = directory;
    this->field_10 = directory;
    this->field_18 = directory;
    this->field_20 = directory;
    this->field_28 = directory;
    this->field_30 = directory;
    this->field_38 = directory;
    this->field_40 = directory;
    this->field_48 = directory;
    this->field_50 = directory;
    this->field_58 = directory;
}

void resource_pack_directory::clear() {
    this->field_0 = nullptr;
    this->field_8 = nullptr;
    this->field_10 = nullptr;
    this->field_18 = nullptr;
    this->field_20 = nullptr;
    this->field_28 = nullptr;
    this->field_30 = nullptr;
    this->field_38 = nullptr;
    this->field_40 = nullptr;
    this->field_48 = nullptr;
    this->field_50 = nullptr;
    this->field_58 = nullptr;
}

void resource_pack_directory_patch() {}
