#pragma once

#include <config.h>
#include <variable.h>

struct slab_allocator {
    struct slab_list_t;

    struct slab_t {
        struct iterator {
            slab_t *_ptr;

            slab_t *operator*();

            iterator operator++(int a3);

            bool operator!=(const slab_t::iterator &a2);

            bool operator==(const slab_t::iterator &a2);
        };

        uint32_t begin_sentry;
        char *arena;
        uint16_t field_8;
        uint16_t m_size;
        int16_t total_object_count;
        int16_t alloc_object_count;
        void *field_10;

        struct {
            slab_t *_sl_next_element;
            slab_t *_sl_prev_element;
            slab_list_t *_sl_list_owner;
        } simple_list_vars;
        uint32_t end_sentry;

        slab_t(char *a2);

        bool contains(uint32_t a2);

        bool is_set(int a2);

        void set(int16_t a2);

        void unset(uint16_t a2);

        int get_free_object_count();

        int get_alloc_object_count();

        void *get_obj();

        void free_object(void *object);

        int get_total_object_count();

        void sub_592D00(int16_t size);
    };

    //0x0059F5A0
    static void initialize();

    //0x0059F750
    static void *allocate(int size, slab_t **a2);

    //0x00439820
    static uint32_t get_max_object_size();

    //0x0059DE20
    static slab_allocator::slab_t *create_slab(int size);

    //0x0059DCA0
    static void deallocate(void *a1, slab_t *a2);

    //0x00592D50
    static slab_t *find_slab_for_object(void *obj);

    //0x0059AF70
    static void process_lists();

    static void dump_debug_info();

    //0x00965F34
    static Var<int *> static_slab_arena;

    //0x00965F38
    static Var<slab_t *> static_slab_headers;

    static Var<bool> initialized;

    static Var<bool> g_dump_slab_info;

    static constexpr auto SLAB_SIZE = 4096;

    static int allocated_object_count[44];
    static int free_object_count[44];

    static int partial_slab_count[44];
    static int full_slab_count[44];

    static int free_slab_count;
    static int total_slab_count;

    struct slab_list_t {
        slab_t *_first_element;
        slab_t *_last_element;
        int _size;

        slab_list_t() {
            this->_first_element = nullptr;
            this->_last_element = nullptr;
            this->_size = 0;
        }

        ~slab_list_t() {
            this->_first_element = nullptr;
            this->_last_element = nullptr;
            this->_size = 0;
        }

        slab_t *front() {
            return this->_first_element;
        }

        auto begin() {
            slab_t::iterator iter{this->_first_element};

            return iter;
        }

        bool contains(slab_t *iter) {
            return iter && iter->simple_list_vars._sl_list_owner == this;
        }

        slab_t::iterator get_default_iterator();

        //0x005B3C10
        slab_t::iterator push_back(slab_t *tmp);

        //0x005B3040
        bool remove_slab(slab_allocator::slab_t *slab);

        //0x005B30A0
        slab_t::iterator add_slab(slab_allocator::slab_t *slab);
    };

    struct slab_partial_list_t {
        int field_0;
        slab_list_t field_4[44];
    };

    static Var<slab_list_t *> slab_partial_list;

    static Var<slab_list_t *> slab_full_list;

    static Var<slab_list_t *> slab_free_list;

}; // namespace slab_allocator

extern void swap(slab_allocator::slab_t::iterator &a, slab_allocator::slab_t::iterator &b);

extern void slab_allocator_patch();
