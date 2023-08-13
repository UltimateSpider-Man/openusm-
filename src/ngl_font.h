#pragma once

#include "fixedstring.h"
#include "variable.h"

struct nglTexture;

struct nglGlyphInfo {
    int field_0;
    int field_4;
    int GlyphSize[2];
    int field_10;
    int field_14;
    int field_18;
};

struct nglGlyphSize {
    float field_0;
    float field_4;
    float field_8;
    float field_C;
};

struct nglFont {
    tlFixedString field_0;
    int field_20;
    nglTexture *field_24;
    nglGlyphInfo *GlyphInfo;

    struct {
        int Version;
        int CellHeight;
        int Ascent;
        int FirstGlyph;
        int NumGlyphs;

    } Header;

    int field_40;
    int field_44;
    int field_48;

    nglGlyphSize *field_4C;
    char field_50;
    char empty0[3];

    nglGlyphInfo *GetGlyphInfo(unsigned char Character);
};

extern Var<nglFont *> nglSysFont;

//0x00778F80
extern void nglParseFDF(char *a3, nglFont *a2);
