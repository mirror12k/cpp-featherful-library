
#include "featherful.hpp"

#include <cstring>
#include <cstdlib>
#include <cstdio>

#include <exception>

using std::exception;


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
    str[this->i_length] = '\0';
    return str;
}




bytestring bytestring::concat(const bytestring& other) const
{
    uint lengths[2];
    const char* buffers[2];

    lengths[0] = this->length();
    lengths[1] = other.length();

    buffers[0] = this->buffer();
    buffers[1] = other.buffer();

    return bytestring(2, lengths, buffers);
}

bytestring bytestring::substring(int start, int end) const
{
    if (start < 0)
    {
        start = this->i_length + start;
        if (start < 0)
            throw exception();
    }
    else if (start >= this->i_length)
    {
        throw exception();
    }

    if (end < 0)
    {
        end = this->i_length + end;
        if (end < 0)
            throw exception();
    }
    else if (end >= this->i_length)
    {
        throw exception();
    }

    end++;

    if (start > end)
    {
        throw exception();
    }

    return bytestring(end - start, this->a_buffer + start);
}


bytestring bytestring::strip(char c) const
{
    uint length = this->i_length;
    const char* buffer = this->a_buffer;

    uint stripped_offset = 0;
    char* stripped_buffer = (char*)malloc(length);

    for (uint i = 0; i < length; i++)
        if (buffer[i] != c)
            stripped_buffer[stripped_offset++] = buffer[i];

    bytestring result(stripped_offset, stripped_buffer);
    free(stripped_buffer);
    return result;
}

bytestring bytestring::strip(const bytestring& chars) const
{
    bytestring result = *this;

    const char* buffer = chars.buffer();
    for (uint i = 0; i < chars.length(); i++)
        result = result.strip(buffer[i]);

    return result;
}

bytestring bytestring::strip_whitespace() const
{
    return this->strip(bytestring(" \t\r\n"));
}




bool bytestring::contains(char c, uint offset) const
{
    return this->find(c, offset) >= 0;
}

bool bytestring::contains(const bytestring& needle, uint offset) const
{
    return this->find(needle, offset) >= 0;
}

int bytestring::find(char c, uint offset) const
{
    uint length = this->i_length;
    const char* buffer = this->a_buffer;
    for (uint i = offset; i < length; i++)
        if (buffer[i] == c)
            return i;
    return -1;
}

int bytestring::find(const bytestring& needle, uint offset) const
{
    uint length = this->i_length;
    uint needle_length = needle.length();

    if (needle_length > length)
        return -1;

    const char* buffer = this->a_buffer;
    const char* needle_buffer = needle.buffer();

    uint needle_offset = 0;
    for (uint i = offset; i <= length - needle_length; i++)
    {
        for (needle_offset = 0; needle_offset < needle_length; needle_offset++)
            if (buffer[i + needle_offset] != needle_buffer[needle_offset])
                break;
        if (needle_offset == needle_length)
            return i;
    }
    return -1;
}




}




