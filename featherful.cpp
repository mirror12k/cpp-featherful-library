
#include "featherful.hpp"

#include <cstring>
#include <cstdlib>
#include <cstdio>


namespace featherful
{

const char* empty_buffer = "";


bytestring::bytestring() : bytestring(empty_buffer) {}
bytestring::bytestring(const char* s) : bytestring(strlen(s), s) {}

bytestring::bytestring(uint length, const char* s)
{
    char* allocated = (char*)malloc(length);
    memcpy(allocated, s, length);
    this->i_length = length;
    this->a_buffer = allocated;
}

bytestring::bytestring(uint string_count, uint* length, const char** s)
{
    uint total_length = 0;
    for (uint i = 0; i < string_count; i++)
        total_length += length[i];

    char* allocated = (char*)malloc(total_length);

    uint offset = 0;
    for (uint i = 0; i < string_count; i++)
    {
        memcpy(allocated + offset, s[i], length[i]);
        offset += length[i];
    }

    this->i_length = total_length;
    this->a_buffer = allocated;
}

bytestring::bytestring(const bytestring& other) : bytestring(other.length(), other.buffer()) {
//    printf("debug copy constructor\n");
}

bytestring& bytestring::operator=(const bytestring& other)
{
//    printf("debug equal copier\n");

    free((void*)this->a_buffer);

    this->i_length = other.length();
    char* allocated = (char*)malloc(this->i_length);
    memcpy(allocated, other.buffer(), this->i_length);
    this->a_buffer = allocated;

    return *this;
}


bytestring::~bytestring()
{
//    printf("debug dtor\n");
    free((void*)this->a_buffer);
}


bytestring bytestring::concat(const bytestring& other) const
{
    uint lengths[2];
    const char* buffers[2];

    lengths[0] = this->length();
    lengths[1] = other.length();

    buffers[0] = this->buffer();
    buffers[1] = other.buffer();

    bytestring result(2, lengths, buffers);
    return result;
}


uint bytestring::length() const
{
    return this->i_length;
}

const char* bytestring::buffer() const
{
    return this->a_buffer;
}

char* bytestring::c_str() const
{
    char* str = (char*)malloc(this->i_length + 1);
    memcpy(str, this->a_buffer, this->i_length);
}

}

