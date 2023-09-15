#include "chunk_file.h"

#include <cstring>
#include <cassert>

#include "script_object.h"

chunk_flavor::chunk_flavor(const char *s)
{
    assert(strlen( s ) < CHUNK_FLAVOR_SIZE);
    strcpy(this->field_0, s);
}

bool chunk_flavor::operator==(const chunk_flavor &a2) const {
    return strcmp(this->field_0, a2.field_0) == 0;
}

void chunk_file::open(const mString &a1, int a3)
{
    static_cast<text_file *>(this)->open(a1, a3);
}

void chunk_file::read(script_object *so) {
}

template<>
chunk_flavor chunk_file::read() {
    chunk_flavor a1a {};
    static_cast<text_file *>(this)->read((char *) &a1a, sizeof(a1a));
    return a1a;
}

template<>
int chunk_file::read()
{
    int a1;
    static_cast<text_file *>(this)->read(&a1);
    return a1;
}

template<>
mString chunk_file::read()
{
    mString result;
    auto *v2 = static_cast<text_file *>(this);
    v2->read(&result);
    return result;
}
