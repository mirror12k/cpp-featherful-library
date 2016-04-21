
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
bytestring::bytestring(char c) : bytestring(1, &c) {}
bytestring::bytestring(const char* s) : bytestring(strlen(s), s) {}

bytestring::bytestring(uint length, const char* s)
{
    char* allocated = (char*)malloc(length);
    if (allocated == nullptr)
        throw exception();

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
    if (allocated == nullptr)
        throw exception();

    uint offset = 0;
    for (uint i = 0; i < string_count; i++)
    {
        memcpy(allocated + offset, s[i], length[i]);
        offset += length[i];
    }

    this->i_length = total_length;
    this->a_buffer = allocated;
}

bytestring::bytestring(const bytestring& other) : bytestring(other.length(), other.buffer()) {}

bytestring& bytestring::operator=(const bytestring& other)
{
    free((void*)this->a_buffer);

    this->i_length = other.length();
    char* allocated = (char*)malloc(this->i_length);
    if (allocated == nullptr)
        throw exception();
    memcpy(allocated, other.buffer(), this->i_length);
    this->a_buffer = allocated;

    return *this;
}

bytestring::~bytestring()
{
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
    if (str == nullptr)
        throw exception();
    memcpy(str, this->a_buffer, this->i_length);
    str[this->i_length] = '\0';
    return str;
}


char bytestring::operator[](int index) const
{
    return this->char_at(index);
}

bytestring bytestring::operator+(const bytestring& other) const
{
    return this->concat(other);
}

bytestring bytestring::operator-(const bytestring& other) const
{
    return this->remove(other);
}

bytestring bytestring::operator*(uint times) const
{
    return this->multiply(times);
}

bool bytestring::operator==(const bytestring& other) const
{
    return this->equal(other);
}




bytestring::const_iterator bytestring::begin() const
{
    return this->a_buffer;
}
bytestring::const_iterator bytestring::end() const
{
    return this->a_buffer + this->i_length;
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
        throw exception();

    if (end < 0)
    {
        end = this->i_length + end;
        if (end < 0)
            throw exception();
    }
    else if (end >= this->i_length)
        throw exception();

    end++;

    if (start > end)
        throw exception();

    return bytestring(end - start, this->a_buffer + start);
}


bytestring bytestring::strip(char c) const
{
    uint stripped_offset = 0;
    char* stripped_buffer = (char*)malloc(this->i_length);
    if (stripped_buffer == nullptr)
        throw exception();

    for (bytestring::const_iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; iter++)
        if (*iter != c)
            stripped_buffer[stripped_offset++] = *iter;

    bytestring result(stripped_offset, stripped_buffer);
    free(stripped_buffer);
    return result;
}

bytestring bytestring::strip(const bytestring& chars) const
{
    bytestring result = *this;

    for (bytestring::const_iterator iter = chars.begin(), iter_end = chars.end(); iter != iter_end; iter++)
        result = result.strip(*iter);

    return result;
}

bytestring bytestring::strip_whitespace() const
{
    return this->strip(bytestring(" \t\r\n"));
}


bytestring bytestring::insert(const bytestring& other, int offset) const
{
    if (offset < 0)
    {
        offset = this->i_length + offset + 1;
        if (offset < 0)
            throw exception();
    }
    if (offset > this->i_length)
        throw exception();

    uint lengths[3];
    const char* buffers[3];

    lengths[0] = offset;
    lengths[1] = other.length();
    lengths[2] = this->length() - offset;

    buffers[0] = this->buffer();
    buffers[1] = other.buffer();
    buffers[2] = this->buffer() + offset;

    return bytestring(3, lengths, buffers);
}

bytestring bytestring::erase(int start, int end) const
{
    if (start < 0)
    {
        start = this->i_length + start;
        if (start < 0)
            throw exception();
    }
    else if (start >= this->i_length)
        throw exception();

    if (end < 0)
    {
        end = this->i_length + end;
        if (end < 0)
            throw exception();
    }
    else if (end >= this->i_length)
        throw exception();

    end++;

    if (start > end)
        throw exception();

    uint lengths[2];
    const char* buffers[2];

    lengths[0] = start;
    lengths[1] = this->length() - end;

    buffers[0] = this->buffer();
    buffers[1] = this->buffer() + end;

    return bytestring(2, lengths, buffers);
}

bytestring bytestring::remove(const bytestring& needle) const
{
    bytestring result = *this;
    int offset = result.find(needle);
    while (offset != -1)
    {
        result = result.erase(offset, offset + needle.length() - 1);
        offset = result.find(needle, offset);
    }
    return result;
}

bytestring bytestring::replace(const bytestring& needle, const bytestring& replacement) const
{
    bytestring result = *this;
    int offset = result.find(needle);
    while (offset != -1)
    {
        result = result.splice(replacement, offset, offset + needle.length() - 1);
        offset = result.find(needle, offset + replacement.length());
    }
    return result;
}

bytestring bytestring::splice(const bytestring& segment, int start, int end) const
{
    if (start < 0)
    {
        start = this->i_length + start;
        if (start < 0)
            throw exception();
    }
    else if (start >= this->i_length)
        throw exception();

    if (end < 0)
    {
        end = this->i_length + end;
        if (end < 0)
            throw exception();
    }
    else if (end >= this->i_length)
        throw exception();

    end++;

    if (start > end)
        throw exception();

    uint lengths[3];
    const char* buffers[3];

    lengths[0] = start;
    lengths[1] = segment.length();
    lengths[2] = this->length() - end;

    buffers[0] = this->buffer();
    buffers[1] = segment.buffer();
    buffers[2] = this->buffer() + end;

    return bytestring(3, lengths, buffers);
}




bytestring bytestring::multiply(uint times) const
{
    if (times == 0)
        return bytestring();
    else if (times == 1)
        return *this;
    else
        return times & 0x1 ? *this + this->concat(*this).multiply(times / 2) : this->concat(*this).multiply(times / 2);
}



char bytestring::char_at(int index) const
{
    if (index < 0)
        throw exception();
    else if (index >= this->i_length)
        throw exception();
    else
        return this->a_buffer[index];
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
    for (bytestring::const_iterator iter = this->begin() + offset, iter_end = this->end(); iter < iter_end; iter++)
        if (*iter == c)
            return iter - this->begin();
    return -1;
}

int bytestring::find(const bytestring& needle, uint offset) const
{
    if (needle.length() == 0)
        throw exception();
    if (needle.length() > this->length())
        return -1;

    bytestring::const_iterator check_iter, needle_iter, needle_end = needle.end();
    for (bytestring::const_iterator iter = this->begin() + offset, iter_end = this->end() - needle.length(); iter <= iter_end; iter++)
    {
        for (check_iter = iter, needle_iter = needle.begin(); needle_iter != needle_end; check_iter++, needle_iter++)
            if (*check_iter != *needle_iter)
                break;
        if (needle_iter == needle_end)
            return iter - this->begin();
    }
    return -1;
}

bool bytestring::equal(const bytestring& other) const
{
    return this->compare(other) == 0;
}

int bytestring::compare(const bytestring& other) const
{
    bytestring::const_iterator iter = this->begin(), iter_end = this->end();
    bytestring::const_iterator other_iter = other.begin(), other_iter_end = other.end();

    for (; iter != iter_end && other_iter != other_iter_end; iter++, other_iter++)
        if (*iter != *other_iter)
        {
            if (*iter < *other_iter)
                return -1;
            else
                return 1;
        }

    if (iter != iter_end)
        return -1;
    else if (other_iter != other_iter_end)
        return 1;
    else
        return 0;
}


bool bytestring::empty() const
{
    return this->i_length == 0;
}






//template <class T>
//typename list<T>::const_iterator& list<T>::
//template <class T>
//typename list<T>::const_iterator& list<T>::end() const
//{
//    return *this->p_tail_link;
//}


//template <class T>
//list<T>::list_link::list_link(list_link* prev, T* item, list_link* next)
//{
//    this->p_item = item;
//    this->p_prev = prev;
//    this->p_next = next;
//}
//
//template <class T>
//T& list<T>::list_link::operator*() const
//{
//    return *this->p_item;
//}


}




