#pragma once

#include "tlresource_directory.h"

struct resource_directory;
struct nglTexture;
struct tlFixedString;
struct nglMeshFile;
struct tlHashString;
struct nglMesh;
struct nglMorphSet;
struct nglMaterialFile;
struct nglMaterialBase;
struct nalBaseSkeleton;
struct nalAnimFile;
struct nalAnyPose;
struct nalSceneAnim;

template<typename T>
struct nalAnimClass;

struct resource_pack_directory {
    resource_directory *field_0;
    tlResourceDirectory<nglTexture, tlFixedString> field_4;
    void *field_8;
    tlResourceDirectory<nglMeshFile, tlFixedString> field_C;
    void *field_10;
    tlResourceDirectory<nglMesh, tlHashString> field_14;
    void *field_18;
    tlResourceDirectory<nglMorphSet, tlHashString> field_1C;
    void *field_20;
    void *field_24;
    void *field_28;
    tlResourceDirectory<nglMaterialBase, tlHashString> field_2C;
    void *field_30;
    tlResourceDirectory<nglMaterialFile, tlFixedString> field_34;
    void *field_38;
    tlResourceDirectory<nalAnimFile, tlFixedString> field_3C;
    void *field_40;
    tlResourceDirectory<nalAnimClass<nalAnyPose>, tlFixedString> field_44;
    void *field_48;
    tlResourceDirectory<nalSceneAnim, tlFixedString> field_4C;
    void *field_50;
    tlResourceDirectory<nalBaseSkeleton, tlFixedString> field_54;
    void *field_58;

    //0x0052A9A0
    resource_pack_directory();

    resource_directory *get_resource_directory() {
        return this->field_0;
    }

    void set_resource_directory(resource_directory *dir);

    void clear();
};

extern void resource_pack_directory_patch();
