
#include "bytestring.hpp"
#include "exception.hpp"

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
    char* allocated = new char[length];

    memcpy(allocated, s, length);
    this->i_length = length;
    this->a_buffer = allocated;
}

bytestring::bytestring(uint string_count, uint* length, const char** s)
{
    uint total_length = 0;
    for (uint i = 0; i < string_count; i++)
        total_length += length[i];

    char* allocated = new char[total_length];

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
    char* allocated = new char[this->i_length];
    memcpy(allocated, other.buffer(), this->i_length);
    this->a_buffer = allocated;

    return *this;
}

bytestring::~bytestring()
{
//    printf("dtor %s\n", this->c_str());
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
    char* str = new char[this->i_length + 1];
    memcpy(str, this->a_buffer, this->i_length);
    str[this->i_length] = '\0';
    return str;
}


char bytestring::operator[](int index) const
{
    return this->char_at(index);
}

bytestring bytestring::operator+(const bytestring& appended) const
{
    return this->concat(appended);
}

bytestring bytestring::operator-(const bytestring& removed) const
{
    return this->remove(removed);
}

bytestring bytestring::operator*(uint times) const
{
    return this->multiply(times);
}

list<bytestring> bytestring::operator/(uint times) const
{
    return this->divide(times);
}

list<bytestring> bytestring::operator/(const bytestring& delimiter) const
{
    return this->split(delimiter);
}

bool bytestring::operator==(const bytestring& other) const
{
    return this->equal(other);
}

bool bytestring::operator!=(const bytestring& other) const
{
    return ! this->equal(other);
}

bool bytestring::operator<(const bytestring& other) const
{
    return this->compare(other) < 0;
}

bool bytestring::operator<=(const bytestring& other) const
{
    return this->compare(other) <= 0;
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

bytestring bytestring::concat(const list<bytestring>& strings) const
{
    uint* lengths = new uint[strings.length() + 1];
    const char** buffers = new const char*[strings.length() + 1];

    lengths[0] = this->length();
    buffers[0] = this->buffer();
    int offset = 1;
    for (list<bytestring>::iterator iter = strings.begin(), iter_end = strings.end(); iter != iter_end; ++iter, offset++)
    {
        lengths[offset] = (*iter).length();
        buffers[offset] = (*iter).buffer();
    }

    bytestring result(strings.length() + 1, lengths, buffers);
    delete lengths;
    delete buffers;
    return result;
}

bytestring bytestring::substring(int start, int end) const
{
    if (start < 0)
    {
        start = this->i_length + start;
        if (start < 0)
            throw range_exception("negative start index too large in bytestring::substring", start);
    }
    else if (start >= this->i_length)
        throw range_exception("start index too large in bytestring::substring", start);

    if (end < 0)
    {
        end = this->i_length + end;
        if (end < 0)
            throw range_exception("negative end index too large in bytestring::substring", end);
    }
    else if (end >= this->i_length)
        throw range_exception("end index too large in bytestring::substring", end);

    end++;

    if (start > end)
        return bytestring();

    return bytestring(end - start, this->a_buffer + start);
}


bytestring bytestring::strip(char c) const
{
    uint stripped_offset = 0;
    char* stripped_buffer = new char[this->i_length];

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

bytestring bytestring::trim() const
{
    uint offsetleft = 0, offsetright = this->i_length - 1;
    const char* buffer = this->a_buffer;

    while (offsetleft <= offsetright && (buffer[offsetleft] == ' ' || buffer[offsetleft] == '\t' ||
            buffer[offsetleft] == '\r' || buffer[offsetleft] == '\n'))
    {
        offsetleft++;
    }
    while (offsetleft <= offsetright && (buffer[offsetright] == ' ' || buffer[offsetright] == '\t' ||
            buffer[offsetright] == '\r' || buffer[offsetright] == '\n'))
    {
        offsetright--;
    }

    if (offsetleft > offsetright)
        return bytestring();
    else
        return this->substring(offsetleft, offsetright);
}



bytestring bytestring::leftpad(char c, uint length) const
{
    if (this->i_length >= length)
        return *this;
    else
        return (bytestring(c) * (length - this->i_length)).concat(*this);
}

bytestring bytestring::leftpad(const bytestring& pad, uint length) const
{
    if (this->i_length >= length)
        return *this;
    else
        return (pad * ((length - this->i_length + pad.length() - 1) / pad.length())).substring(0, length - this->i_length - 1).concat(*this);
}

bytestring bytestring::rightpad(char c, uint length) const
{
    if (this->i_length >= length)
        return *this;
    else
        return this->concat(bytestring(c) * (length - this->i_length));
}

bytestring bytestring::rightpad(const bytestring& pad, uint length) const
{
    if (this->i_length >= length)
        return *this;
    else
        return this->concat((pad * ((length - this->i_length + pad.length() - 1) / pad.length())).substring(0, length - this->i_length - 1));
}






bytestring bytestring::insert(const bytestring& other, int offset) const
{
    if (offset < 0)
    {
        offset = this->i_length + offset + 1;
        if (offset < 0)
            throw range_exception("negative offset index too large in bytestring::insert", offset);
    }
    if (offset > this->i_length)
        throw range_exception("offset index too large in bytestring::insert", offset);

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
            throw range_exception("negative start index too large in bytestring::erase", start);
    }
    else if (start >= this->i_length)
        throw range_exception("start index too large in bytestring::erase", start);

    if (end < 0)
    {
        end = this->i_length + end;
        if (end < 0)
            throw range_exception("negative end index too large in bytestring::erase", end);
    }
    else if (end >= this->i_length)
        throw range_exception("end index too large in bytestring::erase", end);

    end++;

    if (start > end)
        throw range_exception("start index greater than end index in bytestring::erase", start, end);

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
        offset += replacement.length();
        if ((uint)(offset) == result.length())
            return result;
        offset = result.find(needle, offset);
    }
    return result;
}

bytestring bytestring::replace_once(const bytestring& needle, const bytestring& replacement) const
{
    bytestring result = *this;
    int offset = result.find(needle);
    if (offset != -1)
        result = result.splice(replacement, offset, offset + needle.length() - 1);
    return result;
}

bytestring bytestring::splice(const bytestring& segment, int start, int end) const
{
    if (start < 0)
    {
        start = this->i_length + start;
        if (start < 0)
            throw range_exception("negative start index too large in bytestring::splice", start);
    }
    else if (start >= this->i_length)
        throw range_exception("start index too large in bytestring::splice", start);

    if (end < 0)
    {
        end = this->i_length + end;
        if (end < 0)
            throw range_exception("negative end index too large in bytestring::splice", end);
    }
    else if (end >= this->i_length)
        throw range_exception("end index too large in bytestring::splice", end);

    end++;

    if (start > end)
        throw range_exception("start index larger than end index in bytestring::splice", start, end);

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



bytestring bytestring::before(char c, int offset) const
{
    offset = this->find(c, offset);
    if (offset == -1)
        return *this;
    else if (offset == 0)
        return bytestring();
    else
        return this->substring(0, offset - 1);
}

bytestring bytestring::before(const bytestring& needle, int offset) const
{
    offset = this->find(needle, offset);
    if (offset == -1)
        return *this;
    else if (offset == 0)
        return bytestring();
    else
        return this->substring(0, offset - 1);
}

bytestring bytestring::after(char c, int offset) const
{
    offset = this->find(c, offset);
    if (offset == -1)
        return *this;
    else if (offset == this->i_length - 1)
        return bytestring();
    else
        return this->substring(offset + 1);
}

bytestring bytestring::after(const bytestring& needle, int offset) const
{
    offset = this->find(needle, offset);
    if (offset == -1)
        return *this;
    else if (offset == this->i_length - needle.length())
        return bytestring();
    else
        return this->substring(offset + needle.length());
}




bytestring bytestring::multiply(uint times) const
{
    if (times == 0)
        return bytestring();
    else if (times == 1)
        return *this;
    else // fast but memory inefficient technique
        return times & 0x1 ? *this + this->concat(*this).multiply(times / 2) : this->concat(*this).multiply(times / 2);
}


list<bytestring> bytestring::divide(uint times) const
{
    list<bytestring> result;
    int length = this->i_length / times;
    for (uint i = 0; i < times; i++)
        result.push(new bytestring(this->substring(i * length, (i + 1) * length - 1)));
    return result;
}

list<bytestring> bytestring::split(char c) const
{
    list<bytestring> result;
    int offset = 0;
    int start = this->find(c, offset);
    while (start >= 0)
    {
        result.push(new bytestring(this->substring(offset, start - 1)));
        offset = start + 1;
        start = this->find(c, offset);
    }
    result.push(new bytestring(this->substring(offset, this->length() - 1)));
    return result;
}

list<bytestring> bytestring::split(const bytestring& delimiter) const
{
    list<bytestring> result;
    int offset = 0;
    int start = this->find(delimiter, offset);
    while (start >= 0)
    {
        result.push(new bytestring(this->substring(offset, start - 1)));
        offset = start + delimiter.length();
        start = this->find(delimiter, offset);
    }
    result.push(new bytestring(this->substring(offset, this->length() - 1)));
    return result;
}

bytestring bytestring::join(const list<bytestring>& strings) const
{
    if (strings.empty())
        return bytestring();

    uint* lengths = new uint[strings.length() * 2 - 1];
    const char** buffers = new const char*[strings.length() * 2 - 1];

    list<bytestring>::iterator iter = strings.begin(), iter_end = strings.end();
    lengths[0] = (*iter).length();
    buffers[0] = (*iter).buffer();
    int offset = 0;
    for (++iter; iter != iter_end; ++iter, offset++)
    {
        lengths[offset * 2 + 1] = this->i_length;
        lengths[offset * 2 + 2] = (*iter).length();
        buffers[offset * 2 + 1] = this->a_buffer;
        buffers[offset * 2 + 2] = (*iter).buffer();
    }

    bytestring result(strings.length() * 2 - 1, lengths, buffers);
    delete lengths;
    delete buffers;
    return result;
}



char bytestring::char_at(int index) const
{
    if (index < 0)
    {
        index = index + this->i_length;
        if (index < 0)
            throw range_exception("negative index too large in bytestring::char_at", index);
    }
    else if (index >= this->i_length)
        throw range_exception("index too large in bytestring::char_at", index);

    return this->a_buffer[index];
}

bool bytestring::contains(char c, int offset) const
{
    return this->find(c, offset) >= 0;
}

bool bytestring::contains(const bytestring& needle, int offset) const
{
    return this->find(needle, offset) >= 0;
}

int bytestring::find(char c, int offset) const
{
    if (offset < 0)
    {
        offset = offset + this->i_length;
        if (offset < 0)
            throw range_exception("negative offset too large in bytestring::find", offset);
    }
    else if (offset >= this->i_length)
        throw range_exception("offset too large in bytestring::find", offset);

    for (bytestring::const_iterator iter = this->begin() + offset, iter_end = this->end(); iter < iter_end; iter++)
        if (*iter == c)
            return iter - this->begin();
    return -1;
}

int bytestring::find(const bytestring& needle, int offset) const
{
    if (offset < 0)
    {
        offset = offset + this->i_length;
        if (offset < 0)
            throw range_exception("negative offset too large in bytestring::find", offset);
    }
    else if (offset >= this->i_length)
        throw range_exception("offset too large in bytestring::find", offset);

    if (needle.length() == 0)
        throw invalid_exception("bytestring::find called with 0 length needle");
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





bytestring bytestring::to_lowercase() const
{
    char* str = this->c_str();
    for (char* iter = str, * iter_end = str + this->i_length; iter != iter_end; iter++)
    {
        if (*iter >= 0x41 && *iter <= 0x5a)
            *iter |= 0x20;
    }
    bytestring result (this->i_length, str);
    delete str;

    return result;
}

bytestring bytestring::to_uppercase() const
{
    char* str = this->c_str();
    for (char* iter = str, * iter_end = str + this->i_length; iter != iter_end; iter++)
    {
        if (*iter >= 0x61 && *iter <= 0x7a)
            *iter &= 0xdf;
    }
    bytestring result (this->i_length, str);
    delete str;

    return result;
}







int bytestring::parse_int() const
{
    if (this->i_length == 0)
        return 0;

    int result = 0;
    bool negative = this->a_buffer[0] == '-';

    for (int offset = negative; offset < this->i_length; offset++)
    {
        char val = this->a_buffer[offset];
        if (val < '0' || val > '9')
            break;

        result = result * 10 + val - '0';
    }

    return negative ? -result : result;
}

uint bytestring::parse_uint() const
{
    if (this->i_length == 0)
        return 0;

    int result = 0;
    for (int offset = 0; offset < this->i_length; offset++)
    {
        char val = this->a_buffer[offset];
        if (val < '0' || val > '9')
            break;

        result = result * 10 + val - '0';
    }

    return result;
}



bytestring bytestring::to_hex() const
{
    char* buf = new char[this->i_length * 2], *write = buf;
    for (const char* read = this->a_buffer, *read_end = this->a_buffer + this->i_length; read != read_end; read++)
    {
        char c1 = *read >> 4, c2 = *read & 0xf;
        if (c1 < 0xa)
            *write++ = '0' + c1;
        else
            *write++ = 'a' + c1;
        if (c2 < 0xa)
            *write++ = '0' + c2;
        else
            *write++ = 'a' + c2;
    }

    bytestring result(this->i_length * 2, buf);
    delete buf;

    return result;
}


bytestring bytestring::from_hex() const
{
    int str_len = 0;
    for (bytestring::const_iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; iter++)
    {
        if (((*iter >= '0' && *iter <= '9') || (*iter >= 'a' && *iter <= 'f') || (*iter >= 'A' && *iter <= 'F')) &&
            (++iter != iter_end) &&
            ((*iter >= '0' && *iter <= '9') || (*iter >= 'a' && *iter <= 'f') || (*iter >= 'A' && *iter <= 'F')))
        {
            str_len++;
        }
        else
        {
            break;
        }
    }

    char* buf = new char[str_len], *write = buf;
    for (bytestring::const_iterator iter = this->begin(), iter_end = this->begin() + str_len * 2; iter != iter_end; iter++)
    {
        char val;
        if (*iter >= '0' && *iter <= '9')
            val = *iter - '0';
        else if (*iter >= 'a' && *iter <= 'f')
            val = *iter - 'a';
        else if (*iter >= 'A' && *iter <= 'F')
            val = *iter - 'A';

        iter++;
        val <<= 4;

        if (*iter >= '0' && *iter <= '9')
            val |= *iter - '0';
        else if (*iter >= 'a' && *iter <= 'f')
            val |= *iter - 'a';
        else if (*iter >= 'A' && *iter <= 'F')
            val |= *iter - 'A';
        *write++ = val;
    }

    bytestring result(str_len, buf);
    delete buf;

    return result;
}






std::ostream& operator<<(std::ostream& output, const bytestring& str)
{
    output.write(str.buffer(), str.length());
    return output;
}



}





