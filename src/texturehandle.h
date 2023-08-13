#pragma once

#include <windows.h>

struct TextureHandle {
    HANDLE field_0;
    HANDLE field_4;
    void *field_8;
    int m_fileSize;

    //0x007DF14F
    TextureHandle();

    //0x007DF430
    ~TextureHandle();

    int sub_7DF161(LPCWSTR lpWideCharStr, int a3);
};

extern void TextureHandle_patch();
