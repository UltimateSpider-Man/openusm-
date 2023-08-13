#include "ini_parser.h"

#include "func_wrapper.h"
#include "log.h"
#include "os_developer_options.h"
#include "os_file.h"

#include <cassert>

Var<char[255]> ini_parser::filename{0x009682F8};

Var<int> ini_parser::scan_pos{0x009684F8};
Var<char *> ini_parser::line{0x009684FC};
Var<char> ini_parser::token{0x009683F8};
Var<char> ini_parser::stored_token{0x00968500};
Var<char> ini_parser::stored_type{0x00968501};
Var<char> ini_parser::stored_num{0x00968502};

void ini_parser::new_line(char *lpBuffer) {
    ini_parser::line() = lpBuffer;
    ini_parser::scan_pos() = 0;
}

signed int ini_parser::build_token(char *a1, char *a2) {
    char *v2 = a1;
    char v3 = *a1;
    signed int result = 0;
    if (*a1 == '=') {
        *a2 = '=';
        a2[1] = 0;
        result = 1;
    } else {
        for (; v3 != '\n'; ++v2) {
            if (v3 == '\r') {
                break;
            }

            if (v3 == '\0') {
                break;
            }

            if (v3 == '=') {
                break;
            }

            if (v3 == ';') {
                break;
            }

            v2[a2 - a1] = v3;
            v3 = v2[1];
            ++result;
        }
        a2[result] = '\0';
    }
    return result;
}

int sub_5B8AB0(char *a1) {
    int result; // eax
    int i;      // esi

    result = strlen(a1);
    for (i = result - 1; i >= 0; a1[--i + 1] = 0) {
        result = isspace(a1[i]);
        if (!result)
            break;
    }
    return result;
}

int ini_parser::get_token(char **a1, int *a2, int *a3) {
    int result;
    char *v4;
    int v5;
    int v6;
    char v7;
    int *v8;
    unsigned int v9;

    if (ini_parser::stored_token()) {
        *a1 = &ini_parser::token();
        *a2 = ini_parser::stored_type();
        *a3 = ini_parser::stored_num();
        ini_parser::stored_token() = 0;
        result = *a2;
    } else {
        v4 = ini_parser::line();
        v5 = ini_parser::scan_pos();
        ini_parser::token() = 0;
        while (1) {
            v6 = isspace(v4[v5]);
            v4 = ini_parser::line();
            v5 = ini_parser::scan_pos();
            if (!v6 || (v7 = ini_parser::line()[ini_parser::scan_pos()]) == 0) {
                v7 = ini_parser::line()[ini_parser::scan_pos()];
                if (v7 != '\n' && v7 != '\r' && v7 != ';') {
                    break;
                }
            }

            if (v7 == ';') {
                do {
                    if (v7 == 13) {
                        break;
                    }
                    if (!v7) {
                        break;
                    }

                    ini_parser::scan_pos() = ++v5;
                    v7 = ini_parser::line()[v5];
                } while (v7 != 10);
            } else {
                v5 = ini_parser::scan_pos()++ + 1;
            }
        }
        result = ini_parser::build_token(&ini_parser::line()[ini_parser::scan_pos()],
                                         &ini_parser::token());
        ini_parser::scan_pos() = result + v5;
        if (result) {
            *a1 = &ini_parser::token();
            sub_5B8AB0(&ini_parser::token());
            if (ini_parser::token() == '[') {
                strlwr(&ini_parser::token());
                v8 = a2;
                *a2 = 1;
            } else if (ini_parser::token() == '=') {
                v8 = a2;
                *a2 = 3;
            } else {
                v9 = strlen(&ini_parser::token());
                v8 = a2;
                *a2 = v9 > 0 ? 2 : 0;
            }

            ini_parser::stored_num() = *bit_cast<char *>(a3);
            ini_parser::stored_type() = *bit_cast<char *>(v8);
            result = *v8;
        } else {
            *a1 = nullptr;
        }
    }
    return result;
}

static constexpr int TOKEN_STRING = 2;

void ini_parser::parse(const char *ini_filename, os_developer_options *a2) {
    if constexpr (1) {
        assert(ini_filename != nullptr);

        int v11;

        os_file file{};

        int v9 = 0;
        strncpy(ini_parser::filename(), ini_filename, 256u);

        static Var<char> byte_9683F7{0x009683F7};
        byte_9683F7() = 0;
        ini_parser::scan_pos() = 0;
        ini_parser::line() = nullptr;
        ini_parser::token() = 0;
        ini_parser::stored_token() = 0;
        ini_parser::stored_type() = 0;
        ini_parser::stored_num() = 0;
        mString v13{ini_parser::filename()};

        file.open(v13, 1u);

        //sub_4209C0(&v13, 0);
        //nullsub_2(0);
        if (file.opened) {
            auto file_size = file.get_size();
            char *buf = static_cast<char *>(malloc(file_size + 1));
            assert(buf != nullptr);

            char *v12 = buf;
            file.read(buf, file_size);
            buf[file_size] = '\0';
            file.close();
            char *Str = nullptr;
            ini_parser::new_line(buf);

            int token_type;
            if (ini_parser::get_token(&Str, &token_type, &v11)) {
                signed int num_names = 0;
                while (1) {
                    if (token_type == 1) {
                        char *v5 = Str;
                        strlwr(Str);
                        if (memcmp("[flags]", v5, 8u) == 0) {
                            v9 = 1;
                        } else {
                            v9 = (memcmp("[ints]", v5, 7u) == 0)    ? 2
                                : memcmp("[strings]", v5, 10u) != 0 ? 0
                                                                    : 3;
                        }
                    } else if (token_type == TOKEN_STRING) {
                        strupr(Str);
                        const char **names = nullptr;
                        switch (v9) {
                        case 1:
                            names = flag_names();
                            num_names = 150;
                            break;
                        case 2:
                            names = int_names();
                            num_names = 76;
                            break;
                        case 3:
                            names = string_names();
                            num_names = 14;
                            break;
                        default:
                            names = nullptr;
                            break;
                        }

                        signed int i;
                        for (i = 0; i < num_names; ++i) {
                            if (!strcmp(names[i], Str)) {
                                break;
                            }
                        }

                        if (ini_parser::get_token(&Str, &token_type, &v11) == 3) {
                            ini_parser::get_token(&Str, &token_type, &v11);

                            assert(token_type == TOKEN_STRING);

                            if (i != num_names) { // useless checking
                                switch (v9) {
                                case 1:
                                    a2->m_flags[i] = atoi(Str) != 0;
                                    break;
                                case 2:
                                    a2->m_ints[i] = atoi(Str);
                                    break;
                                case 3:
                                    a2->m_strings[i] = Str;
                                    break;
                                }
                            }
                        } else {
                            sp_log(
                                "Mangled INI file, expected '=' but found '%s', trying to salvage "
                                "things...",
                                ini_filename);
                            ini_parser::stored_token() = 1;
                        }
                    } else if (token_type == 3) {
                        sp_log(
                            "Mangled INI file, expected a key value, but found '=', trying to "
                            "salvage "
                            "things...");
                    }

                    if (!ini_parser::get_token(&Str, &token_type, &v11)) {
                        break;
                    }

                    num_names = 0;
                }
                buf = v12;
            }
            free(buf);
        } else {
            sp_log("Error.  Could not open ini file %s\n", ini_parser::filename());
            //assert(0);
        }

        //sub_59B6F0(&file);
    } else {
        CDECL_CALL(0x005CA120, ini_filename, a2);
    }
}
