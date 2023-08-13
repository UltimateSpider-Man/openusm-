#pragma once

#include "variable.h"

struct os_developer_options;

struct ini_parser {
    //0x005CA120
    static void parse(const char *ini_filename, os_developer_options *a2);

    //0x005C3000
    static int get_token(char **a1, int *a2, int *a3);

    //0x005B8B00
    static signed int build_token(char *a1, char *a2);

    static void new_line(char *lpBuffer);

    static Var<char[255]> filename;

    static Var<int> scan_pos;
    static Var<char *> line;
    static Var<char> token;
    static Var<char> stored_token;
    static Var<char> stored_type;
    static Var<char> stored_num;
};
