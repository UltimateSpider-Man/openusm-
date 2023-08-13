#pragma once

#include "string_hash_entry.h"

#include "os_file.h"

template<typename T>
struct mAvlTree;

struct ghetto_mash_file_header;

struct string_hash_dictionary {
    int field_0;

    static Var<mAvlTree<string_hash_entry> *> entries;
    static Var<mAvlTree<string_hash_entry> *> prereg_entries;

    static Var<char *> default_dictionary_filename;
    static Var<char *> dictionary_extension;

    static Var<char *> file_header_identifier_string;

    static Var<ghetto_mash_file_header *> header;

    static Var<uint8_t *> mash_image_buffer;

    static Var<char *> textfile_extension;

    static Var<os_file> _hard_log;

    static Var<char *> hard_log_filename;

    static Var<bool> is_setup;

    //0x0053DE30
#ifdef TEST_CASE
    [[nodiscard]] static string_hash register_string(const char *str);
#else
    static string_hash register_string(const char *str);
#endif

    static bool is_loaded();

    //0x00531990
    static char *lookup_string(string_hash a1);

    //0x0053DD00
    static bool register_in_tree(mAvlTree<string_hash_entry> *a1,
                                 const char *str,
                                 const string_hash *a3);

    //0x005588B0
    static void create_inst();

    //0x0054C1F0
    static void delete_inst();

    //0x00547A30
    static void clear();

    //0x00531A60
    static void save_dictionary(const char *a1);

    //0x00550DC0
    static bool read(const char *a1);

    //0x00556000
    static void load_dictionary(const char *a1);

    //0x0051EB70
    static void hard_log_string(const char *a1, const string_hash &a2);

    //0x0050DC80
    static mString figure_out_filename(const char *a2,
                                       const char *dict_filename,
                                       const char *dict_ext);

    //0x0052A5E0
    static void create_new_dictionary();

    //0x0052A6A0
    static void write_text(const char *a1);
};

void string_hash_dictionary_patch();
