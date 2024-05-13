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

    static inline auto & filename = var<char[255]>(0x009682F8);


    static int & scan_pos;
    static char *& line;
    static char & token;
    static char & stored_token;
    static char & stored_type;
    static char & stored_num;
};
